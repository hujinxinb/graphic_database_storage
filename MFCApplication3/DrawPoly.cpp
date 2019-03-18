#include "stdafx.h"
#include "DrawPoly.h"


CDrawPoly::CDrawPoly()
{
	shape_type = 3;
	color = RGB(0, 0, 0);
	solid = 2;
	len_point = 0;
}


CDrawPoly::~CDrawPoly()
{
}



int CDrawPoly::addPoint(CPoint* p)
{

	point[len_point] = p;
	len_point += 1;

	return len_point;
}

int CDrawPoly::removePoint(int ID)
{
	point[len_point - 1] = point[ID];

	for (int i = ID; i < len_point - 1; i++)
	{
		point[i] = point[i + 1];
	}

	delete point[len_point - 1];
	len_point -= 1;

	return len_point;
}


int CDrawPoly::emptyPoint()
{
	for (int i = 0; i < len_point; i++)
	{
		delete point[i];
	}

	len_point = 0;
	return 0;
}



CPoint* CDrawPoly::getPoint(int ID)
{
	return point[ID];
}






void CDrawPoly::Draw(CDC *pDC)
{
	CPen pen(PS_SOLID, solid, color);
	CPen *pOldPen = pDC->SelectObject(&pen); //将其选入设备表

	if (len_point == 0)
		return;
	if (len_point == 1)
	{
		
		pDC->MoveTo(*point[0]);
		pDC->SelectObject(pOldPen);
		return;
	}
	
	if (len_point > 1)
	{
		for (int i = 0; i < len_point - 1; i++)
		{			
			pDC->MoveTo(*point[i]);
			pDC->LineTo(*point[i + 1]);
		

		}
	}
	
	pDC->SelectObject(pOldPen);
}