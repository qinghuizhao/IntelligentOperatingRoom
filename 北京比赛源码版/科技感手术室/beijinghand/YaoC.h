#pragma once
#include "DJWStatic.h"
#include "WinSock2.h"
#pragma comment(lib, "ws2_32.lib")  

// CYaoC �Ի���

class CYaoC : public CDialog
{
	DECLARE_DYNAMIC(CYaoC)

public:
	CYaoC(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CYaoC();

// �Ի�������
	enum { IDD = IDD_YaoC };
public:
	
public:
	void startYao();
	void startcontrol(int cout);
	void  printi();
	void closeYaoc();
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnPaint();
	afx_msg void OnStnClickedYao1();
};
