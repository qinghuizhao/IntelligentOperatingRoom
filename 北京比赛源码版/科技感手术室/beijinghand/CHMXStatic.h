
#pragma once
#ifndef _CHMXSTATIC_H
#define _CHMXSTATIC_H


class CHMXStatic : public CStatic
{
	// Construction
public:
	CHMXStatic();

	// Attributes
public:

	// Operations

private:
	bool m_bMode;//true带框，flase不带框
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHMXStatic)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	// Implementation
public://对外接口
	bool SetToolTipText(const CString& sText, bool bActivate = true);
	bool ActivateToolTip(bool bEnable = true);
	bool GetTransparent();
	bool SetTransparent( bool bTransparent = true);
	bool SetFontRotation( int nAngle );
	bool SetFontBold(bool bBold = true);

	/********************************************************************
	函数名：SetFontItalic
	参数： 
	bool bItalic					[in]: true倾斜，false不倾斜
	返回值：
	bool								: 总是true
	作用：设置字体倾斜
	*********************************************************************/
	bool SetFontItalic( bool bItalic = true);

	/********************************************************************
	函数名：SetFontHeight
	参数： 
	int nHeight					[in]: 字体大小
	返回值：
	bool								: 总是true
	作用：设置字体大小
	*********************************************************************/
	bool SetFontHeight( int nHeight );

	/********************************************************************
	函数名：SetFontFaceName
	参数： 
	CString sFaceName				[in]: 字体名
	返回值：
	bool								: 总是true
	作用：设置字体
	*********************************************************************/
	bool SetFontFaceName( const CString& sFaceName );

	/********************************************************************
	函数名：GetTextFont
	参数： 
	LOGFONT* plgfnt			[in/out]: 字体
	返回值：
	bool								: 总是true
	作用：获取字体
	*********************************************************************/
	bool GetTextFont( LOGFONT* plgfnt);

	/********************************************************************
	函数名：SetTextFont
	参数： 
	LONG nHeight					[in]: 字体大小
	bool bBold					[in]: true加粗，false不加粗
	bool bItalic					[in]: true倾斜，false不倾斜
	CString sFaceName				[in]: 字体名
	返回值：
	bool								: 总是true
	作用：set the font for the control
	*********************************************************************/
	bool SetTextFont( LONG nHeight, bool bBold, bool bItalic, const CString& sFaceName );

	/********************************************************************
	函数名：SetTextFont
	参数： 
	LOGFONT lgfnt					[in]: 字体
	返回值：
	bool								: 总是true
	作用：设置字体
	*********************************************************************/
	bool SetTextFont( const LOGFONT& lgfnt );

	/********************************************************************
	函数名：GetTextClr
	参数： 
	LOGFONT lgfnt				[in/out]: 字体
	返回值：
	bool								: 总是true
	作用：获取字体
	*********************************************************************/
	bool GetTextClr(COLORREF &clr);

	/********************************************************************
	函数名：SetTextClr
	参数： 
	LOGFONT lgfnt					[in]: 字体
	返回值：
	bool								: 总是true
	作用：设置字体
	*********************************************************************/
	bool SetTextClr( COLORREF clr );

	/********************************************************************
	函数名：GetBkClr
	参数： 
	LOGFONT lgfnt				[in/out]: 颜色
	返回值：
	bool								: 总是true
	作用：获取颜色
	*********************************************************************/
	bool GetBkClr(COLORREF &clr);

	/********************************************************************
	函数名：SetBkClr
	参数： 
	LOGFONT lgfnt					[in]: 颜色
	返回值：
	bool								: 总是true
	作用：设置背景颜色
	*********************************************************************/
	bool SetBkClr( COLORREF clr );

	/********************************************************************
	函数名：SetCommonMode
	参数： 
	int mode						[in]: 0普通样式
	返回值：
	none								
	作用：设置控件为普通样式
	*********************************************************************/
	void SetCommonMode(int mode = 0);//

	/********************************************************************
	函数名：SetLineInf
	参数： 
	COLORREF colLineColor				[in]: 边线颜色
	int	nLineWidth					[in]: 边线粗细
	返回值：
	none									
	作用：设置控件边线颜色粗细
	*********************************************************************/
	void SetLineInf(COLORREF colLineColor, int	nLineWidth);


	virtual ~CHMXStatic();

protected:
	bool InitToolTip();
	CToolTipCtrl m_tt;
	CFont m_fntText;
	COLORREF m_clrTextClr;
	COLORREF m_clrBkClr;
	CBrush m_brsBkGnd;
	CBrush m_brsHollow;
	bool m_bTransparent;

private:
	COLORREF m_colLineColor;
	int	m_nLineWidth;

	// Generated message map functions
protected:
	//{{AFX_MSG(CHMXStatic)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

#endif 
