// AddMarkEdit.cpp: 实现文件
//

#include "pch.h"
#include "StudentManagementSystem.h"
#include "AddMarkEdit.h"
#include "afxdialogex.h"


// AddMarkEdit 对话框

IMPLEMENT_DYNAMIC(AddMarkEdit, CDialogEx)

AddMarkEdit::AddMarkEdit(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD_SUB_INFO, pParent)
{

}

AddMarkEdit::~AddMarkEdit()
{
}

void AddMarkEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_MARK, EditMark);
	DDX_Control(pDX, IDC_COMBO_SUB, ComboSub);
}


BEGIN_MESSAGE_MAP(AddMarkEdit, CDialogEx)
END_MESSAGE_MAP()


// AddMarkEdit 消息处理程序


void AddMarkEdit::OnOK()
{
	info.sub = subs[ComboSub.GetCurSel()];
	CString buf;
	EditMark.GetWindowTextW(buf);
	info.mark = _ttoi(buf);
	CDialogEx::OnOK();
}


BOOL AddMarkEdit::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	int i = 0;
	auto it = subjects->begin();
	while (it != subjects->end())
	{
		subs[i] = &it->second;
		CString buf;
		buf.Format(_T("%d | %s"), it->second.num, it->second.name);
		ComboSub.AddString(buf);
		i++;
		++it;
	}
	ComboSub.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
