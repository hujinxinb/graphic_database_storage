#include "stdafx.h"
#include "DrawBase.h"


CDrawBase::CDrawBase()
{
	shape_type = 0;
}


CDrawBase::~CDrawBase()
{
}


void CDrawBase::GetStart(CPoint point)
{
	m_Start.x = point.x;
	m_Start.y = point.y;
}

void CDrawBase::GetEnd(CPoint point)
{
	m_End.x = point.x;
	m_End.y = point.y;
}


void CDrawBase::Draw(CDC *PDC)
{

}