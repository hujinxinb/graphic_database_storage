#pragma once


// Dlg_login 对话框

class Dlg_login : public CDialogEx
{
	DECLARE_DYNAMIC(Dlg_login)

public:
	Dlg_login(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~Dlg_login();

// 对话框数据
	enum { IDD = IDD_DIALOG3 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_ServerName;
	CString m_DatabaseName;
	CString m_SidName;
	CString m_PwdName;
};
