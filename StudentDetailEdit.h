#pragma once

#include "SMSFile.h"

// StudentDetailEdit 对话框

class StudentDetailEdit : public CDialogEx
{
DECLARE_DYNAMIC(StudentDetailEdit)

public:
	StudentDetailEdit(CWnd* pParent = nullptr); // 标准构造函数
	virtual ~StudentDetailEdit();
	Student stu;
	map<int32_t, Subject>* subjects;
	void RefreshList();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_STUDENT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 支持

DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CStatic stuInfo;
	CListCtrl subList;
	afx_msg void OnBnClickedBtnDelSub();
	afx_msg void OnBnClickedBtnAddSub();
};
