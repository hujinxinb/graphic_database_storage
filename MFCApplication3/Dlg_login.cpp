// Dlg_login.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "Dlg_login.h"
#include "afxdialogex.h"


// Dlg_login 对话框

IMPLEMENT_DYNAMIC(Dlg_login, CDialogEx)

Dlg_login::Dlg_login(CWnd* pParent /*=NULL*/)
	: CDialogEx(Dlg_login::IDD, pParent)
	, m_ServerName(_T(""))
	, m_DatabaseName(_T(""))
	, m_SidName(_T(""))
	, m_PwdName(_T(""))
{

}

Dlg_login::~Dlg_login()
{
}

void Dlg_login::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_ServerName);
	DDX_Text(pDX, IDC_EDIT2, m_DatabaseName);
	DDX_Text(pDX, IDC_EDIT3, m_SidName);
	DDX_Text(pDX, IDC_EDIT4, m_PwdName);


}


BEGIN_MESSAGE_MAP(Dlg_login, CDialogEx)
END_MESSAGE_MAP()


// Dlg_login 消息处理程序
