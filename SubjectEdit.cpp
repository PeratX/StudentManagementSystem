// SubjectEdit.cpp: 实现文件
//

#include "pch.h"
#include "StudentManagementSystem.h"
#include "SubjectEdit.h"
#include "afxdialogex.h"


// SubjectEdit 对话框

IMPLEMENT_DYNAMIC(SubjectEdit, CDialogEx)

SubjectEdit::SubjectEdit(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD_SUB, pParent)
{
}

SubjectEdit::~SubjectEdit()
{
}

void SubjectEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_SUB_ID, editNum);
	DDX_Control(pDX, IDC_EDIT_SUB_NAME, editName);
}

void SubjectEdit::OnOK()
{
	editName.GetWindowTextW(name);
	CString buf;
	editNum.GetWindowTextW(buf);
	num = _ttoi(buf);
	CDialogEx::OnOK();
}

BEGIN_MESSAGE_MAP(SubjectEdit, CDialogEx)
END_MESSAGE_MAP()


// SubjectEdit 消息处理程序
