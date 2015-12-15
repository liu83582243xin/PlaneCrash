
// PlaneCrashView.h : CPlaneCrashView 类的接口
//

#pragma once


class CPlaneCrashView : public CView
{
protected: // 仅从序列化创建
	CPlaneCrashView();
	DECLARE_DYNCREATE(CPlaneCrashView)

// 特性
public:
	CPlaneCrashDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CPlaneCrashView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	int offsetX;
	int offsetY;
	CRect m_client;
	CImage m_background;

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // PlaneCrashView.cpp 中的调试版本
inline CPlaneCrashDoc* CPlaneCrashView::GetDocument() const
   { return reinterpret_cast<CPlaneCrashDoc*>(m_pDocument); }
#endif

