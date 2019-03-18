
// MFCApplication3View.cpp : CMFCApplication3View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCApplication3.h"
#endif

#include "MFCApplication3Doc.h"
#include "MFCApplication3View.h"

#include "MainFrm.h"
#include <iostream>
#include <string>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication3View

IMPLEMENT_DYNCREATE(CMFCApplication3View, CView)

BEGIN_MESSAGE_MAP(CMFCApplication3View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CMFCApplication3View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_SHAPE_RECT, &CMFCApplication3View::OnShapeRect)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_RECT, &CMFCApplication3View::OnUpdateShapeRect)
	ON_COMMAND(ID_SHAPE_FONT, &CMFCApplication3View::OnShapeFont)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_FONT, &CMFCApplication3View::OnUpdateShapeFont)
	ON_COMMAND(ID_SHAPE_POLY, &CMFCApplication3View::OnShapePoly)
	ON_UPDATE_COMMAND_UI(ID_SHAPE_POLY, &CMFCApplication3View::OnUpdateShapePoly)
	ON_COMMAND(ID_SIZE_20, &CMFCApplication3View::OnSize20)
	ON_UPDATE_COMMAND_UI(ID_SIZE_20, &CMFCApplication3View::OnUpdateSize20)
	ON_COMMAND(ID_SIZE_40, &CMFCApplication3View::OnSize40)
	ON_UPDATE_COMMAND_UI(ID_SIZE_40, &CMFCApplication3View::OnUpdateSize40)
	ON_COMMAND(ID_SIZE_80, &CMFCApplication3View::OnSize80)
	ON_UPDATE_COMMAND_UI(ID_SIZE_80, &CMFCApplication3View::OnUpdateSize80)
	ON_COMMAND(ID_SOLID_2, &CMFCApplication3View::OnSolid2)
	ON_UPDATE_COMMAND_UI(ID_SOLID_2, &CMFCApplication3View::OnUpdateSolid2)
	ON_COMMAND(ID_SOLID_4, &CMFCApplication3View::OnSolid4)
	ON_UPDATE_COMMAND_UI(ID_SOLID_4, &CMFCApplication3View::OnUpdateSolid4)
	ON_COMMAND(ID_SOLID_8, &CMFCApplication3View::OnSolid8)
	ON_UPDATE_COMMAND_UI(ID_SOLID_8, &CMFCApplication3View::OnUpdateSolid8)
	ON_COMMAND(ID_COLOR_RED, &CMFCApplication3View::OnColorRed)
	ON_UPDATE_COMMAND_UI(ID_COLOR_RED, &CMFCApplication3View::OnUpdateColorRed)
	ON_COMMAND(ID_COLOR_GREEN, &CMFCApplication3View::OnColorGreen)
	ON_UPDATE_COMMAND_UI(ID_COLOR_GREEN, &CMFCApplication3View::OnUpdateColorGreen)
	ON_COMMAND(ID_COLOR_BLUE, &CMFCApplication3View::OnColorBlue)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLUE, &CMFCApplication3View::OnUpdateColorBlue)
	ON_COMMAND(ID_COLOR_BLACK, &CMFCApplication3View::OnColorBlack)
	ON_UPDATE_COMMAND_UI(ID_COLOR_BLACK, &CMFCApplication3View::OnUpdateColorBlack)
	ON_COMMAND(ID_SELECT, &CMFCApplication3View::OnSelect)
	ON_COMMAND(ID_SELECT_CANCEL, &CMFCApplication3View::OnSelectCancel)
	ON_UPDATE_COMMAND_UI(ID_SELECT, &CMFCApplication3View::OnUpdateSelect)
	ON_UPDATE_COMMAND_UI(ID_SELECT_CANCEL, &CMFCApplication3View::OnUpdateSelectCancel)
	ON_COMMAND(ID_COMB, &CMFCApplication3View::OnComb)
	ON_COMMAND(ID_UNCOMB, &CMFCApplication3View::OnUncomb)
	ON_COMMAND(ID_LOD_32812, &CMFCApplication3View::OnLod32812)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_COMMAND(ID_LOD_32813, &CMFCApplication3View::OnLod32813)
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CMFCApplication3View 构造/析构

CMFCApplication3View::CMFCApplication3View()
{
	// TODO:  在此处添加构造代码
	draw_time = 0;
	draw_type = 0;
	draw_point_len = 0;
	draw_solid = 2;
	draw_size = 20;
	draw_color = RGB(0, 0, 0);

	select_object = false;
	opengl_view = false;
}

CMFCApplication3View::~CMFCApplication3View()
{
	
}

BOOL CMFCApplication3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}


// CMFCApplication3View 绘制
void CMFCApplication3View::OnDraw(CDC* pDC)
{
	CMFCApplication3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;


	if (opengl_view)
	{
		//绘制LOD内容
	}


	else
	{
		for (int i = 0; i < pDoc->len_drawbase; i++)
			pDoc->getDrawBase(i)->Draw(pDC);

		//画选区框
		if (select_object)
		{

			CDC* pDC = GetDC();
			CPen pen(PS_DOT, 1, RGB(0, 0, 0));
			CBrush br;
			br.CreateStockObject(NULL_BRUSH);
			pDC->SelectObject(&pen);
			pDC->SelectObject(&br);
			pDC->Rectangle(select_start.x, select_start.y, select_end.x, select_end.y);
		}
	}


}



void CMFCApplication3View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CMFCApplication3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCApplication3View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMFCApplication3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}

void CMFCApplication3View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	//ClientToScreen(&point);
	//OnContextMenu(this, point);
	draw_type = 0;
	draw_point_len = 0;
	CDC* pDC = GetDC();
	OnDraw(pDC);
}

void CMFCApplication3View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CMFCApplication3View 诊断

#ifdef _DEBUG
void CMFCApplication3View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCApplication3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCApplication3Doc* CMFCApplication3View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCApplication3Doc)));
	return (CMFCApplication3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCApplication3View 消息处理程序


void CMFCApplication3View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	
	CMFCApplication3Doc* pDoc = GetDocument();
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;


	 if (select_object == true && !pMain->m_wndProperties.prop_changed)
	{
		select_start.x = point.x;
		select_start.y = point.y;
	}

	

	 if (select_object==false)
	{
		 select_object_id = -1000;

		if (draw_type == 1)
		{
			now = new CDrawRC();
			now->GetStart(point);
			now->color = draw_color;
		}

		if (draw_type == 2)
		{
			now = new CDrawFont();
			((CDrawFont*)now)->font_str = draw_text;
			((CDrawFont*)now)->size = draw_size;
			now->GetStart(point);
			now->m_End = CPoint(point.x+30, point.y);
			now->color = draw_color;

		}

		if (draw_type == 3)
		{
			((CDrawPoly*)now)->solid = draw_solid;

			CPoint *temp_point = new CPoint(point.x, point.y);
			((CDrawPoly*)now)->addPoint(temp_point);

			now->color = draw_color;
			now->m_Start = *(((CDrawPoly*)now)->getPoint(0));
			int len = ((CDrawPoly*)now)->len_point;
			now->m_End = *(((CDrawPoly*)now)->getPoint(len-1));
			pDoc->top[pDoc->len_drawbase - 1] = now;
		}
	}

	CView::OnLButtonDown(nFlags, point);
}


void CMFCApplication3View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CView::OnLButtonUp(nFlags, point);

	CMFCApplication3Doc* pDoc = GetDocument();
	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;


	if (select_object == true && !pMain->m_wndProperties.prop_changed)
	{
		select_end.x = point.x;
		select_end.y = point.y;

		for (int i = 0; i < pDoc->len_drawbase; i++)
		{
			CPoint start = pDoc->getDrawBase(i)->m_Start;

			//说明现在的这个i就是被选中的对象id
			if (select_start.x < start.x && start.x < select_end.x && select_start.y < start.y && start.y < select_end.y)
			{
				select_object_id = i;

				CMFCPropertyGridProperty * pProp;
				
				
				//修改Property里的“形状”,
				pProp = pMain->m_wndProperties.m_wndPropList.GetProperty(0)->GetSubItem(0);
				if (pDoc->getDrawBase(i)->shape_type == 1)
				{
					pProp->SetValue((_variant_t)_T("矩形"));
				
				}
					
				else if (pDoc->getDrawBase(i)->shape_type == 2)
				{
					pProp->SetValue((_variant_t)_T("文字"));

					//修改Property里的“字体大小”
					pProp = pMain->m_wndProperties.m_wndPropList.GetProperty(1)->GetSubItem(0);
					long pProp_font_size = ((CDrawFont*)pDoc->getDrawBase(i))->size; 
					pProp->SetValue((_variant_t)pProp_font_size);

					//修改Property里的“文字内容”
					pProp = pMain->m_wndProperties.m_wndPropList.GetProperty(1)->GetSubItem(1);
					pProp->SetValue((_variant_t)((CDrawFont*)pDoc->getDrawBase(i))->font_str);
				}
					
				else if (pDoc->getDrawBase(i)->shape_type == 3)
				{
					pProp->SetValue((_variant_t)_T("折线"));

					//修改Property里的“折线粗细”
					pProp = pMain->m_wndProperties.m_wndPropList.GetProperty(2)->GetSubItem(0);
					long pProp_poly_size = ((CDrawPoly*)pDoc->getDrawBase(i))->solid;
					pProp->SetValue((_variant_t)pProp_poly_size);

					//修改Property里的“折线点总数”
					pProp = pMain->m_wndProperties.m_wndPropList.GetProperty(2)->GetSubItem(1);
					long pProp_poly_len = ((CDrawPoly*)pDoc->getDrawBase(i))->len_point;
					pProp->SetValue((_variant_t)pProp_poly_len);
			
				}
					

				//修改Property里的id
				pProp = pMain->m_wndProperties.m_wndPropList.GetProperty(0)->GetSubItem(1);
				string select = to_string(i);
				CString select_id(select.c_str());
				//读取数据
				CString itemname;
				itemname = pProp->GetName(); //获取名称
				COleVariant itemvalue;
				itemvalue = pProp->GetValue();//获取值
				//写入数据
				pProp->SetValue((_variant_t)select_id);

				//修改Property里的颜色
				CMFCPropertyGridColorProperty* pPropc = (CMFCPropertyGridColorProperty*)pMain->m_wndProperties.m_wndPropList.GetProperty(0)->GetSubItem(2);
				if (pDoc->getDrawBase(i)->color ==RGB(255,0,0))
					pPropc->SetColor(RGB(255,0,0));
				else if (pDoc->getDrawBase(i)->color == RGB(0, 255, 0))
					pPropc->SetColor(RGB(0, 255, 0));
				else if (pDoc->getDrawBase(i)->color == RGB(0, 0, 255))
					pPropc->SetColor(RGB(0, 0, 255));
				else if (pDoc->getDrawBase(i)->color == RGB(0, 0, 0))
					pPropc->SetColor(RGB(0, 0, 0));

				//修改Property里的“Start”点
				pProp = pMain->m_wndProperties.m_wndPropList.GetProperty(0)->GetSubItem(3)->GetSubItem(0);
				long pProp_Start_x = pDoc->getDrawBase(i)->m_Start.x;
				pProp->SetValue((_variant_t)pProp_Start_x);
				pProp = pMain->m_wndProperties.m_wndPropList.GetProperty(0)->GetSubItem(3)->GetSubItem(1);
				long pProp_Start_y = pDoc->getDrawBase(i)->m_Start.y;
				pProp->SetValue((_variant_t)pProp_Start_y);

				//修改Property里的“End”点
				pProp = pMain->m_wndProperties.m_wndPropList.GetProperty(0)->GetSubItem(4)->GetSubItem(0);
				long pProp_End_x = pDoc->getDrawBase(i)->m_End.x;
				pProp->SetValue((_variant_t)pProp_End_x);
				pProp = pMain->m_wndProperties.m_wndPropList.GetProperty(0)->GetSubItem(4)->GetSubItem(1);
				long pProp_End_y = pDoc->getDrawBase(i)->m_End.y;
				pProp->SetValue((_variant_t)pProp_End_y);
				
				break;
			}

			//if (pDoc->getDrawBase(i)->shape_type == 2)
			//{
			//	CString ss1;
			//	//ss1.Format(_T("%d"), pDoc->getDrawBase(i)->shape_type);//返回列数，也即表中的字段数
			//	ss1 = ((CDrawFont*)(pDoc->getDrawBase(i)))->font_str;
			//	pDC->TextOut(100, 100 + 20 * i, ss1);
			//}
		}

		//直接用这个函数重绘窗口而不用再OnDraw(pDC)更好
		Invalidate();
		//CDC* pDC = GetDC();
		//OnDraw(pDC);
	}



	if (select_object == true && pMain->m_wndProperties.prop_changed)
	{
		//根据Property修改文档中该对象的颜色
		if (pMain->m_wndProperties.prop_name == _T("颜色"))
		{
			if (pMain->m_wndProperties.prop_value.lVal == 255l)
				pDoc->getDrawBase(select_object_id)->color = RGB(255, 0, 0);
			if (pMain->m_wndProperties.prop_value.lVal == 65280l)
				pDoc->getDrawBase(select_object_id)->color = RGB(0, 255, 0);
			if (pMain->m_wndProperties.prop_value.lVal == 16711680l)
				pDoc->getDrawBase(select_object_id)->color = RGB(0, 0, 255);
			if (pMain->m_wndProperties.prop_value.lVal == 0l)
				pDoc->getDrawBase(select_object_id)->color = RGB(0, 0, 0);
		}

		//根据Property修改文档中该对象的字体大小
		if (pMain->m_wndProperties.prop_name == _T("字体大小") && pDoc->getDrawBase(select_object_id)->shape_type==2)
		{
			((CDrawFont*)pDoc->getDrawBase(select_object_id))->size = pMain->m_wndProperties.prop_value.lVal;
		}

		//根据Property修改文档中该对象的文字内容
		if (pMain->m_wndProperties.prop_name == _T("文字内容") && pDoc->getDrawBase(select_object_id)->shape_type == 2)
		{
			((CDrawFont*)pDoc->getDrawBase(select_object_id))->font_str = pMain->m_wndProperties.prop_value;
		}

		//根据Property修改文档中该对象的折线粗细
		if (pMain->m_wndProperties.prop_name == _T("折线粗细") && pDoc->getDrawBase(select_object_id)->shape_type == 3)
		{
			((CDrawPoly*)pDoc->getDrawBase(select_object_id))->solid = pMain->m_wndProperties.prop_value.lVal;
		}


		//根据Property修改文档中该对象的起点和终点坐标
		pDoc->getDrawBase(select_object_id)->m_Start.x = pMain->m_wndProperties.prop_x1.lVal;
		pDoc->getDrawBase(select_object_id)->m_Start.y = pMain->m_wndProperties.prop_y1.lVal;
		pDoc->getDrawBase(select_object_id)->m_End.x = pMain->m_wndProperties.prop_x2.lVal;
		pDoc->getDrawBase(select_object_id)->m_End.y = pMain->m_wndProperties.prop_y2.lVal;

		pMain->m_wndProperties.prop_changed = false;

		select_start.x = 0, select_start.y = 0, select_end.x = 0, select_end.y = 0;
		Invalidate();
	}


	if (select_object==false)
	{
		if (draw_type == 1)
		{
			now->GetEnd(point);
			pDoc->addDrawBase(now);
		}

		if (draw_type == 2)
		{
			pDoc->addDrawBase(now);
		}

		if (draw_type == 3)
		{
			CDC* pDC = GetDC();
			OnDraw(pDC);
		}
	}

}


void CMFCApplication3View::OnShapeRect()
{
	// TODO:  在此添加命令处理程序代码
	draw_type = 1;
}


void CMFCApplication3View::OnUpdateShapeRect(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (draw_type == 1)
		pCmdUI->SetRadio(1);

	else
		pCmdUI->SetRadio(0);
}


void CMFCApplication3View::OnShapeFont()
{
	// TODO:  在此添加命令处理程序代码
	draw_type = 2;

	//Dlg_text *textDlg = new Dlg_text();
	//textDlg->Create(IDD_DIALOG1); //创建一个非模态对话框  
	//textDlg->ShowWindow(SW_SHOWNORMAL);

	//得加回来的
	Dlg_text dlg_text;
	if (IDOK == dlg_text.DoModal())
	{
		//m_strA = dlgB.m_strB;   // m_strA是a编辑框关联的变量，m_strB是b对话框关联的变量
		draw_text=dlg_text.m_edit1;
	}


	
}


void CMFCApplication3View::OnUpdateShapeFont(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (draw_type == 2)
		pCmdUI->SetRadio(1);

	else
		pCmdUI->SetRadio(0);
}


void CMFCApplication3View::OnShapePoly()
{
	// TODO:  在此添加命令处理程序代码
	draw_type = 3;
	now = new CDrawPoly();

	CMFCApplication3Doc* pDoc = GetDocument();
	pDoc->addDrawBase(now);

}


void CMFCApplication3View::OnUpdateShapePoly(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (draw_type == 3)
		pCmdUI->SetRadio(1);

	else
		pCmdUI->SetRadio(0);
}


void CMFCApplication3View::OnSize20()
{
	// TODO:  在此添加命令处理程序代码
	draw_size = 20;
}


void CMFCApplication3View::OnUpdateSize20(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (draw_size == 20)
		pCmdUI->SetRadio(1);

	else
		pCmdUI->SetRadio(0);
}


void CMFCApplication3View::OnSize40()
{
	// TODO:  在此添加命令处理程序代码
	draw_size = 40;
}


void CMFCApplication3View::OnUpdateSize40(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (draw_size == 40)
		pCmdUI->SetRadio(1);

	else
		pCmdUI->SetRadio(0);
}


void CMFCApplication3View::OnSize80()
{
	// TODO:  在此添加命令处理程序代码
	draw_size = 80;
}


void CMFCApplication3View::OnUpdateSize80(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (draw_size == 80)
		pCmdUI->SetRadio(1);

	else
		pCmdUI->SetRadio(0);
}


void CMFCApplication3View::OnSolid2()
{
	// TODO:  在此添加命令处理程序代码
	draw_solid = 2;
}


void CMFCApplication3View::OnUpdateSolid2(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (draw_solid == 2)
		pCmdUI->SetRadio(1);

	else
		pCmdUI->SetRadio(0);
}


void CMFCApplication3View::OnSolid4()
{
	// TODO:  在此添加命令处理程序代码
	draw_solid = 4;
}


void CMFCApplication3View::OnUpdateSolid4(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (draw_solid == 4)
		pCmdUI->SetRadio(1);

	else
		pCmdUI->SetRadio(0);
}


void CMFCApplication3View::OnSolid8()
{
	// TODO:  在此添加命令处理程序代码
	draw_solid = 8;
}


void CMFCApplication3View::OnUpdateSolid8(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (draw_solid == 8)
		pCmdUI->SetRadio(1);

	else
		pCmdUI->SetRadio(0);
}


void CMFCApplication3View::OnColorRed()
{
	// TODO:  在此添加命令处理程序代码
	draw_color = RGB(255, 0, 0);
}


void CMFCApplication3View::OnUpdateColorRed(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (draw_color == RGB(255, 0, 0))
		pCmdUI->SetRadio(1);

	else
		pCmdUI->SetRadio(0);
	
}


void CMFCApplication3View::OnColorGreen()
{
	// TODO:  在此添加命令处理程序代码
	draw_color = RGB(0, 255, 0);
}


void CMFCApplication3View::OnUpdateColorGreen(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (draw_color == RGB(0, 255, 0))
		pCmdUI->SetRadio(1);

	else
		pCmdUI->SetRadio(0);
	
}


void CMFCApplication3View::OnColorBlue()
{
	// TODO:  在此添加命令处理程序代码
	draw_color = RGB(0, 0, 255);
}


void CMFCApplication3View::OnUpdateColorBlue(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (draw_color == RGB(0, 0, 255))
		pCmdUI->SetRadio(1);

	else
		pCmdUI->SetRadio(0);
}


void CMFCApplication3View::OnColorBlack()
{
	// TODO:  在此添加命令处理程序代码
	draw_color = RGB(0, 0, 0);
}


void CMFCApplication3View::OnUpdateColorBlack(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (draw_color == RGB(0, 0, 0))
		pCmdUI->SetRadio(1);

	else
		pCmdUI->SetRadio(0);
}


void CMFCApplication3View::OnSelect()
{
	// TODO:  在此添加命令处理程序代码
	select_object = true;

}


void CMFCApplication3View::OnSelectCancel()
{
	// TODO:  在此添加命令处理程序代码
	select_object = false;

	//取消以前画的选区框
	Invalidate();
}


void CMFCApplication3View::OnUpdateSelect(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (select_object == true)
		pCmdUI->SetRadio(1);
	else
		pCmdUI->SetRadio(0);
}


void CMFCApplication3View::OnUpdateSelectCancel(CCmdUI *pCmdUI)
{
	// TODO:  在此添加命令更新用户界面处理程序代码
	if (select_object == false)
		pCmdUI->SetRadio(1);
	else
		pCmdUI->SetRadio(0);
}


void CMFCApplication3View::OnComb()
{
	// TODO:  在此添加命令处理程序代码
	CMFCApplication3Doc* pDoc = GetDocument();

	if (select_object == true)
	{
		for (int i = 0; i < pDoc->len_drawbase; i++)
		{
			pDoc->getDrawBase(i)->m_Start;

			//if (pDoc->getDrawBase(i)->shape_type == 2)
			//{
			//	CString ss1;
			//	//ss1.Format(_T("%d"), pDoc->getDrawBase(i)->shape_type);//返回列数，也即表中的字段数
			//	ss1 = ((CDrawFont*)(pDoc->getDrawBase(i)))->font_str;
			//	pDC->TextOut(100, 100 + 20 * i, ss1);
			//}

		}
	}

	//pDoc->db.insertRelationQuery("16,C1,C3,18,20", "temp7_relation");

	
}


//如何去得到和修改属性窗口中的值
void CMFCApplication3View::OnUncomb()
{
	// TODO:  在此添加命令处理程序代码
	CMFCPropertyGridProperty * pProp;

	CMainFrame* pMain = (CMainFrame*)AfxGetApp()->m_pMainWnd;


	pProp = pMain->m_wndProperties.m_wndPropList.GetProperty(1)->GetSubItem(0);
	//读取数据
	CString itemname;
	itemname = pProp->GetName(); //获取名称
	COleVariant itemvalue;
	itemvalue = pProp->GetValue();//获取值
	//写入数据
	//pProp->SetValue((_variant_t)_T("*******************************"));
	pProp->SetValue((_variant_t)40l);
}


void CMFCApplication3View::OnLod32812()
{
	// TODO:  在此添加命令处理程序代码
	opengl_view = true;
	Invalidate();
}


void CMFCApplication3View::OnLod32813()
{
	// TODO:  在此添加命令处理程序代码
	opengl_view = false;
	Invalidate();
}



int CMFCApplication3View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


void CMFCApplication3View::OnDestroy()
{
	CView::OnDestroy();

}


