
#pragma once
#ifndef _DJWSTATIC_H
#define _DJWSTATIC_H

class CDJWStatic : public CStatic
{
public:
	//构造函数
    CDJWStatic();
	//析构函数
    virtual ~CDJWStatic();

protected:
    virtual void PreSubclassWindow();
	virtual BOOL DestroyWindow();

//对外接口
public:
	//控件初始化  参数：unSideBmpID边框图片ID  unCenterBmpID中心小图片ID unCenterBmpSelID中心大图片ID
	void InitControl(UINT unSideBmpID, UINT unCenterBmpID, UINT unCenterBmpSelID);
	//设置按钮选中状态
	void SetCheck(BOOL bCheck);
	//设置边框颜色
	void SetSideColor(COLORREF clSideColor);
	//设置字体
	bool SetTextFont( const LOGFONT& lgfnt );
	//设置字体
	bool SetTextFont( LONG nHeight, bool bBold, bool bItalic, const CString& sFaceName );
	//鼠标按下控件的变化
	void ChangeAfterClicked();

private:
    BOOL			m_bOverControl;			//鼠标是否在控件内                
    UINT			m_nTimerID;				//计时器ID
	BOOL			m_bCheck;				//按钮是否选定
//	BOOL			m_bBKClock;				//TRUE：按钮被选中，背景被锁定
	COLORREF		m_crSideColor;			//边框颜色
	UINT			m_unSideBmpID;			//边框图片资源ID
	UINT			m_unCenterBmpID;		//中心图片资源ID(小)
	UINT			m_unCenterSelBmpID;		//中心图片资源ID(大)
	COLORREF		m_crCheckedColour;		//选中字体颜色
	COLORREF		m_crHotColour;			//鼠标在控件上字体颜色
	COLORREF		m_crNormalColour;		//普通状态下字体颜色
	CFont		    m_fntText;				//字体

protected:
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    //afx_msg void OnClicked();
    DECLARE_MESSAGE_MAP()
};

#endif 
