#include "stdafx.h"
#include "DrawRC.h"


CDrawRC::CDrawRC()
{
	color = RGB(0, 255, 0);
	shape_type = 1;
}


CDrawRC::~CDrawRC()
{
}


void CDrawRC::Draw(CDC *pDC)
{
	//pDC->Rectangle(m_Start.x, m_Start.y, m_End.x, m_End.y);

	CBrush brush(color);
	pDC->FillRect(CRect(m_Start, m_End), &brush);
}