// Reading.cpp : 实现文件
//
#pragma once
#include "stdafx.h"
#include "beijinghand.h"
#include "Reading.h"
#include "afxdialogex.h"
#include "beijinghandDlg.h"
CDJWStatic					m_s0;					
CDJWStatic					m_s1;					
CDJWStatic					m_s2;
CDJWStatic					m_s3;	
CDJWStatic				    m_s4;	
extern int GesturesNum;
int nFrame0=-1;
extern bool nStop;
bool readP1_2=TRUE;
bool readP3=TRUE;
bool readP4=TRUE;
int nfrread=0;
// CReading 对话框

IMPLEMENT_DYNAMIC(CReading, CDialog)

CReading::CReading(CWnd* pParent /*=NULL*/)
	: CDialog(CReading::IDD, pParent)
{
	read1 = imread("res/12.bmp");
	read2 = imread("res/12.bmp");
	read3 = imread("res/12.bmp");
	read4 = imread("res/12.bmp");
	read5 = imread("res/12.bmp");
}

CReading::~CReading()
{
}

void CReading::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_YUE1, m_s0);
	DDX_Control(pDX, IDC_YUE2, m_s1);
	DDX_Control(pDX, IDC_YUE3, m_s2);
	DDX_Control(pDX, IDC_YUE4, m_s3);
	DDX_Control(pDX, IDC_YUE5, m_s4);
}


BEGIN_MESSAGE_MAP(CReading, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CReading 消息处理程序


void CReading::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	//设置背景图片
	CRect    rect;  
	GetClientRect(&rect);  
	CDC    *pDC=GetDC();  
	CDC    memdc;  
	memdc.CreateCompatibleDC(pDC);  
	CBitmap    bitmap;  
	//从资源中载入位图  
	bitmap.LoadBitmap(IDB_readback);  
	memdc.SelectObject(bitmap);  
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memdc,0,0,SRCCOPY);
}
void CReading::YueP(){
	m_s0.SetTextFont( 9, 0, 0, _T("宋体") );
	m_s1.SetTextFont( 9, 0, 0, _T("宋体") );
	m_s2.SetTextFont( 9, 0, 0, _T("宋体") );
	m_s3.SetTextFont( 9, 0, 0, _T("宋体") );
	m_s4.SetTextFont( 9, 0, 0, _T("宋体") );
		//设置图片
	m_s0.InitControl(IDB_BITMAP5, IDB_smallwaike, IDB_bigwaike);	//设置图片
	m_s1.InitControl(IDB_BITMAP5, IDB_smallshenjing, IDB_bigshenjing);
	m_s2.InitControl(IDB_BITMAP6, IDB_smallneike, IDB_bigneike);
	m_s3.InitControl(IDB_BITMAP7, IDB_smallwuguan, IDB_bigwuguan);
	m_s4.InitControl(IDB_BITMAP6, IDB_smallchuanran, IDB_bigchuanran);
	if(readP1_2==TRUE){
		nfrread=1;
		readP4=TRUE;
		nStop=TRUE;
		if (GesturesNum==2)
		{
			nFrame0=nFrame0+1;
			nFrame0=nFrame0%5;
			if (nFrame0==0)
			{
				m_s0.SetCheck(TRUE);
				m_s1.SetCheck(FALSE);
				m_s2.SetCheck(FALSE);
				m_s3.SetCheck(FALSE);
				m_s4.SetCheck(FALSE);	
			}
			else if  (nFrame0==1)
			{
				m_s0.SetCheck(FALSE);
				m_s1.SetCheck(TRUE);
				m_s2.SetCheck(FALSE);
				m_s3.SetCheck(FALSE);
				m_s4.SetCheck(FALSE);
			}
			else if (nFrame0==2)
			{
				m_s0.SetCheck(FALSE);
				m_s1.SetCheck(FALSE);
				m_s2.SetCheck(TRUE);
				m_s3.SetCheck(FALSE);
				m_s4.SetCheck(FALSE);
	
			}
			else if (nFrame0==3)
			{
				m_s0.SetCheck(FALSE);
				m_s1.SetCheck(FALSE);
				m_s2.SetCheck(FALSE);
				m_s3.SetCheck(TRUE);
				m_s4.SetCheck(FALSE);
	
			}
			else if (nFrame0==4)
			{
				m_s0.SetCheck(FALSE);
				m_s1.SetCheck(FALSE);
				m_s2.SetCheck(FALSE);
				m_s3.SetCheck(FALSE);
				m_s4.SetCheck(TRUE);
	
			}
			
		}
		if (GesturesNum==1)
		{
			nfrread=1;
			nFrame0=nFrame0+4;
			nFrame0=nFrame0%5;
			if (nFrame0==0)
			{
				m_s0.SetCheck(TRUE);
				m_s1.SetCheck(FALSE);
				m_s2.SetCheck(FALSE);
				m_s3.SetCheck(FALSE);
				m_s4.SetCheck(FALSE);
	
			}
			else if  (nFrame0==1)
			{
				m_s0.SetCheck(FALSE);
				m_s1.SetCheck(TRUE);
				m_s2.SetCheck(FALSE);
				m_s3.SetCheck(FALSE);
				m_s4.SetCheck(FALSE);
			}
			else if (nFrame0==2)
			{
				m_s0.SetCheck(FALSE);
				m_s1.SetCheck(FALSE);  
				m_s2.SetCheck(TRUE);
				m_s3.SetCheck(FALSE);
				m_s4.SetCheck(FALSE);
	
			}
			else if (nFrame0==3)
			{
				m_s0.SetCheck(FALSE);
				m_s1.SetCheck(FALSE);
				m_s2.SetCheck(FALSE);
				m_s3.SetCheck(TRUE);
				m_s4.SetCheck(FALSE);
	
			}
			else if (nFrame0==4)
			{
				m_s0.SetCheck(FALSE);
				m_s1.SetCheck(FALSE);
				m_s2.SetCheck(FALSE);
				m_s3.SetCheck(FALSE);
				m_s4.SetCheck(TRUE);
	
			}
		}

		else if (GesturesNum==3&&nfrread>0)
		{
			if (readP3==TRUE)
			{
				if (nFrame0==0)
				{					
					namedWindow("ghj");
					imshow("ghj", read1);
					waitKey(10);
				}
				else if (nFrame0==1)
				{
					namedWindow("ghj");
					imshow("ghj", read2);
					waitKey(10);
				}
				else if (nFrame0==2)
				{
					namedWindow("ghj");
					imshow("ghj", read3);
					waitKey(10);
				}
				else if (nFrame0==3)
				{
					namedWindow("ghj");
					imshow("ghj", read4);
					waitKey(10);
				}
				else if (nFrame0==4)
				{
					namedWindow("ghj");
					imshow("ghj", read5);
					waitKey(10);
				}
				
				readP1_2=FALSE;
				nStop=FALSE;			
				readP3=FALSE;

			}	
		}
}
if (GesturesNum==4&&readP1_2==FALSE)
{
	if(readP4==TRUE){
		if (nFrame0==0)
		{
			destroyWindow("ghj");
		}
		else if (nFrame0==1)
		{
			destroyWindow("ghj");
		}
		else if (nFrame0==2)
		{
			destroyWindow("ghj");
		}
		else if (nFrame0==3)
		{
			destroyWindow("ghj");
		}
		else if (nFrame0==4)
		{
			destroyWindow("ghj");
		}
		readP1_2=TRUE;
		readP3=TRUE;
		readP4=FALSE;
	}
}

}
void CReading::CloseYueP(){
	m_s0.SetCheck(FALSE);
	m_s1.SetCheck(FALSE);
	m_s2.SetCheck(FALSE);
	m_s3.SetCheck(FALSE);
	m_s4.SetCheck(FALSE);
    nFrame0=-1;
}

////while(GesturesNum<=3){
////	
////	GesturesNum=2;
////	if (GesturesNum==2)
////	{
////		nFrame0=nFrame0+1;
////		nFrame0=nFrame0%5;
////		if (nFrame0==0)
////		{
////			m_s0.SetCheck(TRUE);
////			m_s1.SetCheck(FALSE);
////			m_s2.SetCheck(FALSE);
////			m_s3.SetCheck(FALSE);
////			m_s4.SetCheck(FALSE);
////
////		}
////		else if  (nFrame0==1)
////		{
////			m_s0.SetCheck(FALSE);
////			m_s1.SetCheck(TRUE);
////			m_s2.SetCheck(FALSE);
////			m_s3.SetCheck(FALSE);
////			m_s4.SetCheck(FALSE);
////		}
////		else if (nFrame0==2)
////		{
////			m_s0.SetCheck(FALSE);
////			m_s1.SetCheck(FALSE);
////			m_s2.SetCheck(TRUE);
////			m_s3.SetCheck(FALSE);
////			m_s4.SetCheck(FALSE);
////
////		}
////		else if (nFrame0==3)
////		{
////			m_s0.SetCheck(FALSE);
////			m_s1.SetCheck(FALSE);
////			m_s2.SetCheck(FALSE);
////			m_s3.SetCheck(TRUE);
////			m_s4.SetCheck(FALSE);
////
////		}
////		else if (nFrame0==4)
////		{
////			m_s0.SetCheck(FALSE);
////			m_s1.SetCheck(FALSE);
////			m_s2.SetCheck(FALSE);
////			m_s3.SetCheck(FALSE);
////			m_s4.SetCheck(TRUE);
////
////		}
////		nFrame0=nFrame0+1;
////	}
////	if (GesturesNum==1)
////	{
////		nFrame0=nFrame0+2;
////		nFrame0=nFrame0%5;
////		if (nFrame0==0)
////		{
////			m_s0.SetCheck(TRUE);
////			m_s1.SetCheck(FALSE);
////			m_s2.SetCheck(FALSE);
////			m_s3.SetCheck(FALSE);
////			m_s4.SetCheck(FALSE);
////
////		}
////		else if  (nFrame0==1)
////		{
////			m_s0.SetCheck(FALSE);
////			m_s1.SetCheck(TRUE);
////			m_s2.SetCheck(FALSE);
////			m_s3.SetCheck(FALSE);
////			m_s4.SetCheck(FALSE);
////		}
////		else if (nFrame0==2)
////		{
////			m_s0.SetCheck(FALSE);
////			m_s1.SetCheck(FALSE);  
////			m_s2.SetCheck(TRUE);
////			m_s3.SetCheck(FALSE);
////			m_s4.SetCheck(FALSE);
////
////		}
////		else if (nFrame0==3)
////		{
////			m_s0.SetCheck(FALSE);
////			m_s1.SetCheck(FALSE);
////			m_s2.SetCheck(FALSE);
////			m_s3.SetCheck(TRUE);
////			m_s4.SetCheck(FALSE);
////
////		}
////		else if (nFrame0==4)
////		{
////			m_s0.SetCheck(FALSE);
////			m_s1.SetCheck(FALSE);
////			m_s2.SetCheck(FALSE);
////			m_s3.SetCheck(FALSE);
////			m_s4.SetCheck(TRUE);
////
////		}
////		nFrame0=nFrame0+2;
////	}
