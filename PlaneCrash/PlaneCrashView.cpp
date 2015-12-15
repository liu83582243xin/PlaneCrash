
// PlaneCrashView.cpp : CPlaneCrashView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "PlaneCrash.h"
#endif

#include "PlaneCrashDoc.h"
#include "PlaneCrashView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPlaneCrashView

IMPLEMENT_DYNCREATE(CPlaneCrashView, CView)

BEGIN_MESSAGE_MAP(CPlaneCrashView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_CREATE()
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CPlaneCrashView 构造/析构

CPlaneCrashView::CPlaneCrashView()
{
	this->offsetX = 100;
	this->offsetY = 100;
}

CPlaneCrashView::~CPlaneCrashView()
{
}

BOOL CPlaneCrashView::PreCreateWindow(CREATESTRUCT& cs)
{
	m_background.Load(_T("res\\bg.png"));
	return CView::PreCreateWindow(cs);
}

// CPlaneCrashView 绘制

void CPlaneCrashView::OnDraw(CDC* pDC)
{
	CPlaneCrashDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	GetClientRect(&this->m_client);
	CDC m_cachedDc;
	CBitmap m_cachedMap;
	m_cachedDc.CreateCompatibleDC(pDC);
	m_cachedMap.CreateCompatibleBitmap(pDC, m_client.Width(), m_client.Height());
	m_cachedDc.SelectObject(&m_cachedMap);

	m_background.Draw(m_cachedDc, m_client);

	CBitmap bitmap;
	bitmap.LoadBitmapW(IDB_ME);

	CImageList imageList;
	imageList.Create(50, 60, ILC_COLOR8 | ILC_MASK, 1, 0);
	imageList.Add(&bitmap, RGB(0, 0, 0));
	imageList.Draw(&m_cachedDc, 0, CPoint(this->offsetX, this->offsetY), ILD_NORMAL);

	pDC->BitBlt(0, 0, m_client.Width(), m_client.Height(), &m_cachedDc, 0, 0, SRCCOPY);

	ValidateRect(&m_client);
	ReleaseDC(&m_cachedDc);
}


// CPlaneCrashView 打印

BOOL CPlaneCrashView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CPlaneCrashView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CPlaneCrashView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CPlaneCrashView 诊断

#ifdef _DEBUG
void CPlaneCrashView::AssertValid() const
{
	CView::AssertValid();
}

void CPlaneCrashView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPlaneCrashDoc* CPlaneCrashView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPlaneCrashDoc)));
	return (CPlaneCrashDoc*)m_pDocument;
}
#endif //_DEBUG


// CPlaneCrashView 消息处理程序


void CPlaneCrashView::OnTimer(UINT_PTR nIDEvent)
{
	Invalidate();
	CView::OnTimer(nIDEvent);
}



int CPlaneCrashView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;


	SetTimer(1,	16, NULL);

	return 0;
}


void CPlaneCrashView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_UP: 
		this->offsetY -= 10;
		break;
	case VK_DOWN:
		this->offsetY += 10;
		break;
	case VK_LEFT:
		this->offsetX -= 10;
		break;
	case VK_RIGHT:
		this->offsetX += 10;
		break;
	default:
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


BOOL CPlaneCrashView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	return true;
	//return CView::OnEraseBkgnd(pDC);
}
