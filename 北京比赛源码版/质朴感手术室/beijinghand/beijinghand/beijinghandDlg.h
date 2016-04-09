
// beijinghandDlg.h : ͷ�ļ�
//

#pragma once
#include "DJWStatic.h"
#include <vector>  
#include <XnCppWrapper.h>   
#include <XnModuleCppInterface.h>   
#include "cv.h"  
#include "highgui.h"
#include "PhoneDlg.h"
#include "Reading.h"
#include "CHMXStatic.h"
#include "YaoC.h"
// CbeijinghandDlg �Ի���
class CbeijinghandDlg : public CDialogEx
{
// ����
public:
	CbeijinghandDlg(CWnd* pParent = NULL);	// ��׼���캯��
	CReading reading;
	CYaoC    yaochuang;

// �Ի�������
	enum { IDD = IDD_BEIJINGHAND_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	//��ʼ��UI
	void InitUI();
private:
	CBrush						m_brBk;							//������ˢ
public:
	CHMXStatic					m_staVersion;					//�ؼ��������汾��
	CHMXStatic					m_staAuthor;					//�ؼ�����������
	CHMXStatic					m_staEmail;		
private:
	//��dlg1
	CPhoneDlg*					m_phonedlg;		
	CReading*                   m_readingdlg;
	CYaoC*                      m_yaocdlg;
	CPhoneDlg                   m_phone;
	//CChildDlg3*					m_dlg3;							//��dlg3
	//CChildDlg4*					m_dlg4;
	
	
// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void DrawPicToHDC(IplImage *img,unsigned int id);
};
