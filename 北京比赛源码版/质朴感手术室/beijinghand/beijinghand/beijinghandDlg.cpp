
// beijinghandDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "beijinghand.h"
#include "beijinghandDlg.h"
#include "afxdialogex.h"
#include "CvvImage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
void  Identify(void *);

void XN_CALLBACK_TYPE NewUser( xn::UserGenerator& generator, XnUserID user,void* pCookie ) ;
void XN_CALLBACK_TYPE LostUser( xn::UserGenerator& generator, XnUserID user,void* pCookie );
void XN_CALLBACK_TYPE CalibrationStart( xn::SkeletonCapability& skeleton,XnUserID user,void* pCookie );
void XN_CALLBACK_TYPE CalibrationEnd( xn::SkeletonCapability& skeleton,XnUserID user,XnCalibrationStatus calibrationError,void* pCookie )  ;
void XN_CALLBACK_TYPE PoseDetected( xn::PoseDetectionCapability& poseDetection,const XnChar* strPose,XnUserID user,void* pCookie)  ;
int  ProcessGesture(XnPoint3D head,XnPoint3D left,XnPoint3D right);
void  startKinect();
int startSkelPoints[14]={1,2,6,6,12,17,6,7,12,13,17,18,21,22};  
int endSkelPoints[14]={2,3,12,21,17,21,7,9,13,15,18,20,22,24}; 
using namespace std;  
using namespace xn;
using namespace cv;
vector<float> nleft1;
vector<float> nleft2;
vector<float> nright1;
vector<float> nright2;
xn::UserGenerator userGenerator;  
xn::DepthGenerator depthGenerator;  
xn::ImageGenerator imageGenerator;
int GesturesNum=0;
CDJWStatic					m_stastart;	
CDJWStatic					m_sta0;	
CDJWStatic					m_sta1;	
CDJWStatic					m_sta2;	
int nFrame=-1;
IplImage *dst ;
IplImage *dstSum ;
IplImage* cameraImg;
bool nfra=FALSE;
bool nVideoPhone=FALSE;
bool nYuepian=FALSE;
bool nYaochuang=FALSE;
bool nStop=TRUE;
/*extern CDJWStatic					m_s0;					
extern CDJWStatic					m_s1;					
extern CDJWStatic					m_s2;
extern CDJWStatic					m_s3;	
extern CDJWStatic				    m_s4;*/	

// CbeijinghandDlg 对话框




CbeijinghandDlg::CbeijinghandDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CbeijinghandDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CbeijinghandDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RUN, m_stastart);
	DDX_Control(pDX, IDC_SYUEPIAN, m_sta0);
	DDX_Control(pDX, IDC_SCALL, m_sta1);
	DDX_Control(pDX, IDC_SCHUANG, m_sta2);
	DDX_Control(pDX, IDC_STA_VERSION, m_staVersion);
	DDX_Control(pDX, IDC_STA_AUTHOR, m_staAuthor);
	DDX_Control(pDX, IDC_STA_EMAIL, m_staEmail);
}

BEGIN_MESSAGE_MAP(CbeijinghandDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CbeijinghandDlg 消息处理程序

BOOL CbeijinghandDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	//设置窗口透明风格
	DWORD  dwExStyle = ::GetWindowLong(m_hWnd, GWL_EXSTYLE);
	if ((dwExStyle&WS_EX_LAYERED)!=WS_EX_LAYERED)
	{
		::SetWindowLong(m_hWnd, GWL_EXSTYLE, dwExStyle^WS_EX_LAYERED);
	}
	::SetLayeredWindowAttributes(m_hWnd,0,242,LWA_ALPHA);
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	InitUI();
	m_readingdlg = new CReading;
	m_readingdlg->Create(IDD_LANPIAN, GetDlgItem(IDC_DLG));
	m_phonedlg = new CPhoneDlg;
	m_phonedlg->Create(IDD_CALLDLG, GetDlgItem(IDC_DLG));
	m_yaocdlg = new CYaoC;
	m_yaocdlg->Create(IDD_YaoC, GetDlgItem(IDC_DLG));
	/*m_readingdlg->ShowWindow(SW_SHOW);*/
	/*m_phonedlg = new CPhoneDlg;
	m_phonedlg->Create(IDD_CALLDLG, GetDlgItem(IDC_DLG));*/
	// TODO: 在此添加额外的初始化代码
	SetTimer(1,1,NULL);
	//_beginthread(Identify,0,(void*)0);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CbeijinghandDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
		
	}
	else
	{
		CDialogEx::OnPaint();
	}
	
	
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CbeijinghandDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CbeijinghandDlg::InitUI()
{
	CBitmap bmp;
	bmp.LoadBitmap(IDB_maindlgback);	 
	m_brBk.CreatePatternBrush(&bmp);
	bmp.DeleteObject();
	//CDC *pdcdesk = GetDesktopWindow()->GetWindowDC();  //获取窗口dc  
	//CBitmap bmp;  
	//bmp.LoadBitmap(IDB_maindlgback);
	//CRect rc;  
	//GetDesktopWindow()->GetWindowRect(&rc);  //获取窗口大小  	
	//int rcWidth = rc.right - rc.left;
	//int rcHeight = rc.bottom - rc.top;
	/*CBitmap m_Bmp;
	CRect Rect;  
	m_Bmp.LoadBitmap(IDB_maindlgback);
	GetDesktopWindow()->GetWindowRect(&Rect);  
	m_brBk.CreatePatternBrush(&m_Bmp);
	CDC *pdcdesk = GetDesktopWindow()->GetWindowDC();
	CDC backBmp;                 
	backBmp.CreateCompatibleDC(pdcdesk);  
	pdcdesk->PatBlt(0,0,Rect.Width(),Rect.Height(),PATCOPY);  
	CBrush* pOldMemDCBrush=pdcdesk->SelectObject(&m_brBk); 	
	pdcdesk->SelectObject(pOldMemDCBrush); */



	m_staVersion.SetCommonMode();
	m_staAuthor.SetCommonMode();
	m_staVersion.SetTextClr(RGB(73,41,62));
	m_staAuthor.SetTextClr(RGB(73,41,62));
	m_staEmail.SetCommonMode();
	m_staEmail.SetTextClr(RGB(73,41,62));


	  m_stastart.SetTextFont( 16, 0, 0, _T("宋体") );//设置字体
	  m_sta0.SetTextFont( 16, 0, 0, _T("宋体") );
	  m_sta1.SetTextFont( 16, 0, 0, _T("宋体") );
	  m_sta2.SetTextFont( 16, 0, 0, _T("宋体") );
	//m_sta4.SetTextFont( 9, 0, 0, _T("宋体") );
	//m_sta5.SetTextFont( 9, 0, 0, _T("宋体") );
	//m_sta6.SetTextFont( 9, 0, 0, _T("宋体") );
	//m_sta7.SetTextFont( 9, 0, 0, _T("宋体") );
    m_stastart.InitControl(IDB_zhegai, NULL, IDB_darun);
	m_sta0.InitControl(IDB_BITMAP5, IDB_smallread, IDB_bigread);	//设置图片
	m_sta1.InitControl(IDB_BITMAP6, IDB_smallphone, IDB_bigphone);
	m_sta2.InitControl(IDB_BITMAP7, IDB_smallchuang, IDB_bigchuang);
	//m_sta4.InitControl(IDB_BTN_BK_4, IDB_BTN_CENTER_SMALL_4, IDB_BTN_CENTER_BIG_4);
	//m_sta5.InitControl(IDB_BTN_BK_5, IDB_BTN_CENTER_SMALL_5, IDB_BTN_CENTER_BIG_5);
	//m_sta6.InitControl(IDB_BTN_BK_6, IDB_BTN_CENTER_SMALL_6, IDB_BTN_CENTER_BIG_6);
	//m_sta7.InitControl(IDB_BTN_BK_7, IDB_BTN_CENTER_SMALL_7, IDB_BTN_CENTER_BIG_7);

}

HBRUSH CbeijinghandDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性
	if (pWnd == this)
	{
		return m_brBk;//窗口背景
	}
	if (nCtlColor   ==   CTLCOLOR_STATIC)  //静态文本背景透明   
	{     
		pDC->SetBkMode(TRANSPARENT);  
		hbr=(HBRUSH)GetStockObject(NULL_BRUSH);   
	}  
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
void CbeijinghandDlg::DrawPicToHDC(IplImage *img,unsigned int id)
{
	CDC* pDC = GetDlgItem(id)->GetDC();
	HDC hDC = pDC->GetSafeHdc();
	CRect rect;
	GetDlgItem(id)->GetClientRect(&rect);
	CvvImage cimg;
	cimg.CopyOf(img,img->nChannels); 
	cimg.DrawToHDC(hDC,&rect);
	ReleaseDC(pDC);
}

void  Identify(void *)
{
	//CDemo0003Dlg De;
	XnStatus xResult = XN_STATUS_OK;
	char key=0;  
	int imgPosX=0;  
	int imgPosY=0;  	 
	xn::Context context;  
	xResult=context.Init();
	if (XN_STATUS_OK !=xResult)
	{
		AfxMessageBox(_T("初始化环境失败，请检查环境是否安装正确"));
		return;
	}
	xn::ImageMetaData imageMD;  
   /*IplImage**/ cameraImg=cvCreateImage(cvSize(640,480),IPL_DEPTH_8U,3); 
	XnMapOutputMode mapMode;  
	mapMode.nXRes = 640;  
	mapMode.nYRes = 480;  
	mapMode.nFPS = 30; 
	depthGenerator.Create( context );  
	depthGenerator.SetMapOutputMode( mapMode );  
	imageGenerator.Create( context );  
	userGenerator.Create( context );  
	XnCallbackHandle userCBHandle;  
	userGenerator.RegisterUserCallbacks( NewUser, LostUser, NULL, userCBHandle );  
	xn::SkeletonCapability skeletonCap = userGenerator.GetSkeletonCap();  
	skeletonCap.SetSkeletonProfile( XN_SKEL_PROFILE_ALL );  
	XnCallbackHandle calibCBHandle;  
	skeletonCap.RegisterToCalibrationStart( CalibrationStart,&userGenerator, calibCBHandle );  
	skeletonCap.RegisterToCalibrationComplete( CalibrationEnd,&userGenerator, calibCBHandle );  
	XnCallbackHandle poseCBHandle;  
	userGenerator.GetPoseDetectionCap().RegisterToPoseDetected( PoseDetected,&userGenerator, poseCBHandle );  
	context.SetGlobalMirror(TRUE); 
	dst =cvCreateImage(cvSize(320,240),8,3);
	dstSum=cvCreateImage(cvSize(320,240),8,3);
	//cvNamedWindow("Camera",1);
	UINT nFrameImage = 0;//检测到有人的帧数
	context.StartGeneratingAll();
	while (1)
	{
		context.WaitAndUpdateAll();  
		imageGenerator.GetMetaData(imageMD); 
		int temp = imageGenerator.GetFrameID();
		if (temp < nFrameImage)
		{
			break;
		}
		memcpy(cameraImg->imageData,imageMD.Data(),640*480*3);  
		cvCvtColor(cameraImg,cameraImg,CV_RGB2BGR);  
		XnUInt16 userCounts = userGenerator.GetNumberOfUsers();  
		if( userCounts > 0 )  
		{  
			XnUserID* userID = new XnUserID[userCounts];  
			userGenerator.GetUsers( userID, userCounts );  
			for( int i = 0; i < userCounts; ++i )  
			{  
				if( skeletonCap.IsTracking( userID[i] ) )  
				{ 
					XnPoint3D skelPointsIn[24],skelPointsOut[24];  
					XnSkeletonJointTransformation mJointTran;  
					for(int iter=0;iter<24;iter++)  
					{             
						skeletonCap.GetSkeletonJoint( userID[i],XnSkeletonJoint(iter+1), mJointTran );  
						skelPointsIn[iter]=mJointTran.position.position;  
					}  
					depthGenerator.ConvertRealWorldToProjective(24,skelPointsIn,skelPointsOut);
					for(int d=0;d<14;d++)  
					{  
						CvPoint startpoint = cvPoint(skelPointsOut[startSkelPoints[d]-1].X,skelPointsOut[startSkelPoints[d]-1].Y);  
						CvPoint endpoint = cvPoint(skelPointsOut[endSkelPoints[d]-1].X,skelPointsOut[endSkelPoints[d]-1].Y);  
						/*cvCircle(cameraImg,startpoint,3,CV_RGB(0,0,255),12);  
						cvCircle(cameraImg,endpoint,3,CV_RGB(0,0,255),12);  
						cvLine(cameraImg,startpoint,endpoint,CV_RGB(0,0,255),4); */
						m_stastart.SetCheck(TRUE);

					}       
						GesturesNum=ProcessGesture(skelPointsOut[0],skelPointsOut[8],skelPointsOut[14]);				              
				}				
			}  
			delete [] userID;  
			
		}  
		cvResize(cameraImg,dst,CV_INTER_CUBIC);
		/*cvCopy(dst,dstSum);*/
		/*cvShowImage("Camera",cameraImg); */		
		temp = imageGenerator.GetFrameID();
		key=cvWaitKey(20);   
		if (GesturesNum==-1)
		{
			break;
		}
		nfra=TRUE;
	}
	/*cvDestroyWindow("Camera"); */
	cvReleaseImage(&cameraImg);  
	cvReleaseImage(&dst);
	cvReleaseImage(&dstSum);
	context.StopGeneratingAll();  
	context.Shutdown();  
}

void XN_CALLBACK_TYPE NewUser( xn::UserGenerator& generator, XnUserID user,void* pCookie )
{  
	string s="C:\\Users\\csu\\Desktop\\UserCalibration.txt";
	const XnChar *ch=s.c_str();
	userGenerator.GetSkeletonCap().LoadCalibrationDataFromFile( user,ch);  
	generator.GetPoseDetectionCap().StartPoseDetection("Psi", user);  
}  

// callback function of user generator: lost user  
void XN_CALLBACK_TYPE LostUser( xn::UserGenerator& generator, XnUserID user,void* pCookie )  
{   
}  

// callback function of skeleton: calibration start  
void XN_CALLBACK_TYPE CalibrationStart( xn::SkeletonCapability& skeleton,XnUserID user,void* pCookie )  
{  
}  

// callback function of skeleton: calibration end   
void XN_CALLBACK_TYPE CalibrationEnd( xn::SkeletonCapability& skeleton,XnUserID user,XnCalibrationStatus calibrationError,void* pCookie )  
{  
	if( calibrationError==XN_CALIBRATION_STATUS_OK )  
	{  
		skeleton.StartTracking( user ); 
		string s="C:\\Users\\csu\\Desktop\\UserCalibration.txt";
		const XnChar *ch=s.c_str();
		userGenerator.GetSkeletonCap().SaveCalibrationDataToFile(user,ch);  
	}  
	else  
	{   
		//For the current version of OpenNI, only Psi pose is available  
		((xn::UserGenerator*)pCookie)->GetPoseDetectionCap().StartPoseDetection( "Psi", user );  
	}  
}  

// callback function of pose detection: pose start  
void XN_CALLBACK_TYPE PoseDetected( xn::PoseDetectionCapability& poseDetection,const XnChar* strPose,XnUserID user,void* pCookie)  
{  
	((xn::UserGenerator*)pCookie)->GetSkeletonCap().RequestCalibration( user, FALSE );  
	poseDetection.StopPoseDetection( user );  
}  

void clearImg(IplImage* inputimg)  
{  
	CvFont font;  
	cvInitFont( &font, CV_FONT_VECTOR0,1, 1, 0, 3, 5);  
	memset(inputimg->imageData,255,640*480*3);  
}  

int ProcessGesture(XnPoint3D head,XnPoint3D left,XnPoint3D right)
{

	float fleftx;
	float fleftz;
	float frightx;
	float frightz;
	bool isTurnLfet = false;
	bool isTurnRight = false;
	bool isSelect = false;
	bool isGoBack = false;

	if(left.X<(head.X-200))
	{
		fleftx = left.X;
		nleft1.push_back(fleftx);
		while(nleft1.size()>30)
		{
			isTurnLfet = true;
			//cout<<"左"<<endl;
			nleft1.clear();
		}
		return 1;
	}
	if (right.X>(head.X+200))
	{
		frightx = right.X;
		nright1.push_back(frightx);
		while (nright1.size()>30)
		{
			isTurnRight = true;
			//cout<<"右"<<endl;
			nright1.clear();
		}
		return 2;
	}
	if (left.Z < head.Z-400)
	{   
		fleftz = left.Z;
		nleft2.push_back(fleftz);
		while (nleft2.size()>45)//time = 1.5s
		{
			isSelect = true;
			//cout<<"停"<<endl;
			nleft2.clear();

		}
		return 3;
	}
	if (right.Z < head.Z-400)
	{
		frightz = right.Z;
		nright2.push_back(frightz);
		while (nright2.size()>45)//time = 1.5s
		{
			isGoBack = true;
			//cout<<"返回"<<endl;
			nright2.clear();
		}
		return 4;
	} 
}


void CbeijinghandDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (1==nIDEvent)
	{
		KillTimer(1);
		SetTimer(2,2000,NULL);
		SetTimer(3,30,NULL);
		SetTimer(4,100,NULL);		
		_beginthread(Identify,0,(void*)0);
		SetTimer(5,200,NULL);
		SetTimer(6,2000,NULL);
		SetTimer(7,2000,NULL);
		SetTimer(8,2000,NULL);
		return;
	}

	else if (2==nIDEvent)
	{
		if (GesturesNum==2)
		{
			nFrame=nFrame+1;
			nFrame=nFrame%3;
			if (nFrame==0)
			{
				m_sta0.SetCheck(TRUE);
				m_sta1.SetCheck(FALSE);
				m_sta2.SetCheck(FALSE);
				m_readingdlg->ShowWindow(SW_SHOW);
				m_phonedlg->ShowWindow(SW_HIDE);
				m_yaocdlg->ShowWindow(SW_HIDE);
			}
			else if  (nFrame==1)
			{
				m_sta0.SetCheck(FALSE);
				m_sta1.SetCheck(TRUE);
				m_sta2.SetCheck(FALSE);
				m_readingdlg->ShowWindow(SW_HIDE);
				m_phonedlg->ShowWindow(SW_SHOW);
				m_yaocdlg->ShowWindow(SW_HIDE);
			}
			else if (nFrame==2)
			{
				m_sta0.SetCheck(FALSE);
				m_sta1.SetCheck(FALSE);
				m_sta2.SetCheck(TRUE);
				m_readingdlg->ShowWindow(SW_HIDE);
				m_phonedlg->ShowWindow(SW_HIDE);
				m_yaocdlg->ShowWindow(SW_SHOW);
			}
		}
		if (GesturesNum==1)
		{
			nFrame=nFrame+2;
			nFrame=nFrame%3;
			if (nFrame==0)
			{
				m_sta0.SetCheck(TRUE);
				m_sta1.SetCheck(FALSE);
				m_sta2.SetCheck(FALSE);
				m_readingdlg->ShowWindow(SW_SHOW);
				m_phonedlg->ShowWindow(SW_HIDE);
				m_yaocdlg->ShowWindow(SW_HIDE);
				
			}
			else if  (nFrame==1)
			{
				m_sta0.SetCheck(FALSE);
				m_sta1.SetCheck(TRUE);
				m_sta2.SetCheck(FALSE);
				m_readingdlg->ShowWindow(SW_HIDE);
				m_phonedlg->ShowWindow(SW_SHOW);
				m_yaocdlg->ShowWindow(SW_HIDE);
			}
			else if (nFrame==2)
			{
				m_sta0.SetCheck(FALSE);
				m_sta1.SetCheck(FALSE);
				m_sta2.SetCheck(TRUE);
				m_readingdlg->ShowWindow(SW_HIDE);
				m_phonedlg->ShowWindow(SW_HIDE);
				m_yaocdlg->ShowWindow(SW_SHOW);

			}
		}
	}
		else if (3==nIDEvent){	
 			if(GesturesNum==3){
			if (nFrame%3==0)
			{
				//进入阅片界面
				KillTimer(2);
			    KillTimer(3);
				nYuepian=TRUE;
					
            }
			if(nFrame%3==1){
				//进入打电话界面
				KillTimer(2);
				KillTimer(3);
				nVideoPhone=TRUE;
			//m_phone.phoneconnetion();
			}
			if (nFrame%3==2)
			{
				KillTimer(2);
				KillTimer(3);
				nYaochuang=TRUE;
			}
			}
		}
	else if(4==nIDEvent){
		if(nStop==TRUE){
		if(GesturesNum==4){
	/*		if(nFrame%3!=2){*/
		nVideoPhone=FALSE;
		nYuepian=FALSE;
		nYaochuang=FALSE;
		KillTimer(2);
		KillTimer(3);
		KillTimer(4);
		KillTimer(6);
		KillTimer(7);
		KillTimer(8);
		if (nFrame%3==0)
		{
		 reading.CloseYueP();
		}
		if(nFrame%3==1){
		m_phone.ClosePhone();
		}	
		if (nFrame%3==2)
		{
		yaochuang.closeYaoc();
		}
		SetTimer(2,2000,NULL);
		SetTimer(3,30,NULL);
		SetTimer(4,100,NULL);
		SetTimer(6,2000,NULL);
		SetTimer(7,2000,NULL);
		SetTimer(8,2000,NULL);
		}
	}
	}
	else if (5==nIDEvent)
	{
		if(nfra==TRUE){
		DrawPicToHDC(cameraImg,IDC_COLOR);
		}
	}
	else if (6==nIDEvent)
	{
			if ( nYuepian==TRUE)
			{
        m_phonedlg->ShowWindow(SW_HIDE);
		m_yaocdlg->ShowWindow(SW_HIDE);
		m_readingdlg->ShowWindow(SW_SHOW);
		reading.YueP();	
			}
	}
	else if (7==nIDEvent)
	{
		if (nYaochuang==TRUE)
		{
			m_phonedlg->ShowWindow(SW_HIDE);
			m_readingdlg->ShowWindow(SW_HIDE);
			m_yaocdlg->ShowWindow(SW_SHOW);
			yaochuang.startYao();		
		} 
	}
	else if (8==nIDEvent)
	{
		if (nVideoPhone==TRUE)
		{
			m_readingdlg->ShowWindow(SW_HIDE);
			m_yaocdlg->ShowWindow(SW_HIDE);
			m_phonedlg->ShowWindow(SW_SHOW);
		    m_phone.startPhone();		
		} 
	}
	//else if (8==nIDEvent)
	//{
	//   yaochuang.startYao();
	//}
	//else if (9==nIDEvent)
	//{
	//	if (GesturesNum==3)
	//	{
	//		KillTimer(8);
	//		KillTimer(9);
	//		//发送消息
	//		nStop=FALSE;
	//		//yaochuang.printi();
	//		SetTimer(10,1,NULL);
	//	}
	//}
	//else if (10==nIDEvent)
	//{
	//	if (GesturesNum==4)
	//	{
	//	KillTimer(10);
	//	nStop=TRUE;
	//	SetTimer(8,2000,NULL);
	//	SetTimer(9,1,NULL);
	//	}
	//}
	CDialogEx::OnTimer(nIDEvent);
}
