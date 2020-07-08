#pragma once

#include "SMSFile.h"
#include <map>

using namespace std;

// AddMarkEdit 对话框

class AddMarkEdit : public CDialogEx
{
	DECLARE_DYNAMIC(AddMarkEdit)

public:
	AddMarkEdit(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~AddMarkEdit();
	map<int32_t, Subject> *subjects;
	map<int, Subject*> subs;
	SubjectInfo info;

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_SUB_INFO };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit EditMark;
	CComboBox ComboSub;
	virtual void OnOK();
	virtual BOOL OnInitDialog();
};
