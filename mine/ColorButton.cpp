#include "StdAfx.h"
#include "ColorButton.h"

CColorButton::CColorButton(void)
{
}

CColorButton::~CColorButton(void)
{
}

BOOL CColorButton::Attach(const UINT nID, CWnd* pParent)
{
	if (!SubclassDlgItem(nID, pParent)) 
		return FALSE; 
	return TRUE; 
}

void CColorButton::SetButtonColor(COLORREF color)
{
	m_ButtonColor = color;
}

void CColorButton::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	CBrush brush(m_ButtonColor);   
	dc.FillRect(&(lpDrawItemStruct->rcItem),&brush);
}