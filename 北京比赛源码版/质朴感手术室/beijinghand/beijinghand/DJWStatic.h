
#pragma once
#ifndef _DJWSTATIC_H
#define _DJWSTATIC_H

class CDJWStatic : public CStatic
{
public:
	//���캯��
    CDJWStatic();
	//��������
    virtual ~CDJWStatic();

protected:
    virtual void PreSubclassWindow();
	virtual BOOL DestroyWindow();

//����ӿ�
public:
	//�ؼ���ʼ��  ������unSideBmpID�߿�ͼƬID  unCenterBmpID����СͼƬID unCenterBmpSelID���Ĵ�ͼƬID
	void InitControl(UINT unSideBmpID, UINT unCenterBmpID, UINT unCenterBmpSelID);
	//���ð�ťѡ��״̬
	void SetCheck(BOOL bCheck);
	//���ñ߿���ɫ
	void SetSideColor(COLORREF clSideColor);
	//��������
	bool SetTextFont( const LOGFONT& lgfnt );
	//��������
	bool SetTextFont( LONG nHeight, bool bBold, bool bItalic, const CString& sFaceName );
	//��갴�¿ؼ��ı仯
	void ChangeAfterClicked();

private:
    BOOL			m_bOverControl;			//����Ƿ��ڿؼ���                
    UINT			m_nTimerID;				//��ʱ��ID
	BOOL			m_bCheck;				//��ť�Ƿ�ѡ��
//	BOOL			m_bBKClock;				//TRUE����ť��ѡ�У�����������
	COLORREF		m_crSideColor;			//�߿���ɫ
	UINT			m_unSideBmpID;			//�߿�ͼƬ��ԴID
	UINT			m_unCenterBmpID;		//����ͼƬ��ԴID(С)
	UINT			m_unCenterSelBmpID;		//����ͼƬ��ԴID(��)
	COLORREF		m_crCheckedColour;		//ѡ��������ɫ
	COLORREF		m_crHotColour;			//����ڿؼ���������ɫ
	COLORREF		m_crNormalColour;		//��ͨ״̬��������ɫ
	CFont		    m_fntText;				//����

protected:
    afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
    afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
    //afx_msg void OnClicked();
    DECLARE_MESSAGE_MAP()
};

#endif 
