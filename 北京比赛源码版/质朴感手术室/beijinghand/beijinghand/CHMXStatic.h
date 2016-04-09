
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
	bool m_bMode;//true����flase������
public:

	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHMXStatic)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

	// Implementation
public://����ӿ�
	bool SetToolTipText(const CString& sText, bool bActivate = true);
	bool ActivateToolTip(bool bEnable = true);
	bool GetTransparent();
	bool SetTransparent( bool bTransparent = true);
	bool SetFontRotation( int nAngle );
	bool SetFontBold(bool bBold = true);

	/********************************************************************
	��������SetFontItalic
	������ 
	bool bItalic					[in]: true��б��false����б
	����ֵ��
	bool								: ����true
	���ã�����������б
	*********************************************************************/
	bool SetFontItalic( bool bItalic = true);

	/********************************************************************
	��������SetFontHeight
	������ 
	int nHeight					[in]: �����С
	����ֵ��
	bool								: ����true
	���ã����������С
	*********************************************************************/
	bool SetFontHeight( int nHeight );

	/********************************************************************
	��������SetFontFaceName
	������ 
	CString sFaceName				[in]: ������
	����ֵ��
	bool								: ����true
	���ã���������
	*********************************************************************/
	bool SetFontFaceName( const CString& sFaceName );

	/********************************************************************
	��������GetTextFont
	������ 
	LOGFONT* plgfnt			[in/out]: ����
	����ֵ��
	bool								: ����true
	���ã���ȡ����
	*********************************************************************/
	bool GetTextFont( LOGFONT* plgfnt);

	/********************************************************************
	��������SetTextFont
	������ 
	LONG nHeight					[in]: �����С
	bool bBold					[in]: true�Ӵ֣�false���Ӵ�
	bool bItalic					[in]: true��б��false����б
	CString sFaceName				[in]: ������
	����ֵ��
	bool								: ����true
	���ã�set the font for the control
	*********************************************************************/
	bool SetTextFont( LONG nHeight, bool bBold, bool bItalic, const CString& sFaceName );

	/********************************************************************
	��������SetTextFont
	������ 
	LOGFONT lgfnt					[in]: ����
	����ֵ��
	bool								: ����true
	���ã���������
	*********************************************************************/
	bool SetTextFont( const LOGFONT& lgfnt );

	/********************************************************************
	��������GetTextClr
	������ 
	LOGFONT lgfnt				[in/out]: ����
	����ֵ��
	bool								: ����true
	���ã���ȡ����
	*********************************************************************/
	bool GetTextClr(COLORREF &clr);

	/********************************************************************
	��������SetTextClr
	������ 
	LOGFONT lgfnt					[in]: ����
	����ֵ��
	bool								: ����true
	���ã���������
	*********************************************************************/
	bool SetTextClr( COLORREF clr );

	/********************************************************************
	��������GetBkClr
	������ 
	LOGFONT lgfnt				[in/out]: ��ɫ
	����ֵ��
	bool								: ����true
	���ã���ȡ��ɫ
	*********************************************************************/
	bool GetBkClr(COLORREF &clr);

	/********************************************************************
	��������SetBkClr
	������ 
	LOGFONT lgfnt					[in]: ��ɫ
	����ֵ��
	bool								: ����true
	���ã����ñ�����ɫ
	*********************************************************************/
	bool SetBkClr( COLORREF clr );

	/********************************************************************
	��������SetCommonMode
	������ 
	int mode						[in]: 0��ͨ��ʽ
	����ֵ��
	none								
	���ã����ÿؼ�Ϊ��ͨ��ʽ
	*********************************************************************/
	void SetCommonMode(int mode = 0);//

	/********************************************************************
	��������SetLineInf
	������ 
	COLORREF colLineColor				[in]: ������ɫ
	int	nLineWidth					[in]: ���ߴ�ϸ
	����ֵ��
	none									
	���ã����ÿؼ�������ɫ��ϸ
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
