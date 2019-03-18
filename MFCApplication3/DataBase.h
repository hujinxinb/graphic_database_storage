
#pragma once
#include "DrawRC.h"
#include "DrawFont.h"
#include "DrawPoly.h"
#include "Dlg_text.h"
#include <string>
#include<vector>


using namespace std;

class DataBase
{
public:
	string ServerName;
	string DataBaseName;
	string UidName;
	string PwdName;//前面几个是远程控制的
	vector<string> all_table_name;
	vector<string> all_table_name_only;
	string table_name;//这几个是和库中表名的相关的

	vector<string> all_CombRelations;
	string CombRelation;
	int comb_id;
	string comb_name;//这几个是关系表中的

	int d_id;
	string d_name;
	string d_shapetype;
	string d_start;
	string d_value;
	string d_color;
	int d_size;
	int d_lens;
	BYTE* d_geo;
	long d_geo_len;

	//查询得到的结果构建的CDrawBase
	CDrawBase* open;
	CDrawBase* opens[100000];
	int opens_num;

	string order;


	


public:
	vector<string> get_all_table_inf();//得到这个数据库里的所有表名及其相关表描述

	int createTable(string TableName);
	int dropTable(string TableName);

	int insertQuery(CDrawBase* newObj,string TableName);//在图元表中插入
	int insertRelationQuery(int comb_Id, string comb_Name, string relations, string TableName);//在关系表中插入

	int countQuery(string TableName);
	int removeAll(string TableName);
	int readQuery(int id, string TableName);//在图元表中读取某条记录
	int readAllQuery(string TableName);//在图原表中读取全部记录
	int readRelationQuery(int comb_Id, string TableName);//在关系表中读取

	BYTE* writeBinary(int id, BYTE* bg, string TableName);
	BYTE* readBinary(int id, string TableName);


	vector<string> splitString(const string &s, const string &seperator);//多分割符的分割字符串函数

	DataBase();
	~DataBase();
};





////连接BYTE*测试，用memcpy，注意，第二个要+1，因为strlen是不包含结束的\0的，但在第二个memcpy时要把\0拷进去
//string s2 = "(1,2,3);(2.3,3.14,5.6789);1.23;我;我们";
//string s3 = ";1,2,3";
//const char *p2 = s2.c_str();;
//const char *p3 = s3.c_str();;
//
//BYTE* b = (BYTE*)p2;
//BYTE* b2 = (BYTE*)p3;
//
//int len1 = strlen((char*)b);
//int len2 = strlen((char*)b2);
//int lens = len1 + len2;
//
//BYTE* b3 = new BYTE[lens + 1];
//memcpy(b3, b, len1);
//memcpy(b3 + len1, b2, len2 + 1);
//
//int lenb3 = strlen((char*)b3);
//
//
//pDoc->db.writeBinary(1, b3, "temp7");//写入数据库测试
//
//
//BYTE* bb = pDoc->db.readBinary(1, "temp7");//从数据库读入BYTE*
////求BYTE*的长度：strlen((char*)bb)，但针对某些情况，如未初始化BYTE*没用，所以用d_geo_len
////这行直接得到string"0123,.;"
//std::string s(reinterpret_cast<char const*>(bb), pDoc->db.d_geo_len);
//
//CDC* pDC = GetDC();
//CString ss(s.c_str());
//pDC->TextOut(100, 100, ss);







////const char*和CString是一样的，string转char* 也是用.c_str()
///*  string =====> const char*   */
//
//string s1 = "123123";
//const char *p1 = s1.c_str();
//cout << p1 << endl;
//
//const char *p2 = s1.data();
//cout << p2 << endl;
//
///*  string =====> char *       这个不知道为什么会引起p3的长度变化 */
//string s2 = "321321";
//char *p3 = NULL;
//p3 = (char *)malloc(s2.length() * sizeof(char));
//s2.copy(p3, s2.length(), 0);
//cout << p3 << endl;
//
///*  char * =====> string        */
//char *p = "12341234";
//string s3 = p;
//cout << s3 << endl;
//
///*  string =====> char []       */
////方法一(使用copy函数:
//string s4 = "44444"
//char p4[6] = { 0 };
//s4.copy(p4, s4.length(), 0);
//p4[s4.length()] = '\0'; //填充结束符
//cout << p4 << endl;
