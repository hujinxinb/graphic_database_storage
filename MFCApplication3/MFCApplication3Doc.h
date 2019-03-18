
// MFCApplication3Doc.h : CMFCApplication3Doc 类的接口
//


#pragma once


#include "DrawRC.h"
#include "DrawFont.h"
#include "DrawPoly.h"
#include "Dlg_text.h"
#include "Dlg_table.h"
#include "Dlg_login.h"

#include "DataBase.h"

#include <string>
#include<vector>


using namespace std;

class CMFCApplication3Doc : public CDocument
{
protected: // 仅从序列化创建
	CMFCApplication3Doc();
	DECLARE_DYNCREATE(CMFCApplication3Doc)

// 特性
public:
	DataBase db;

	CDrawBase* top[100000];//DrawBase指针数组
	CDrawBase* open;
	
	vector<string> all_comb_relation;
	string comb_relation;

	int len_drawbase;


	//数据库相关
	//int d_id;
	//string d_name;
	//string d_shapetype;
	//string d_start;
	//string d_value;
	//string d_color;
	//int d_size;
	//int d_lens;

	//string order;
	
	//ODBC数据库相关
	//CShapeDB* my;
	//CShapeDB* you;
	//CString sql;
	//CString result;


// 操作
public:
	//CDrawBase* newDrawBase(CPoint start_point,CPoint end_point);
	int addDrawBase(CDrawBase* r);
	int removeDrawBase(int ID);
	int emptyDrawBase();
	CDrawBase* getDrawBase(int ID);

	//数据库


	vector<string> splitString(const string &s, const string &seperator);//多分割符的分割字符串函数

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CMFCApplication3Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnDatabaseWrite();
	afx_msg void OnDatabaseRead();
	afx_msg void OnConnect();
};
