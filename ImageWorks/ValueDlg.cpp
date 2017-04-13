// ValueDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ImageWorks.h"
#include "ValueDlg.h"
#include "afxdialogex.h"


// CValueDlg dialog

IMPLEMENT_DYNAMIC(CValueDlg, CDialog)

CValueDlg::CValueDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CValueDlg::IDD, pParent)
	, m_EditValue(0)
{

}

CValueDlg::~CValueDlg()
{
}

void CValueDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SLIDER_VALUE, m_SliderValue);
	DDX_Text(pDX, IDC_EDIT_VALUE, m_EditValue);
	DDV_MinMaxDouble(pDX, m_EditValue, 0., 255.);
}


BEGIN_MESSAGE_MAP(CValueDlg, CDialog)
	ON_WM_HSCROLL()
	ON_EN_CHANGE(IDC_EDIT_VALUE, &CValueDlg::OnEnChangeEditValue)
END_MESSAGE_MAP()


// CValueDlg message handlers


BOOL CValueDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  Add extra initialization here
	m_SliderValue.SetRange(0, 255);

	m_SliderValue.SetPos(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}


void CValueDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: Add your message handler code here and/or call default
	if(pScrollBar != NULL && pScrollBar->m_hWnd == m_SliderValue.m_hWnd){
		SetDlgItemInt(IDC_EDIT_VALUE, m_SliderValue.GetPos());
    }

	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CValueDlg::OnEnChangeEditValue()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	if(UpdateData(TRUE))
		m_SliderValue.SetPos((int)m_EditValue);
}
