// RotateDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageWorks.h"
#include "RotateDlg.h"
#include "afxdialogex.h"


// CRotateDlg dialog

IMPLEMENT_DYNAMIC(CRotateDlg, CDialog)

CRotateDlg::CRotateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRotateDlg::IDD, pParent)
	, m_EditRotate(0)
{

}

CRotateDlg::~CRotateDlg()
{
}

void CRotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_ROTATE, m_SliderRotate);
	DDX_Text(pDX, IDC_EDIT_ROTATE, m_EditRotate);
	DDV_MinMaxInt(pDX, m_EditRotate, 0, 90);
}


BEGIN_MESSAGE_MAP(CRotateDlg, CDialog)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_ROTATE, &CRotateDlg::OnNMCustomdrawSliderRotate)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_ROTATE, &CRotateDlg::OnEnChangeEditRotate)
END_MESSAGE_MAP()


// CRotateDlg message handlers


void CRotateDlg::OnNMCustomdrawSliderRotate(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


BOOL CRotateDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_SliderRotate.SetRange(0, 90);

	m_SliderRotate.SetPos(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CRotateDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if(pScrollBar != NULL && pScrollBar->m_hWnd == m_SliderRotate.m_hWnd){
		SetDlgItemInt(IDC_EDIT_ROTATE, m_SliderRotate.GetPos());
    }

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CRotateDlg::OnEnChangeEditRotate()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	if(UpdateData(TRUE))
		m_SliderRotate.SetPos(m_EditRotate);
}
