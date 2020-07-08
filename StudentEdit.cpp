// StudentEdit.cpp: 实现文件
//

#include "pch.h"
#include "StudentManagementSystem.h"
#include "StudentEdit.h"
#include "afxdialogex.h"


// StudentEdit 对话框

IMPLEMENT_DYNAMIC(StudentEdit, CDialogEx)

StudentEdit::StudentEdit(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD_STU, pParent)
{

}

StudentEdit::~StudentEdit()
{
}

void StudentEdit::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_STU_ID, editStuId);
	DDX_Control(pDX, IDC_EDIT_STU_NAME, editStuName);
	DDX_Control(pDX, IDC_EDIT_STU_CREDIT, editCredit);
}


BEGIN_MESSAGE_MAP(StudentEdit, CDialogEx)
END_MESSAGE_MAP()


// StudentEdit 消息处理程序


void StudentEdit::OnOK()
{
	editStuName.GetWindowTextW(name);
	CString buf;
	editStuId.GetWindowTextW(buf);
	num = _ttoi(buf);
	editCredit.GetWindowTextW(buf);
	credit = _tstof(buf);
	CDialogEx::OnOK();
}
