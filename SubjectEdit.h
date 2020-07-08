#pragma once

#include <cstdint>

// SubjectEdit 对话框

class SubjectEdit : public CDialogEx
{
DECLARE_DYNAMIC(SubjectEdit)

public:
	SubjectEdit(CWnd* pParent = nullptr); // 标准构造函数
	virtual ~SubjectEdit();
	CString name;
	int32_t num;

	virtual void OnOK() override;

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_SUB };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 支持

DECLARE_MESSAGE_MAP()
public:
	CEdit editNum;
	CEdit editName;
};
