// StudentDetailEdit.cpp: 实现文件
//

#include "pch.h"
#include "StudentManagementSystem.h"
#include "StudentDetailEdit.h"
#include "AddMarkEdit.h"

#include <string>

#include "afxdialogex.h"


// StudentDetailEdit 对话框

IMPLEMENT_DYNAMIC(StudentDetailEdit, CDialogEx)

StudentDetailEdit::StudentDetailEdit(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_STUDENT, pParent)
{
}

StudentDetailEdit::~StudentDetailEdit()
{
}

void StudentDetailEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_INFO, stuInfo);
	DDX_Control(pDX, IDC_LIST_SUB, subList);
}


BEGIN_MESSAGE_MAP(StudentDetailEdit, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_DEL_SUB, &StudentDetailEdit::OnBnClickedBtnDelSub)
	ON_BN_CLICKED(IDC_BTN_ADD_SUB, &StudentDetailEdit::OnBnClickedBtnAddSub)
END_MESSAGE_MAP()


// StudentDetailEdit 消息处理程序


BOOL StudentDetailEdit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	CString info;
	info.Format(_T("学号：%lld\n姓名：%s"), stu.num, stu.name);
	stuInfo.SetWindowTextW(info);

	subList.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	subList.InsertColumn(0, _T("课程序号"), LVCFMT_LEFT, 100);
	subList.InsertColumn(1, _T("课程名称"), LVCFMT_LEFT, 100);
	subList.InsertColumn(2, _T("成绩"), LVCFMT_LEFT, 100);

	RefreshList();

	return TRUE; // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void StudentDetailEdit::RefreshList()
{
	subList.DeleteAllItems();
	auto it = stu.subjects.begin();
	int i = 0;
	while (it != stu.subjects.end())
	{
		auto sub = it->second;
		subList.InsertItem(i, _T(""));
		subList.SetItemText(i, 0, CString(to_string(sub.sub->num).c_str()));
		subList.SetItemText(i, 1, sub.sub->name);
		subList.SetItemText(i, 2, CString(to_string(sub.mark).c_str()));
		i++;
		++it;
	}
}


void StudentDetailEdit::OnBnClickedBtnDelSub()
{
	int n = subList.GetNextItem(-1, LVNI_SELECTED);
	if (n != -1)
	{
		stu.subjects.erase(_ttoi(subList.GetItemText(n, 0)));
		RefreshList();
	}
}


void StudentDetailEdit::OnBnClickedBtnAddSub()
{
	AddMarkEdit edit;
	edit.subjects = subjects;
	if (edit.DoModal() == IDOK)
	{
		auto info = edit.info;
		if (stu.subjects.find(info.sub->num) == stu.subjects.end())
		{
			if (info.mark < 0 || info.mark > 100)
			{
				MessageBoxW(_T("非法的成绩"));
			}
			else
			{
				stu.subjects[info.sub->num] = info;
				RefreshList();
			}
		}
		else
		{
			MessageBoxW(_T("该课程成绩已存在"));
		}
	}
}
