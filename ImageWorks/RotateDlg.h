#pragma once
#include "afxcmn.h"


// CRotateDlg dialog

class CRotateDlg : public CDialog
{
	DECLARE_DYNAMIC(CRotateDlg)

public:
	CRotateDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CRotateDlg();

// Dialog Data
	enum { IDD = IDD_ROTATE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CSliderCtrl m_SliderRotate;
	int m_EditRotate;
	afx_msg void OnNMCustomdrawSliderRotate(NMHDR *pNMHDR, LRESULT *pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnEnChangeEditRotate();
};
