#pragma once
#include "DJWStatic.h"
#include "cv.hpp"

using namespace cv;
// CReading �Ի���

class CReading : public CDialog
{
	DECLARE_DYNAMIC(CReading)

public:
	CReading(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReading();

// �Ի�������
	enum { IDD = IDD_LANPIAN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	void YueStart();
	void YueP();
	void CloseYueP();	
public:
	Mat read1;
	Mat read2;
	Mat read3;
	Mat read4;
	Mat read5;

};
