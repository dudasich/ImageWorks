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

// ImageWorksView.h : CImageWorksView Ŭ������ �������̽�
//

#pragma once


class CImageWorksView : public CView
{
protected: // serialization������ ��������ϴ�.
	CImageWorksView();
	DECLARE_DYNCREATE(CImageWorksView)

// Ư���Դϴ�.
public:
	CImageWorksDoc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CImageWorksView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBrightnessPlus();
	afx_msg void OnBrightnessSub();
	afx_msg void OnNegativeImage();
	afx_msg void OnBinarization();
	afx_msg void OnHistogramEqual();
	afx_msg void OnHistogramStretch();
	afx_msg void OnHistogramEndInSearch();
	void OnDoubleBuffer(CDC* pDC);
	afx_msg void OnAndLogic();
	afx_msg void OnEmbossing();
	afx_msg void OnOrLogic();
	afx_msg void OnGamma();
	afx_msg void OnBlur();
	afx_msg void OnSharpen();
	afx_msg void OnEqulImage();
	afx_msg void OnSobelmask();
	afx_msg void OnCapParabola();
	afx_msg void OnCubParabola();
	afx_msg void OnLaplacian();
	afx_msg void OnLog();
	afx_msg void OnLaplacia();
	afx_msg void OnLapliGau();
	afx_msg void OnZoomin();
	afx_msg void OnZoomout();
	afx_msg void OnMoveImage();
	afx_msg void OnMirrorHor();
	afx_msg void OnMirrorVer();
	afx_msg void OnMirrorHorver();
	afx_msg void OnRotateImage();
	afx_msg void OnHistogramMake();
	afx_msg void OnBrightnessMul();
	afx_msg void OnBrightnessDiv();
	afx_msg void OnRangeHighright();
	afx_msg void OnHomogen();
	afx_msg void OnDivBrightness();
};

#ifndef _DEBUG  // ImageWorksView.cpp�� ����� ����
inline CImageWorksDoc* CImageWorksView::GetDocument() const
   { return reinterpret_cast<CImageWorksDoc*>(m_pDocument); }
#endif

