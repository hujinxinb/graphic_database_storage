#pragma once
#include "afxwin.h"

class CDrawBase
{
public:
	CPoint m_Start, m_End;
	COLORREF color;
	int shape_type;


	void GetEnd(CPoint point);
	void GetStart(CPoint point);
	
	virtual void Draw(CDC *PDC);

	CDrawBase();
	~CDrawBase();
};
