// Dlg_table.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplication3.h"
#include "Dlg_table.h"
#include "afxdialogex.h"



// Dlg_table 对话框

IMPLEMENT_DYNAMIC(Dlg_table, CDialogEx)

Dlg_table::Dlg_table(CWnd* pParent /*=NULL*/)
	: CDialogEx(Dlg_table::IDD, pParent)
	, m_table_name(_T(""))
{

}

Dlg_table::~Dlg_table()
{
}

void Dlg_table::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TABLE_LISTS, m_listBox);


	CListBox* plstbox = (CListBox*)GetDlgItem(IDC_TABLE_LISTS);



	while (m_listBox.GetCount())
		m_listBox.DeleteString(0);


	vector<string> all_table_inf = db.get_all_table_inf();

	for (auto one_table_inf : all_table_inf)
	{
		CString ss(one_table_inf.c_str());
		m_listBox.AddString(ss);
	}

	//m_listBox.AddString(_T("新浪"));        // 在列表框结尾添加字符串“新浪”   
	//m_listBox.InsertString(2, _T("百度"));  // 在列表框中索引为2的位置插入字符串“百度”   

	DDX_Text(pDX, IDC_EDIT1, m_table_name);
}




BEGIN_MESSAGE_MAP(Dlg_table, CDialogEx)
	ON_LBN_SELCHANGE(IDC_TABLE_LISTS, &Dlg_table::OnLbnSelchangeTableLists)
	ON_BN_CLICKED(IDC_BUTTON1, &Dlg_table::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &Dlg_table::OnBnClickedButton2)
END_MESSAGE_MAP()


// Dlg_table 消息处理程序


void Dlg_table::OnLbnSelchangeTableLists()
{
	// TODO:  在此添加控件通知处理程序代码
	
	int nCurSel;
	nCurSel = m_listBox.GetCurSel();           // 获取当前选中列表项   


	string ss = db.all_table_name_only[nCurSel];
	//m_listBox.GetText(nCurSel, strText);       // 获取选中列表项的字符串  

	CString strText(ss.c_str());
	SetDlgItemText(IDC_EDIT1, strText ); // 将选中列表项的字符串显示到编辑框中   
}


void Dlg_table::OnBnClickedButton1()
{
	// 删除表按钮
	//DROP一个表
	CString strText;
	GetDlgItemText(IDC_EDIT1, strText);

	USES_CONVERSION;	
	string s = W2A(strText);

	int nCurSel = -1000;
	for (int i = 0; i < db.all_table_name_only.size(); i++)
	{
		if (s == db.all_table_name_only[i])
		{
			nCurSel = i;
		}
	}


	db.dropTable(s);

	//重新刷新CListBox m_listBox的内容
	while (m_listBox.GetCount())
		m_listBox.DeleteString(0);

	vector<string> all_table_inf = db.get_all_table_inf();
	for (auto one_table_inf : all_table_inf)
	{
		CString ss(one_table_inf.c_str());
		m_listBox.AddString(ss);
	}
	
}


void Dlg_table::OnBnClickedButton2()
{
	//添加表按钮
	////判断是新建的还是选了原有的数据库表名
	//auto ret = std::find(dlg_table.db.all_table_name_only.begin(), dlg_table.db.all_table_name_only.end(), db.table_name);
	//if (ret == dlg_table.db.all_table_name_only.end())//那就要新建一个表
	//{
	
	//}
	CString strText;
	GetDlgItemText(IDC_EDIT1, strText);

	USES_CONVERSION;
	string s = W2A(strText);


	db.createTable(s);

	//更新m_listBox
	while (m_listBox.GetCount())
		m_listBox.DeleteString(0);
	
	vector<string> all_table_inf = db.get_all_table_inf();
	for (auto one_table_inf : all_table_inf)
	{
		CString ss(one_table_inf.c_str());
		m_listBox.AddString(ss);
	}
}
