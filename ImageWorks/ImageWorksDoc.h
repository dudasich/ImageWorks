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

// ImageWorksDoc.h : CImageWorksDoc Ŭ������ �������̽�
//


#pragma once


class CImageWorksDoc : public CDocument
{
protected: // serialization������ ��������ϴ�.
	CImageWorksDoc();
	DECLARE_DYNCREATE(CImageWorksDoc)

// Ư���Դϴ�.
public:

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// �����Դϴ�.
public:
	virtual ~CImageWorksDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// �˻� ó���⿡ ���� �˻� �������� �����ϴ� ����� �Լ�
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
