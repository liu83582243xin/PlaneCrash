
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
}

CPlaneCrashView::~CPlaneCrashView()
{
}

BOOL CPlaneCrashView::PreCreateWindow(CREATESTRUCT& cs)
{
	m_background.LoadFromResource(AfxGetInstanceHandle(), IDB_BG2);
	m_bgOffsetY = 0;

	//pMemCacheDc = new CDC;

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
	m_cachedMap.CreateCompatibleBitmap(pDC, m_client.Width(), 1000);
	m_cachedDc.SelectObject(&m_cachedMap);
	if (m_bgOffsetY >= 0)
	{
		m_background.Draw(m_cachedDc, 0 ,0,m_client.Width(),m_client.Height(),0,m_bgOffsetY,m_client.Width(),500);
		m_bgOffsetY -= 1;
	}
	else
	{
		m_bgOffsetY = 500;
	}



	//this->myPlane.Draw(&m_cachedDc, m_client);
	//mPlaneEnyne.Draw(&m_cachedDc, m_client);
	//mPlaneBoss.Draw(&m_cachedDc, m_client);
	mGm.drawGameObjects(&m_cachedDc,m_client);

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
	mGm.create();
	Invalidate();
	CView::OnTimer(nIDEvent);
}



int CPlaneCrashView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	PlaneEnyne::loadImage();
	PlaneBoss::loadImage();
	Explosion::loadImage();
	Ball::loadImage();
	Bomb::loadImage();


	SetTimer(1,	30 , NULL);

	return 0;
}


void CPlaneCrashView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case VK_UP: 
		mGm.getPlayer()->moveUp();
		break;
	case VK_DOWN:
		mGm.getPlayer()->moveDown();
		break;
	case VK_LEFT:
		mGm.getPlayer()->moveLeft();
		break;
	case VK_RIGHT:
		mGm.getPlayer()->moveRight();
		break;
	case VK_SPACE:
		mGm.createBomb();
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
