// StudentManagementSystemDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "StudentManagementSystem.h"
#include "StudentManagementSystemDlg.h"
#include "afxdialogex.h"
#include "SubjectEdit.h"

#include <string>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 支持

	// 实现
protected:
DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStudentManagementSystemDlg 对话框


CStudentManagementSystemDlg::CStudentManagementSystemDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STUDENTMANAGEMENTSYSTEM_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStudentManagementSystemDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_STU, stuList);
	DDX_Control(pDX, IDC_LIST_SUB, subList);
}

BEGIN_MESSAGE_MAP(CStudentManagementSystemDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ADD_SUB, &CStudentManagementSystemDlg::OnBnClickedBtnAddSub)
	ON_BN_CLICKED(IDC_BTN_OPEN_FILE, &CStudentManagementSystemDlg::OnBnClickedBtnOpenFile)
	ON_BN_CLICKED(IDC_BTN_SAVE_FILE, &CStudentManagementSystemDlg::OnBnClickedBtnSaveFile)
	ON_BN_CLICKED(IDC_BTN_DEL_SUB, &CStudentManagementSystemDlg::OnBnClickedBtnDelSub)
END_MESSAGE_MAP()


void CStudentManagementSystemDlg::UpdateWindowTitle()
{
	CString tmp;
	tmp.Format(_T("学生管理系统 - %s"), sms.path);
	SetWindowText(tmp);
}

// CStudentManagementSystemDlg 消息处理程序

BOOL CStudentManagementSystemDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE); // 设置大图标
	SetIcon(m_hIcon, FALSE); // 设置小图标

	ShowWindow(SW_NORMAL);

	sms.path = _T("请打开或保存文件");
	UpdateWindowTitle();

	subList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	subList.InsertColumn(0, _T("课程序号"), LVCFMT_LEFT, 100);
	subList.InsertColumn(1, _T("课程名称"), LVCFMT_LEFT, 100);
	subList.InsertColumn(2, _T("平均分"), LVCFMT_LEFT, 100);

	return TRUE; // 除非将焦点设置到控件，否则返回 TRUE
}

void CStudentManagementSystemDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CStudentManagementSystemDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CStudentManagementSystemDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CStudentManagementSystemDlg::OpenFile(CString path)
{
	sms.Open(path);
	UpdateWindowTitle();
	RefreshSubjects();
}

void CStudentManagementSystemDlg::SaveFile(CString path)
{
	sms.path = path;
	sms.fileOpened = true;
	sms.Save();
	UpdateWindowTitle();
}


void CStudentManagementSystemDlg::OnBnClickedBtnOpenFile()
{
	CFileDialog OpenDlg(TRUE);
	OpenDlg.m_ofn.lpstrTitle = _T("打开学生管理系统文件");
	OpenDlg.m_ofn.lpstrFilter = _T("");

	if (IDOK == OpenDlg.DoModal())
	{
		OpenFile(OpenDlg.GetPathName());
	}
}

void CStudentManagementSystemDlg::OnBnClickedBtnSaveFile()
{
	CFileDialog OpenDlg(TRUE);
	OpenDlg.m_ofn.lpstrTitle = _T("保存学生管理系统文件");
	OpenDlg.m_ofn.lpstrFilter = _T("");
	if (IDOK == OpenDlg.DoModal())
	{
		SaveFile(OpenDlg.GetPathName());
	}
}

void CStudentManagementSystemDlg::OnBnClickedBtnAddSub()
{
	SubjectEdit edit;
	if (edit.DoModal() == IDOK)
	{
		MessageBox(sms.addSubject({edit.num, edit.name}));
		RefreshSubjects();
	}
}

void CStudentManagementSystemDlg::RefreshSubjects()
{
	subList.DeleteAllItems();
	auto iter = sms.subjects.begin();
	int i = 0;
	while(iter != sms.subjects.end())
	{
		auto sub = iter->second;
		subList.InsertItem(i, _T(""));
		subList.SetItemText(i, 0, CString(to_string(sub.num).c_str()));
		subList.SetItemText(i, 1, sub.name);
		i++;
		++iter;
	}
}

void CStudentManagementSystemDlg::OnBnClickedBtnDelSub()
{
	int n = subList.GetNextItem(-1, LVNI_SELECTED);
	if(n != -1)
	{
		sms.delSubject(_ttoi(subList.GetItemText(n, 0)));
		RefreshSubjects();
	}
}
