// �� MFC ���� �ҽ� �ڵ�� MFC Microsoft Office Fluent ����� �������̽�("Fluent UI")�� 
// ����ϴ� ����� ���� �ָ�, MFC C++ ���̺귯�� ����Ʈ��� ���Ե� 
// Microsoft Foundation Classes Reference �� ���� ���� ������ ���� 
// �߰������� �����Ǵ� �����Դϴ�.  
// Fluent UI�� ����, ��� �Ǵ� �����ϴ� �� ���� ��� ����� ������ �����˴ϴ�.  
// Fluent UI ���̼��� ���α׷��� ���� �ڼ��� ������ 
// http://go.microsoft.com/fwlink/?LinkId=238214.
//
// Copyright (C) Microsoft Corporation
// All rights reserved.

// ImageWorksView.cpp : CImageWorksView Ŭ������ ����
//

#include "stdafx.h"
// SHARED_HANDLERS�� �̸� ����, ����� �׸� �� �˻� ���� ó���⸦ �����ϴ� ATL ������Ʈ���� ������ �� ������
// �ش� ������Ʈ�� ���� �ڵ带 �����ϵ��� �� �ݴϴ�.
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
	// ǥ�� �μ� ����Դϴ�.
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

// CImageWorksView ����/�Ҹ�

CImageWorksView::CImageWorksView()
{
	// TODO: ���⿡ ���� �ڵ带 �߰��մϴ�.

}

CImageWorksView::~CImageWorksView()
{
}

BOOL CImageWorksView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs�� �����Ͽ� ���⿡��
	//  Window Ŭ���� �Ǵ� ��Ÿ���� �����մϴ�.

	return CView::PreCreateWindow(cs);
}

// CImageWorksView �׸���

void CImageWorksView::OnDraw(CDC* pDC)
{
	CImageWorksDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: ���⿡ ���� �����Ϳ� ���� �׸��� �ڵ带 �߰��մϴ�.
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


// CImageWorksView �μ�


void CImageWorksView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CImageWorksView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// �⺻���� �غ�
	return DoPreparePrinting(pInfo);
}

void CImageWorksView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ��ϱ� ���� �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
}

void CImageWorksView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: �μ� �� ���� �۾��� �߰��մϴ�.
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


// CImageWorksView ����

#ifdef _DEBUG
void CImageWorksView::AssertValid() const
{
	CView::AssertValid();
}

void CImageWorksView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImageWorksDoc* CImageWorksView::GetDocument() const // ����׵��� ���� ������ �ζ������� �����˴ϴ�.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImageWorksDoc)));
	return (CImageWorksDoc*)m_pDocument;
}
#endif //_DEBUG


// CImageWorksView �޽��� ó����


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
