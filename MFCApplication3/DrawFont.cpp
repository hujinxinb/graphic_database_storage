#include "stdafx.h"
#include "DrawFont.h"


CDrawFont::CDrawFont()
{
	shape_type = 2;
	font_str = (CString)" ";
	size = 20;
}


CDrawFont::~CDrawFont()
{
}


void CDrawFont::Draw(CDC *pDC)
{
	//pDC->MoveTo(m_Start);
	//pDC->LineTo(m_End);

	TEXTMETRIC tm;
	CFont * pOldFont;
	CFont * pNewFont = new CFont;
	pNewFont->CreateFont(size, 0, 0, 0,
		FW_NORMAL,
		false, false, 0,
		ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
		DEFAULT_PITCH&FF_SWISS, _T("Aerial"));

	pDC->SetTextColor(color);

	pOldFont = (CFont *)pDC->SelectObject(pNewFont);//选择新字体，并保留原来字体
	pDC->GetTextMetrics(&tm);

	//CString str = (CString)"单文档用户界面和菜单的使用!";
	CString str = font_str;
	pDC->TextOut(m_Start.x, m_Start.y, str);

	//CString ss1;
	//ss1.Format(_T("%d"), pDoc->my->GetODBCFieldCount());//返回列数，也即表中的字段数
	//pDC->TextOut(100, -550, ss1);


	//还可以pDC->SetTextColor, COLORREF color = pDC->SetTextColor;
	pDC->SelectObject(pOldFont);//恢复原来的字体，如果像上面写的都不这样做恢复的话会建太多而用完
	delete pNewFont;//删除新字体

}