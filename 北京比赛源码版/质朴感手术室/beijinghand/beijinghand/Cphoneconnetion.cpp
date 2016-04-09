#include "StdAfx.h"
#include "Cphoneconnetion.h"

//extern IplImage* cameraconnect;

Cphoneconnetion::Cphoneconnetion(void)
{
}


Cphoneconnetion::~Cphoneconnetion(void)
{
}
void Cphoneconnetion::phoneconnetion()
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
	
	/*capture=cvCreateCameraCapture(0); 
	while(1)
	{frame=cvQueryFrame (capture);
	if(frame) break;	}*/	
    while(1){
	SOCKET sockClient = socket(AF_INET,SOCK_STREAM,0);
	//向服务器发送连接请求
	connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
	//发送数据
	char recvBuf[10000];
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
	/*frame=cvQueryFrame (capture);
	if(!frame) break;*/
	/*IplImage *dst =cvCreateImage(cvSize(320,240),frame->depth,frame->nChannels);
	cvResize(frame,dst,CV_INTER_CUBIC);*/
	/*extern IplImage* cameraconnect;
	cvSaveImage("input.jpg",cameraconnect);
	cvNamedWindow("xx");
	cvSaveImage("",cameraconnect);
	cvWaitKey(10);*/
	char sendBuf[1000];
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
	cvNamedWindow("video");
	cvShowImage("video",showimage);
	cvWaitKey(100);
	cout<<"第"<<np<<"图片接收完毕！"<<endl;
	cvReleaseImage(&showimage);
	cvReleaseImage(&dst);
	np++;
		
}

	WSACleanup();
	

}
void Cphoneconnetion::closeconnetion()
{
	cvReleaseImage(&showimage);
	cvReleaseImage(&dst);
	cvReleaseCapture(&capture);
	WSACleanup();
}