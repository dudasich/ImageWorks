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

// ImageWorksDoc.h : CImageWorksDoc 클래스의 인터페이스
//


#pragma once


class CImageWorksDoc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CImageWorksDoc();
	DECLARE_DYNCREATE(CImageWorksDoc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CImageWorksDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	unsigned char**m_InputImageR, **m_InputImageG, **m_InputImageB;
	unsigned char**m_OutputImageR, **m_OutputImageG, **m_OutputImageB;
	int m_InputHeight, m_InputWidth, m_OutputHeight, m_OutputWidth;
	virtual BOOL OnOpenDocument(LPCTSTR lpszPathName);
	virtual void OnCloseDocument();
	void OnNegativeImage(void);
	void OnBinarization(void);
	void OnHistogramEqual(void);
	void OnHistogramStretch(void);
	void OnHistogramEndInSearch(void);
	void OnAndLogic(void);
	void OnBrightnessPlus(void);
	void OnBrightnessSub(void);
	void OnEmbossing(void);
	double** OnMaskProcessingR(unsigned char** Input, double** Mask, int Size);
	double** m_tempImageR, **m_tempImageG, **m_tempImageB;
	double** OnMaskProcessingG(unsigned char** Input, double** Mask, int Size);
	double** OnMaskProcessingB(unsigned char** Input, double** Mask, int Size);
	void OnOrLogic(void);
	void OnGamma(void);
	void OnBlur(void);
	void OnSharpen(void);
	void OnEqualImage(void);
	void OnSobelmask(void);
	void OnCapParabola(void);
	void OnCupParabola(void);
	void OnCubParabola(void);
	void OnLaplacia(void);
	void OnLapliGau(void);
	void OnZoomin(void);
	void OnZoomout(void);
	unsigned char OnFindMean(double** Mask, int mSize);
	void OnMirrorHor(void);
	void OnMirrorVer(void);
	void OnMirrorHorver(void);
	void OnRotateImage(void);
	void OnHistogramMake(void);
	void OnBrightnessMul(void);
	void OnBrightnessDiv(void);
	virtual BOOL OnSaveDocument(LPCTSTR lpszPathName);
	CImage m_inImage;
	CImage m_outImage;
	void OnHomogen(void);
	double OnFindMaxValue(double** tImage, int x, int y);
};
