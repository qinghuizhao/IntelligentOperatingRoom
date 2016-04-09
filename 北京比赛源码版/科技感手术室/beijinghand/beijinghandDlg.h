
// beijinghandDlg.h : 头文件
//

#pragma once
#include "DJWStatic.h"
#include <vector>  
#include <XnCppWrapper.h>   
#include <XnModuleCppInterface.h>   
#include "cv.h"  
#include "highgui.h"
#include "PhoneDlg.h"
#include "Reading.h"
#include "CHMXStatic.h"
#include "YaoC.h"
// CbeijinghandDlg 对话框
class CbeijinghandDlg : public CDialogEx
{
// 构造
public:
	CbeijinghandDlg(CWnd* pParent = NULL);	// 标准构造函数
	CReading reading;
	CYaoC    yaochuang;

// 对话框数据
	enum { IDD = IDD_BEIJINGHAND_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	//初始化UI
	void InitUI();
private:
	CBrush						m_brBk;							//背景画刷
public:
	CHMXStatic					m_staVersion;					//控件变量：版本号
	CHMXStatic					m_staAuthor;					//控件变量：作者
	CHMXStatic					m_staEmail;		
private:
	//子dlg1
	CPhoneDlg*					m_phonedlg;		
	CReading*                   m_readingdlg;
	CYaoC*                      m_yaocdlg;
	CPhoneDlg                   m_phone;
	//CChildDlg3*					m_dlg3;							//子dlg3
	//CChildDlg4*					m_dlg4;
	
	
// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void DrawPicToHDC(IplImage *img,unsigned int id);
};
