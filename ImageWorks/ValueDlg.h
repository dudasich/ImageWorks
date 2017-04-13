#pragma once
#include "afxcmn.h"


// CValueDlg dialog

class CValueDlg : public CDialog
{
	DECLARE_DYNAMIC(CValueDlg)

public:
	CValueDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CValueDlg();

// Dialog Data
	enum { IDD = IDD_VALUE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_SliderValue;
	double m_EditValue;
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditValue();
};
