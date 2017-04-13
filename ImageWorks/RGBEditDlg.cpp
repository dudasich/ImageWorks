// RGBEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageWorks.h"
#include "RGBEditDlg.h"
#include "afxdialogex.h"


// CRGBEditDlg dialog

IMPLEMENT_DYNAMIC(CRGBEditDlg, CDialog)

CRGBEditDlg::CRGBEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CRGBEditDlg::IDD, pParent)
	, m_EditRed(0)
	, m_EditGreen(0)
	, m_EditBlue(0)
{

}

CRGBEditDlg::~CRGBEditDlg()
{
}

void CRGBEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_RED, m_SliderRed);
	DDX_Text(pDX, IDC_EDIT_RED, m_EditRed);
	DDX_Control(pDX, IDC_SLIDER_GREEN, m_SliderGreen);
	DDX_Text(pDX, IDC_EDIT_GREEN, m_EditGreen);
	DDX_Control(pDX, IDC_SLIDER_BLUE, m_SliderBlue);
	DDX_Text(pDX, IDC_EDIT_BLUE, m_EditBlue);
	DDV_MinMaxDouble(pDX, m_EditRed, 0, 255);
	DDV_MinMaxDouble(pDX, m_EditGreen, 0, 255);
	DDV_MinMaxDouble(pDX, m_EditBlue, 0, 255);
}


BEGIN_MESSAGE_MAP(CRGBEditDlg, CDialog)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_RED, &CRGBEditDlg::OnEnChangeEditRed)
	ON_EN_CHANGE(IDC_EDIT_GREEN, &CRGBEditDlg::OnEnChangeEditGreen)
	ON_EN_CHANGE(IDC_EDIT_BLUE, &CRGBEditDlg::OnEnChangeEditBlue)
END_MESSAGE_MAP()


// CRGBEditDlg message handlers


BOOL CRGBEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_SliderRed.SetRange(0, 255);
	m_SliderGreen.SetRange(0, 255);
	m_SliderBlue.SetRange(0, 255);

	m_SliderRed.SetPos(0);
	m_SliderGreen.SetPos(0);
	m_SliderBlue.SetPos(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CRGBEditDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if(pScrollBar != NULL && pScrollBar->m_hWnd == m_SliderRed.m_hWnd){
		SetDlgItemInt(IDC_EDIT_RED, m_SliderRed.GetPos());
    }
	if(pScrollBar != NULL && pScrollBar->m_hWnd == m_SliderGreen.m_hWnd){
		SetDlgItemInt(IDC_EDIT_GREEN, m_SliderGreen.GetPos());
    }
	if(pScrollBar != NULL && pScrollBar->m_hWnd == m_SliderBlue.m_hWnd){
		SetDlgItemInt(IDC_EDIT_BLUE, m_SliderBlue.GetPos());
    }

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CRGBEditDlg::OnEnChangeEditRed()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	if(UpdateData(TRUE))
		m_SliderRed.SetPos((int)m_EditRed);
}


void CRGBEditDlg::OnEnChangeEditGreen()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	if(UpdateData(TRUE))
		m_SliderGreen.SetPos((int)m_EditGreen);
}


void CRGBEditDlg::OnEnChangeEditBlue()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	if(UpdateData(TRUE))
		m_SliderBlue.SetPos((int)m_EditBlue);
}
