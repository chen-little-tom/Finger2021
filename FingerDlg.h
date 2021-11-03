
// FingerDlg.h: 头文件
//
#pragma once
#include"CZKFPEngX.h"
#include <fstream>
#include <iomanip>
#include <direct.h>
using namespace std;

// CFingerDlg 对话框
class CFingerDlg : public CDialogEx
{

#define STEP_IMG_1 "temp\\Step1_Source.bmp"
#define STEP_TXT_1 "temp\\Step1_Source.txt"

#define STEP_TXT_2 "temp\\Step2_MidFilter.txt"
#define STEP_IMG_2 "temp\\Step2_MidFilter.bmp"

#define STEP_TXT_3 "temp\\Step3_Normalize.txt"
#define STEP_IMG_3 "temp\\Step3_Normalize.bmp"

#define STEP_TXT_4 "temp\\Step4_Direction.txt"
#define STEP_IMG_4 "temp\\Step4_Direction.bmp"

#define STEP_TXT_5 "temp\\Step5_Frequency.txt"
#define STEP_IMG_5 "temp\\Step5_Frequency.bmp"
	
#define STEP_TXT_6 "temp\\Step6_Mask.txt"
#define STEP_IMG_6 "temp\\Step6_Mask.bmp"

#define STEP_TXT_7 "temp\\Step7_GaborEnhance.txt"
#define STEP_IMG_7 "temp\\Step7_GaborEnhance.bmp"

#define STEP_TXT_8 "temp\\Step8_Binary.txt"
#define STEP_IMG_8 "temp\\Step8_Binary.bmp"

#define STEP_IMG_9 "temp\\Step9_Thinning.bmp"
#define STEP_TXT_9 "temp\\Step9_Thinning.txt"

#define STEP_IMG_10 "temp\\Step10_MinuExtract.bmp"
#define STEP_TXT_10 "temp\\Step10_MinuExtract.txt"

#define STEP_IMG_11 "temp\\Step11_MinuFilter.bmp"
#define STEP_TXT_11 "temp\\Step11_MinuFilter.txt"
#define STEP_IMG_11_MDL "temp\\Step11_MinuFilter_MDL.mdl"

#define STEP_IMG_12 "temp\\Step12_Result.bmp"

#define TEMP_DIR "temp\\"//临时文件夹，用于存放指纹入库前的所有中间处理结果
#define DB_DIR "Database\\"//指纹库文件夹
#define DB_INDEX_TXT "Database\\index.txt"//指纹库索引文件

	// 构造
public:
	CFingerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FINGER_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CZKFPEngX m_zkfpEng;
	CStatic m_staticInfo;
	CStatic m_picCtrl1;
	CStatic m_picCtrl2;
	CString m_name;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	DECLARE_EVENTSINK_MAP()
	afx_msg void OnImageReceivedZkfpengx(BOOL FAR*AImageValid);
public:
	afx_msg void OnBnClickedBtnExit();//退出按钮点击事件
	afx_msg void OnBnClickedBtnConnect();//启动按钮点击事件
	afx_msg void OnBnClickedButton1(); //保存指纹
	afx_msg void InitDatabase();
	afx_msg void InitFile(char * filename);
	afx_msg void GetDatabaseInfo(char * info);
	afx_msg void OnBnClickedBtnDisconnect();//停止采集器
	afx_msg void OnBnClickedBtnCapture();//保存指纹
	afx_msg int ShowImageInCtrl(CStatic &picCtrl, char *filename);//载入图像
	afx_msg void OnBnClickedBtnDatabase();
	afx_msg void OnBnClickedBtnStep6();
	afx_msg void OnBnClickedBtnStep7();
	afx_msg void OnBnClickedBtnStep4();
	afx_msg void OnBnClickedBtnStep5();
	afx_msg void OnBnClickedBtnStep8();
	afx_msg void OnBnClickedBtnStep9();
	afx_msg void OnBnClickedBtnStep10();
	afx_msg void OnBnClickedBtnStep11();
	afx_msg void OnBnClickedBtnStep2();
	afx_msg void OnBnClickedBtnStep3();
	afx_msg void OnBnClickedBtnStep12a();
	afx_msg void OnBnClickedBtnStep12b();
	afx_msg void OnBnClickedBtnStepAddimage();
	afx_msg void OnBnClickedBtnMatchImage();
	afx_msg void OnBnClickedBtnRegister();
	afx_msg void OnBnClickedBtnIdentify();
	afx_msg void OnEnChangeEditName();
};
