//DJWStatic.cpp实现文件

#include "stdafx.h"
#include "CHMXStatic.h"

CHMXStatic::CHMXStatic()
{
	m_bTransparent = true;
	m_clrBkClr = ::GetSysColor(COLOR_WINDOW);
	m_clrTextClr = ::GetSysColor(COLOR_WINDOWTEXT);
	m_brsBkGnd.CreateSolidBrush(m_clrBkClr);
	m_brsHollow.CreateStockObject(HOLLOW_BRUSH);
	m_bMode = true;
	m_colLineColor = RGB(113,113,113);
	m_nLineWidth = 1;
}

CHMXStatic::~CHMXStatic()
{
	m_brsBkGnd.DeleteObject();
	m_brsHollow.DeleteObject();
	m_fntText.DeleteObject();
}


BEGIN_MESSAGE_MAP(CHMXStatic, CStatic)
	//{{AFX_MSG_MAP(CHMXStatic)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_ERASEBKGND()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHMXStatic message handlers

HBRUSH CHMXStatic::CtlColor(CDC* pDC, UINT nCtlColor)
{
	// TODO: Change any attributes of the DC here
	if( m_bTransparent )
		pDC->SetBkMode( TRANSPARENT );
	else {
		pDC->SetBkMode( OPAQUE );
		pDC->SetBkColor(m_clrBkClr);
	}
	pDC->SetTextColor(m_clrTextClr);

	// TODO: Return a non-NULL brush if the parent's handler should not be called
	if( m_bTransparent )
		return (HBRUSH)m_brsHollow;
	else
		return (HBRUSH)m_brsBkGnd;
}

BOOL CHMXStatic::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	if( m_bTransparent )
		pDC->SetBkMode( TRANSPARENT );
	else
		pDC->SetBkColor(m_clrBkClr);

	return CStatic::OnEraseBkgnd(pDC);
}

/////////////////////////////////////////////////////////////////////////////

/********************************************************************

in:			clr
out:		none
return:		always true;

purpose:	set background color

*********************************************************************/

bool CHMXStatic::SetBkClr(COLORREF clr)
{
	m_clrBkClr = clr;
	m_brsBkGnd.DeleteObject();
	m_brsBkGnd.CreateSolidBrush(m_clrBkClr);
	Invalidate();

	return true;
}

/********************************************************************

in:			
out:		
return:		

purpose:	Set information of line around the text

*********************************************************************/
void CHMXStatic::SetLineInf(COLORREF colLineColor, int	nLineWidth)
{
	m_colLineColor = colLineColor;
	m_nLineWidth = nLineWidth;
	//	m_pen.CreatePen(PS_SOLID, m_nLineWidth, m_colLineColor);
}

/********************************************************************

in:			
out:		
return:		

purpose:	Set ctrl common style 

*********************************************************************/
void CHMXStatic::SetCommonMode(int mode)
{
	m_bMode = false;
}

/********************************************************************

in:			none
out:		clr
return:		always true

purpose:	return background color

*********************************************************************/

bool CHMXStatic::GetBkClr(COLORREF & clr)
{
	clr = m_clrBkClr;
	return true;
}

/********************************************************************

in:			clr
out:		none
return:		always true;

purpose:	set Text color

*********************************************************************/

bool CHMXStatic::SetTextClr(COLORREF clr)
{
	m_clrTextClr = clr;
	Invalidate();

	return true;
}

/********************************************************************

in:			none
out:		clr
return:		always true

purpose:	get text color

*********************************************************************/

bool CHMXStatic::GetTextClr(COLORREF & clr)
{
	clr = m_clrTextClr;
	return true;
}

/********************************************************************

in:			nHeight, bBold, bItalic, sFaceName
out:		none
return:		always true

purpose:	set the font for the control

*********************************************************************/

bool CHMXStatic::SetTextFont( LONG nHeight, bool bBold, bool bItalic, const CString& sFaceName )
{
	LOGFONT lgfnt;

	lgfnt.lfHeight			= -MulDiv(nHeight, GetDeviceCaps(GetDC()->m_hDC, LOGPIXELSY), 72);
	lgfnt.lfWidth			= 0;
	lgfnt.lfEscapement		= 0;
	lgfnt.lfOrientation		= 0;
	lgfnt.lfWeight			= bBold?FW_BOLD:FW_DONTCARE;
	lgfnt.lfItalic			= bItalic?TRUE:FALSE;
	lgfnt.lfUnderline		= FALSE;
	lgfnt.lfStrikeOut		= FALSE;
	lgfnt.lfCharSet			= DEFAULT_CHARSET;
	lgfnt.lfOutPrecision	= OUT_DEFAULT_PRECIS;
	lgfnt.lfClipPrecision	= CLIP_DEFAULT_PRECIS;
	lgfnt.lfQuality			= DEFAULT_QUALITY;
	lgfnt.lfPitchAndFamily	= DEFAULT_PITCH | FF_DONTCARE;
	strcpy_s( lgfnt.lfFaceName, (char*)(LPCTSTR)sFaceName );


	return SetTextFont( lgfnt );

}

/********************************************************************

in:			lgFont
out:		none
return:		always true

purpose:	set the font for the control

*********************************************************************/

bool CHMXStatic::SetTextFont( const LOGFONT& lgfnt )
{
	m_fntText.DeleteObject();
	m_fntText.CreateFontIndirect( &lgfnt );
	SetFont( &m_fntText, TRUE );

	return true;
}

/********************************************************************

in:			none
out:		lgFont
return:		always true

purpose:	get text font

*********************************************************************/

bool CHMXStatic::GetTextFont( LOGFONT* plgfnt)
{
	GetFont()->GetObject( sizeof(LOGFONT), (void*)plgfnt);
	return true;
}

/********************************************************************

in:			bTransparent
out:		none
return:		always true

purpose:	set transparency

*********************************************************************/

bool CHMXStatic::SetTransparent( bool bTransparent /* = true */)
{
	m_bTransparent = bTransparent;
	Invalidate();
	return true;
}

/********************************************************************

in:			none
out:		none
return:		transparency

purpose:	get transparency

*********************************************************************/

bool CHMXStatic::GetTransparent()
{
	return m_bTransparent;
}

/********************************************************************

in:			bBold
out:		none
return:		always true

purpose:	set font bold

*********************************************************************/

bool CHMXStatic::SetFontBold( bool bBold )
{
	LOGFONT lgfnt;

	GetTextFont( &lgfnt );
	lgfnt.lfWeight	= bBold?FW_BOLD:FW_DONTCARE; 

	SetTextFont( lgfnt );

	return true;
}

/********************************************************************

in:			bItalic
out:		none
return:		always true

purpose:	set the font italic

*********************************************************************/

bool CHMXStatic::SetFontItalic( bool bItalic )
{
	LOGFONT lgfnt;

	GetTextFont( &lgfnt );
	lgfnt.lfItalic	= bItalic ? TRUE : FALSE; 

	SetTextFont( lgfnt );
	return true;
}

/********************************************************************

in:			nHeight
out:		none
return:		always true

purpose:	set the font height

*********************************************************************/

bool CHMXStatic::SetFontHeight( int nHeight )
{
	LOGFONT lgfnt;

	GetTextFont( &lgfnt );
	lgfnt.lfHeight	= -MulDiv(nHeight, GetDeviceCaps(GetDC()->m_hDC, LOGPIXELSY), 72);    
	lgfnt.lfWidth	= 0; 

	SetTextFont( lgfnt );
	return true;
}

/********************************************************************

in:			sFaceName
out:		none
return:		always true

purpose:	set the font face name

*********************************************************************/

bool CHMXStatic::SetFontFaceName( const CString& sFaceName )
{
	LOGFONT lgfnt;

	GetTextFont( &lgfnt );
	strcpy_s( lgfnt.lfFaceName, (char*)(LPCTSTR)sFaceName );


	SetTextFont( lgfnt );
	return true;
}

/********************************************************************

in:			nAngle
out:		none
return:		always true

purpose:	set the rotation of fonts
works only with TT fonts

*********************************************************************/

bool CHMXStatic::SetFontRotation( int nAngle )
{
	LOGFONT lgfnt;

	GetTextFont( &lgfnt );
	lgfnt.lfEscapement	= long(nAngle)*10;
	lgfnt.lfOrientation	= long(nAngle)*10;
	SetTextFont( lgfnt );

	return true;
}

/********************************************************************

in:			none
out:		none
return:		always true

purpose:	init tooltip

*********************************************************************/

bool CHMXStatic::InitToolTip()
{
	if (m_tt.m_hWnd == NULL) {
		m_tt.Create(this);
		m_tt.Activate(true);
		m_tt.SendMessage(TTM_SETMAXTIPWIDTH, 0, 400);
	}

	return true;
}

/********************************************************************

in:			sText, bActivate
out:		none
return:		always true

purpose:	set tooltip text

*********************************************************************/

bool CHMXStatic::SetToolTipText(const CString& sText, bool bActivate)
{
	InitToolTip(); 

	// If there is no tooltip defined then add it
	if (m_tt.GetToolCount() == 0)
	{
		CRect rect; 
		GetClientRect(rect);
		m_tt.AddTool(this, sText, rect, 1);
	}

	m_tt.UpdateTipText(sText, this, 1);
	m_tt.Activate(bActivate);

	return true;
}

/********************************************************************

in:			bActivate
out:		none
return:		always true

purpose:	activate/deactivate tooltip

*********************************************************************/

bool CHMXStatic::ActivateToolTip(bool bActivate)
{
	if (m_tt.GetToolCount() == 0)
		return false;

	// Activate tooltip
	m_tt.Activate(bActivate);

	return true;
}

/********************************************************************

in:			see CWnd::PretanslateMessage
out:		see CWnd::PretanslateMessage
return:		see CWnd::PretanslateMessage

purpose:	let tooltip works

*********************************************************************/

BOOL CHMXStatic::PreTranslateMessage(MSG* pMsg) 
{
	InitToolTip();
	m_tt.RelayEvent(pMsg);

	return CStatic::PreTranslateMessage(pMsg);
} 

/********************************************************************

in:			see CStatic::OnPaint()
out:		see CStatic::OnPaint()
return:		see CStatic::OnPaint()

purpose:	draw the ctrl



*********************************************************************/

void CHMXStatic::OnPaint() 
{
	CStatic::OnPaint();
	if (m_bMode == true)
	{
		CRect rect;
		GetClientRect(&rect);
		rect.InflateRect(1,1,1,1);
		CPen pen(PS_SOLID, m_nLineWidth, m_colLineColor);
		CBrush* brush = CBrush::FromHandle((HBRUSH)GetStockObject(NULL_BRUSH));
		CClientDC dc(this);
		CPen * pOldPen = dc.SelectObject(&pen);
		CBrush* pOldBrush = dc.SelectObject(brush);
		dc.Rectangle(rect);
		if(pOldBrush != NULL)
			dc.SelectObject(pOldPen);
		if(pOldBrush != NULL)
			dc.SelectObject(pOldBrush);
	}
}

