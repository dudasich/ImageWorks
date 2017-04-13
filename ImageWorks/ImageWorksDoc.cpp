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

// ImageWorksDoc.cpp : CImageWorksDoc 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "ImageWorks.h"
#endif

#include "ImageWorksDoc.h"
#include "RGBEditDlg.h"
#include "ValueDlg.h"
#include "RotateDlg.h"
#include "math.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// Define MIN value, MAX value
#define MIN 0
#define MAX 255

// CImageWorksDoc

IMPLEMENT_DYNCREATE(CImageWorksDoc, CDocument)

BEGIN_MESSAGE_MAP(CImageWorksDoc, CDocument)
END_MESSAGE_MAP()


// CImageWorksDoc 생성/소멸

CImageWorksDoc::CImageWorksDoc()
	: m_InputImageR(NULL)
	, m_tempImageR(NULL)
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CImageWorksDoc::~CImageWorksDoc()
{
}

BOOL CImageWorksDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CImageWorksDoc serialization

void CImageWorksDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CImageWorksDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CImageWorksDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CImageWorksDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = NULL;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != NULL)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CImageWorksDoc 진단

#ifdef _DEBUG
void CImageWorksDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CImageWorksDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CImageWorksDoc 명령


BOOL CImageWorksDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;

	// TODO:  Add your specialized creation code here
	/*CFile File;
	File.Open(lpszPathName, CFile::modeRead | CFile::typeBinary);

	File.Close();*/
	
	int i, j;

	m_inImage.Load(lpszPathName);

	m_InputHeight = m_inImage.GetHeight();
	m_InputWidth = m_inImage.GetWidth();

	m_InputImageR = new unsigned char *[m_InputHeight];
	m_InputImageG = new unsigned char *[m_InputHeight];
	m_InputImageB = new unsigned char *[m_InputHeight];
	for(i=0; i<m_InputHeight; i++){
		m_InputImageR[i] = new unsigned char [m_InputWidth];
		m_InputImageG[i] = new unsigned char [m_InputWidth];
		m_InputImageB[i] = new unsigned char [m_InputWidth];
	}

	COLORREF pixel;
	for(i=0; i<m_InputHeight; i++){
		for(j=0; j<m_InputWidth; j++){
			pixel = m_inImage.GetPixel(j, i);
			m_InputImageR[i][j] = (unsigned char)GetRValue(pixel);
			m_InputImageG[i][j] = (unsigned char)GetGValue(pixel);
			m_InputImageB[i][j] = (unsigned char)GetBValue(pixel);
		}
	}

	return TRUE;
}


void CImageWorksDoc::OnCloseDocument()
{
	// TODO: Add your specialized code here and/or call the base class
	int i;

	for(i=0; i<m_InputHeight; i++){
		delete m_InputImageR[i];
	}
	delete m_InputImageR;

	for(i=0; i<m_InputHeight; i++){
		delete m_InputImageG[i];
	}
	delete m_InputImageG;

	for(i=0; i<m_InputHeight; i++){
		delete m_InputImageB[i];
	}
	delete m_InputImageB;

	if(m_OutputImageR != NULL){
		for(i=0; i<m_OutputHeight; i++){
			delete m_OutputImageR[i];
		}
		delete m_OutputImageR;
	}

	if(m_OutputImageG != NULL){
		for(i=0; i<m_OutputHeight; i++){
			delete m_OutputImageG[i];
		}
		delete m_OutputImageG;
	}

	if(m_OutputImageB != NULL){
		for(i=0; i<m_OutputHeight; i++){
			delete m_OutputImageB[i];
		}
		delete m_OutputImageB;
	}

	CDocument::OnCloseDocument();
}


void CImageWorksDoc::OnBrightnessPlus(void)
{
	CRGBEditDlg dlg;
	if(dlg.DoModal() == IDOK){
		int i, j;
		int tempR, tempG, tempB;

		m_OutputHeight = m_InputHeight;
		m_OutputWidth = m_InputWidth;

		m_OutputImageR = new unsigned char *[m_OutputHeight];
		m_OutputImageG = new unsigned char *[m_OutputHeight];
		m_OutputImageB = new unsigned char *[m_OutputHeight];
		for(i=0; i<m_OutputHeight; i++){
			m_OutputImageR[i] = new unsigned char [m_OutputWidth];
			m_OutputImageG[i] = new unsigned char [m_OutputWidth];
			m_OutputImageB[i] = new unsigned char [m_OutputWidth];
		}
		
		m_outImage.Create(m_OutputHeight, m_OutputWidth,32,0);

		for(i=0; i<m_OutputHeight; i++){
			for(j=0; j<m_OutputWidth; j++){

				tempR = m_InputImageR[i][j] + (int)dlg.m_EditRed;
				tempG = m_InputImageG[i][j] + (int)dlg.m_EditGreen;
				tempB = m_InputImageB[i][j] + (int)dlg.m_EditBlue;
			
				if(tempR > MAX){
					m_OutputImageR[i][j] = MAX;
				}
				else if(tempR < MIN){
					m_OutputImageR[i][j] = MIN;
				}
				else{
					m_OutputImageR[i][j] = tempR;
				}
				
				if(tempG > MAX){
					m_OutputImageG[i][j] = MAX;
				}
				else if(tempG < MIN){
					m_OutputImageG[i][j] = MIN;
				}
				else{
					m_OutputImageG[i][j] = tempG;
				}

				if(tempB > MAX){
					m_OutputImageB[i][j] = MAX;
				}
				else if(tempB < MIN){
					m_OutputImageB[i][j] = MIN;
				}
				else{
					m_OutputImageB[i][j] = tempB;
				}
				m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
			}
		}
	}
}


void CImageWorksDoc::OnBrightnessSub(void)
{
	CRGBEditDlg dlg;
	if(dlg.DoModal() == IDOK){
		int i, j;
		int tempR, tempG, tempB;

		m_OutputHeight = m_InputHeight;
		m_OutputWidth = m_InputWidth;

		m_OutputImageR = new unsigned char *[m_OutputHeight];
		m_OutputImageG = new unsigned char *[m_OutputHeight];
		m_OutputImageB = new unsigned char *[m_OutputHeight];
		for(i=0; i<m_OutputHeight; i++){
			m_OutputImageR[i] = new unsigned char [m_OutputWidth];
			m_OutputImageG[i] = new unsigned char [m_OutputWidth];
			m_OutputImageB[i] = new unsigned char [m_OutputWidth];
		}

		m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

		for(i=0; i<m_OutputHeight; i++){
			for(j=0; j<m_OutputWidth; j++){

				tempR = m_InputImageR[i][j] - (int)dlg.m_EditRed;
				tempG = m_InputImageG[i][j] - (int)dlg.m_EditGreen;
				tempB = m_InputImageB[i][j] - (int)dlg.m_EditBlue;
			
				if(tempR > MAX){
					m_OutputImageR[i][j] = MAX;
				}
				else if(tempR < MIN){
					m_OutputImageR[i][j] = MIN;
				}
				else{
					m_OutputImageR[i][j] = tempR;
				}
				
				if(tempG > MAX){
					m_OutputImageG[i][j] = MAX;
				}
				else if(tempG < MIN){
					m_OutputImageG[i][j] = MIN;
				}
				else{
					m_OutputImageG[i][j] = tempG;
				}

				if(tempB > MAX){
					m_OutputImageB[i][j] = MAX;
				}
				else if(tempB < MIN){
					m_OutputImageB[i][j] = MIN;
				}
				else{
					m_OutputImageB[i][j] = tempB;
				}
				m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
			}
		}
	}
}


void CImageWorksDoc::OnNegativeImage(void)
{
	int i, j;
	int tempR, tempG, tempB;

	m_OutputHeight = m_InputHeight;
	m_OutputWidth = m_InputWidth;

	m_OutputImageR = new unsigned char *[m_OutputHeight];
	m_OutputImageG = new unsigned char *[m_OutputHeight];
	m_OutputImageB = new unsigned char *[m_OutputHeight];
	for(i=0; i<m_OutputHeight; i++){
		m_OutputImageR[i] = new unsigned char [m_OutputWidth];
		m_OutputImageG[i] = new unsigned char [m_OutputWidth];
		m_OutputImageB[i] = new unsigned char [m_OutputWidth];
	}

	m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			tempR = MAX - m_InputImageR[i][j];
			tempG = MAX - m_InputImageG[i][j];
			tempB = MAX - m_InputImageB[i][j];

			if(tempR < MIN || tempG < MIN || tempB < MIN){
				m_OutputImageR[i][j] = MIN;
				m_OutputImageG[i][j] = MIN;
				m_OutputImageB[i][j] = MIN;
			}
			else{
				m_OutputImageR[i][j] = tempR;
				m_OutputImageG[i][j] = tempG;
				m_OutputImageB[i][j] = tempB;
			}
			m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
		}
	}
}


void CImageWorksDoc::OnBinarization(void)
{
	CValueDlg dlg;

	if(dlg.DoModal() == IDOK){
		int i, j;

		m_OutputHeight = m_InputHeight;
		m_OutputWidth = m_InputWidth;

		m_OutputImageR = new unsigned char *[m_OutputHeight];
		m_OutputImageG = new unsigned char *[m_OutputHeight];
		m_OutputImageB = new unsigned char *[m_OutputHeight];
		for(i=0; i<m_OutputHeight; i++){
			m_OutputImageR[i] = new unsigned char [m_OutputWidth];
			m_OutputImageG[i] = new unsigned char [m_OutputWidth];
			m_OutputImageB[i] = new unsigned char [m_OutputWidth];
		}

		//m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

		for(i=0; i<m_OutputHeight; i++){
			for(j=0; j<m_OutputWidth; j++){
				if(m_InputImageR[i][j] < dlg.m_EditValue){
					m_OutputImageR[i][j] = MIN;
				}
				else{
					m_OutputImageR[i][j] = MAX;
				}
				// ImageG
				if(m_InputImageG[i][j] < dlg.m_EditValue){
					m_OutputImageG[i][j] = MIN;
				}
				else{
					m_OutputImageG[i][j] = MAX;
				}
				// ImageB
				if(m_InputImageB[i][j] < dlg.m_EditValue){
					m_OutputImageB[i][j] = MIN;
				}
				else{
					m_OutputImageB[i][j] = MAX;
				}
				//m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
			}
		}
	}
}

// Histogram global values
double m_HistR[256], m_HistG[256], m_HistB[256];
double m_SumOfHistR[256], m_SumOfHistG[256], m_SumOfHistB[256];
unsigned char m_ScaleHistR[256], m_ScaleHistG[256], m_ScaleHistB[256];

void CImageWorksDoc::OnHistogramEqual(void)
{
	int i, j, valueR, valueG, valueB;
	double SUM[3] = {0.0, };
	unsigned char tempR, tempG, tempB;

	m_OutputHeight = m_InputHeight;
	m_OutputWidth = m_InputWidth;

	m_OutputImageR = new unsigned char *[m_OutputHeight];
	m_OutputImageG = new unsigned char *[m_OutputHeight];
	m_OutputImageB = new unsigned char *[m_OutputHeight];
	for(i=0; i<m_OutputHeight; i++){
		m_OutputImageR[i] = new unsigned char [m_OutputWidth];
		m_OutputImageG[i] = new unsigned char [m_OutputWidth];
		m_OutputImageB[i] = new unsigned char [m_OutputWidth];
	}

	m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

	for(i=0; i<256; i++){
		m_HistR[i] = 0;
		m_HistG[i] = 0;
		m_HistB[i] = 0;
	}

	for(i=0; i<m_InputHeight; i++){
		for(j=0; j<m_InputWidth; j++){
			valueR = m_InputImageR[i][j];
			valueG = m_InputImageG[i][j];
			valueB = m_InputImageB[i][j];

			m_HistR[valueR]++;
			m_HistG[valueG]++;
			m_HistB[valueB]++;
		}
	}
	// SUM[0] = R, SUM[1] = G, SUM[2] = B
	for(i=0; i<256; i++){
		SUM[0] += m_HistR[i];
		SUM[1] += m_HistG[i];
		SUM[2] += m_HistB[i];

		m_SumOfHistR[i] = SUM[0];
		m_SumOfHistG[i] = SUM[1];
		m_SumOfHistB[i] = SUM[2];
	}

	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			tempR = m_InputImageR[i][j];
			tempG = m_InputImageG[i][j];
			tempB = m_InputImageB[i][j];

			m_OutputImageR[i][j] = (unsigned char)(m_SumOfHistR[tempR] * 255 / (m_InputHeight * m_InputWidth));
			m_OutputImageG[i][j] = (unsigned char)(m_SumOfHistG[tempG] * 255 / (m_InputHeight * m_InputWidth));
			m_OutputImageB[i][j] = (unsigned char)(m_SumOfHistB[tempB] * 255 / (m_InputHeight * m_InputWidth));

			m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
		}
	}
}


void CImageWorksDoc::OnHistogramStretch(void)
{
	int i, j;
	unsigned char minR, minG, minB;
	unsigned char maxR, maxG, maxB;

	m_OutputHeight = m_InputHeight;
	m_OutputWidth = m_InputWidth;

	m_OutputImageR = new unsigned char *[m_OutputHeight];
	m_OutputImageG = new unsigned char *[m_OutputHeight];
	m_OutputImageB = new unsigned char *[m_OutputHeight];
	for(i=0; i<m_OutputHeight; i++){
		m_OutputImageR[i] = new unsigned char [m_OutputWidth];
		m_OutputImageG[i] = new unsigned char [m_OutputWidth];
		m_OutputImageB[i] = new unsigned char [m_OutputWidth];
	}

	m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

	minR = m_InputImageR[0][0];
	minG = m_InputImageG[0][0];
	minB = m_InputImageB[0][0];

	maxR = m_InputImageR[0][0];
	maxG = m_InputImageG[0][0];
	maxB = m_InputImageB[0][0];

	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			if(m_InputImageR[i][j] > maxR){
				maxR = m_InputImageR[i][j];
			}
			else if(m_InputImageR[i][j] < minR){
				minR = m_InputImageR[i][j];
			}

			if(m_InputImageG[i][j] > maxG){
				maxG = m_InputImageG[i][j];
			}
			else if(m_InputImageG[i][j] < minG){
				minG = m_InputImageG[i][j];
			}

			if(m_InputImageB[i][j] > maxB){
				maxB = m_InputImageB[i][j];
			}
			else if(m_InputImageB[i][j] < minB){
				minB = m_InputImageB[i][j];
			}
		}
	}

	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			m_OutputImageR[i][j] = ((m_InputImageR[i][j] - minR) * 255) / (maxR - minR);
			m_OutputImageG[i][j] = ((m_InputImageG[i][j] - minG) * 255) / (maxG - minG);
			m_OutputImageB[i][j] = ((m_InputImageB[i][j] - minB) * 255) / (maxB - minB);

			m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
		}
	}
}


void CImageWorksDoc::OnHistogramEndInSearch(void)
{
	CValueDlg dlg;
	if(dlg.DoModal() == IDOK){
		int i, j;

		m_OutputHeight = m_InputHeight;
		m_OutputWidth = m_InputWidth;

		m_OutputImageR = new unsigned char *[m_OutputHeight];
		m_OutputImageG = new unsigned char *[m_OutputHeight];
		m_OutputImageB = new unsigned char *[m_OutputHeight];
		for(i=0; i<m_OutputHeight; i++){
			m_OutputImageR[i] = new unsigned char [m_OutputWidth];
			m_OutputImageG[i] = new unsigned char [m_OutputWidth];
			m_OutputImageB[i] = new unsigned char [m_OutputWidth];
		}

		m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

		// search MIN, MAX
		unsigned char minR, minG, minB;
		unsigned char maxR, maxG, maxB;
	
		minR = m_InputImageR[0][0];
		minG = m_InputImageR[0][0];
		minB = m_InputImageB[0][0];

		maxR = m_InputImageR[0][0];
		maxG = m_InputImageG[0][0];
		maxB = m_InputImageB[0][0];

		for(i=0; i<m_OutputHeight; i++){
			for(j=0; j<m_OutputWidth; j++){
				// search minR, maxR
				if(m_InputImageR[i][j] > maxR){
					maxR = m_InputImageR[i][j];
				}
				else if(m_InputImageR[i][j] < minR){
					minR = m_InputImageR[i][j];
				}
				// search minG, maxG
				if(m_InputImageG[i][j] > maxG){
					maxG = m_InputImageG[i][j];
				}
				else if(m_InputImageG[i][j] < minG){
					minG = m_InputImageG[i][j];
				}
				// search minB, maxB
				if(m_InputImageB[i][j] > maxB){
					maxB = m_InputImageB[i][j];
				}
				else if(m_InputImageB[i][j] < minB){
					minB = m_InputImageB[i][j];
				}
			}
		}

		minR += (int)dlg.m_EditValue;
		minG += (int)dlg.m_EditValue;
		minB += (int)dlg.m_EditValue;
		maxR -= (int)dlg.m_EditValue;
		maxG -= (int)dlg.m_EditValue;
		maxB -= (int)dlg.m_EditValue;

		unsigned char tempR, tempG, tempB;

		for(i=0; i<m_OutputHeight; i++){
			for(j=0; j<m_OutputWidth; j++){
				tempR = m_InputImageR[i][j];
				tempG = m_InputImageG[i][j];
				tempB = m_InputImageB[i][j];

				if(tempR < minR){
					m_OutputImageR[i][j] = 0;
				}
				else if(tempR > maxR){
					m_OutputImageR[i][j] = 255;
				}
				else{
					m_OutputImageR[i][j] = ((tempR - minR) * MAX) / (maxR - minR);
				}

				if(tempR < minR){
					m_OutputImageR[i][j] = 0;
				}
				else if(tempR > maxR){
					m_OutputImageR[i][j] = 255;
				}
				else{
					m_OutputImageG[i][j] = ((tempG - minG) * MAX) / (maxG - minG);
				}

				if(tempR < minR){
					m_OutputImageR[i][j] = 0;
				}
				else if(tempR > maxR){
					m_OutputImageR[i][j] = 255;
				}
				else{
					m_OutputImageB[i][j] = ((tempB - minB) * MAX) / (maxB - minB);
				}
				m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
			}
		}
	}
}


void CImageWorksDoc::OnAndLogic(void)
{
	CRGBEditDlg dlg;
	
	if(dlg.DoModal() == IDOK){
		int i, j;
		int valueR, valueG, valueB;

		m_OutputHeight = m_InputHeight;
		m_OutputWidth = m_InputWidth;

		m_OutputImageR = new unsigned char* [m_OutputHeight];
		m_OutputImageG = new unsigned char* [m_OutputHeight];
		m_OutputImageB = new unsigned char* [m_OutputHeight];

		for(i=0; i<m_OutputHeight; i++){
			m_OutputImageR[i] = new unsigned char [m_OutputWidth];
			m_OutputImageG[i] = new unsigned char [m_OutputWidth];
			m_OutputImageB[i] = new unsigned char [m_OutputWidth];
		}

		m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

		for(i=0; i<m_OutputHeight; i++){
			for(j=0; j<m_OutputWidth; j++){
				valueR = m_InputImageR[i][j] & (int)dlg.m_EditRed;
				valueG = m_InputImageG[i][j] & (int)dlg.m_EditGreen;
				valueB = m_InputImageB[i][j] & (int)dlg.m_EditBlue;

				if(valueR < MIN){
					m_OutputImageR[i][j] = MIN;
				}
				else if(valueR > MAX){
					m_OutputImageR[i][j] = MAX;
				}
				else{
					m_OutputImageR[i][j] = valueR;
				}

				if(valueG < MIN){
					m_OutputImageG[i][j] = MIN;
				}
				else if(valueG > MAX){
					m_OutputImageG[i][j] = MAX;
				}
				else{
					m_OutputImageG[i][j] = valueG;
				}

				if(valueB < MIN){
					m_OutputImageB[i][j] = MIN;
				}
				else if(valueB > MAX){
					m_OutputImageB[i][j] = MAX;
				}
				else{
					m_OutputImageB[i][j] = valueB;
				}
				m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
			}
		}
	}
}


void CImageWorksDoc::OnEmbossing(void)
{
	int i, j;
	m_OutputHeight = m_InputHeight;
	m_OutputWidth = m_InputWidth;

	m_OutputImageR = new unsigned char *[m_OutputHeight];
	m_OutputImageG = new unsigned char *[m_OutputHeight];
	m_OutputImageB = new unsigned char *[m_OutputHeight];
	for(i=0; i<m_OutputHeight; i++){
		m_OutputImageR[i] = new unsigned char [m_OutputWidth];
		m_OutputImageG[i] = new unsigned char [m_OutputWidth];
		m_OutputImageB[i] = new unsigned char [m_OutputWidth];
	}

	m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

	// Universe Mask array
	int maskSize = 3; // Mask Size
	double **maskValue;
	maskValue = new double* [maskSize];
	for(i=0; i<maskSize; i++){
		maskValue[i] = new double [maskSize];
	}

	// Embossing Mask 상수 값
	double EmboMask[3][3] = {
		{-1. , 0. , 0. },
		{0. , 0. , 0. },
		{0. , 0. , 1. }
	};
	
	for(i=0; i<maskSize; i++){
		for(j=0; j<maskSize; j++){
			maskValue[i][j] = EmboMask[i][j];
		}
	}

	m_tempImageR = OnMaskProcessingR(m_InputImageR, maskValue, maskSize);
	m_tempImageG = OnMaskProcessingG(m_InputImageR, maskValue, maskSize);
	m_tempImageB = OnMaskProcessingB(m_InputImageR, maskValue, maskSize);

	for(i=0; i<m_InputHeight; i++){
		for(j=0; j<m_InputWidth; j++){
			m_tempImageR[i][j] += 127;
			m_tempImageG[i][j] += 127;
			m_tempImageB[i][j] += 127;
		}
	}

	// Overflow Check
	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			if(m_tempImageR[i][j] > 255.0){
				m_tempImageR[i][j] = 255.0;
			}
			else if(m_tempImageR[i][j] < 0.0){
				m_tempImageR[i][j] = 0.0;
			}

			if(m_tempImageG[i][j] > 255.0){
				m_tempImageG[i][j] = 255.0;
			}
			else if(m_tempImageG[i][j] < 0.0){
				m_tempImageG[i][j] = 0.0;
			}

			if(m_tempImageB[i][j] > 255.0){
				m_tempImageB[i][j] = 255.0;
			}
			else if(m_tempImageB[i][j] < 0.0){
				m_tempImageB[i][j] = 0.0;
			}
		}
	}

	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			m_OutputImageR[i][j] = (unsigned char)m_tempImageR[i][j];
			m_OutputImageG[i][j] = (unsigned char)m_tempImageG[i][j];
			m_OutputImageB[i][j] = (unsigned char)m_tempImageB[i][j];

			m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
		}
	}

	if(m_tempImageR != NULL){
		for(i=0; i<m_InputHeight; i++){
			delete m_tempImageR[i];
		}
		delete m_tempImageR;
	}

	if(m_tempImageG != NULL){
		for(i=0; i<m_InputHeight; i++){
			delete m_tempImageG[i];
		}
		delete m_tempImageG;
	}

	if(m_tempImageB != NULL){
		for(i=0; i<m_InputHeight; i++){
			delete m_tempImageB[i];
		}
		delete m_tempImageB;
	}
}


double** CImageWorksDoc::OnMaskProcessingR(unsigned char** Input, double** Mask, int Size)
{
	int i, j, n, m;
	int addPixel = (Size / 2) * 2; 
	int start = addPixel / 2;
	double **tempInputR, **tempOutputR, S=0.0;

	tempInputR = new double* [m_InputHeight+addPixel];
	for(i=0; i<m_InputHeight+addPixel; i++){
		tempInputR[i] = new double [m_InputWidth+addPixel];
	}
	
	tempOutputR = new double* [m_OutputHeight];
	for(i=0; i<m_OutputHeight; i++){
		tempOutputR[i] = new double [m_OutputWidth];
	}

	for(i=0; i<m_InputHeight+addPixel; i++){
		for(j=0; j<m_InputWidth+addPixel; j++){
			tempInputR[i][j] = 255.;
		}
	}

	for(i=0; i<m_InputHeight; i++){
		for(j=0; j<m_InputWidth; j++){
			tempInputR[i+start][j+start] = (double)m_InputImageR[i][j];
		}
	}

	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			for(n=0; n<Size; n++){
				for(m=0; m<Size; m++){
					S += Mask[n][m] * tempInputR[n+i][m+j]; 
				}
			}
			tempOutputR[i][j] = S;
			S = 0.0;
		}
	}

	if(tempInputR != NULL){
		for(i=0; i<m_InputHeight+addPixel; i++){
			delete tempInputR[i];
		}
		delete tempInputR;
	}

	return tempOutputR;
}


double** CImageWorksDoc::OnMaskProcessingG(unsigned char** Input, double** Mask, int Size)
{
	int i, j, n, m;
	int addPixel = (Size / 2) * 2; 
	int start = addPixel / 2;
	double **tempInputG, **tempOutputG, S=0.0;

	tempInputG = new double* [m_InputHeight+addPixel];
	for(i=0; i<m_InputHeight+addPixel; i++){
		tempInputG[i] = new double [m_InputWidth+addPixel];
	}
	
	tempOutputG = new double* [m_OutputHeight];
	for(i=0; i<m_OutputHeight; i++){
		tempOutputG[i] = new double [m_OutputWidth];
	}

	for(i=0; i<m_InputHeight+addPixel; i++){
		for(j=0; j<m_InputWidth+addPixel; j++){
			tempInputG[i][j] = 255.;
		}
	}

	for(i=0; i<m_InputHeight; i++){
		for(j=0; j<m_InputWidth; j++){
			tempInputG[i+start][j+start] = (double)m_InputImageG[i][j];
		}
	}

	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			for(n=0; n<Size; n++){
				for(m=0; m<Size; m++){
					S += Mask[n][m] * tempInputG[n+i][m+j]; 
				}
			}
			tempOutputG[i][j] = S;
			S = 0.0;
		}
	}

	if(tempInputG != NULL){
		for(i=0; i<m_InputHeight+addPixel; i++){
			delete tempInputG[i];
		}
		delete tempInputG;
	}

	return tempOutputG;
}


double** CImageWorksDoc::OnMaskProcessingB(unsigned char** Input, double** Mask, int Size)
{
	int i, j, n, m;
	int addPixel = (Size / 2) * 2; 
	int start = addPixel / 2;
	double **tempInputB, **tempOutputB, S=0.0;

	tempInputB = new double* [m_InputHeight+addPixel];
	for(i=0; i<m_InputHeight+addPixel; i++){
		tempInputB[i] = new double [m_InputWidth+addPixel];
	}
	
	tempOutputB = new double* [m_OutputHeight];
	for(i=0; i<m_OutputHeight; i++){
		tempOutputB[i] = new double [m_OutputWidth];
	}

	for(i=0; i<m_InputHeight+addPixel; i++){
		for(j=0; j<m_InputWidth+addPixel; j++){
			tempInputB[i][j] = 255.;
		}
	}

	for(i=0; i<m_InputHeight; i++){
		for(j=0; j<m_InputWidth; j++){
			tempInputB[i+start][j+start] = (double)m_InputImageB[i][j];
		}
	}

	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			for(n=0; n<Size; n++){
				for(m=0; m<Size; m++){
					S += Mask[n][m] * tempInputB[n+i][m+j]; 
				}
			}
			tempOutputB[i][j] = S;
			S = 0.0;
		}
	}

	if(tempInputB != NULL){
		for(i=0; i<m_InputHeight+addPixel; i++){
			delete tempInputB[i];
		}
		delete tempInputB;
	}

	return tempOutputB;
}


void CImageWorksDoc::OnOrLogic(void)
{
	CRGBEditDlg dlg;
	if(dlg.DoModal() == IDOK){
		int i, j;
		int tempR, tempG, tempB;

		m_OutputHeight = m_InputHeight;
		m_OutputWidth = m_InputWidth;

		m_OutputImageR = new unsigned char *[m_OutputHeight];
		m_OutputImageG = new unsigned char *[m_OutputHeight];
		m_OutputImageB = new unsigned char *[m_OutputHeight];
		for(i=0; i<m_OutputHeight; i++){
			m_OutputImageR[i] = new unsigned char [m_OutputWidth];
			m_OutputImageG[i] = new unsigned char [m_OutputWidth];
			m_OutputImageB[i] = new unsigned char [m_OutputWidth];
		}

		m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

		for(i=0; i<m_OutputHeight; i++){
			for(j=0; j<m_OutputWidth; j++){

				tempR = m_InputImageR[i][j] | (int)dlg.m_EditRed;
				tempG = m_InputImageG[i][j] | (int)dlg.m_EditGreen;
				tempB = m_InputImageB[i][j] | (int)dlg.m_EditBlue;
			
				if(tempR > MAX){
					m_OutputImageR[i][j] = MAX;
				}
				else if(tempR < MIN){
					m_OutputImageR[i][j] = MIN;
				}
				else{
					m_OutputImageR[i][j] = tempR;
				}
				
				if(tempG > MAX){
					m_OutputImageG[i][j] = MAX;
				}
				else if(tempG < MIN){
					m_OutputImageG[i][j] = MIN;
				}
				else{
					m_OutputImageG[i][j] = tempG;
				}

				if(tempB > MAX){
					m_OutputImageB[i][j] = MAX;
				}
				else if(tempB < MIN){
					m_OutputImageB[i][j] = MIN;
				}
				else{
					m_OutputImageB[i][j] = tempB;
				}
				m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
			}
		}
	}
}


void CImageWorksDoc::OnGamma(void)
{
	CRGBEditDlg dlg;
	if(dlg.DoModal() == IDOK) {
		int i, j;
		double valueR, valueG, valueB;

		m_OutputHeight = m_InputHeight;
		m_OutputWidth = m_InputWidth;

		m_OutputImageR = new unsigned char *[m_OutputHeight];
		m_OutputImageG = new unsigned char *[m_OutputHeight];
		m_OutputImageB = new unsigned char *[m_OutputHeight];
		for(i=0; i<m_OutputHeight; i++){
			m_OutputImageR[i] = new unsigned char [m_OutputWidth];
			m_OutputImageG[i] = new unsigned char [m_OutputWidth];
			m_OutputImageB[i] = new unsigned char [m_OutputWidth];
		}

		m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

		for(i=0; i<m_OutputHeight; i++) {
			for(j=0; j<m_OutputWidth; j++) {
				valueR = pow(m_InputImageR[i][j], (double)1/dlg.m_EditRed);
				valueG = pow(m_InputImageG[i][j], (double)1/dlg.m_EditGreen);
				valueB = pow(m_InputImageB[i][j], (double)1/dlg.m_EditBlue);

				if (valueR < MIN){
					m_OutputImageR[i][j] = MIN;
				}
				else if(valueR > MAX){
					m_OutputImageR[i][j] = MAX;
				}
				else{
					m_OutputImageR[i][j] = (unsigned char)valueR;
				}

				if (valueG < MIN){
					m_OutputImageG[i][j] = MIN;
				}
				else if(valueG > MAX){
					m_OutputImageG[i][j] = MAX;
				}
				else{
					m_OutputImageG[i][j] = (unsigned char)valueG;
				}

				if (valueB < MIN){
					m_OutputImageB[i][j] = MIN;
				}
				else if(valueB > MAX){
					m_OutputImageB[i][j] = MAX;
				}
				else{
					m_OutputImageB[i][j] = (unsigned char)valueB;
				}
				m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
			}
		}
	}
}


void CImageWorksDoc::OnBlur(void)
{
	CValueDlg dlg;
	if(dlg.DoModal() == IDOK){
		int i, j;
		m_OutputHeight = m_InputHeight;
		m_OutputWidth = m_InputWidth;

		m_OutputImageR = new unsigned char *[m_OutputHeight];
		m_OutputImageG = new unsigned char *[m_OutputHeight];
		m_OutputImageB = new unsigned char *[m_OutputHeight];
		for(i=0; i<m_OutputHeight; i++){
			m_OutputImageR[i] = new unsigned char [m_OutputWidth];
			m_OutputImageG[i] = new unsigned char [m_OutputWidth];
			m_OutputImageB[i] = new unsigned char [m_OutputWidth];
		}

		m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

		// Universe Mask array
		int maskSize = (int)dlg.m_EditValue; // Mask Size
		double **maskValue;
		maskValue = new double* [maskSize];
		for(i=0; i<maskSize; i++){
			maskValue[i] = new double [maskSize];
		}

		double BlurMask = 1. / (double)(dlg.m_EditValue * dlg.m_EditValue);
		
		for(i=0; i<maskSize; i++){
			for(j=0; j<maskSize; j++){
				maskValue[i][j] = BlurMask;
			}
		}

		m_tempImageR = OnMaskProcessingR(m_InputImageR, maskValue, maskSize);
		m_tempImageG = OnMaskProcessingG(m_InputImageR, maskValue, maskSize);
		m_tempImageB = OnMaskProcessingB(m_InputImageR, maskValue, maskSize);

		// Overflow Check
		for(i=0; i<m_OutputHeight; i++){
			for(j=0; j<m_OutputWidth; j++){
				if(m_tempImageR[i][j] > MAX){
					m_tempImageR[i][j] = MAX;
				}
				else if(m_tempImageR[i][j] < MIN){
					m_tempImageR[i][j] = MIN;
				}

				if(m_tempImageG[i][j] > MAX){
					m_tempImageG[i][j] = MAX;
				}
				else if(m_tempImageG[i][j] < MIN){
					m_tempImageG[i][j] = MIN;
				}

				if(m_tempImageB[i][j] > MAX){
					m_tempImageB[i][j] = MAX;
				}
				else if(m_tempImageB[i][j] < MIN){
					m_tempImageB[i][j] = MIN;
				}
			}
		}

		for(i=0; i<m_OutputHeight; i++){
			for(j=0; j<m_OutputWidth; j++){
				m_OutputImageR[i][j] = (unsigned char)m_tempImageR[i][j];
				m_OutputImageG[i][j] = (unsigned char)m_tempImageG[i][j];
				m_OutputImageB[i][j] = (unsigned char)m_tempImageB[i][j];

				m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
			}
		}

		if(m_tempImageR != NULL){
			for(i=0; i<m_InputHeight; i++){
				delete m_tempImageR[i];
			}
			delete m_tempImageR;
		}

		if(m_tempImageG != NULL){
			for(i=0; i<m_InputHeight; i++){
				delete m_tempImageG[i];
			}
			delete m_tempImageG;
		}

		if(m_tempImageB != NULL){
			for(i=0; i<m_InputHeight; i++){
				delete m_tempImageB[i];
			}
			delete m_tempImageB;
		}
	}
}


void CImageWorksDoc::OnSharpen(void)
{
	int i, j;
	m_OutputHeight = m_InputHeight;
	m_OutputWidth = m_InputWidth;

	m_OutputImageR = new unsigned char *[m_OutputHeight];
	m_OutputImageG = new unsigned char *[m_OutputHeight];
	m_OutputImageB = new unsigned char *[m_OutputHeight];
	for(i=0; i<m_OutputHeight; i++){
		m_OutputImageR[i] = new unsigned char [m_OutputWidth];
		m_OutputImageG[i] = new unsigned char [m_OutputWidth];
		m_OutputImageB[i] = new unsigned char [m_OutputWidth];
	}

	m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

	// Universe Mask array
	int maskSize = 3; // Mask Size
	double **maskValue;
	maskValue = new double* [maskSize];
	for(i=0; i<maskSize; i++){
		maskValue[i] = new double [maskSize];
	}
		
	double SharpenMask[3][3] = {
		{-1. , -1. , -1.},
		{-1. , 9. , -1.},
		{-1. , -1. , -1.}
	};
		
	for(i=0; i<maskSize; i++){
		for(j=0; j<maskSize; j++){
			maskValue[i][j] = SharpenMask[i][j];
		}
	}

	m_tempImageR = OnMaskProcessingR(m_InputImageR, maskValue, maskSize);
	m_tempImageG = OnMaskProcessingG(m_InputImageR, maskValue, maskSize);
	m_tempImageB = OnMaskProcessingB(m_InputImageR, maskValue, maskSize);

	/*for(i=0; i<m_InputHeight; i++){
		for(j=0; j<m_InputWidth; j++){
			m_tempImageR[i][j] += 127;
			m_tempImageG[i][j] += 127;
			m_tempImageB[i][j] += 127;
		}
	}*/

	// Overflow Check
	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			if(m_tempImageR[i][j] > MAX){
				m_tempImageR[i][j] = MAX;
			}
			else if(m_tempImageR[i][j] < MIN){
				m_tempImageR[i][j] = MIN;
			}

			if(m_tempImageG[i][j] > MAX){
				m_tempImageG[i][j] = MAX;
			}
			else if(m_tempImageG[i][j] < MIN){
				m_tempImageG[i][j] = MIN;
			}

			if(m_tempImageB[i][j] > MAX){
				m_tempImageB[i][j] = MAX;
			}
			else if(m_tempImageB[i][j] < MIN){
				m_tempImageB[i][j] = MIN;
			}
		}
	}

	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			m_OutputImageR[i][j] = (unsigned char)m_tempImageR[i][j];
			m_OutputImageG[i][j] = (unsigned char)m_tempImageG[i][j];
			m_OutputImageB[i][j] = (unsigned char)m_tempImageB[i][j];

			m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
		}
	}

	if(m_tempImageR != NULL){
		for(i=0; i<m_InputHeight; i++){
			delete m_tempImageR[i];
		}
		delete m_tempImageR;
	}

	if(m_tempImageG != NULL){
		for(i=0; i<m_InputHeight; i++){
			delete m_tempImageG[i];
		}
		delete m_tempImageG;
	}

	if(m_tempImageB != NULL){
		for(i=0; i<m_InputHeight; i++){
			delete m_tempImageB[i];
		}
		delete m_tempImageB;
	}
}


void CImageWorksDoc::OnEqualImage(void)
{
	int i, j;
	m_OutputHeight = m_InputHeight;
	m_OutputWidth = m_InputWidth;

	m_OutputImageR = new unsigned char* [m_OutputHeight];
	m_OutputImageG = new unsigned char* [m_OutputHeight];
	m_OutputImageB = new unsigned char* [m_OutputHeight];

	for(i=0; i<m_OutputHeight; i++){
		m_OutputImageR[i] = new unsigned char [m_OutputWidth];
		m_OutputImageG[i] = new unsigned char [m_OutputWidth];
		m_OutputImageB[i] = new unsigned char [m_OutputWidth];
	}

	m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			m_OutputImageR[i][j] = m_InputImageR[i][j];
			m_OutputImageG[i][j] = m_InputImageG[i][j];
			m_OutputImageB[i][j] = m_InputImageB[i][j];

			m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
		}
	}
}


void CImageWorksDoc::OnSobelmask(void)
{
	int i, j;
	
	m_OutputHeight = m_InputHeight;
	m_OutputWidth = m_InputWidth;

	m_OutputImageR = new unsigned char *[m_OutputHeight];
	m_OutputImageG = new unsigned char *[m_OutputHeight];
	m_OutputImageB = new unsigned char *[m_OutputHeight];
	for(i=0; i<m_OutputHeight; i++){
		m_OutputImageR[i] = new unsigned char [m_OutputWidth];
		m_OutputImageG[i] = new unsigned char [m_OutputWidth];
		m_OutputImageB[i] = new unsigned char [m_OutputWidth];
	}

	m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

	int maskSize = 3; // after modify
	double** sobelMask;

	sobelMask = new double* [maskSize];
	for(i=0; i<maskSize; i++){
		sobelMask[i] = new double [maskSize];
	}
	
	// Mask const, after modify
	double maskValueCol[3][3] = {
		{-1. , -2. , -1.},
		{0. , 0. , 0.},
		{1. , 2. , 1.}
	};

	double maskValueRow[3][3] = {
		{1. , 0. , -1.},
		{2. , 0. , -2.},
		{1. , 0. , -1.}
	};

	for(i=0; i<maskSize; i++){
		for(j=0; j<maskSize; j++){
			sobelMask[i][j] = maskValueCol[i][j] + maskValueRow[i][j];
		}
	}

	m_tempImageR = OnMaskProcessingR(m_InputImageR, sobelMask, maskSize);
	m_tempImageG = OnMaskProcessingG(m_InputImageR, sobelMask, maskSize);
	m_tempImageB = OnMaskProcessingB(m_InputImageR, sobelMask, maskSize);
	
	// Overflow check
	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			if(m_tempImageR[i][j] > MAX){
				m_tempImageR[i][j] = MAX;
			}
			else if(m_tempImageR[i][j] < MIN){
				m_tempImageR[i][j] = MIN;
			}

			if(m_tempImageG[i][j] > MAX){
				m_tempImageG[i][j] = MAX;
			}
			else if(m_tempImageG[i][j] < MIN){
				m_tempImageG[i][j] = MIN;
			}

			if(m_tempImageB[i][j] > MAX){
				m_tempImageB[i][j] = MAX;
			}
			else if(m_tempImageB[i][j] < MIN){
				m_tempImageB[i][j] = MIN;
			}
		}
	}

	// Processing result(floting) -> m_OutputImage
	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			m_OutputImageR[i][j] = (unsigned char)m_tempImageR[i][j];
			m_OutputImageG[i][j] = (unsigned char)m_tempImageG[i][j];
			m_OutputImageB[i][j] = (unsigned char)m_tempImageB[i][j];

			m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
		}
	}

	if(m_tempImageR != NULL){
		for(i=0; i<m_InputHeight; i++){
			delete m_tempImageR[i];
		}
		delete m_tempImageR;
	}

	if(m_tempImageG != NULL){
		for(i=0; i<m_InputHeight; i++){
			delete m_tempImageG[i];
		}
		delete m_tempImageG;
	}

	if(m_tempImageB != NULL){
		for(i=0; i<m_InputHeight; i++){
			delete m_tempImageB[i];
		}
		delete m_tempImageB;
	}
}


void CImageWorksDoc::OnCapParabola(void)
{
	int i, j;
	m_OutputHeight = m_InputHeight;
	m_OutputWidth = m_InputWidth;

	m_OutputImageR = new unsigned char* [m_OutputHeight];
	m_OutputImageG = new unsigned char* [m_OutputHeight];
	m_OutputImageB = new unsigned char* [m_OutputHeight];

	for(i=0; i<m_OutputHeight; i++){
		m_OutputImageR[i] = new unsigned char [m_OutputWidth];
		m_OutputImageG[i] = new unsigned char [m_OutputWidth];
		m_OutputImageB[i] = new unsigned char [m_OutputWidth];
	}

	m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

	double outR, outG, outB;
	int LUT[256];

	for(i=0; i<255; i++){
		outR = 255.0 - 255.0 * pow((i / 128.0 - 1.0), 2.0);
		if(outR > 255.0){
			outR = 255.0;
		}
		else if(outR < 0.0){
			outR = 0.0;
		}
		LUT[i] = (int)outR;

		outG = 255.0 - 255.0 * pow((i / 128.0 - 1.0), 2.0);
		if(outG > 255.0){
			outG = 255.0;
		}
		else if(outG < 0.0){
			outG = 0.0;
		}
		LUT[i] = (int)outG;

		outB = 255.0 - 255.0 * pow((i / 128.0 - 1.0), 2.0);
		if(outB > 255.0){
			outB = 255.0;
		}
		else if(outB < 0.0){
			outB = 0.0;
		}
		LUT[i] = (int)outB;
	}

	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			m_OutputImageR[i][j] = (unsigned char)LUT[m_InputImageR[i][j]];
			m_OutputImageG[i][j] = (unsigned char)LUT[m_InputImageG[i][j]];
			m_OutputImageB[i][j] = (unsigned char)LUT[m_InputImageB[i][j]];

			m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
		}
	}
}


void CImageWorksDoc::OnCubParabola(void)
{
	int i, j;
	m_OutputHeight = m_InputHeight;
	m_OutputWidth = m_InputWidth;

	m_OutputImageR = new unsigned char* [m_OutputHeight];
	m_OutputImageG = new unsigned char* [m_OutputHeight];
	m_OutputImageB = new unsigned char* [m_OutputHeight];

	for(i=0; i<m_OutputHeight; i++){
		m_OutputImageR[i] = new unsigned char [m_OutputWidth];
		m_OutputImageG[i] = new unsigned char [m_OutputWidth];
		m_OutputImageB[i] = new unsigned char [m_OutputWidth];
	}

	m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

	double outR, outG, outB;
	int LUT[256];

	for(i=0; i<255; i++){
		outR = 255.0 * pow((i / 128.0 - 1.0), 2.0);
		if(outR > 255.0){
			outR = 255.0;
		}
		else if(outR < 0.0){
			outR = 0.0;
		}
		LUT[i] = (int)outR;

		outG = 255.0 * pow((i / 128.0 - 1.0), 2.0);
		if(outG > 255.0){
			outG = 255.0;
		}
		else if(outG < 0.0){
			outG = 0.0;
		}
		LUT[i] = (int)outG;

		outB = 255.0 * pow((i / 128.0 - 1.0), 2.0);
		if(outB > 255.0){
			outB = 255.0;
		}
		else if(outB < 0.0){
			outB = 0.0;
		}
		LUT[i] = (int)outB;
	}

	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			m_OutputImageR[i][j] = (unsigned char)LUT[m_InputImageR[i][j]];
			m_OutputImageG[i][j] = (unsigned char)LUT[m_InputImageG[i][j]];
			m_OutputImageB[i][j] = (unsigned char)LUT[m_InputImageB[i][j]];

			m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
		}
	}
}


void CImageWorksDoc::OnLaplacia(void)
{
	int i, j;
	m_OutputHeight = m_InputHeight;
	m_OutputWidth = m_InputWidth;

	m_OutputImageR = new unsigned char *[m_OutputHeight];
	m_OutputImageG = new unsigned char *[m_OutputHeight];
	m_OutputImageB = new unsigned char *[m_OutputHeight];
	for(i=0; i<m_OutputHeight; i++){
		m_OutputImageR[i] = new unsigned char [m_OutputWidth];
		m_OutputImageG[i] = new unsigned char [m_OutputWidth];
		m_OutputImageB[i] = new unsigned char [m_OutputWidth];
	}

	m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

	// Universe Mask array
	int maskSize = 3; // Mask Size
	double **maskValue;
	maskValue = new double* [maskSize];
	for(i=0; i<maskSize; i++){
		maskValue[i] = new double [maskSize];
	}

	double LapliMask[3][3] = {
		{1. , 1. , 1.},
		{1. , -8. , 1.},
		{1. , 1. , 1.}
	};
	
	for(i=0; i<maskSize; i++){
		for(j=0; j<maskSize; j++){
			maskValue[i][j] = LapliMask[i][j];
		}
	}

	m_tempImageR = OnMaskProcessingR(m_InputImageR, maskValue, maskSize);
	m_tempImageG = OnMaskProcessingG(m_InputImageR, maskValue, maskSize);
	m_tempImageB = OnMaskProcessingB(m_InputImageR, maskValue, maskSize);

	// Overflow Check
	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			if(m_tempImageR[i][j] > 255.0){
				m_tempImageR[i][j] = 255.0;
			}
			else if(m_tempImageR[i][j] < 0.0){
				m_tempImageR[i][j] = 0.0;
			}

			if(m_tempImageG[i][j] > 255.0){
				m_tempImageG[i][j] = 255.0;
			}
			else if(m_tempImageG[i][j] < 0.0){
				m_tempImageG[i][j] = 0.0;
			}

			if(m_tempImageB[i][j] > 255.0){
				m_tempImageB[i][j] = 255.0;
			}
			else if(m_tempImageB[i][j] < 0.0){
				m_tempImageB[i][j] = 0.0;
			}
		}
	}

	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			m_OutputImageR[i][j] = (unsigned char)m_tempImageR[i][j];
			m_OutputImageG[i][j] = (unsigned char)m_tempImageG[i][j];
			m_OutputImageB[i][j] = (unsigned char)m_tempImageB[i][j];

			m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
		}
	}

	if(m_tempImageR != NULL){
		for(i=0; i<m_InputHeight; i++){
			delete m_tempImageR[i];
		}
		delete m_tempImageR;
	}

	if(m_tempImageG != NULL){
		for(i=0; i<m_InputHeight; i++){
			delete m_tempImageG[i];
		}
		delete m_tempImageG;
	}

	if(m_tempImageB != NULL){
		for(i=0; i<m_InputHeight; i++){
			delete m_tempImageB[i];
		}
		delete m_tempImageB;
	}
}


void CImageWorksDoc::OnLapliGau(void)
{
	int i, j;
	m_OutputHeight = m_InputHeight;
	m_OutputWidth = m_InputWidth;

	m_OutputImageR = new unsigned char *[m_OutputHeight];
	m_OutputImageG = new unsigned char *[m_OutputHeight];
	m_OutputImageB = new unsigned char *[m_OutputHeight];
	for(i=0; i<m_OutputHeight; i++){
		m_OutputImageR[i] = new unsigned char [m_OutputWidth];
		m_OutputImageG[i] = new unsigned char [m_OutputWidth];
		m_OutputImageB[i] = new unsigned char [m_OutputWidth];
	}

	m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

	// Universe Mask array
	int maskSize = 5; // Mask Size
	double **maskValue;
	maskValue = new double* [maskSize];
	for(i=0; i<maskSize; i++){
		maskValue[i] = new double [maskSize];
	}

	double LapliMask[5][5] = {
		{0. , 0. , -1. , 0. , 0.},
		{0. , -1. , -2. , -1. , 0.},
		{-1. , -2. , 16. , -2. , -1.},
		{0. , -1. , -2. , -1. , 0.},
		{0. , 0. , -1. , 0. , 0.}
	};
	
	for(i=0; i<maskSize; i++){
		for(j=0; j<maskSize; j++){
			maskValue[i][j] = LapliMask[i][j];
		}
	}

	m_tempImageR = OnMaskProcessingR(m_InputImageR, maskValue, maskSize);
	m_tempImageG = OnMaskProcessingG(m_InputImageR, maskValue, maskSize);
	m_tempImageB = OnMaskProcessingB(m_InputImageR, maskValue, maskSize);

	// Overflow Check
	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			if(m_tempImageR[i][j] > 255.0){
				m_tempImageR[i][j] = 255.0;
			}
			else if(m_tempImageR[i][j] < 0.0){
				m_tempImageR[i][j] = 0.0;
			}

			if(m_tempImageG[i][j] > 255.0){
				m_tempImageG[i][j] = 255.0;
			}
			else if(m_tempImageG[i][j] < 0.0){
				m_tempImageG[i][j] = 0.0;
			}

			if(m_tempImageB[i][j] > 255.0){
				m_tempImageB[i][j] = 255.0;
			}
			else if(m_tempImageB[i][j] < 0.0){
				m_tempImageB[i][j] = 0.0;
			}
		}
	}

	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			m_OutputImageR[i][j] = (unsigned char)m_tempImageR[i][j];
			m_OutputImageG[i][j] = (unsigned char)m_tempImageG[i][j];
			m_OutputImageB[i][j] = (unsigned char)m_tempImageB[i][j];

			m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
		}
	}

	if(m_tempImageR != NULL){
		for(i=0; i<m_InputHeight; i++){
			delete m_tempImageR[i];
		}
		delete m_tempImageR;
	}

	if(m_tempImageG != NULL){
		for(i=0; i<m_InputHeight; i++){
			delete m_tempImageG[i];
		}
		delete m_tempImageG;
	}

	if(m_tempImageB != NULL){
		for(i=0; i<m_InputHeight; i++){
			delete m_tempImageB[i];
		}
		delete m_tempImageB;
	}
}


void CImageWorksDoc::OnZoomin(void)
{
	CValueDlg dlg;
	
	if(dlg.DoModal() == IDOK){
		int scale = (int)dlg.m_EditValue;
		int i, j;

		m_OutputHeight=m_InputHeight * scale;
		m_OutputWidth=m_InputWidth * scale;

		m_OutputImageR = new unsigned char *[m_OutputHeight];
		m_OutputImageG = new unsigned char *[m_OutputHeight];
		m_OutputImageB = new unsigned char *[m_OutputHeight];
		for(i=0; i<m_OutputHeight; i++){
			m_OutputImageR[i] = new unsigned char [m_OutputWidth];
			m_OutputImageG[i] = new unsigned char [m_OutputWidth];
			m_OutputImageB[i] = new unsigned char [m_OutputWidth];
		}

		m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);
		
		double r_H, r_W; // 실수 위치
		int i_H, i_W; // 정수 위치
		double y, x; // 거리
		double rC1, rC2, rC3, rC4;
		double gC1, gC2, gC3, gC4;
		double bC1, bC2, bC3, bC4;
		unsigned char nR, nG, nB;

		for(i=0; i<m_OutputHeight; i++){
			for(j=0; j<m_OutputHeight; j++){
				r_H = i / (double)scale;
				r_W = j / (double)scale;
				i_H = (int)r_H;
				i_W = (int)r_W;
				y = r_H - i_H;
				x = r_W - i_W;

				if(i_H < 0 || i_H >= (m_InputHeight-1) || i_W < 0 || i_W >= (m_InputWidth-1)){
					m_OutputImageR[i][j] = 255;
					m_OutputImageG[i][j] = 255;
					m_OutputImageB[i][j] = 255;
				}
				else{
					rC1 = m_InputImageR[i_H][i_W];
					rC2 = m_InputImageR[i_H][i_W+1];
					rC3 = m_InputImageR[i_H+1][i_W];
					rC4 = m_InputImageR[i_H+1][i_W+1];

					gC1 = m_InputImageG[i_H][i_W];
					gC2 = m_InputImageG[i_H][i_W+1];
					gC3 = m_InputImageG[i_H+1][i_W];
					gC4 = m_InputImageG[i_H+1][i_W+1];

					bC1 = m_InputImageB[i_H][i_W];
					bC2 = m_InputImageB[i_H][i_W+1];
					bC3 = m_InputImageB[i_H+1][i_W];
					bC4 = m_InputImageB[i_H+1][i_W+1];
				
					nR = (unsigned char)(rC1 * (1-y) * (1-x) + rC2 * (1-y) * x + rC3 * y * (1-x) + rC4 * y * x);
					nG = (unsigned char)(gC1 * (1-y) * (1-x) + gC2 * (1-y) * x + gC3 * y * (1-x) + gC4 * y * x);
					nB = (unsigned char)(bC1 * (1-y) * (1-x) + bC2 * (1-y) * x + bC3 * y * (1-x) + bC4 * y * x);
				
					m_OutputImageR[i][j] = nR;
					m_OutputImageG[i][j] = nG;
					m_OutputImageB[i][j] = nB;
				}
				m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
			}
		}
	}
}


void CImageWorksDoc::OnZoomout(void)
{
	CValueDlg dlg;
	int i,j;
	
	if(dlg.DoModal() == IDOK){
		int scale = (int)dlg.m_EditValue;

		m_OutputHeight=m_InputHeight / scale;
		m_OutputWidth=m_InputWidth / scale;

		m_OutputImageR = new unsigned char *[m_OutputHeight];
		m_OutputImageG = new unsigned char *[m_OutputHeight];
		m_OutputImageB = new unsigned char *[m_OutputHeight];
		for(i=0; i<m_OutputHeight; i++){
			m_OutputImageR[i] = new unsigned char [m_OutputWidth];
			m_OutputImageG[i] = new unsigned char [m_OutputWidth];
			m_OutputImageB[i] = new unsigned char [m_OutputWidth];
		}

		// Mask size define
		int MASK_SIZE = scale;
		double **MaskR, **MaskG, **MaskB;
		MaskR = new double* [MASK_SIZE];
		for(i=0; i<MASK_SIZE; i++){
			MaskR[i] = new double [MASK_SIZE];
		}

		MaskG = new double* [MASK_SIZE];
		for(i=0; i<MASK_SIZE; i++){
			MaskG[i] = new double [MASK_SIZE];
		}

		MaskB = new double* [MASK_SIZE];
		for(i=0; i<MASK_SIZE; i++){
			MaskB[i] = new double [MASK_SIZE];
		}

		int n, m;
		for(i=0; i<m_InputHeight; i+=MASK_SIZE){
			for(j=0; j<m_InputWidth; j+=MASK_SIZE){
				for(n=0; n<MASK_SIZE; n++){
					for(m=0; m<MASK_SIZE; m++){
						MaskR[n][m] = m_InputImageR[n+i][m+j];
						MaskG[n][m] = m_InputImageG[n+i][m+j];
						MaskB[n][m] = m_InputImageB[n+i][m+j];
					}
				}
				m_OutputImageR[i/MASK_SIZE][j/MASK_SIZE] = OnFindMean(MaskR, MASK_SIZE);
				m_OutputImageG[i/MASK_SIZE][j/MASK_SIZE] = OnFindMean(MaskG, MASK_SIZE);
				m_OutputImageB[i/MASK_SIZE][j/MASK_SIZE] = OnFindMean(MaskB, MASK_SIZE);
			}
		}
	}
}


unsigned char CImageWorksDoc::OnFindMean(double** Mask, int mSize)
{
	int i, j, k = 0, sum = 0;
	double *Mask1;

	Mask1 = new double [mSize * mSize];

	for(i=0; i<mSize; i++){
		for(j=0; j<mSize; j++){
			Mask1[k++] = Mask[i][j];
		}
	}
	
	for(i=0; i<mSize * mSize; i++){
		sum += (int)Mask1[i];
	}
	sum = sum / (mSize * mSize);
	
	return (unsigned char)sum;
}


void CImageWorksDoc::OnMirrorHor(void)
{
	int i, j;

	m_OutputHeight = m_InputHeight;
	m_OutputWidth = m_InputWidth;

	m_OutputImageR = new unsigned char *[m_OutputHeight];
	m_OutputImageG = new unsigned char *[m_OutputHeight];
	m_OutputImageB = new unsigned char *[m_OutputHeight];
	for(i=0; i<m_OutputHeight; i++){
		m_OutputImageR[i] = new unsigned char [m_OutputWidth];
		m_OutputImageG[i] = new unsigned char [m_OutputWidth];
		m_OutputImageB[i] = new unsigned char [m_OutputWidth];
	}

	m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			m_OutputImageR[i][j] = m_InputImageR[i][m_OutputWidth-j];
			m_OutputImageG[i][j] = m_InputImageG[i][m_OutputWidth-j];
			m_OutputImageB[i][j] = m_InputImageB[i][m_OutputWidth-j];

			m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
		}
	}
}


void CImageWorksDoc::OnMirrorVer(void)
{
	int i, j;

	m_OutputHeight = m_InputHeight;
	m_OutputWidth = m_InputWidth;

	m_OutputImageR = new unsigned char *[m_OutputHeight];
	m_OutputImageG = new unsigned char *[m_OutputHeight];
	m_OutputImageB = new unsigned char *[m_OutputHeight];
	for(i=0; i<m_OutputHeight; i++){
		m_OutputImageR[i] = new unsigned char [m_OutputWidth];
		m_OutputImageG[i] = new unsigned char [m_OutputWidth];
		m_OutputImageB[i] = new unsigned char [m_OutputWidth];
	}

	m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			m_OutputImageR[i][j] = m_InputImageR[m_InputHeight-i-1][j];
			m_OutputImageG[i][j] = m_InputImageG[m_InputHeight-i-1][j];
			m_OutputImageB[i][j] = m_InputImageB[m_InputHeight-i-1][j];

			m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
		}
	}
}


void CImageWorksDoc::OnMirrorHorver(void)
{
	int i, j;

	m_OutputHeight = m_InputHeight;
	m_OutputWidth = m_InputWidth;

	m_OutputImageR = new unsigned char *[m_OutputHeight];
	m_OutputImageG = new unsigned char *[m_OutputHeight];
	m_OutputImageB = new unsigned char *[m_OutputHeight];
	for(i=0; i<m_OutputHeight; i++){
		m_OutputImageR[i] = new unsigned char [m_OutputWidth];
		m_OutputImageG[i] = new unsigned char [m_OutputWidth];
		m_OutputImageB[i] = new unsigned char [m_OutputWidth];
	}

	m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			m_OutputImageR[i][j] = m_InputImageR[m_InputHeight-i-1][m_InputWidth-j];
			m_OutputImageG[i][j] = m_InputImageG[m_InputHeight-i-1][m_InputWidth-j];
			m_OutputImageB[i][j] = m_InputImageB[m_InputHeight-i-1][m_InputWidth-j];

			m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
		}
	}
}


void CImageWorksDoc::OnRotateImage(void)
{
	CRotateDlg dlg;
	if(dlg.DoModal() == IDOK){
		int i, j;
		int degree = dlg.m_EditRotate; // can using dialog
		double a, a90, PI = 3.141592;

		a = degree * PI / 180.0;
		a90 = (90-degree) * PI / 180.0;

		int dx, dy, cx, cy;

		m_OutputHeight = (int)(m_InputHeight * cos(a) + m_InputWidth * cos(a90));
		m_OutputWidth = (int)(m_InputWidth * cos(a90) + m_InputWidth * cos(a));

		cx = m_OutputHeight / 2;
		cy = m_OutputWidth / 2;

		m_OutputImageR = new unsigned char *[m_OutputHeight];
		m_OutputImageG = new unsigned char *[m_OutputHeight];
		m_OutputImageB = new unsigned char *[m_OutputHeight];
		for(i=0; i<m_OutputHeight; i++){
			m_OutputImageR[i] = new unsigned char [m_OutputWidth];
			m_OutputImageG[i] = new unsigned char [m_OutputWidth];
			m_OutputImageB[i] = new unsigned char [m_OutputWidth];
		}

		m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

		// define temp memory
		unsigned char **m_inTempR, **m_inTempG, **m_inTempB;
		m_inTempR = new unsigned char* [m_OutputHeight];
		m_inTempG = new unsigned char* [m_OutputHeight];
		m_inTempB = new unsigned char* [m_OutputHeight];
		for (i=0; i<m_OutputHeight; i++){
			m_inTempR[i] = new unsigned char [m_OutputWidth];
			m_inTempG[i] = new unsigned char [m_OutputWidth];
			m_inTempB[i] = new unsigned char [m_OutputWidth];
		}

		// reset inTemp
		for(i=0; i<m_OutputHeight; i++){
			for(j=0; j<m_OutputWidth; j++){
				m_inTempR[i][j] = MAX;
				m_inTempG[i][j] = MAX;
				m_inTempB[i][j] = MAX;
			}
		}
	
		// center image position
		int startX = (m_OutputHeight - m_InputHeight) / 2;
		int startY = (m_OutputWidth - m_InputWidth) / 2;

		// insert inputimage to inTemp
		for(i=0; i<m_InputHeight; i++){
			for(j=0; j<m_InputWidth; j++){
				m_inTempR[i+startX][j+startY] = m_InputImageR[i][j];
				m_inTempG[i+startX][j+startY] = m_InputImageG[i][j];
				m_inTempB[i+startX][j+startY] = m_InputImageB[i][j];
			}
		}

		double fdx, fdy;
		double r_H, r_W, x, y;
		double rC1, rC2, rC3, rC4, rN;
		double gC1, gC2, gC3, gC4, gN;
		double bC1, bC2, bC3, bC4, bN;
		int i_H, i_W;

		for(i=0; i<m_OutputHeight; i++){
			for(j=0; j<m_OutputWidth; j++){
				fdx = (i-cx) * cos(a) + (j-cy) * sin(a) + cx;
				fdy = -(i-cx) * sin(a) + (j-cy) * cos(a) + cy;

				dx = (int)fdx;
				dy = (int)fdy;

				if(dx >= MIN && dx <m_OutputHeight && dy >= MIN && dy < m_OutputWidth){
					r_H = fdx;
					r_W = fdy;
					i_H = (int)r_H;
					i_W = (int)r_W;
					y = r_H - i_H;
					x = r_W - i_W;

					if(i_H < MIN || i_H >= (m_OutputHeight - 1) || i_W < MIN || i_W >= (m_OutputWidth - 1)){
						rN = MAX;
						gN = MAX;
						bN = MAX;
					}
					else{
						rC1 = m_inTempR[i_H][i_W];
						rC2 = m_inTempR[i_H][i_W+1];
						rC3 = m_inTempR[i_H+1][i_W+1];
						rC4 = m_inTempR[i_H+1][i_W];
						rN = rC1 * (1-y) * (1-x) + rC2 * (1-y) * x + rC3 * y * x + rC4 * y * (1-x);

						gC1 = m_inTempG[i_H][i_W];
						gC2 = m_inTempG[i_H][i_W+1];
						gC3 = m_inTempG[i_H+1][i_W+1];
						gC4 = m_inTempG[i_H+1][i_W];
						gN = gC1 * (1-y) * (1-x) + gC2 * (1-y) * x + gC3 * y * x + gC4 * y * (1-x);

						bC1 = m_inTempB[i_H][i_W];
						bC2 = m_inTempB[i_H][i_W+1];
						bC3 = m_inTempB[i_H+1][i_W+1];
						bC4 = m_inTempB[i_H+1][i_W];
						bN = bC1 * (1-y) * (1-x) + bC2 * (1-y) * x + bC3 * y * x + bC4 * y * (1-x);
					}

					m_OutputImageR[i][j] = (unsigned char)rN;
					m_OutputImageG[i][j] = (unsigned char)gN;
					m_OutputImageB[i][j] = (unsigned char)bN;
				}
				else{
					m_OutputImageR[i][j] = MAX;
					m_OutputImageG[i][j] = MAX;
					m_OutputImageB[i][j] = MAX;
				}
				m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
			}
		}
		// delete memory
		for(i=0; i<m_OutputHeight; i++){
			delete m_inTempR[i];
			delete m_inTempG[i];
			delete m_inTempB[i];
		}
		delete m_inTempR;
		delete m_inTempG;
		delete m_inTempB;
	}
}


void CImageWorksDoc::OnHistogramMake(void)
{
	int i, j;
	double minR, minG, minB, maxR, maxG, maxB, difR, difG, difB;
	unsigned char m_ScaleHistoR[256], m_ScaleHistoG[256], m_ScaleHistoB[256];

	m_OutputHeight = 512;
	m_OutputWidth = 512;

	m_OutputImageR = new unsigned char* [m_OutputHeight];
	m_OutputImageG = new unsigned char* [m_OutputHeight];
	m_OutputImageB = new unsigned char* [m_OutputHeight];
	for(i=0; i<m_OutputHeight; i++){
		m_OutputImageR[i] = new unsigned char [m_OutputWidth];
		m_OutputImageG[i] = new unsigned char [m_OutputWidth];
		m_OutputImageB[i] = new unsigned char [m_OutputWidth];
	}
	
	m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

	for(i=0; i<256; i++){
		m_HistR[i] = 0;
		m_HistG[i] = 0;
		m_HistB[i] = 0;
	}

	for(i=0; i<m_InputHeight; i++){
		for(j=0; j<m_InputWidth; j++){
			m_HistR[m_InputImageR[i][j]]++;
			m_HistG[m_InputImageG[i][j]]++;
			m_HistB[m_InputImageB[i][j]]++;
		}
	}

	minR = maxR = (unsigned char)m_HistR[0];
	minG = maxG = (unsigned char)m_HistG[0];
	minB = maxB = (unsigned char)m_HistB[0];
	for(i=0; i<256; i++){
		if(m_HistR[i] > maxR){
			maxR = m_HistR[i];
		}
		else if(m_HistR[i] < minR){
			minR = m_HistR[i];
		}

		if(m_HistG[i] > maxG){
			maxG = m_HistG[i];
		}
		else if(m_HistG[i] < minG){
			minG = m_HistG[i];
		}

		if(m_HistB[i] > maxB){
			maxB = m_HistB[i];
		}
		else if(m_HistB[i] < minB){
			minB = m_HistB[i];
		}
	}

	difR = maxR - minR;
	difG = maxG - minG;
	difB = maxB - minB;

	for(i=0; i<256; i++){
		m_ScaleHistoR[i] = (unsigned char)((m_HistR[i] - minR) * 255 / difR);
		m_ScaleHistoG[i] = (unsigned char)((m_HistG[i] - minG) * 255 / difG);
		m_ScaleHistoB[i] = (unsigned char)((m_HistB[i] - minB) * 255 / difB);
	}

	for(i=0; i<512; i++){
		for(j=0; j<512; j++){
			m_OutputImageR[i][j] = 0;
			m_OutputImageG[i][j] = 0;
			m_OutputImageB[i][j] = 0;
		}
	}

	for(i=0; i<256; i++){
		for(j=0; j<m_ScaleHistoR[i]; j++){
			m_OutputImageR[256 - j - 1][i] = 255;
		}
	}

	for(i=0; i<256; i++){
		for(j=0; j<m_ScaleHistoG[i]; j++){
			m_OutputImageG[256 - j - 1][i] = 255;
		}
	}
	
	for(i=0; i<256; i++){
		for(j=0; j<m_ScaleHistoB[i]; j++){
			m_OutputImageB[256 - j - 1][i] = 255;
		}
	}
			
	for(i=0; i<256; i++){
		for(j=0; j<m_ScaleHistoR[i]; j++){
			m_OutputImageR[256 - j - 1][i + 256] = 255;
		}
	}

	for(i=0; i<256; i++){
		for(j=0; j<m_ScaleHistoG[i]; j++){
			m_OutputImageG[m_OutputHeight - j - 1][i] = 255;
		}
	}

	for(i=0; i<256; i++){
		for(j=0; j<m_ScaleHistoB[i]; j++){
			m_OutputImageB[m_OutputHeight - j - 1][i + 256] = 255;
		}
	}
	
	for(i=0; i<512; i++){
		for(j=0; j<512; j++){
			m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
		}
	}
}


BOOL CImageWorksDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	// TODO: Add your specialized code here and/or call the base class
	CFile File;
	
	/*if(m_outImage == NULL) {
		AfxMessageBox(L"아직 영상처리가 안되었음..");
		return false;
	}*/

	TCHAR szFilters[]= _T("JPG Files (*.jpg)");

    CFileDialog SaveDlg(TRUE, _T("jpg"), _T(".jpg"), OFN_HIDEREADONLY, szFilters);
		
	if(SaveDlg.DoModal() == IDOK) {
		CString fname;
		fname = SaveDlg.GetPathName();
		m_outImage.Save(fname);
	}

	return TRUE;
	//return CDocument::OnSaveDocument(lpszPathName);
}


void CImageWorksDoc::OnHomogen(void)
{
	int i, j;
	double** tempInputR, **tempInputG, **tempInputB;
	double** tempOutputR, **tempOutputG, **tempOutputB;
	
	m_OutputHeight = m_InputHeight;
	m_OutputWidth = m_InputWidth;

	m_OutputImageR = new unsigned char *[m_OutputHeight];
	m_OutputImageG = new unsigned char *[m_OutputHeight];
	m_OutputImageB = new unsigned char *[m_OutputHeight];
	for(i=0; i<m_OutputHeight; i++){
		m_OutputImageR[i] = new unsigned char [m_OutputWidth];
		m_OutputImageG[i] = new unsigned char [m_OutputWidth];
		m_OutputImageB[i] = new unsigned char [m_OutputWidth];
	}

	tempInputR = new double *[m_OutputHeight];
	tempInputG = new double *[m_OutputHeight];
	tempInputB = new double *[m_OutputHeight];
	for(i=0; i<m_OutputHeight; i++){
		tempInputG[i] = new double [m_OutputWidth];
		tempInputG[i] = new double [m_OutputWidth];
		tempInputB[i] = new double [m_OutputWidth];
	}

	tempOutputR = new double *[m_OutputHeight];
	tempOutputG = new double *[m_OutputHeight];
	tempOutputB = new double *[m_OutputHeight];
	for(i=0; i<m_OutputHeight; i++){
		tempOutputR[i] = new double [m_OutputWidth];
		tempOutputG[i] = new double [m_OutputWidth];
		tempOutputB[i] = new double [m_OutputWidth];
	}

	m_outImage.Create(m_OutputHeight, m_OutputWidth, 32, 0);

	// 원본이미지를 임시메모리에 적재
	for(i=0; i<m_InputHeight; i++){
		for(j=0; j<m_InputWidth; j++){
			tempInputR[i][j] = (double)m_InputImageR[i][j];
			tempInputG[i][j] = (double)m_InputImageG[i][j];
			tempInputB[i][j] = (double)m_InputImageB[i][j];
		}
	}

	// 최대 차이의 값을 tempOutput에 넣기
	for(i=1; i<m_InputHeight-2; i++){
		for(j=1; j<m_InputWidth-2; j++){
			tempOutputR[i][j] = OnFindMaxValue(tempInputR, i, j);
			tempOutputG[i][j] = OnFindMaxValue(tempInputG, i, j);
			tempOutputB[i][j] = OnFindMaxValue(tempInputB, i, j);
		}
	}
	m_tempImageR = tempOutputR;
	m_tempImageG = tempOutputG;
	m_tempImageB = tempOutputB;

	// Overflow check
	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			if(m_tempImageR[i][j] > 255.){
				m_tempImageR[i][j] = 255.;
			}
			else if(m_tempImageR[i][j] < 0.){
				m_tempImageR[i][j] = 0.;
			}

			if(m_tempImageG[i][j] > 255.){
				m_tempImageG[i][j] = 255.;
			}
			else if(m_tempImageG[i][j] < 0.){
				m_tempImageG[i][j] = 0.;
			}

			if(m_tempImageB[i][j] > 255.){
				m_tempImageB[i][j] = 255.;
			}
			else if(m_tempImageB[i][j] < 0.){
				m_tempImageB[i][j] = 0.;
			}
		}
	}

	// Processing result(floting) -> m_OutputImage
	for(i=0; i<m_OutputHeight; i++){
		for(j=0; j<m_OutputWidth; j++){
			m_OutputImageR[i][j] = (unsigned char)m_tempImageR[i][j];
			m_OutputImageG[i][j] = (unsigned char)m_tempImageG[i][j];
			m_OutputImageB[i][j] = (unsigned char)m_tempImageB[i][j];

			m_outImage.SetPixelRGB(j, i, m_OutputImageR[i][j], m_OutputImageG[i][j], m_OutputImageB[i][j]);
		}
	}

	// Memory del
	for(i=0; i<m_OutputHeight; i++){
		delete tempInputR[i];
		}
	delete tempInputR;

	for(i=0; i<m_OutputHeight; i++){
		delete tempInputG[i];
		}
	delete tempInputG;

	for(i=0; i<m_OutputHeight; i++){
		delete tempInputB[i];
		}
	delete tempInputB;
	
	for(i=0; i<m_OutputHeight; i++){
		delete tempOutputR[i];
	}
	delete tempOutputR;

	for(i=0; i<m_OutputHeight; i++){
		delete tempOutputG[i];
	}
	delete tempOutputG;

	for(i=0; i<m_OutputHeight; i++){
		delete tempOutputB[i];
	}
	delete tempOutputB;
}


double CImageWorksDoc::OnFindMaxValue(double** tImage, int x, int y)
{
	int n, m;
	double max = 0.0, absValue;

	// 범용함수가 아니라 3으로 고정
	for(n=0; n<3; n++){
		for(m=0; m<3; m++){
			absValue = fabs(tImage[x+1][y+1] - tImage[x+n][y+m]);
			
			if(absValue > max){
			max = absValue;
			}
		}
	}

	return max;
}
