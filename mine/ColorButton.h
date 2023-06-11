#pragma once
#include "afxwin.h"

class CColorButton :
	public CButton
{
public:
	CColorButton(void);
	~CColorButton(void);
	BOOL Attach(const UINT nID, CWnd* pParent);
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	void SetButtonColor(COLORREF color);
public:
	COLORREF m_ButtonColor;
};
