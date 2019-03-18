#pragma once
#include "Resource.h"

// Dlg_text 对话框

class Dlg_text : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_text)

public:
	Dlg_text(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dlg_text();

// 对话框数据
	enum { IDD = IDD_DIALOG1 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CString m_edit1;
	afx_msg void OnEnChangeEdit1();
};
