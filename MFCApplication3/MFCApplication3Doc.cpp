
// MFCApplication3Doc.cpp : CMFCApplication3Doc 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication3.h"
#endif

#include "MFCApplication3Doc.h"

#include <propkey.h>


#include "iostream"
#include "iomanip"
#include "windows.h"
#include <string>  
#include <sstream> 


using namespace std;
#import "c:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","EndOfFile")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplication3Doc

IMPLEMENT_DYNCREATE(CMFCApplication3Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCApplication3Doc, CDocument)
	ON_COMMAND(ID_DATABASE_WRITE, &CMFCApplication3Doc::OnDatabaseWrite)
	ON_COMMAND(ID_DATABASE_READ, &CMFCApplication3Doc::OnDatabaseRead)
	ON_COMMAND(ID_CONNECT, &CMFCApplication3Doc::OnConnect)
END_MESSAGE_MAP()


// CMFCApplication3Doc 构造/析构

CMFCApplication3Doc::CMFCApplication3Doc()
{
	// TODO:  在此添加一次性构造代码

	len_drawbase = 0;

	//d_id = 0;

}

CMFCApplication3Doc::~CMFCApplication3Doc()
{
	emptyDrawBase();
}

BOOL CMFCApplication3Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO:  在此添加重新初始化代码
	// (SDI 文档将重用该文档)


	//ODBC数据库相关实验，CShapeDB这个类就继承自CRecordset
	//sql.Format(_T("select * from Shape where Id=1"));
	//my = new CShapeDB(&((CMFCApplication3App*)AfxGetApp())->m_database);
	//if (!my->Open(AFX_DB_USE_DEFAULT_TYPE, sql))
	//{
	//	MessageBox(NULL, _T("打开表失败"), _T("打开表失败"), MB_YESNO);
	//}




	//int len = my->m_Geometry.m_dwDataLength;

	//LPBYTE Buf = new BYTE[my->m_Geometry.m_dwDataLength];
	//ASSERT(my->m_Geometry.m_hData != NULL);
	//memcpy(Buf, (LPBYTE)my->m_Geometry.m_hData, my->m_Geometry.m_dwDataLength); // Copy data

	return TRUE;
}





//CDrawBase* CMFCApplication3Doc::newDrawBase(CPoint start_point, CPoint end_point)
//{
//	
//}
int CMFCApplication3Doc::addDrawBase(CDrawBase* r)
{


	top[len_drawbase] = r;
	len_drawbase += 1;

	SetModifiedFlag(TRUE);   //  在对文档作了修改之后调用该函数。
	UpdateAllViews(NULL);    //文档被修改后可调用此函数，把文档被修改的信息通知给每个视图。然后重新调用每个view
	//每个view再重新OnDraw，第一个参数通常设置为NULL=
	return len_drawbase;
}

int CMFCApplication3Doc::removeDrawBase(int ID)
{
	top[len_drawbase - 1] = top[ID];
	
	for (int i = ID; i < len_drawbase-1; i++)
	{
		top[i] = top[i + 1];
	}

	delete top[len_drawbase - 1];
	len_drawbase -= 1;

	SetModifiedFlag(TRUE);   //  在对文档作了修改之后调用该函数。
	UpdateAllViews(NULL);    //文档被修改后可调用此函数，把文档被修改的信息通知给每个视图。然后重新调用每个view
	//每个view再重新OnDraw，第一个参数通常设置为NULL=
	return len_drawbase;
}


int CMFCApplication3Doc::emptyDrawBase()
{
	for (int i = 0; i < len_drawbase; i++)
	{
		delete top[i];
	}

	len_drawbase = 0;

	SetModifiedFlag(TRUE);   //  在对文档作了修改之后调用该函数。
	UpdateAllViews(NULL);    //文档被修改后可调用此函数，把文档被修改的信息通知给每个视图。然后重新调用每个view
	//每个view再重新OnDraw，第一个参数通常设置为NULL=
	return 0;
}

CDrawBase* CMFCApplication3Doc::getDrawBase(int ID)
{
	return top[ID];
}



// CMFCApplication3Doc 序列化

void CMFCApplication3Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO:  在此添加存储代码
	}
	else
	{
		// TODO:  在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CMFCApplication3Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CMFCApplication3Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CMFCApplication3Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCApplication3Doc 诊断

#ifdef _DEBUG
void CMFCApplication3Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCApplication3Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCApplication3Doc 命令


void CMFCApplication3Doc::OnDatabaseWrite()
{
	// TODO:  在此添加命令处理程序代码
	
	Dlg_table dlg_table;
	dlg_table.db.ServerName = db.ServerName;
	dlg_table.db.DataBaseName = db.DataBaseName;
	dlg_table.db.UidName = db.UidName;
	dlg_table.db.PwdName = db.PwdName;

	if (IDOK == dlg_table.DoModal())
	{

		//draw_text = dlg_text.m_edit1;
		USES_CONVERSION;
		db.table_name = W2A(dlg_table.m_table_name);


		int no = db.removeAll(db.table_name);


		for (int i = 0; i < len_drawbase; i++)
		{
			db.d_id = i;
			db.insertQuery(top[i],db.table_name);
		}


	}

}


void CMFCApplication3Doc::OnDatabaseRead()
{
	// TODO:  在此添加命令处理程序代码
	

	Dlg_table dlg_table;
	dlg_table.db.ServerName = db.ServerName;
	dlg_table.db.DataBaseName = db.DataBaseName;
	dlg_table.db.UidName = db.UidName;
	dlg_table.db.PwdName = db.PwdName;
	if (IDOK == dlg_table.DoModal())
	{
		
		//draw_text = dlg_text.m_edit1;
		USES_CONVERSION;
		db.table_name = W2A(dlg_table.m_table_name);

		emptyDrawBase();

		db.readAllQuery(db.table_name);

		for (int i = 0; i < db.countQuery(db.table_name); i++)
		{
			//db.readQuery(i + 1, db.table_name);
			
			//addDrawBase(db.opens[i]);
			top[len_drawbase] = db.opens[i];
			len_drawbase += 1;
		}

		SetModifiedFlag(TRUE);   //  在对文档作了修改之后调用该函数。
		UpdateAllViews(NULL);    //文档被修改后可调用此函数，把文档被修改的信息通知给每个视图。然后重新调用每个view
	}



}


void CMFCApplication3Doc::OnConnect()
{
	// TODO:  在此添加命令处理程序代码
	Dlg_login dlg_login;
	
	if (IDOK == dlg_login.DoModal())
	{

		int i = 0;


		//draw_text = dlg_text.m_edit1;
		USES_CONVERSION;
		string servername(W2A(dlg_login.m_ServerName));
		db.ServerName = servername;


		string databasename(W2A(dlg_login.m_DatabaseName));
		db.DataBaseName = databasename;
		

		string sidname(W2A(dlg_login.m_SidName));
		db.UidName = sidname;

		string pwdname(W2A(dlg_login.m_PwdName));
		db.PwdName = pwdname;



	}

}
