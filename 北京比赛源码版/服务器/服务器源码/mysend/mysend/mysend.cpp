// mysend.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <WinSock2.h>
#include <stdio.h>
#include "highgui.h"
#include "cv.h"
#include<iostream>
#pragma comment(lib,"Ws2_32")
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD(1,1);
	err = WSAStartup(wVersionRequested,&wsaData);
	if (err!=0) 
	{
		return 0;
	}

	if (LOBYTE(wsaData.wVersion)!=1||HIBYTE(wsaData.wVersion)!=1)
	{
		WSACleanup();
		return 0;
	}
	//�������ڼ������׽���
	SOCKET sockSrv = socket(AF_INET,SOCK_STREAM,0);

	SOCKADDR_IN addrSrv;
	addrSrv.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_port = htons(6000);

	//���׽���
	bind(sockSrv,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
	//��Ϊ����ģʽ,�ڶ��������ǵȴ����е�������
	listen(sockSrv,5);
	SOCKADDR_IN addrClient;
	int len = sizeof(SOCKADDR);               
	//��Ƶͷ
	IplImage* frame;
	CvCapture *capture ;
	capture=cvCreateCameraCapture(0); 
	while(1)
	{frame=cvQueryFrame (capture);
	if(frame) break;	}
	int npp=0;
	
	while(1)
	{
		
		/*char pp0[1];
		SOCKET sockConn00 = accept(sockSrv,(SOCKADDR*)&addrClient,&len);
		recv(sockConn00,pp0,10,0);     
		closesocket(sockConn00);
		int fr=pp0[1];*/		
		SOCKET sockConn = accept(sockSrv,(SOCKADDR*)&addrClient,&len);	
		frame=cvQueryFrame (capture);
		if(!frame) break;
		IplImage *dst=cvCreateImage(cvSize(320,240),frame->depth,frame->nChannels);
		cvResize(frame,dst,CV_INTER_CUBIC);
		cvSaveImage("input.jpg",dst);
		
		//��������
		//SOCKET sockClient = socket(AF_INET,SOCK_STREAM,0);
		////�������������������
		//connect(sockClient,(SOCKADDR*)&addrSrv,sizeof(SOCKADDR));
		char sendBuf[1000];
		memset(sendBuf,0,sizeof(sendBuf));
		FILE* fp=fopen("input.jpg","rb+");		
		int rc; 
		while( (rc=fread(sendBuf,sizeof(unsigned char),40,fp)) != 0 )
		{
			send(sockConn,sendBuf,40,0);
		}
		fclose(fp);	
		closesocket(sockConn);
		/*char pp[1];
		SOCKET sockConn0 = accept(sockSrv,(SOCKADDR*)&addrClient,&len);
		recv(sockConn0,pp,100,0);
		closesocket(sockConn0);*/
		//��������
		SOCKET sockConn1 = accept(sockSrv,(SOCKADDR*)&addrClient,&len);	
		char recvBuf[1000];
		memset(recvBuf,0,sizeof(recvBuf));
		FILE* tof=fopen("output.jpg","wb+");
		while (recv(sockConn1,recvBuf,40,0)>0)
		{
			fwrite(recvBuf,sizeof(char),40,tof);
		}
		fclose(tof);
		closesocket(sockConn1);
		IplImage *showimage=cvLoadImage("output.jpg");
		cvNamedWindow("video");
		cvShowImage("video",showimage);
		cvWaitKey(100);
		npp=npp+1;

		cout<<"��"<<npp<<"ͼƬ������ϣ�"<<endl;
		cvReleaseImage(&showimage);
		cvReleaseImage(&dst);

	} 
	
	return 0;
}
