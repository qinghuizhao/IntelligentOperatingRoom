#pragma once
#include "stdafx.h"
#include <WinSock2.h>
#include <stdio.h>
#include <string>
#pragma comment(lib,"Ws2_32")
#include<iostream>
#include "highgui.h"
#include "cv.h"
#include "CvvImage.h"
#include "DJWStatic.h"
using namespace std;
// CPhoneDlg 对话框

class CPhoneDlg : public CDialog
{
	DECLARE_DYNAMIC(CPhoneDlg)


public:
	CPhoneDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPhoneDlg();
public:
	void phoneconnetion();
	void closeconnetion();
	/*void DrawPicToHDC(IplImage *img,unsigned int id);*/
	void startPhone();
	void ClosePhone();

// 对话框数据
	enum { IDD = IDD_CALLDLG };
public:
	//CvCapture *capture ;
	///*IplImage *dst ;*/
	//IplImage *showimage;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
};
