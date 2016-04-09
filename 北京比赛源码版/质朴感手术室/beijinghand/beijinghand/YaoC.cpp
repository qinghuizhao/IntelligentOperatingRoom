// YaoC.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "beijinghand.h"
#include "YaoC.h"
#include "afxdialogex.h"
extern int GesturesNum;
int nFrameY=-1;
extern bool nStop;
bool nXun=TRUE;
bool nStart=FALSE;
int nFr=0;
bool nfr1=TRUE;
bool nfr2=TRUE;
CDJWStatic					m_Y0;					
CDJWStatic					m_Y1;					
CDJWStatic					m_Y2;
CDJWStatic					m_Y3;	
CDJWStatic				    m_Y4;
CDJWStatic				    m_Y5;

// CYaoC �Ի���

IMPLEMENT_DYNAMIC(CYaoC, CDialog)

CYaoC::CYaoC(CWnd* pParent /*=NULL*/)
	: CDialog(CYaoC::IDD, pParent)
{

}

CYaoC::~CYaoC()
{
}

void CYaoC::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_YAO1, m_Y0);
	DDX_Control(pDX, IDC_YAO2, m_Y1);
	DDX_Control(pDX, IDC_YAO3, m_Y2);
	DDX_Control(pDX, IDC_YAO4, m_Y3);
	DDX_Control(pDX, IDC_YAO5, m_Y4);
	DDX_Control(pDX, IDC_YAO6, m_Y5);
}


BEGIN_MESSAGE_MAP(CYaoC, CDialog)
	ON_WM_TIMER()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CYaoC ��Ϣ�������
void CYaoC::startYao(){
	m_Y0.SetTextFont( 9, 0, 0, _T("����") );
	m_Y1.SetTextFont( 9, 0, 0, _T("����") );
	m_Y2.SetTextFont( 9, 0, 0, _T("����") );
	m_Y3.SetTextFont( 9, 0, 0, _T("����") );
	m_Y4.SetTextFont( 9, 0, 0, _T("����") );
	m_Y5.SetTextFont( 9, 0, 0, _T("����") );
	m_Y0.InitControl(IDB_BITMAP5, IDB_smallheadup, IDB_smallheadup);	//����ͼƬ
	m_Y1.InitControl(IDB_BITMAP5, IDB_smallheaddown, IDB_bigheaddown);	//����ͼƬ
	m_Y2.InitControl(IDB_BITMAP7, IDB_smallleft, IDB_bigleft);
	m_Y3.InitControl(IDB_BITMAP6, IDB_smallright, IDB_bigright);	
	m_Y4.InitControl(IDB_BITMAP7, IDB_smallfootup, IDB_bigfootup);
	m_Y5.InitControl(IDB_BITMAP6, IDB_smallfootdown, IDB_bigfootdown);
	/*m_Y0.SetCheck(TRUE);
	m_Y1.SetCheck(FALSE);
	m_Y2.SetCheck(FALSE);
	m_Y3.SetCheck(FALSE);
	m_Y4.SetCheck(FALSE);	
	m_Y5.SetCheck(FALSE);*/
	if(nXun==TRUE){
		nfr2=TRUE;
		nStop=TRUE;
	if (GesturesNum==2)
	{
		nFr=1;
		nFrameY=nFrameY+1;
		nFrameY=nFrameY%6;
		if (nFrameY==0)
		{
			m_Y0.SetCheck(TRUE);
			m_Y1.SetCheck(FALSE);
			m_Y2.SetCheck(FALSE);
			m_Y3.SetCheck(FALSE);
			m_Y4.SetCheck(FALSE);	
			m_Y5.SetCheck(FALSE);
		}
		else if  (nFrameY==1)
		{
			m_Y0.SetCheck(FALSE);
			m_Y1.SetCheck(TRUE);
			m_Y2.SetCheck(FALSE);
			m_Y3.SetCheck(FALSE);
			m_Y4.SetCheck(FALSE);
			m_Y5.SetCheck(FALSE);
		}
		else if (nFrameY==2)
		{
			m_Y0.SetCheck(FALSE);
			m_Y1.SetCheck(FALSE);
			m_Y2.SetCheck(TRUE);
			m_Y3.SetCheck(FALSE);
			m_Y4.SetCheck(FALSE);
			m_Y5.SetCheck(FALSE);

		}
		else if (nFrameY==3)
		{
			m_Y0.SetCheck(FALSE);
			m_Y1.SetCheck(FALSE);
			m_Y2.SetCheck(FALSE);
			m_Y3.SetCheck(TRUE);
			m_Y4.SetCheck(FALSE);
			m_Y5.SetCheck(FALSE);

		}
		else if (nFrameY==4)
		{
			m_Y0.SetCheck(FALSE);
			m_Y1.SetCheck(FALSE);
			m_Y2.SetCheck(FALSE);
			m_Y3.SetCheck(FALSE);
			m_Y4.SetCheck(TRUE);
			m_Y5.SetCheck(FALSE);

		}
		else if (nFrameY==5)
		{
			m_Y0.SetCheck(FALSE);
			m_Y1.SetCheck(FALSE);
			m_Y2.SetCheck(FALSE);
			m_Y3.SetCheck(FALSE);
			m_Y4.SetCheck(FALSE);
			m_Y5.SetCheck(TRUE);

		}

	}
	if (GesturesNum==1)
	{
		nFr=1;
		nFrameY=nFrameY+5;
		nFrameY=nFrameY%6;
		if (nFrameY==0)
		{
			m_Y0.SetCheck(TRUE);
			m_Y1.SetCheck(FALSE);
			m_Y2.SetCheck(FALSE);
			m_Y3.SetCheck(FALSE);
			m_Y4.SetCheck(FALSE);
			m_Y5.SetCheck(FALSE);

		}
		else if  (nFrameY==1)
		{
			m_Y0.SetCheck(FALSE);
			m_Y1.SetCheck(TRUE);
			m_Y2.SetCheck(FALSE);
			m_Y3.SetCheck(FALSE);
			m_Y4.SetCheck(FALSE);
			m_Y5.SetCheck(FALSE);

		}
		else if (nFrameY==2)
		{
			m_Y0.SetCheck(FALSE);
			m_Y1.SetCheck(FALSE);  
			m_Y2.SetCheck(TRUE);
			m_Y3.SetCheck(FALSE);
			m_Y4.SetCheck(FALSE);
			m_Y5.SetCheck(FALSE);

		}
		else if (nFrameY==3)
		{
			m_Y0.SetCheck(FALSE);
			m_Y1.SetCheck(FALSE);
			m_Y2.SetCheck(FALSE);
			m_Y3.SetCheck(TRUE);
			m_Y4.SetCheck(FALSE);
			m_Y5.SetCheck(FALSE); 

		}
		else if (nFrameY==4)
		{
			m_Y0.SetCheck(FALSE);
			m_Y1.SetCheck(FALSE);
			m_Y2.SetCheck(FALSE);
			m_Y3.SetCheck(FALSE);
			m_Y4.SetCheck(TRUE);
			m_Y5.SetCheck(FALSE);

		}
		else if (nFrameY==5)
		{
			m_Y0.SetCheck(FALSE);
			m_Y1.SetCheck(FALSE);
			m_Y2.SetCheck(FALSE);
			m_Y3.SetCheck(FALSE);
			m_Y4.SetCheck(FALSE);
			m_Y5.SetCheck(TRUE);
		}
	}
	else if (GesturesNum==3&&nFr>0)
	{
		if (nfr1==TRUE)
		{
		nXun=FALSE;
		nStop=FALSE;
		int count =nFrameY+1;
		startcontrol(count);
		nfr1=FALSE;
		}		 
	}	
	}
 if (GesturesNum==4&&nXun==FALSE)
{
	if(nfr2==TRUE){
		startcontrol(-5);
		nXun=TRUE;
		nfr1=TRUE;
		nfr2=FALSE;
	}
 }
}
void CYaoC::closeYaoc(){
    nFrameY=-1;
	m_Y0.SetCheck(FALSE);
	m_Y1.SetCheck(FALSE);
	m_Y2.SetCheck(FALSE);
	m_Y3.SetCheck(FALSE);
	m_Y4.SetCheck(FALSE);
	m_Y5.SetCheck(FALSE);
}
//if (nStart=TRUE)
//{
//	/*CString str;
//	int count =nFrameY+1;
//	str.Format("��ť=%d",count);
//	SetDlgItemText(IDC_Result,str);*/
//	
//}

//	SetTimer(1,2000,NULL);
//	SetTimer(2,20,NULL);

//}
void CYaoC::startcontrol(int cout){
	const int BUF_SIZE = 64;
	WSADATA wsd; //WSADATA����
	SOCKET sHost; //�������׽���
	SOCKADDR_IN servAddr; //��������ַ
	char buf[BUF_SIZE]; //�������ݻ�����
	char bufRecv[BUF_SIZE];
	int retVal; //����ֵ
	//��ʼ���׽��ֶ�̬��
   WSAStartup(MAKEWORD(2,2), &wsd) ;
	//�����׽���
	sHost = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	//���÷�������ַ�Ͷ˿�
	servAddr.sin_family =AF_INET;
	servAddr.sin_addr.s_addr = inet_addr("192.168.118.56");
	servAddr.sin_port = htons((short)60001);
	int nServAddlen  = sizeof(servAddr);
	//���ӷ�����
	retVal=connect(sHost,(LPSOCKADDR)&servAddr, sizeof(servAddr));
	//���������������
	ZeroMemory(buf, BUF_SIZE);
	sprintf(buf,"%d",cout);
	retVal = send(sHost, buf, strlen(buf), 0);
		//RecvLine(sHost, bufRecv);
	/*ZeroMemory(bufRecv, BUF_SIZE);*/
	//recv(sHost, bufRecv,BUF_SIZE , 0); // ���շ������˵����ݣ� ֻ����5���ַ�
	closesocket(sHost); //�ر��׽���
	WSACleanup(); //�ͷ��׽�����Դ
}

void CYaoC::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (1==nIDEvent)
	{

		if (GesturesNum==2)
		{
			nFrameY=nFrameY+1;
			nFrameY=nFrameY%5;
			if (nFrameY==0)
			{
				m_Y0.SetCheck(TRUE);
				m_Y1.SetCheck(FALSE);
				m_Y2.SetCheck(FALSE);
				m_Y3.SetCheck(FALSE);
				m_Y4.SetCheck(FALSE);	
				m_Y5.SetCheck(FALSE);
			}
			else if  (nFrameY==1)
			{
				m_Y0.SetCheck(FALSE);
				m_Y1.SetCheck(TRUE);
				m_Y2.SetCheck(FALSE);
				m_Y3.SetCheck(FALSE);
				m_Y4.SetCheck(FALSE);
				m_Y5.SetCheck(FALSE);
			}
			else if (nFrameY==2)
			{
				m_Y0.SetCheck(FALSE);
				m_Y1.SetCheck(FALSE);
				m_Y2.SetCheck(TRUE);
				m_Y3.SetCheck(FALSE);
				m_Y4.SetCheck(FALSE);
				m_Y5.SetCheck(FALSE);

			}
			else if (nFrameY==3)
			{
				m_Y0.SetCheck(FALSE);
				m_Y1.SetCheck(FALSE);
				m_Y2.SetCheck(FALSE);
				m_Y3.SetCheck(TRUE);
				m_Y4.SetCheck(FALSE);
				m_Y5.SetCheck(FALSE);

			}
			else if (nFrameY==4)
			{
				m_Y0.SetCheck(FALSE);
				m_Y1.SetCheck(FALSE);
				m_Y2.SetCheck(FALSE);
				m_Y3.SetCheck(FALSE);
				m_Y4.SetCheck(TRUE);
				m_Y5.SetCheck(FALSE);

			}
			else if (nFrameY==5)
			{
				m_Y0.SetCheck(FALSE);
				m_Y1.SetCheck(FALSE);
				m_Y2.SetCheck(FALSE);
				m_Y3.SetCheck(FALSE);
				m_Y4.SetCheck(FALSE);
				m_Y5.SetCheck(TRUE);

			}

		}
		if (GesturesNum==1)
		{
			nFrameY=nFrameY+4;
			nFrameY=nFrameY%5;
			if (nFrameY==0)
			{
				m_Y0.SetCheck(TRUE);
				m_Y1.SetCheck(FALSE);
				m_Y2.SetCheck(FALSE);
				m_Y3.SetCheck(FALSE);
				m_Y4.SetCheck(FALSE);
				m_Y5.SetCheck(FALSE);

			}
			else if  (nFrameY==1)
			{
				m_Y0.SetCheck(FALSE);
				m_Y1.SetCheck(TRUE);
				m_Y2.SetCheck(FALSE);
				m_Y3.SetCheck(FALSE);
				m_Y4.SetCheck(FALSE);
				m_Y5.SetCheck(FALSE);

			}
			else if (nFrameY==2)
			{
				m_Y0.SetCheck(FALSE);
				m_Y1.SetCheck(FALSE);  
				m_Y2.SetCheck(TRUE);
				m_Y3.SetCheck(FALSE);
				m_Y4.SetCheck(FALSE);
				m_Y5.SetCheck(FALSE);

			}
			else if (nFrameY==3)
			{
				m_Y0.SetCheck(FALSE);
				m_Y1.SetCheck(FALSE);
				m_Y2.SetCheck(FALSE);
				m_Y3.SetCheck(TRUE);
				m_Y4.SetCheck(FALSE);
				m_Y5.SetCheck(FALSE);

			}
			else if (nFrameY==4)
			{
				m_Y0.SetCheck(FALSE);
				m_Y1.SetCheck(FALSE);
				m_Y2.SetCheck(FALSE);
				m_Y3.SetCheck(FALSE);
				m_Y4.SetCheck(TRUE);
				m_Y5.SetCheck(FALSE);

			}
			else if (nFrameY==5)
			{
				m_Y0.SetCheck(FALSE);
				m_Y1.SetCheck(FALSE);
				m_Y2.SetCheck(FALSE);
				m_Y3.SetCheck(FALSE);
				m_Y4.SetCheck(FALSE);
				m_Y5.SetCheck(TRUE);

			}
		}
	}
	else if (2==nIDEvent)
	{
		if (GesturesNum==3)
		{
			KillTimer(1);
			 //������Ϣ
			nStop=FALSE;
			CString str;
			int count =nFrameY+1;
			str.Format("��ť=%d",count);
			SetDlgItemText(IDC_Result,str);
            SetTimer(3,1,NULL);

		}
	 
	}
	else if (3==nIDEvent)
	{
		if (GesturesNum==4)
		{
			KillTimer(3);
			nStop=TRUE;
			SetTimer(1,2000,NULL);
		}
	}
	CDialog::OnTimer(nIDEvent);
}

void  CYaoC::printi(){
	CString str;
	int count =nFrameY+1;
	str.Format("��ť=%d",count);
	SetDlgItemText(IDC_Result,str);
}
void CYaoC::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnPaint()
	//���ñ���ͼƬ
	CRect    rect;  
	GetClientRect(&rect);  
	CDC    *pDC=GetDC();  
	CDC    memdc;  
	memdc.CreateCompatibleDC(pDC);  
	CBitmap    bitmap;  
	//����Դ������λͼ  
	bitmap.LoadBitmap(IDB_chuangback);  
	memdc.SelectObject(bitmap);  
	pDC->BitBlt(0,0,rect.Width(),rect.Height(),&memdc,0,0,SRCCOPY);
}
