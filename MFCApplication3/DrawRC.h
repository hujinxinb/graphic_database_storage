#pragma once
#include "DrawBase.h"
class CDrawRC :
	public CDrawBase
{
public:
	void Draw(CDC *pDC);

	CDrawRC();
	~CDrawRC();
};

