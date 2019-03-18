#pragma once
#include "Resource.h"
#include "afxwin.h"
#include "DataBase.h"



// Dlg_table 对话框

class Dlg_table : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_table)

public:
	Dlg_table(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dlg_table();
	

// 对话框数据
	enum { IDD = IDD_DIALOG2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_listBox;
	DataBase db;
	afx_msg void OnLbnSelchangeTableLists();
	CString m_table_name;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
};
