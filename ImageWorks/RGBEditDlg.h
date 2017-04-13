#pragma once
#include "afxcmn.h"


// CRGBEditDlg dialog

class CRGBEditDlg : public CDialog
{
	DECLARE_DYNAMIC(CRGBEditDlg)

public:
	CRGBEditDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRGBEditDlg();

// Dialog Data
	enum { IDD = IDD_RGB_EDIT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CSliderCtrl m_SliderRed;
	double m_EditRed;
	CSliderCtrl m_SliderGreen;
	double m_EditGreen;
	CSliderCtrl m_SliderBlue;
	double m_EditBlue;
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditRed();
	afx_msg void OnEnChangeEditGreen();
	afx_msg void OnEnChangeEditBlue();
};
