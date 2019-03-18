//
//
#include <afxdb.h>
#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。


#include "DataBase.h"

#include <propkey.h>


#include "iostream"
#include "iomanip"
#include "windows.h"
#include <string>  
#include <sstream> 
#include "Dlg_text.h"

using namespace std;
#import "c:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","EndOfFile")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



DataBase::DataBase()
{
	d_id = 0;
	opens_num = 0;

}


DataBase::~DataBase()
{
	d_id = 0;
}



//得到数据库中的所有表的名字，创建时间和修改时间
vector<string> DataBase::get_all_table_inf()
{
	::CoInitialize(NULL);

	all_table_name.clear();
	all_table_name_only.clear();

	int count;
	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");

	
		string strConnects = "Provider=SQLNCLI11;Server=" + this->ServerName + ";Database=" + this->DataBaseName + ";uid=" + this->UidName + ";pwd=" + this->PwdName + ";";
		_bstr_t strConnect = strConnects.c_str();

		m_pConnection->Open(strConnect, "", "", adModeUnknown);
		if (m_pConnection == NULL)
		{
			cerr << "Lind data ERROR!\n";
		}

		string temp = "SELECT name,crdate,refdate FROM SysObjects Where XType='U' ORDER BY Name";
		//cout << temp << endl;
		_bstr_t bstrSQL(temp.c_str());
		m_pRecordset.CreateInstance(_uuidof(Recordset));
		m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

		string temps = "";

		while (!m_pRecordset->BOF)
		{
			_variant_t sqlname = m_pRecordset->GetCollect(_variant_t((long)0));
			_variant_t sqlcrdate = m_pRecordset->GetCollect(_variant_t((long)1));
			_variant_t sqlrefdate = m_pRecordset->GetCollect(_variant_t((long)2));

			temps += (string)(_bstr_t)sqlname;

			string temp_name = (string)(_bstr_t)sqlname;
			for (int i = temp_name.size(); i < 60; i++)
				temps += " ";
			
			temps += (string)(_bstr_t)sqlcrdate;
			string temp_crdate = (string)(_bstr_t)sqlcrdate;
			for (int i = temp_crdate.size(); i < 50; i++)
				temps += " ";
			
			temps += (string)(_bstr_t)sqlrefdate;

			all_table_name.push_back(temps);
			all_table_name_only.push_back((string)(_bstr_t)sqlname);

			temps = "";
			m_pRecordset->MoveNext();
		}
		

	}
	catch (_com_error c)
	{
		cerr << "\nERROR:" << (char*)c.Description();
		return all_table_name;
	}
	if (m_pConnection->State)
		m_pConnection->Close();



	::CoUninitialize();

	return all_table_name;
}




//在数据库中创建表
int DataBase::createTable(string TableName)
{
	::CoInitialize(NULL);

	int id;
	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");

		string strConnects = "Provider=SQLNCLI11;Server=" + this->ServerName + ";Database=" + this->DataBaseName + ";uid=" + this->UidName + ";pwd=" + this->PwdName + ";";
		_bstr_t strConnect = strConnects.c_str();
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
		if (m_pConnection == NULL)
		{
			cerr << "Lind data ERROR!\n";
		}

		//string temp = "DELETE FROM " + TableName;
		string temp = "CREATE TABLE "+TableName+"(Id int UNIQUE,Name varchar(50) UNIQUE,ShapeType varchar(50),Start varchar(20),Value varchar(MAX),Color varchar(20),Size int,Lens int,Created DATETIME,Geometry varbinary(MAX));";
		m_pConnection->Execute(temp.c_str(), NULL, 1);

		temp = "CREATE TABLE " + TableName + "_relation" + "(Id int UNIQUE,Name varchar(50) UNIQUE,CombRelation varchar(MAX), Created DATETIME);";
		m_pConnection->Execute(temp.c_str(), NULL, 1);
	}
	catch (_com_error c)
	{
		cerr << "\nERROR:" << (char*)c.Description();
		return -1;
	}
	if (m_pConnection->State)
		m_pConnection->Close();

	::CoUninitialize();
	return 0;
}




//在数据库中删除表
int DataBase::dropTable(string TableName)
{
	::CoInitialize(NULL);

	int id;
	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");

		string strConnects = "Provider=SQLNCLI11;Server=" + this->ServerName + ";Database=" + this->DataBaseName + ";uid=" + this->UidName + ";pwd=" + this->PwdName + ";";
		_bstr_t strConnect = strConnects.c_str();
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
		if (m_pConnection == NULL)
		{
			cerr << "Lind data ERROR!\n";
		}

		//string temp = "DELETE FROM " + TableName;
		string temp = "DROP TABLE "+TableName;
		m_pConnection->Execute(temp.c_str(), NULL, 1);
	}
	catch (_com_error c)
	{
		cerr << "\nERROR:" << (char*)c.Description();
		return -1;
	}
	if (m_pConnection->State)
		m_pConnection->Close();

	::CoUninitialize();
	return 0;
}


//数据库关系表，插入操作
int DataBase::insertRelationQuery(int comb_Id, string comb_Name, string relations, string TableName)
{
	::CoInitialize(NULL);

	int id;
	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");

		string strConnects = "Provider=SQLNCLI11;Server=" + this->ServerName + ";Database=" + this->DataBaseName + ";uid=" + this->UidName + ";pwd=" + this->PwdName + ";";
		_bstr_t strConnect = strConnects.c_str();
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
		if (m_pConnection == NULL)
		{
			cerr << "Lind data ERROR!\n";
		}

		//string temp = "DELETE FROM " + TableName;
		string temp = "SELECT * FROM "+TableName;
		//cout << temp << endl;
		_bstr_t bstrSQL(temp.c_str());
		m_pRecordset.CreateInstance(_uuidof(Recordset));
		m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

		
		
		COleVariant vx(COleDateTime::GetCurrentTime());

		m_pRecordset->AddNew();
		m_pRecordset->PutCollect("Id",comb_Id);
		m_pRecordset->PutCollect("Name", _variant_t(comb_Name.c_str()));//string转_variant_t，即先转CString，再转_variant_t
		m_pRecordset->PutCollect("CombRelation", _variant_t(relations.c_str()));
		m_pRecordset->PutCollect("Created", vx);

		m_pRecordset->Update();       //更新数据表记录
		m_pRecordset->Close();        //关闭记录集

	}
	catch (_com_error c)
	{
		cerr << "\nERROR:" << (char*)c.Description();
		return -1;
	}
	if (m_pConnection->State)
		m_pConnection->Close();

	::CoUninitialize();
	return 0;
}












// 数据库图元表，插入操作
int DataBase::insertQuery(CDrawBase* newObj, string TableName)
{
	::CoInitialize(NULL);

	int id = 0;
	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");

		string strConnects = "Provider=SQLNCLI11;Server=" + this->ServerName + ";Database=" + this->DataBaseName + ";uid=" + this->UidName + ";pwd=" + this->PwdName + ";";
		_bstr_t strConnect = strConnects.c_str();
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
		if (m_pConnection == NULL)
		{
			cerr << "Lind data ERROR!\n";
		}


		string temp = "";
		if (newObj->shape_type == 1)
		{
			//d_id
			d_id += 1;

			//d_name
			d_name = "Rect_" + to_string(d_id);

			//d_shapetype
			d_shapetype = "Rect";

			//d_start
			d_start = to_string(newObj->m_Start.x) + "," + to_string(newObj->m_Start.y) + ";";

			//d_value
			d_value = to_string(newObj->m_End.x) + "," + to_string(newObj->m_End.y) + ";";

			//d_color
			if (newObj->color == RGB(255, 0, 0))
				d_color = "RGB(255,0,0)";
			else if (newObj->color == RGB(0, 255, 0))
				d_color = "RGB(0,255,0)";
			else if (newObj->color == RGB(0, 0, 255))
				d_color = "RGB(0,0,255)";
			else
				d_color = "RGB(0,0,0)";

			//d_size
			d_size = 0;
			//d_lens
			d_lens = 0;
		}

		if (newObj->shape_type == 2)
		{
			//d_id
			d_id += 1;

			//d_name
			d_name = "Font_" + to_string(d_id);

			//d_shapetype
			d_shapetype = "Font";

			//d_start
			d_start = to_string(newObj->m_Start.x) + "," + to_string(newObj->m_Start.y) + ";";

			//d_value，CString转string
			USES_CONVERSION;
			string str(W2A(((CDrawFont*)newObj)->font_str));
			d_value = str;

			//d_color
			if (newObj->color == RGB(255, 0, 0))
				d_color = "RGB(255,0,0)";
			else if (newObj->color == RGB(0, 255, 0))
				d_color = "RGB(0,255,0)";
			else if (newObj->color == RGB(0, 0, 255))
				d_color = "RGB(0,0,255)";
			else
				d_color = "RGB(0,0,0)";

			//d_size
			d_size = ((CDrawFont*)newObj)->size;
			//d_lens
			d_lens = 0;
		}

		if (newObj->shape_type == 3)
		{
			//d_id
			d_id += 1;

			//d_name
			d_name = "Poly_" + to_string(d_id);

			//d_shapetype
			d_shapetype = "Poly";

			//d_start
			d_start = to_string(newObj->m_Start.x) + "," + to_string(newObj->m_Start.y) + ";";

			//d_value
			int lens = ((CDrawPoly*)newObj)->len_point;
			string temp2;
			for (int i = 0; i < lens; i++)
			{
				temp2 += to_string(((CDrawPoly*)newObj)->getPoint(i)->x);
				temp2 += ",";
				temp2 += to_string(((CDrawPoly*)newObj)->getPoint(i)->y);
				temp2 += ";";
			}
			d_value = temp2;

			//d_color
			if (newObj->color == RGB(255, 0, 0))
				d_color = "RGB(255,0,0)";
			else if (newObj->color == RGB(0, 255, 0))
				d_color = "RGB(0,255,0)";
			else if (newObj->color == RGB(0, 0, 255))
				d_color = "RGB(0,0,255)";
			else
				d_color = "RGB(0,0,0)";

			//d_size
			d_size = ((CDrawPoly*)newObj)->solid;
			//d_lens
			d_lens = ((CDrawPoly*)newObj)->len_point;
		}

		temp = temp + "INSERT INTO "+TableName+" (Id,Name,ShapeType,Start,Value,Color,Size,Lens,Created) VALUES (" + to_string(d_id);
		temp = temp + ", '" + d_name;
		temp = temp + "', '" + d_shapetype;
		temp = temp + "', '" + d_start;
		temp = temp + "', '" + d_value;
		temp = temp + "', '" + d_color;
		temp = temp + "', " + to_string(d_size);
		temp = temp + ", " + to_string(d_lens);
		temp = temp + ", GETDATE())";

		order = temp;
		m_pConnection->Execute(temp.c_str(), NULL, 1);
		temp = "";
		temp = temp + "SELECT * FROM "+TableName+" WHERE Name='" + d_name + "'";

		_bstr_t bstrSQL(temp.c_str());
		m_pRecordset.CreateInstance(_uuidof(Recordset));
		m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		_variant_t sqlid = m_pRecordset->GetCollect("Id");
		id = (int)sqlid;

		//***********************************************写入BYTE*
		d_geo_len = d_value.size();
		d_geo = new BYTE[d_geo_len];
		d_geo = (BYTE*)(d_value.c_str());

		_variant_t var;
		var.vt = VT_ARRAY | VT_UI1;

		SAFEARRAYBOUND rgsabound[1];
		rgsabound[0].cElements = d_geo_len;
		rgsabound[0].lLbound = 0;

		var.parray = SafeArrayCreate(VT_UI1, 1, rgsabound);

		void * pArrayData = NULL;
		SafeArrayAccessData(var.parray, &pArrayData);
		memcpy(pArrayData, d_geo, d_geo_len);
		SafeArrayUnaccessData(var.parray);

		m_pRecordset->PutCollect("Geometry", var);//修改，这里修改m_pRecordset这行的Geometry列，第二个参数必须是_variant_t
		m_pRecordset->Update();



	}
	catch (_com_error c)
	{
		cerr << "\nERROR:" << (char*)c.Description();
		return -1;
	}
	if (m_pConnection->State)
		m_pConnection->Close();

	::CoUninitialize();

	return id;
}













//测试二进制流的交互
BYTE* DataBase::writeBinary(int id, BYTE* bg, string TableName)
{
	::CoInitialize(NULL);

	int count;
	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");

		string strConnects = "Provider=SQLNCLI11;Server=" + this->ServerName + ";Database=" + this->DataBaseName + ";uid=" + this->UidName + ";pwd=" + this->PwdName + ";";
		_bstr_t strConnect = strConnects.c_str();
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
		if (m_pConnection == NULL)
		{
			cerr << "Lind data ERROR!\n";
		}

		string temp = "select * from "+TableName+" where ID=1";
		//cout << temp << endl;
		_bstr_t bstrSQL(temp.c_str());
		m_pRecordset.CreateInstance(_uuidof(Recordset));
		m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		//_variant_t sqlgeo = m_pRecordset->GetCollect(_variant_t((long)0));
		//d_geo = (BYTE*)sqlgeo.pbVal;

		//下面是向数据库写入BYTE*，已测试可行
		d_geo = bg;
		d_geo_len = strlen((char*)bg);
	
		_variant_t var;
		var.vt = VT_ARRAY | VT_UI1;

		SAFEARRAYBOUND rgsabound[1];
		rgsabound[0].cElements = d_geo_len;
		rgsabound[0].lLbound = 0;

		var.parray = SafeArrayCreate(VT_UI1, 1, rgsabound);

		void * pArrayData = NULL;
		SafeArrayAccessData(var.parray, &pArrayData);
		memcpy(pArrayData, d_geo, d_geo_len);
		SafeArrayUnaccessData(var.parray);

		m_pRecordset->PutCollect("Geometry", var);//修改，这里修改m_pRecordset这行的Geometry列，第二个参数必须是_variant_t
		m_pRecordset->Update();

	
		

	}
	catch (_com_error c)
	{
		CString s = (CString)"000";
		cerr << "\nERROR:" << (char*)c.Description();
		return d_geo;
	}
	if (m_pConnection->State)
		m_pConnection->Close();

	::CoUninitialize();
	CString ss = (CString)"111";

	return d_geo;
}





//测试二进制流的交互
BYTE* DataBase::readBinary(int id, string TableName)
{
	::CoInitialize(NULL);

	int count;
	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");

		string strConnects = "Provider=SQLNCLI11;Server=" + this->ServerName + ";Database=" + this->DataBaseName + ";uid=" + this->UidName + ";pwd=" + this->PwdName + ";";
		_bstr_t strConnect = strConnects.c_str();

		

		m_pConnection->Open(strConnect, "", "", adModeUnknown);
		if (m_pConnection == NULL)
		{
			cerr << "Lind data ERROR!\n";
		}

		string temp1 = to_string(id);
		string temp = "select * from "+TableName+" where ID="+temp1;
		//cout << temp << endl;
		_bstr_t bstrSQL(temp.c_str());
		m_pRecordset.CreateInstance(_uuidof(Recordset));
		m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		//_variant_t sqlgeo = m_pRecordset->GetCollect(_variant_t((long)0));
		//d_geo = (BYTE*)sqlgeo.pbVal;

		
		_variant_t vtValue = m_pRecordset->GetCollect("Geometry");////得到，这里得到m_pRecordset这行的Geometry列，得到的是_variant_t值
		
		//得到数据库里“Geometry”字段的实际长度，然后根据此new BYTE[]给d_geo
		d_geo_len = m_pRecordset->GetFields()->GetItem("Geometry")->ActualSize;
	
		 d_geo = new BYTE[d_geo_len];	

		if (vtValue.vt == (VT_ARRAY | VT_UI1))
		{
			BYTE *pByte = NULL;
			SafeArrayAccessData(vtValue.parray, (void **)&pByte);
			memcpy(d_geo,pByte,d_geo_len);
			SafeArrayUnaccessData(vtValue.parray);

		}

	}
	catch (_com_error c)
	{
		CString s = (CString)"000";
		cerr << "\nERROR:" << (char*)c.Description();


		return d_geo;
	}
	if (m_pConnection->State)
		m_pConnection->Close();

	::CoUninitialize();
	CString ss = (CString)"111";
	return d_geo;
}






//数据库统计有多少条记录
int DataBase::countQuery(string TableName)
{
	::CoInitialize(NULL);

	int count;
	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");

		

		string strConnects = "Provider=SQLNCLI11;Server=" + this->ServerName + ";Database=" + this->DataBaseName + ";uid=" + this->UidName + ";pwd=" + this->PwdName + ";";
		_bstr_t strConnect = strConnects.c_str();
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
		if (m_pConnection == NULL)
		{
			cerr << "Lind data ERROR!\n";
		}

		string temp = "SELECT count(*) FROM "+TableName;
		//cout << temp << endl;
		_bstr_t bstrSQL(temp.c_str());
		m_pRecordset.CreateInstance(_uuidof(Recordset));
		m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);


		_variant_t sqlid = m_pRecordset->GetCollect(_variant_t((long)0));
		count = (int)sqlid;

	}
	catch (_com_error c)
	{
		cerr << "\nERROR:" << (char*)c.Description();
		return -1;
	}
	if (m_pConnection->State)
		m_pConnection->Close();



	::CoUninitialize();

	return count;
}


//数据库删除全部记录
int DataBase::removeAll(string TableName)
{
	::CoInitialize(NULL);

	int id;
	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");

		string strConnects = "Provider=SQLNCLI11;Server=" + this->ServerName + ";Database=" + this->DataBaseName + ";uid=" + this->UidName + ";pwd=" + this->PwdName + ";";
		_bstr_t strConnect = strConnects.c_str();
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
		if (m_pConnection == NULL)
		{
			cerr << "Lind data ERROR!\n";
		}

		string temp = "DELETE FROM "+TableName;
		m_pConnection->Execute(temp.c_str(), NULL, 1);
	}
	catch (_com_error c)
	{
		cerr << "\nERROR:" << (char*)c.Description();
		return -1;
	}
	if (m_pConnection->State)
		m_pConnection->Close();

	::CoUninitialize();
	return 0;
}


//数据库关系表，读取某条记录
int DataBase::readRelationQuery(int comb_Id, string TableName)
{
	::CoInitialize(NULL);

	int count;
	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");



		string strConnects = "Provider=SQLNCLI11;Server=" + this->ServerName + ";Database=" + this->DataBaseName + ";uid=" + this->UidName + ";pwd=" + this->PwdName + ";";
		_bstr_t strConnect = strConnects.c_str();
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
		if (m_pConnection == NULL)
		{
			cerr << "Lind data ERROR!\n";
		}

		string temp = "SELECT * FROM " + TableName + " WHERE Id=" + std::to_string(comb_Id);
		//cout << temp << endl;
		_bstr_t bstrSQL(temp.c_str());
		m_pRecordset.CreateInstance(_uuidof(Recordset));
		m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);

		_variant_t sqlid, sqlname, sqlcombrelation;
		sqlid = m_pRecordset->GetCollect("Id");
		sqlname = m_pRecordset->GetCollect("Name");
		sqlcombrelation = m_pRecordset->GetCollect("CombRelation");
		
		comb_id = (int)sqlid.lVal;
		comb_name = (string)(_bstr_t)sqlname;
		CombRelation = (string)(_bstr_t)sqlcombrelation;
		
	}
	catch (_com_error c)
	{
		cerr << "\nERROR:" << (char*)c.Description();
		return -1;
	}
	if (m_pConnection->State)
		m_pConnection->Close();



	::CoUninitialize();

	return comb_Id;
}





//数据库图原表，读取表中全部的记录
int DataBase::readAllQuery(string TableName)
{
	::CoInitialize(NULL);

	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");

		string strConnects = "Provider=SQLNCLI11;Server=" + this->ServerName + ";Database=" + this->DataBaseName + ";uid=" + this->UidName + ";pwd=" + this->PwdName + ";";
		_bstr_t strConnect = strConnects.c_str();
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
		if (m_pConnection == NULL)
		{
			cerr << "Lind data ERROR!\n";
		}
		string temp;

		temp = "SELECT * FROM " + TableName ;
		cout << temp.c_str() << endl;
		_bstr_t bstrSQL(temp.c_str());
		//创建记录集
		m_pRecordset.CreateInstance(_uuidof(Recordset));
		//取得表中的记录
		m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);


		//opens_num清0
		opens_num = 0;

		_variant_t sqlid, sqlname, sqltype, sqlstart, sqlvalue, sqlcolor, sqlsize, sqllens, sqltime;
		int count = 0;

		while (!m_pRecordset->EndOfFile)
		{

			sqlid = m_pRecordset->GetCollect(_variant_t((long)0));
			sqlname = m_pRecordset->GetCollect(_variant_t((long)1));
			sqltype = m_pRecordset->GetCollect(_variant_t((long)2));
			sqlstart = m_pRecordset->GetCollect(_variant_t((long)3));
			sqlvalue = m_pRecordset->GetCollect(_variant_t((long)4));
			sqlcolor = m_pRecordset->GetCollect(_variant_t((long)5));
			sqlsize = m_pRecordset->GetCollect(_variant_t((long)6));
			sqllens = m_pRecordset->GetCollect(_variant_t((long)7));

			if (((char *)(_bstr_t)sqltype)[0] == 'R')
			{
				open = new CDrawRC();
				open->shape_type = 1;

				//CDrawRC->m_start
				d_start = (string)(_bstr_t)sqlstart;

				vector<string> temp_string_vec;
				temp_string_vec = splitString(d_start, ",;");
				open->m_Start = CPoint(atoi(temp_string_vec[0].c_str()), atoi(temp_string_vec[1].c_str()));

				//string s = "12";
				//int a = atoi(s.c_str());

				//CDrawRC->m_end

				//下面第一种是采用读取字符串流，速度会快些。第二种是采用读取二进制流，速度慢些；都测试可行
				d_value = (string)(_bstr_t)sqlvalue;

				//BYTE* bb = readBinary(id, TableName);//从数据库读入BYTE*
				//std::string s(reinterpret_cast<char const*>(bb), d_geo_len);
				//d_value = s;
				//delete bb;

				temp_string_vec.clear();
				temp_string_vec = splitString(d_value, ",;");
				open->m_End = CPoint(atoi(temp_string_vec[0].c_str()), atoi(temp_string_vec[1].c_str()));

				//CDrawRC->color
				d_color = (string)(_bstr_t)sqlcolor;
				if (d_color == "RGB(255,0,0)")
					open->color = RGB(255, 0, 0);
				else if (d_color == "RGB(0,255,0)")
					open->color = RGB(0, 255, 0);
				else if (d_color == "RGB(0,0,255)")
					open->color = RGB(0, 0, 255);
				else
					open->color = RGB(0, 0, 0);

				d_size = 0;
				d_lens = 0;
			}

			if (((char *)(_bstr_t)sqltype)[0] == 'F')
			{
				open = new CDrawFont();
				open->shape_type = 2;

				//CDrawFont->m_start
				d_start = (string)(_bstr_t)sqlstart;

				vector<string> temp_string_vec;
				temp_string_vec = splitString(d_start, ",;");
				open->m_Start = CPoint(atoi(temp_string_vec[0].c_str()), atoi(temp_string_vec[1].c_str()));

				open->m_End = CPoint(atoi(temp_string_vec[0].c_str()) + 30, atoi(temp_string_vec[1].c_str()));

				//string s = "12";
				//int a = atoi(s.c_str());

				//CDrawFont->font_str

				//下面第一种是采用读取字符串流，速度会快些。第二种是采用读取二进制流，速度慢些；都测试可行
				d_value = (string)(_bstr_t)sqlvalue;

				//BYTE* bb = readBinary(id, TableName);//从数据库读入BYTE*
				//std::string s(reinterpret_cast<char const*>(bb), d_geo_len);
				//d_value = s;
				//delete bb;

				temp_string_vec.clear();

				//string转CString
				((CDrawFont*)open)->font_str = d_value.c_str();

				//CDrawFont->color
				d_color = (string)(_bstr_t)sqlcolor;
				if (d_color == "RGB(255,0,0)")
					open->color = RGB(255, 0, 0);
				else if (d_color == "RGB(0,255,0)")
					open->color = RGB(0, 255, 0);
				else if (d_color == "RGB(0,0,255)")
					open->color = RGB(0, 0, 255);
				else
					open->color = RGB(0, 0, 0);

				//CDrawFont->size
				d_size = (int)sqlsize.lVal;
				temp_string_vec.clear();
				((CDrawFont*)open)->size = d_size;

				d_lens = 0;
			}

			if (((char *)(_bstr_t)sqltype)[0] == 'P')
			{
				open = new CDrawPoly();
				open->shape_type = 3;

				//CDrawPoly->m_start
				d_start = (string)(_bstr_t)sqlstart;

				vector<string> temp_string_vec;
				temp_string_vec = splitString(d_start, ",;");
				open->m_Start = CPoint(atoi(temp_string_vec[0].c_str()), atoi(temp_string_vec[1].c_str()));

				//string s = "12";
				//int a = atoi(s.c_str());

				//CDrawPoly->CPoint*

				//下面第一种是采用读取字符串流，速度会快些。第二种是采用读取二进制流，速度慢些；都测试可行
				d_value = (string)(_bstr_t)sqlvalue;

				//BYTE* bb = readBinary(id, TableName);//从数据库读入BYTE*
				//std::string s(reinterpret_cast<char const*>(bb), d_geo_len);
				//d_value = s;
				//delete bb;

				temp_string_vec.clear();
				temp_string_vec = splitString(d_value, ",;");






				for (int i = 0; i < temp_string_vec.size(); i += 2)
				{
					CPoint *temp_point = new CPoint(CPoint(atoi(temp_string_vec[i].c_str()), atoi(temp_string_vec[i + 1].c_str())));
					((CDrawPoly*)open)->addPoint(temp_point);
					open->m_End = CPoint(atoi(temp_string_vec[i].c_str()), atoi(temp_string_vec[i + 1].c_str()));
				}



				//CDrawPoly->color
				d_color = (string)(_bstr_t)sqlcolor;
				if (d_color == "RGB(255,0,0)")
					open->color = RGB(255, 0, 0);
				else if (d_color == "RGB(0,255,0)")
					open->color = RGB(0, 255, 0);
				else if (d_color == "RGB(0,0,255)")
					open->color = RGB(0, 0, 255);
				else
					open->color = RGB(0, 0, 0);


				//CDrawPoly->solid
				d_size = (int)sqlsize.lVal;
				temp_string_vec.clear();
				((CDrawPoly*)open)->solid = d_size;

				//CDrawPoly->len_point
				d_lens = (int)sqllens.lVal;
				((CDrawPoly*)open)->len_point = d_lens;

			}

			
			opens[count] = open;
			opens_num += 1;
			count+=1;

			m_pRecordset->MoveNext();

		}//while


	}//try
	catch (_com_error c)
	{
		cerr << "\nERROR:" << (char*)c.Description();
		return -1;
	}
	if (m_pConnection->State)
		m_pConnection->Close();

	::CoUninitialize();
	return 1;
}

















//数据库图原表，读取某条记录
int DataBase::readQuery(int id, string TableName)
{
	::CoInitialize(NULL);

	_RecordsetPtr m_pRecordset("ADODB.Recordset");
	_ConnectionPtr m_pConnection("ADODB.Connection");
	try
	{
		m_pConnection.CreateInstance("ADODB.Connection");

		string strConnects = "Provider=SQLNCLI11;Server=" + this->ServerName + ";Database=" + this->DataBaseName + ";uid=" + this->UidName + ";pwd=" + this->PwdName + ";";
		_bstr_t strConnect = strConnects.c_str();
		m_pConnection->Open(strConnect, "", "", adModeUnknown);
		if (m_pConnection == NULL)
		{
			cerr << "Lind data ERROR!\n";
		}
		string temp;

		temp = "SELECT * FROM "+TableName+" WHERE Id=" + std::to_string(id);
		cout << temp.c_str() << endl;
		_bstr_t bstrSQL(temp.c_str());
		//创建记录集
		m_pRecordset.CreateInstance(_uuidof(Recordset));
		//取得表中的记录
		m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
		_variant_t sqlid, sqlname, sqltype, sqlstart, sqlvalue, sqlcolor, sqlsize, sqllens, sqltime;
		int count = 0;
		
			sqlid = m_pRecordset->GetCollect(_variant_t((long)0));
			sqlname = m_pRecordset->GetCollect(_variant_t((long)1));
			sqltype = m_pRecordset->GetCollect(_variant_t((long)2));
			sqlstart = m_pRecordset->GetCollect(_variant_t((long)3));
			sqlvalue = m_pRecordset->GetCollect(_variant_t((long)4));
			sqlcolor = m_pRecordset->GetCollect(_variant_t((long)5));
			sqlsize = m_pRecordset->GetCollect(_variant_t((long)6));
			sqllens = m_pRecordset->GetCollect(_variant_t((long)7));

			if (((char *)(_bstr_t)sqltype)[0] == 'R')
			{
				open = new CDrawRC();
				open->shape_type = 1;

				//CDrawRC->m_start
				d_start = (string)(_bstr_t)sqlstart;

				vector<string> temp_string_vec;
				temp_string_vec = splitString(d_start, ",;");
				open->m_Start = CPoint(atoi(temp_string_vec[0].c_str()), atoi(temp_string_vec[1].c_str()));

				//string s = "12";
				//int a = atoi(s.c_str());

				//CDrawRC->m_end

				//下面第一种是采用读取字符串流，速度会快些。第二种是采用读取二进制流，速度慢些；都测试可行
				d_value = (string)(_bstr_t)sqlvalue;

				//BYTE* bb = readBinary(id, TableName);//从数据库读入BYTE*
				//std::string s(reinterpret_cast<char const*>(bb), d_geo_len);
				//d_value = s;
				//delete bb;

				temp_string_vec.clear();
				temp_string_vec = splitString(d_value, ",;");
				open->m_End = CPoint(atoi(temp_string_vec[0].c_str()), atoi(temp_string_vec[1].c_str()));

				//CDrawRC->color
				d_color = (string)(_bstr_t)sqlcolor;
				if (d_color == "RGB(255,0,0)")
					open->color = RGB(255, 0, 0);
				else if (d_color == "RGB(0,255,0)")
					open->color = RGB(0, 255, 0);
				else if (d_color == "RGB(0,0,255)")
					open->color = RGB(0, 0, 255);
				else
					open->color = RGB(0, 0, 0);

				d_size = 0;
				d_lens = 0;
			}

			if (((char *)(_bstr_t)sqltype)[0] == 'F')
			{
				open = new CDrawFont();
				open->shape_type = 2;

				//CDrawFont->m_start
				d_start = (string)(_bstr_t)sqlstart;

				vector<string> temp_string_vec;
				temp_string_vec = splitString(d_start, ",;");
				open->m_Start = CPoint(atoi(temp_string_vec[0].c_str()), atoi(temp_string_vec[1].c_str()));

				open->m_End = CPoint(atoi(temp_string_vec[0].c_str()) + 30, atoi(temp_string_vec[1].c_str()));

				//string s = "12";
				//int a = atoi(s.c_str());

				//CDrawFont->font_str

				//下面第一种是采用读取字符串流，速度会快些。第二种是采用读取二进制流，速度慢些；都测试可行
				d_value = (string)(_bstr_t)sqlvalue;

				//BYTE* bb = readBinary(id, TableName);//从数据库读入BYTE*
				//std::string s(reinterpret_cast<char const*>(bb), d_geo_len);
				//d_value = s;
				//delete bb;

				temp_string_vec.clear();

				//string转CString
				((CDrawFont*)open)->font_str = d_value.c_str();

				//CDrawFont->color
				d_color = (string)(_bstr_t)sqlcolor;
				if (d_color == "RGB(255,0,0)")
					open->color = RGB(255, 0, 0);
				else if (d_color == "RGB(0,255,0)")
					open->color = RGB(0, 255, 0);
				else if (d_color == "RGB(0,0,255)")
					open->color = RGB(0, 0, 255);
				else
					open->color = RGB(0, 0, 0);

				//CDrawFont->size
				d_size = (int)sqlsize.lVal;
				temp_string_vec.clear();
				((CDrawFont*)open)->size = d_size;

				d_lens = 0;
			}

			if (((char *)(_bstr_t)sqltype)[0] == 'P')
			{
				open = new CDrawPoly();
				open->shape_type = 3;

				//CDrawPoly->m_start
				d_start = (string)(_bstr_t)sqlstart;

				vector<string> temp_string_vec;
				temp_string_vec = splitString(d_start, ",;");
				open->m_Start = CPoint(atoi(temp_string_vec[0].c_str()), atoi(temp_string_vec[1].c_str()));

				//string s = "12";
				//int a = atoi(s.c_str());

				//CDrawPoly->CPoint*

				//下面第一种是采用读取字符串流，速度会快些。第二种是采用读取二进制流，速度慢些；都测试可行
				d_value = (string)(_bstr_t)sqlvalue;

				//BYTE* bb = readBinary(id, TableName);//从数据库读入BYTE*
				//std::string s(reinterpret_cast<char const*>(bb), d_geo_len);
				//d_value = s;
				//delete bb;

				temp_string_vec.clear();
				temp_string_vec = splitString(d_value, ",;");

			

				
				

				for (int i = 0; i < temp_string_vec.size(); i += 2)
				{
					CPoint *temp_point = new CPoint(CPoint(atoi(temp_string_vec[i].c_str()), atoi(temp_string_vec[i + 1].c_str())));
					((CDrawPoly*)open)->addPoint(temp_point);
					open->m_End = CPoint(atoi(temp_string_vec[i].c_str()), atoi(temp_string_vec[i + 1].c_str()));
				}

				

				//CDrawPoly->color
				d_color = (string)(_bstr_t)sqlcolor;
				if (d_color == "RGB(255,0,0)")
					open->color = RGB(255, 0, 0);
				else if (d_color == "RGB(0,255,0)")
					open->color = RGB(0, 255, 0);
				else if (d_color == "RGB(0,0,255)")
					open->color = RGB(0, 0, 255);
				else
					open->color = RGB(0, 0, 0);


				//CDrawPoly->solid
				d_size = (int)sqlsize.lVal;
				temp_string_vec.clear();
				((CDrawPoly*)open)->solid = d_size;

				//CDrawPoly->len_point
				d_lens = (int)sqllens.lVal;
				((CDrawPoly*)open)->len_point = d_lens;
				
			}

		
	}
	catch (_com_error c)
	{
		cerr << "\nERROR:" << (char*)c.Description();
		return -1;
	}
	if (m_pConnection->State)
		m_pConnection->Close();

	::CoUninitialize();
	return id;
}


//分割字符串
vector<string> DataBase::splitString(const string &s, const string &seperator){
	vector<string> result;
	typedef string::size_type string_size;
	string_size i = 0;

	while (i != s.size()){
		//找到字符串中首个不等于分隔符的字母；
		int flag = 0;
		while (i != s.size() && flag == 0){
			flag = 1;
			for (string_size x = 0; x < seperator.size(); ++x)
			if (s[i] == seperator[x]){
				++i;
				flag = 0;
				break;
			}
		}

		//找到又一个分隔符，将两个分隔符之间的字符串取出；
		flag = 0;
		string_size j = i;
		while (j != s.size() && flag == 0){
			for (string_size x = 0; x < seperator.size(); ++x)
			if (s[j] == seperator[x]){
				flag = 1;
				break;
			}
			if (flag == 0)
				++j;
		}
		if (i != j){
			result.push_back(s.substr(i, j - i));
			i = j;
		}
	}
	return result;
}