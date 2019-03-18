
// MFCApplication3View.h : CMFCApplication3View 类的接口
//

#pragma once


class CMFCApplication3View : public CView
{
protected: // 仅从序列化创建
	CMFCApplication3View();
	DECLARE_DYNCREATE(CMFCApplication3View)

// 特性
public:
	CMFCApplication3Doc* GetDocument() const;

// 操作
public:
	CDrawBase* now;

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

	int draw_time;
	int draw_type;
	COLORREF draw_color;
	int draw_size;
	int draw_solid;
	CString draw_text;
	CPoint* draw_point[100000];
	int draw_point_len;

	//用于opengl显示
	bool opengl_view;
	//用于选区操作
	bool select_object;
	CPoint select_start;
	CPoint select_end;

	//被框选的对象id
	int select_object_id;



protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);


// 实现
public:
	virtual ~CMFCApplication3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnShapeRect();
	afx_msg void OnUpdateShapeRect(CCmdUI *pCmdUI);
	afx_msg void OnShapeFont();
	afx_msg void OnUpdateShapeFont(CCmdUI *pCmdUI);
	afx_msg void OnShapePoly();
	afx_msg void OnUpdateShapePoly(CCmdUI *pCmdUI);
	afx_msg void OnSize20();
	afx_msg void OnUpdateSize20(CCmdUI *pCmdUI);
	afx_msg void OnSize40();
	afx_msg void OnUpdateSize40(CCmdUI *pCmdUI);
	afx_msg void OnSize80();
	afx_msg void OnUpdateSize80(CCmdUI *pCmdUI);
	afx_msg void OnSolid2();
	afx_msg void OnUpdateSolid2(CCmdUI *pCmdUI);
	afx_msg void OnSolid4();
	afx_msg void OnUpdateSolid4(CCmdUI *pCmdUI);
	afx_msg void OnSolid8();
	afx_msg void OnUpdateSolid8(CCmdUI *pCmdUI);
	afx_msg void OnColorRed();
	afx_msg void OnUpdateColorRed(CCmdUI *pCmdUI);
	afx_msg void OnColorGreen();
	afx_msg void OnUpdateColorGreen(CCmdUI *pCmdUI);
	afx_msg void OnColorBlue();
	afx_msg void OnUpdateColorBlue(CCmdUI *pCmdUI);
	afx_msg void OnColorBlack();
	afx_msg void OnUpdateColorBlack(CCmdUI *pCmdUI);
	afx_msg void OnSelect();
	afx_msg void OnSelectCancel();
	afx_msg void OnUpdateSelect(CCmdUI *pCmdUI);
	afx_msg void OnUpdateSelectCancel(CCmdUI *pCmdUI);
	afx_msg void OnComb();
	afx_msg void OnUncomb();
	afx_msg void OnLod32812();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnLod32813();
	
};

#ifndef _DEBUG  // MFCApplication3View.cpp 中的调试版本
inline CMFCApplication3Doc* CMFCApplication3View::GetDocument() const
   { return reinterpret_cast<CMFCApplication3Doc*>(m_pDocument); }
#endif

