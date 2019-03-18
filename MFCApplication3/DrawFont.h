#pragma once
#include "DrawBase.h"
class CDrawFont :
	public CDrawBase
{
public:

	CString font_str;
	int size;

	void Draw(CDC *pDC);

	CDrawFont();
	~CDrawFont();
};

