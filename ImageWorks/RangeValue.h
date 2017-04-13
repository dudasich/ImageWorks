#pragma once
#include "afxcmn.h"


// CRangeValue dialog

class CRangeValue : public CDialog
{
	DECLARE_DYNAMIC(CRangeValue)

public:
	CRangeValue(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRangeValue();

// Dialog Data
	enum { IDD = IDD_RANGE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_SliderRangeOne;
	double m_EditRangeOne;
	CSliderCtrl m_SliderRangeTwo;
	double m_EditRangeTwo;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditRangeone();
	afx_msg void OnEnChangeEditRangetwo();
};
