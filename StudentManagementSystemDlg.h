// StudentManagementSystemDlg.h: 头文件
//

#pragma once

#include "SMSFile.h"

struct SubjectStatistic
{
	double avg = 0;
	double passed = 0;
	int total = 0;
	CString info;
	CString stat;
};

// CStudentManagementSystemDlg 对话框
class CStudentManagementSystemDlg : public CDialogEx
{
	// 构造
public:
	CStudentManagementSystemDlg(CWnd* pParent = nullptr); // 标准构造函数
	CString DoubleToString(double);

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDENTMANAGEMENTSYSTEM_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 支持


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
	void RefreshStudents();
	void AddStudentsToList(map<int64_t, Student>);
	SubjectStatistic StatSubject(Subject);

public:
	SMSFile sms;
	CListCtrl stuList;
	CListCtrl subList;
	afx_msg void OnBnClickedBtnAddSub();
	afx_msg void OnBnClickedBtnOpenFile();
	afx_msg void OnBnClickedBtnSaveFile();
	afx_msg void OnBnClickedBtnDelSub();
	afx_msg void OnBnClickedBtnAddStu();
	afx_msg void OnBnClickedBtnDelStu();
	afx_msg void OnBnClickedBtnResetSearch();
	CEdit editSearch;
	afx_msg void OnBnClickedBtnSearch();
	afx_msg void OnBnClickedBtnSearchNum();
	virtual void OnOK();
	afx_msg void OnDblclkListSub(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDblclkListStu(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDestroy();
	afx_msg void OnDropFiles(HDROP hDropInfo);
	afx_msg void OnBnClickedBtnNewFile();
};
