#pragma once
#include "DrawBase.h"
class CDrawPoly :
	public CDrawBase
{
public:
	int solid;
	

	CPoint* point[100000];//DrawBase指针数组
	int len_point;

	// 操作
public:
	//CDrawBase* newDrawBase(CPoint start_point,CPoint end_point);
	int addPoint(CPoint* p);
	int removePoint(int ID);
	int emptyPoint();
	CPoint* getPoint(int ID);



	void Draw(CDC *pDC);

	CDrawPoly();
	~CDrawPoly();
};

