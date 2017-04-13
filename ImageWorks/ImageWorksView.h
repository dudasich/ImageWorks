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

// ImageWorksView.h : CImageWorksView 클래스의 인터페이스
//

#pragma once


class CImageWorksView : public CView
{
protected: // serialization에서만 만들어집니다.
	CImageWorksView();
	DECLARE_DYNCREATE(CImageWorksView)

// 특성입니다.
public:
	CImageWorksDoc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 구현입니다.
public:
	virtual ~CImageWorksView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
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

#ifndef _DEBUG  // ImageWorksView.cpp의 디버그 버전
inline CImageWorksDoc* CImageWorksView::GetDocument() const
   { return reinterpret_cast<CImageWorksDoc*>(m_pDocument); }
#endif

