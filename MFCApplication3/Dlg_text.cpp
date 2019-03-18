// Dlg_text.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "Dlg_text.h"
#include "afxdialogex.h"


// Dlg_text 对话框

IMPLEMENT_DYNAMIC(Dlg_text, CDialogEx)

Dlg_text::Dlg_text(CWnd* pParent /*=NULL*/)
	: CDialogEx(Dlg_text::IDD, pParent)
	, m_edit1(_T(""))
{

}

Dlg_text::~Dlg_text()
{
}

void Dlg_text::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_edit1);
}


BEGIN_MESSAGE_MAP(Dlg_text, CDialogEx)
	ON_BN_CLICKED(IDOK, &Dlg_text::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &Dlg_text::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT1, &Dlg_text::OnEnChangeEdit1)
END_MESSAGE_MAP()


// Dlg_text 消息处理程序


void Dlg_text::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void Dlg_text::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void Dlg_text::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
