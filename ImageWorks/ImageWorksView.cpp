// 이 MFC 샘플 소스 코드는 MFC Microsoft Office Fluent 사용자 인터페이스("Fluent UI")를 
// 사용하는 방법을 보여 주며, MFC C++ 라이브러리 소프트웨어에 포함된 
// Microsoft Foundation Classes Reference 및 관련 전자 문서에 대해 
// 추가적으로 제공되는 내용입니다.  
// Fluent UI를 복사, 사용 또는 배포하는 데 대한 사용 약관은 별도로 제공됩니다.  
// Fluent UI 라이선싱 프로그램에 대한 자세한 내용은 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// ImageWorksView.cpp : CImageWorksView 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageWorks.h"
#endif

#include "ImageWorksDoc.h"
#include "ImageWorksView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImageWorksView

IMPLEMENT_DYNCREATE(CImageWorksView, CView)

BEGIN_MESSAGE_MAP(CImageWorksView, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CImageWorksView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BRIGHTNESS_PLUS, &CImageWorksView::OnBrightnessPlus)
	ON_COMMAND(ID_NEGATIVE_IMAGE, &CImageWorksView::OnNegativeImage)
	ON_COMMAND(ID_BINARIZATION, &CImageWorksView::OnBinarization)
	ON_COMMAND(ID_HISTOGRAM_EQUAL, &CImageWorksView::OnHistogramEqual)
	ON_COMMAND(ID_HISTOGRAM_STRETCH, &CImageWorksView::OnHistogramStretch)
	ON_COMMAND(ID_HISTOGRAM_END_IN_SEARCH, &CImageWorksView::OnHistogramEndInSearch)
	ON_COMMAND(ID_AND_LOGIC, &CImageWorksView::OnAndLogic)
	ON_COMMAND(ID_BRIGHTNESS_SUB, &CImageWorksView::OnBrightnessSub)
	ON_COMMAND(ID_EMBOSSING, &CImageWorksView::OnEmbossing)
	ON_COMMAND(ID_OR_LOGIC, &CImageWorksView::OnOrLogic)
	ON_COMMAND(ID_GAMMA, &CImageWorksView::OnGamma)
	ON_COMMAND(ID_BLUR, &CImageWorksView::OnBlur)
	ON_COMMAND(ID_SHARPEN, &CImageWorksView::OnSharpen)
	ON_COMMAND(ID_EQUL_IMAGE, &CImageWorksView::OnEqulImage)
	ON_COMMAND(ID_SOBELMASK, &CImageWorksView::OnSobelmask)
	ON_COMMAND(ID_CAP_PARABOLA, &CImageWorksView::OnCapParabola)
	ON_COMMAND(ID_CUB_PARABOLA, &CImageWorksView::OnCubParabola)
	ON_COMMAND(ID_LAPLACIA, &CImageWorksView::OnLaplacia)
	ON_COMMAND(ID_LAPLI_GAU, &CImageWorksView::OnLapliGau)
	ON_COMMAND(ID_ZOOMIN, &CImageWorksView::OnZoomin)
	ON_COMMAND(ID_ZOOMOUT, &CImageWorksView::OnZoomout)
	ON_COMMAND(ID_MIRROR_HOR, &CImageWorksView::OnMirrorHor)
	ON_COMMAND(ID_MIRROR_VER, &CImageWorksView::OnMirrorVer)
	ON_COMMAND(ID_MIRROR_HORVER, &CImageWorksView::OnMirrorHorver)
	ON_COMMAND(ID_ROTATE_IMAGE, &CImageWorksView::OnRotateImage)
	ON_COMMAND(ID_HISTOGRAM_MAKE, &CImageWorksView::OnHistogramMake)
	ON_COMMAND(ID_HOMOGEN, &CImageWorksView::OnHomogen)
END_MESSAGE_MAP()

// CImageWorksView 생성/소멸

CImageWorksView::CImageWorksView()
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CImageWorksView::~CImageWorksView()
{
}

BOOL CImageWorksView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CImageWorksView 그리기

void CImageWorksView::OnDraw(CDC* pDC)
{
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CDC* mDC = GetDC();

	CRect rect;
	GetClientRect(&rect);

	CDC MemDC;
	CBitmap* pOldBmp;
	CBitmap Bitmap;

	MemDC.CreateCompatibleDC(mDC);
	Bitmap.CreateCompatibleBitmap(mDC, rect.Width(), rect.Height());
	pOldBmp = (CBitmap *)MemDC.SelectObject(&Bitmap);
	MemDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

	OnDoubleBuffer(&MemDC);

	mDC->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);

	MemDC.SelectObject(pOldBmp);
	MemDC.DeleteDC();
}


// CImageWorksView 인쇄


void CImageWorksView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageWorksView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CImageWorksView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CImageWorksView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}

void CImageWorksView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CImageWorksView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CImageWorksView 진단

#ifdef _DEBUG
void CImageWorksView::AssertValid() const
{
	CView::AssertValid();
}

void CImageWorksView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageWorksDoc* CImageWorksView::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageWorksDoc)));
	return (CImageWorksDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageWorksView 메시지 처리기


void CImageWorksView::OnBrightnessPlus()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBrightnessPlus();
	Invalidate(FALSE);
}


void CImageWorksView::OnBrightnessSub()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBrightnessSub();
	Invalidate(FALSE);
}


void CImageWorksView::OnNegativeImage()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	pDoc->OnNegativeImage();
	Invalidate(FALSE);
}


void CImageWorksView::OnBinarization()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	pDoc->OnBinarization();
	Invalidate(FALSE);
}


void CImageWorksView::OnHistogramEqual()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	pDoc->OnHistogramEqual();
	Invalidate(FALSE);
}


void CImageWorksView::OnHistogramStretch()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	pDoc->OnHistogramStretch();
	Invalidate(FALSE);
}


void CImageWorksView::OnHistogramEndInSearch()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	
	pDoc->OnHistogramEndInSearch();
	Invalidate(FALSE);
}


void CImageWorksView::OnDoubleBuffer(CDC* pDC)
{
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	int i, j;
	unsigned char R, G, B;
	// Input
	for(i=0; i<pDoc->m_InputHeight; i++){
		for(j=0; j<pDoc->m_InputWidth; j++){
			R = pDoc->m_InputImageR[i][j];
			G = pDoc->m_InputImageG[i][j];
			B = pDoc->m_InputImageB[i][j];

			pDC->SetPixel(j+5, i+5, RGB(R, G, B));
		}
	}

	// Output
	for(i=0; i<pDoc->m_OutputHeight; i++){
		for(j=0; j<pDoc->m_OutputWidth; j++){
			R = pDoc->m_OutputImageR[i][j];
			G = pDoc->m_OutputImageG[i][j];
			B = pDoc->m_OutputImageB[i][j];

			pDC->SetPixel(j+10+pDoc->m_InputWidth, i+5, RGB(R, G, B));
		}
	}
}


void CImageWorksView::OnAndLogic()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnAndLogic();
	Invalidate(FALSE);
}


void CImageWorksView::OnEmbossing()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnEmbossing();
	Invalidate(FALSE);
}


void CImageWorksView::OnOrLogic()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnOrLogic();
	Invalidate(FALSE);
}


void CImageWorksView::OnGamma()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnGamma();
	Invalidate(FALSE);
}


void CImageWorksView::OnBlur()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnBlur();
	Invalidate(FALSE);
}


void CImageWorksView::OnSharpen()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnSharpen();
	Invalidate(FALSE);
}


void CImageWorksView::OnEqulImage()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnEqualImage();
	Invalidate(FALSE);
}


void CImageWorksView::OnSobelmask()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnSobelmask();
	Invalidate(FALSE);
}


void CImageWorksView::OnCapParabola()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnCapParabola();
	Invalidate(FALSE);
}


void CImageWorksView::OnCubParabola()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnCubParabola();
	Invalidate(FALSE);
}



void CImageWorksView::OnLaplacia()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnLaplacia();
	Invalidate(FALSE);
}


void CImageWorksView::OnLapliGau()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnLapliGau();
	Invalidate(FALSE);
}


void CImageWorksView::OnZoomin()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnZoomin();
	Invalidate(FALSE);
}


void CImageWorksView::OnZoomout()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnZoomout();
	Invalidate(FALSE);
}



void CImageWorksView::OnMirrorHor()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnMirrorHor();
	Invalidate(FALSE);
}


void CImageWorksView::OnMirrorVer()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnMirrorVer();
	Invalidate(FALSE);
}


void CImageWorksView::OnMirrorHorver()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnMirrorHorver();
	Invalidate(FALSE);
}


void CImageWorksView::OnRotateImage()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnRotateImage();
	Invalidate(FALSE);
}


void CImageWorksView::OnHistogramMake()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnHistogramMake();
	Invalidate(FALSE);
}


void CImageWorksView::OnHomogen()
{
	// TODO: Add your command handler code here
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	pDoc->OnHomogen();
	Invalidate(FALSE);
}
