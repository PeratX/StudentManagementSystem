#pragma once
#include <cstdint>


// StudentEdit 对话框

class StudentEdit : public CDialogEx
{
DECLARE_DYNAMIC(StudentEdit)

public:
	StudentEdit(CWnd* pParent = nullptr); // 标准构造函数
	virtual ~StudentEdit();
	int64_t num;
	CString name;
	double credit;


	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD_STU };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV 支持

DECLARE_MESSAGE_MAP()
public:
	CEdit editStuId;
	CEdit editStuName;
	virtual void OnOK();
	CEdit editCredit;
};
