
// StudentManagementSystemDlg.h: 头文件
//

#pragma once

#include "SMSFile.h"


// CStudentManagementSystemDlg 对话框
class CStudentManagementSystemDlg : public CDialogEx
{
// 构造
public:
	CStudentManagementSystemDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDENTMANAGEMENTSYSTEM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	void UpdateWindowTitle();

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void OpenFile(CString path);
	void SaveFile(CString path);
	void RefreshSubjects();

public:
	SMSFile sms;
	CListCtrl stuList;
	CListCtrl subList;
	afx_msg void OnBnClickedBtnAddSub();
	afx_msg void OnBnClickedBtnOpenFile();
	afx_msg void OnBnClickedBtnSaveFile();
	afx_msg void OnBnClickedBtnDelSub();
};
