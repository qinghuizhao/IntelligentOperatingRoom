// PhoneDlg.cpp : 实现文件
//
#pragma once
#include "stdafx.h"
#include "beijinghand.h"
#include "PhoneDlg.h"
#include "afxdialogex.h"
#include "beijinghandDlg.h"
extern IplImage* dst;
extern int GesturesNum;
CDJWStatic					m_phone0;					
CDJWStatic					m_phone1;					
CDJWStatic					m_phone2;
CDJWStatic					m_phone3;	
CDJWStatic				    m_phone4;
int nFramephone=-1;
extern bool nStop;
bool phone1_2=TRUE;
bool phone3=TRUE;
bool phone4=TRUE;
int nfrphone=0;

// CPhoneDlg 对话框

IMPLEMENT_DYNAMIC(CPhoneDlg, CDialog)

	CPhoneDlg::CPhoneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPhoneDlg::IDD, pParent)
{

}

CPhoneDlg::~CPhoneDlg()
{
}

void CPhoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Phone1, m_phone0);
	DDX_Control(pDX, IDC_Phone2, m_phone1);
	DDX_Control(pDX, IDC_Phone3, m_phone2);
	DDX_Control(pDX, IDC_Phone4, m_phone3);
	DDX_Control(pDX, IDC_Phone5, m_phone4);
}


BEGIN_MESSAGE_MAP(CPhoneDlg, CDialog)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPhoneDlg 消息处理程序
void CPhoneDlg::startPhone()
{
	m_phone0.SetTextFont( 9, 0, 0, _T("宋体") );
	m_phone1.SetTextFont( 9, 0, 0, _T("宋体") );
	m_phone2.SetTextFont( 9, 0, 0, _T("宋体") );
	m_phone3.SetTextFont( 9, 0, 0, _T("宋体") );
	m_phone4.SetTextFont( 9, 0, 0, _T("宋体") );
	m_phone0.InitControl(IDB_jianbeijing1, IDB_smallwaike, IDB_bigwaike);	//设置图片
	m_phone1.InitControl(IDB_jianbeijing2, IDB_smallshenjing, IDB_bigshenjing);	//设置图片
	m_phone2.InitControl(IDB_jianbeijing3, IDB_smallneike, IDB_bigneike);
	m_phone3.InitControl(IDB_jianbeijing4, IDB_smallwuguan, IDB_bigwuguan);
	m_phone4.InitControl(IDB_jianbeijing5, IDB_smallchuanran, IDB_bigchuanran);
	if(phone1_2==TRUE){
		nfrphone=1;
		phone4=TRUE;
		nStop=TRUE;
		if (GesturesNum==2)
		{
			nFramephone=nFramephone+1;
			nFramephone=nFramephone%5;
			if (nFramephone==0)
			{
				m_phone0.SetCheck(TRUE);
				m_phone1.SetCheck(FALSE);
				m_phone2.SetCheck(FALSE);
				m_phone3.SetCheck(FALSE);
				m_phone4.SetCheck(FALSE);	
			}
			else if  (nFramephone==1)
			{
				m_phone0.SetCheck(FALSE);
				m_phone1.SetCheck(TRUE);
				m_phone2.SetCheck(FALSE);
				m_phone3.SetCheck(FALSE);
				m_phone4.SetCheck(FALSE);
			}
			else if (nFramephone==2)
			{
				m_phone0.SetCheck(FALSE);
				m_phone1.SetCheck(FALSE);
				m_phone2.SetCheck(TRUE);
				m_phone3.SetCheck(FALSE);
				m_phone4.SetCheck(FALSE);

			}
			else if (nFramephone==3)
			{
				m_phone0.SetCheck(FALSE);
				m_phone1.SetCheck(FALSE);
				m_phone2.SetCheck(FALSE);
				m_phone3.SetCheck(TRUE);
				m_phone4.SetCheck(FALSE);

			}
			else if (nFramephone==4)
			{
				m_phone0.SetCheck(FALSE);
				m_phone1.SetCheck(FALSE);
				m_phone2.SetCheck(FALSE);
				m_phone3.SetCheck(FALSE);
				m_phone4.SetCheck(TRUE);

			}

		}
		if (GesturesNum==1)
		{
			nfrphone=1;
			nFramephone=nFramephone+4;
			nFramephone=nFramephone%5;
			if (nFramephone==0)
			{
				m_phone0.SetCheck(TRUE);
				m_phone1.SetCheck(FALSE);
				m_phone2.SetCheck(FALSE);
				m_phone3.SetCheck(FALSE);
				m_phone4.SetCheck(FALSE);

			}
			else if  (nFramephone==1)
			{
				m_phone0.SetCheck(FALSE);
				m_phone1.SetCheck(TRUE);
				m_phone2.SetCheck(FALSE);
				m_phone3.SetCheck(FALSE);
				m_phone4.SetCheck(FALSE);
			}
			else if (nFramephone==2)
			{
				m_phone0.SetCheck(FALSE);
				m_phone1.SetCheck(FALSE);  
				m_phone2.SetCheck(TRUE);
				m_phone3.SetCheck(FALSE);
				m_phone4.SetCheck(FALSE);

			}
			else if (nFramephone==3)
			{
				m_phone0.SetCheck(FALSE);
				m_phone1.SetCheck(FALSE);
				m_phone2.SetCheck(FALSE);
				m_phone3.SetCheck(TRUE);
				m_phone4.SetCheck(FALSE);

			}
			else if (nFramephone==4)
			{
				m_phone0.SetCheck(FALSE);
				m_phone1.SetCheck(FALSE);
				m_phone2.SetCheck(FALSE);
				m_phone3.SetCheck(FALSE);
				m_phone4.SetCheck(TRUE);

			}
		}

		else if (GesturesNum==3&&nfrphone>0)
		{
			if (phone3==TRUE)
			{

				phone1_2=FALSE;
				nStop=FALSE;			
				phone3=FALSE;
				phoneconnetion();

			}	
		}
	}
	if (GesturesNum==4&&phone1_2==FALSE)
	{
		if(phone4==TRUE){
			closeconnetion();
			phone1_2=TRUE;
			phone3=TRUE; 
			phone4=FALSE;
		}
	}

}
void CPhoneDlg::ClosePhone(){
	m_phone0.SetCheck(FALSE);
	m_phone1.SetCheck(FALSE);
	m_phone2.SetCheck(FALSE);
	m_phone3.SetCheck(FALSE);
	m_phone4.SetCheck(FALSE);
    nFramephone=-1;
}

void CPhoneDlg::phoneconnetion()
{
	//加载套接字库
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1,1);
	err = WSAStartup(wVersionRequested,&wsaData);
	if (err!=0)
	{
		cout<<"error";
	}
	if (LOBYTE(wsaData.wVersion)!=1||HIBYTE(wsaData.wVersion)!=1)
	{
		WSACleanup();
		cout<<"error";
	}
	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = inet_addr("192.168.118.56");
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);
	int np=0;
	//视频头
	int len = sizeof(SOCKADDR);
	IplImage* frame;
	cvNamedWindow("videophone");
	while(GesturesNum<=3){
		SOCKET sockClient = socket(AF_INET,SOCK_STREAM,0);
		//向服务器发送连接请求
		connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
		//发送数据
		char recvBuf[1000];
		memset(recvBuf,0,sizeof(recvBuf));
		FILE* tof=fopen("output.jpg","wb+");
		while (recv(sockClient,recvBuf,40,0)>0)
		{
			fwrite(recvBuf,sizeof(char),40,tof);
		}
		fclose(tof);
		closesocket(sockClient);
		SOCKET sockClient1 = socket(AF_INET,SOCK_STREAM,0);
		//向服务器发送连接请求
		connect(sockClient1,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
		char sendBuf[1000];
		cvSaveImage("input.jpg",dst);
		memset(sendBuf,0,sizeof(sendBuf));
		FILE* fp=fopen("input.jpg","rb+");		
		int rc; 
		while( (rc=fread(sendBuf,sizeof(unsigned char),40,fp)) != 0 )
		{
			send(sockClient1,sendBuf,40,0);
		}
		fclose(fp);		
		closesocket(sockClient1);
		IplImage *showimage=cvLoadImage("output.jpg");
		
		cvShowImage("videophone",showimage);
		cvWaitKey(100);
		cvReleaseImage(&showimage);
		np=np+1;

	}
	cvDestroyWindow("videophone");
	WSACleanup();	

}
void CPhoneDlg::closeconnetion()
{
	/*cvReleaseImage(&showimage);
	cvReleaseImage(&dst);*/
	/*cvReleaseCapture(&capture);*/

	WSACleanup();
}


void CPhoneDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialog::OnPaint()
	CRect    rect;  
	GetClientRect(&rect);  
	CDC    *pDC=GetDC();  
	CDC    memdc;  
	memdc.CreateCompatibleDC(pDC);  
	CBitmap    bitmap;  
	//从资源中载入位图  
	bitmap.LoadBitmap(IDB_videophone);  
	memdc.SelectObject(bitmap);  
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memdc,0,0,SRCCOPY);
}
