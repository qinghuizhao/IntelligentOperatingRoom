#pragma once
#include "stdafx.h"
#include <WinSock2.h>
#include <stdio.h>
#include <string>
#pragma comment(lib,"Ws2_32")
#include<iostream>
#include "highgui.h"
#include "cv.h"

//extern IplImage* cameraconnect;
using namespace std;
class Cphoneconnetion
{
public:
	Cphoneconnetion(void);
	~Cphoneconnetion(void);
	void phoneconnetion();
	void closeconnetion();
public:
	CvCapture *capture ;
	IplImage *dst ;
	IplImage *showimage;

};

