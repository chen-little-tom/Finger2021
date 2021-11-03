
// FingerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Finger.h"
#include "FingerDlg.h"
#include "afxdialogex.h"
#include<io.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFingerDlg 对话框
CFingerDlg::CFingerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_FINGER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFingerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ZKFPENGX, m_zkfpEng);
	DDX_Control(pDX, IDC_STATIC_INFO, m_staticInfo);
	DDX_Control(pDX, IDC_STATIC_IMG1, m_picCtrl1);
	DDX_Control(pDX, IDC_STATIC_IMG2, m_picCtrl2);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);


}

BEGIN_MESSAGE_MAP(CFingerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_EXIT, &CFingerDlg::OnBnClickedBtnExit)
	ON_BN_CLICKED(IDC_BTN_CONNECT, &CFingerDlg::OnBnClickedBtnConnect)
	ON_BN_CLICKED(IDC_BTN_DISCONNECT, &CFingerDlg::OnBnClickedBtnDisconnect)
	ON_BN_CLICKED(IDC_BTN_CAPTURE, &CFingerDlg::OnBnClickedBtnCapture)
	ON_BN_CLICKED(IDC_BUTTON1, &CFingerDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BTN_DATABASE, &CFingerDlg::OnBnClickedBtnDatabase)
	ON_BN_CLICKED(IDC_BTN_STEP_6, &CFingerDlg::OnBnClickedBtnStep6)
	ON_BN_CLICKED(IDC_BTN_STEP_7, &CFingerDlg::OnBnClickedBtnStep7)

	ON_BN_CLICKED(IDC_BTN_STEP_4, &CFingerDlg::OnBnClickedBtnStep4)
	ON_BN_CLICKED(IDC_BTN_STEP_5, &CFingerDlg::OnBnClickedBtnStep5)
	ON_BN_CLICKED(IDC_BTN_STEP_8, &CFingerDlg::OnBnClickedBtnStep8)
	ON_BN_CLICKED(IDC_BTN_STEP_9, &CFingerDlg::OnBnClickedBtnStep9)
	ON_BN_CLICKED(IDC_BTN_STEP_10, &CFingerDlg::OnBnClickedBtnStep10)
	ON_BN_CLICKED(IDC_BTN_STEP_11, &CFingerDlg::OnBnClickedBtnStep11)
	ON_BN_CLICKED(IDC_BTN_STEP_2, &CFingerDlg::OnBnClickedBtnStep2)
	ON_BN_CLICKED(IDC_BTN_STEP_3, &CFingerDlg::OnBnClickedBtnStep3)
	ON_BN_CLICKED(IDC_BTN_STEP_12A, &CFingerDlg::OnBnClickedBtnStep12a)
	ON_BN_CLICKED(IDC_BTN_STEP_12B, &CFingerDlg::OnBnClickedBtnStep12b)
	ON_BN_CLICKED(IDC_BTN_STEP_ADDiMAGE, &CFingerDlg::OnBnClickedBtnStepAddimage)
	ON_BN_CLICKED(IDC_BTN_MATCH_IMAGE, &CFingerDlg::OnBnClickedBtnMatchImage)
	ON_BN_CLICKED(IDC_BTN_REGISTER, &CFingerDlg::OnBnClickedBtnRegister)
	ON_BN_CLICKED(IDC_BTN_IDENTIFY, &CFingerDlg::OnBnClickedBtnIdentify)
	ON_EN_CHANGE(IDC_EDIT_NAME, &CFingerDlg::OnEnChangeEditName)
END_MESSAGE_MAP()
BEGIN_EVENTSINK_MAP(CFingerDlg, CDialog)
	ON_EVENT(CFingerDlg, IDC_ZKFPENGX, 8, OnImageReceivedZkfpengx, VTS_PBOOL)
END_EVENTSINK_MAP()


// CFingerDlg 消息处理程序
int minuCount = 0;

BOOL CFingerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitDatabase();
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CFingerDlg::OnPaint()
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
HCURSOR CFingerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
void CFingerDlg::OnBnClickedBtnExit()
{
	OnOK();// 关闭当前对话框
}
//2
wchar_t *ToWideChar(char *str)
{

	int num = MultiByteToWideChar(0, 0, str, -1, NULL, 0);
	wchar_t *wideStr = new wchar_t[num];
	MultiByteToWideChar(0, 0, str, -1, wideStr, num);

	return wideStr;

}
void CFingerDlg::OnBnClickedBtnConnect()
{
	m_zkfpEng.InitEngine();//启动指纹采集器
	switch (m_zkfpEng.InitEngine())
	{
	case 0:
		MessageBox(_T("采集器连接成功。"), _T("提示"));//显示信息
		break;
	default:
		MessageBox(_T("采集器连接失败！请检查并重试。"), _T("提示"));//显示信息
		break;
	}
}

//采集器的接收图像响应事件
void CFingerDlg::OnImageReceivedZkfpengx(BOOL FAR*AImageValid) {
	HDC hdc = this->GetDC()->m_hDC;//获得显示设备上下文环境的句柄


	CRect rectCtrl;
	CStatic *p = (CStatic*)GetDlgItem(IDD_FINGER_DIALOG);
	p->MoveWindow(100, 100, 100, 100);//更改控件大小并移动其到指定位置
	p->GetWindowRect(rectCtrl);
	this->ScreenToClient(rectCtrl);
	int x = rectCtrl.left;
	int y = rectCtrl.top;


	int width = m_zkfpEng.get_ImageWidth();//图像绘制区宽度
	int height = m_zkfpEng.get_ImageHeight();//图像绘制区高度
	m_zkfpEng.PrintImageAt(int(hdc), x, y, width, height);//绘制图像
}
//指纹采集器采集按钮

int CFingerDlg::ShowImageInCtrl(CStatic & picCtrl, char *filename)
{
	//载入图像
	CImage image;
	HRESULT hResult = image.Load(ToWideChar(filename));
	int width = image.GetWidth();//图形宽度
	int height = image.GetHeight();//图像高度

	//设置显示区域
	CRect rect;//定义矩形对象
	picCtrl.GetClientRect(&rect);//获得picture控件所在的矩形区域
	CDC *pDc = picCtrl.GetWindowDC();//获得picture控件的设备环境句柄
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);//设置位图拉伸模式

	//显示图像
	image.StretchBlt(pDc->m_hDC, rect, SRCCOPY);//将图像画到Picture控件表示的矩形区域

	//更新控件显示
	picCtrl.Invalidate(false);

	//释放变量空间
	image.Destroy();
	picCtrl.ReleaseDC(pDc);//释放picture控件的设备环境句柄

	return 0;

}

int WriteBMPImgFile(char *dstFileName, unsigned char** pusImgData) {
	//打开文件
	FILE *fp = fopen(dstFileName, "r+b");
	if (!fp) {
		return -1;
	}
	//读取图像参数信息
	int imgType, iWidth, iHeight;
	int iStartPos = 0;
	fseek(fp, 10L, SEEK_SET);
	fread((char*)(&iStartPos), 4, 1, fp);
	fseek(fp, 18L, SEEK_SET);
	fread((char*)(&iWidth), 4, 1, fp);
	fread((char*)(&iHeight), 4, 1, fp);
	unsigned short temp;
	fseek(fp, 28L, SEEK_SET);
	fread((char*)(&temp), 2, 1, fp);
	imgType = temp;
	if (imgType != 8) {//目前仅支持8位BMP位图图像
		return -2;
	}
	//向数据区写入数据
	unsigned char* usImgData = *pusImgData;
	int iWidthInFile = 0;
	if (iWidth % 4 > 0) {
		iWidthInFile = iWidth - iWidth % 4 + 4;
	}
	else {
		iWidthInFile = iWidth;
	}

	for (int i = iHeight - 1; i >= 0; i--)//从最后一行到第一行倒序存储
	{
		fseek(fp, iStartPos, SEEK_SET);
		fwrite((usImgData + i * iWidth), 1, iWidth, fp);
		iStartPos += iWidthInFile;
	}

	fclose(fp);
	return 0;
}
//2
int ReadBMPImgFilePara(char *fileName, int & width, int & height, int & depth)
{
	//载入图像
	CImage image;
	HRESULT hResult = image.Load(ToWideChar(fileName));
	if (FAILED(hResult) || image.IsNull()) //图像损坏或文件不存在等因素均可导致载入失败
	{
		return -1;
	}

	//获得图像参数
	width = image.GetWidth();//获得以像素为单位的图像宽度
	height = image.GetHeight();//高度
	depth = image.GetBPP();//获得以bit为单位的图像深度（每个像素的位数）

	if (depth != 8)	//目前系统仅支持8位位图，其他类型位图暂不支持		
	{
		return -2;
	}

	//释放变量空间
	image.Destroy();

	return 0;
}
//2-1
int ReadBMPImgFileData(char *fileName, unsigned char *data)
{
	//载入图像
	CImage image;
	HRESULT hResult = image.Load(ToWideChar(fileName));
	if (FAILED(hResult) || image.IsNull())	//图像损坏或文件不存在等因素可导致载入失败
	{
		return -1;
	}

	//获得图像参数
	int width = image.GetWidth();//获得以像素为单位的图像宽度
	int height = image.GetHeight();//高度	
	int depth = image.GetBPP();//获得以bit为单位的图像深度（每个像素的位数）

	if (depth != 8)	//目前系统仅支持8位位图，其他类型位图暂不支持
	{
		return -2;
	}

	//初始化结果数组
	memset(data, 0, width*height);

	//读取图像数据
	int pitch = image.GetPitch();//每行行首像素的地址偏移量
	unsigned char* pData1 = (unsigned char*)image.GetBits();//图像位图数据区地址
	unsigned char* pData2 = data;
	unsigned char gray = 0;

	unsigned char *pRow1, *pRow2, *pPix1, *pPix2;
	for (int y = 0; y < height; y++)	//逐行扫描
	{
		pRow1 = pData1 + pitch * y;
		pRow2 = pData2 + width * y;
		for (int x = 0; x < width; x++)	//逐列扫描
		{
			//获得源图像素灰度值
			pPix1 = pRow1 + x;
			gray = *pPix1;

			//保存到结果数组
			pPix2 = pRow2 + x;
			*pPix2 = gray;
		}//end for(x)
	}//end for(y)

	//释放变量空间
	image.Destroy();

	return 0;
}
//2
int Frequency(unsigned char * ucImg, float * fDirection, float * fFrequency, int iWidth, int iHeight) {
	const int SIZE_L = 32;
	const int SIZE_W = 16;
	const int SIZE_L2 = 16;
	const int SIZE_W2 = 8;

	int peak_pos[SIZE_L];
	int peak_cnt;
	float peak_freq;
	float Xsig[SIZE_L];

	float dir = 0.0;
	float cosdir = 0.0;
	float sindir = 0.0;
	float maxPeak, minPeak;

	float *frequency1 = new float[iWidth*iHeight];
	memset(fFrequency, 0, sizeof(float)*iWidth*iHeight);
	memset(frequency1, 0, sizeof(float)*iWidth*iHeight);
	int x, y;
	int d, k;
	int u, v;
	for (y = SIZE_L2; y < iHeight - SIZE_L2; y++) {
		for (x = SIZE_L2; x < iWidth - SIZE_L2; x++) {
			dir = fDirection[(y + SIZE_W2)*iWidth + (x + SIZE_W2)];
			cosdir = -sin(dir);
			sindir = cos(dir);

			for (k = 0; k < SIZE_L; k++) {
				Xsig[k] = 0.0;
				for (d = 0; d < SIZE_W; d++) {
					u = (int)(x + (d - SIZE_W2)*cosdir + (k - SIZE_L2)*sindir);
					v = (int)(y + (d - SIZE_W2)*sindir - (k - SIZE_L2)*cosdir);
					if (u < 0) {
						u = 0;
					}
					else if (u > iWidth - 1) {
						u = iWidth - 1;
					}
					if (v < 0) {
						v = 0;
					}
					else if (v > iHeight - 1) {
						v = iHeight - 1;
					}
					Xsig[k] += ucImg[u + v * iWidth];
				}
				Xsig[k] /= SIZE_W;
			}
			maxPeak = minPeak = Xsig[0];
			for (k = 0; k < SIZE_L; k++) {
				if (minPeak > Xsig[k]) {
					minPeak = Xsig[k];
				}
				if (maxPeak < Xsig[k]) {
					maxPeak = Xsig[k];
				}
			}
			peak_cnt = 0;
			if ((maxPeak - minPeak) > 64) {
				for (k = 0; k < SIZE_L; k++) {
					if ((Xsig[k - 1] < Xsig[k]) && (Xsig[k] >= Xsig[k + 1])) {
						peak_pos[peak_cnt++] = k;
					}
				}
			}
			peak_freq = 0.0;
			if (peak_cnt >= 2) {
				for (k = 0; k < peak_cnt - 1; k++) {
					peak_freq += (peak_pos[k + 1] - peak_pos[k]);
				}
				peak_freq /= peak_cnt - 1;
			}
			if (peak_freq<3.0 || peak_freq>25.0) {
				frequency1[x + y * iWidth] = 0.0;
			}
			else {
				frequency1[x + y * iWidth] = 1.0 / peak_freq;
			}
		}
	}
	for (y = SIZE_L2; y < iHeight - SIZE_L2; y++) {
		for (x = SIZE_L2; x < iWidth - SIZE_L2; x++) {
			k = x + y * iWidth;
			peak_freq = 0.0;
			for (v = -2; v <= 2; v++) {
				for (u = -2; u <= 2; u++) {
					peak_freq += frequency1[(x + u) + (y + v)*iWidth];
				}
			}
			fFrequency[k] = peak_freq / 25;
		}
	}

	delete[] frequency1;
	return 0;
}
//2
int ReadDataFromTextFile(char *srcFile, unsigned char *data, int iWidth, int iHeight) {
	// 打开源文件
	ifstream fin(srcFile, ios::in);
	if (!fin) {
		return -1;
	}
	// 读取数据
	int d = 0;
	for (int i = 0; i < iHeight*iWidth; i++) {
		fin >> d;
		data[i] = (unsigned char)d;
	}
	// 关闭文件
	fin.close();
	return 0;
}
//2
int ReadDataFromTextFile(char* srcFile, float* data, int iWidth, int iHeight) {
	ifstream fin(srcFile, ios::in);
	if (!fin) {
		return -1;
	}
	for (int i = 0; i < iHeight*iWidth; i++) {
		fin >> data[i];
	}
	fin.close();
	return 0;
}
//2
int SaveDataToImageFile(char* srcFile, char* dstFile, unsigned char* data) {

	//文件复制
	CopyFile(ToWideChar(srcFile), ToWideChar(dstFile), false);
	//写入数据
	WriteBMPImgFile(dstFile, &data);
	return 0;
}
//2
int SaveDataToImageFile(char* srcFile, char* dstFile, float* data, float scale) {
	//读取图像参数
	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcFile, iWidth, iHeight, iDepth);
	//文件复制
	CopyFile(ToWideChar(srcFile), ToWideChar(dstFile), false);
	//数据转换
	unsigned char *tmpData = new unsigned char[iWidth*iHeight];
	for (int i = 0; i<int(iWidth*iHeight); i++) {
		tmpData[i] = unsigned char((scale* data[i]));
	}

	//写入数据
	WriteBMPImgFile(dstFile, &tmpData);
	delete[] tmpData;//释放内存空间
	return 0;
}
//2
int GetMask(unsigned char * ucImg, float * fDirection, float * fFrequency, unsigned char * ucMask, int iWidth, int iHeight) {
	float freqMin = 1.0 / 25.0;
	float freqMax = 1.0 / 3.0;
	int x, y, k;
	int pos, posout;
	memset(ucMask, 0, iWidth*iHeight);
	for (y = 0; y < iHeight; y++) {
		for (x = 0; x < iWidth; x++) {
			pos = x + y * iWidth;
			posout = x + y * iWidth;
			ucMask[posout] = 0;
			if (fFrequency[pos] >= freqMin && fFrequency[pos] <= freqMax) {
				ucMask[posout] = 255;
			}
		}
	}
	for (k = 0; k < 4; k++) {
		for (y = 1; y < iHeight - 1; y++) {
			for (x = 1; x < iWidth - 1; x++) {
				if (ucMask[x + y * iWidth] == 0xFF) {
					ucMask[x - 1 + y * iWidth] |= 0x80;
					ucMask[x + 1 + y * iWidth] |= 0x80;
					ucMask[x + (y - 1) * iWidth] |= 0x80;
					ucMask[x + (y + 1) * iWidth] |= 0x80;
				}
			}
		}
		for (y = 1; y < iHeight - 1; y++) {
			for (x = 1; x < iWidth - 1; x++) {
				if (ucMask[x + y * iWidth]) {
					ucMask[x + y * iWidth] = 0xFF;
				}
			}
		}
	}
	for (k = 0; k < 12; k++) {
		for (y = 1; y < iHeight - 1; y++) {
			for (x = 1; x < iWidth - 1; x++) {
				if (ucMask[x + y * iWidth] == 0x0) {
					ucMask[x - 1 + y * iWidth] &= 0x80;
					ucMask[x + 1 + y * iWidth] &= 0x80;
					ucMask[x + (y - 1) * iWidth] &= 0x80;
					ucMask[x + (y + 1) * iWidth] &= 0x80;
				}
			}
		}
		for (y = 1; y < iHeight - 1; y++) {
			for (x = 1; x < iWidth - 1; x++) {
				if (ucMask[x + y * iWidth] != 0xFF) {
					ucMask[x + y * iWidth] = 0x0;
				}
			}
		}
	}
	return 0;
}
//2
int SaveDataToTextFile(char *dstFile, unsigned char *data, int width, int height) {
	ofstream fout(dstFile, ios::out);
	if (!fout) {
		return -1;
	}
	// 按指定格式向文件写入数据
	int space = 5;
	for (int i = 0; i < height*width; i++) {
		fout << setw(space) << int(data[i]);
		if (i*width == (width - 1)) {
			fout << endl;
		}
	}
	fout.close();
	return 0;
}
int ShowImageInCtrl(CStatic &picCtrl, char *filename) {
	CImage image;
	HRESULT hResult = image.Load(ToWideChar(filename));
	int width = image.GetWidth();
	int height = image.GetHeight();

	CRect rect;
	picCtrl.GetClientRect(&rect);
	CDC *pDc = picCtrl.GetWindowDC();
	SetStretchBltMode(pDc->m_hDC, STRETCH_HALFTONE);
	image.StretchBlt(pDc->m_hAttribDC, rect, SRCCOPY);
	picCtrl.Invalidate(false);
	image.Destroy();
	picCtrl.ReleaseDC(pDc);
	return 0;
}
//2
int SaveDataToTextFile(char * dstFile, float *data, int width, int height)
{
	//打开目标文件
	ofstream fout(dstFile, ios::out);//使用覆盖写入方法
	if (!fout)
	{
		return -1;
	}

	//按指定格式向文件写入数据
	int preci = 6;//每个浮点型数据均保留六位小数位
	int space = 16;//每个浮点型数据均用16个字符等宽存储
	fout.precision(preci);
	for (int i = 0; i < height*width; i++)
	{
		fout << " " << setw(space) << data[i];//等宽写入数据
		if (i%width == (width - 1))	//行尾
		{
			fout << endl;//换行
		}
	}

	//关闭文件
	fout.close();

	return 0;

}
void CFingerDlg::InitDatabase()
{
	_mkdir(TEMP_DIR);//创建临时文件夹
	_mkdir(DB_DIR);//创建指纹库文件夹
	InitFile(DB_INDEX_TXT);//创建索引文件
}
void CFingerDlg::InitFile(char * filename)
{
	FILE *index = fopen(filename, "w");//若文件不存在则创建，若存在则清空其内容
	fclose(index);//关闭文件
}
//1

void CFingerDlg::GetDatabaseInfo(char *info)
{
	//遍历指纹库
	int pNo = 0;//指纹序号
	char name[MAX_PATH] = { 0 };//登记人姓名
	char srcFile[MAX_PATH] = { 0 };//指纹图像文件
	char mdiFile[MAX_PATH] = { 0 };//指纹特征文件
	FILE *index = fopen(DB_INDEX_TXT, "r");//打开索引文件
	while (!feof(index))
	{
		fscanf(index, "%d %s %s %s\n", &pNo, srcFile, mdiFile, name);
	}
	fclose(index);//关闭文件

	//统计指纹库信息
	sprintf(info, "当前指纹库中共有 %d 条记录", pNo);
}
CString strFile = _T("");
int Step1_LoadBmpImage(char *beginfilename, char* info) {
	char *filename = beginfilename;
	CopyFile(ToWideChar(filename), ToWideChar(STEP_IMG_1), false);

	int iWidth, iHeight, iDepth;
	int flag = ReadBMPImgFilePara(filename, iWidth, iHeight, iDepth);
	if (flag != 0) {
		sprintf(info, "图像加载失败.");
		return -1;
	}
	unsigned char *data = new unsigned char[iWidth*iHeight];
	flag = ReadBMPImgFileData(filename, data);
	if (flag != 0) {
		sprintf(info, "图像数据读取失败.");
		delete[] data;
		return -2;
	}
	flag = SaveDataToTextFile(STEP_TXT_1, data, iWidth, iHeight);
	if (flag != 0) {
		sprintf(info, "数据保存失败.");
		::MessageBox(NULL, _T("数据保存失败"), _T("error"), MB_OK);
		delete[] data;
		return -3;
	}
	//sprintf(info,"第一步图像加载完成.");
	//sprintf(info, "源图[%s],宽度[%d]，高度[%d]，深度[%d b]",filename,iWidth,iHeight,iDepth);
	delete[] data;
	return 0;
}
void CFingerDlg::OnBnClickedBtnCapture()
{
	m_zkfpEng.SaveBitmap(_T("cai.bmp"));//将采集到的指纹保存
	char filename[MAX_PATH] = "cai.bmp";
	char info[MAX_PATH] = { 0 };
	Step1_LoadBmpImage(filename, info);
	ShowImageInCtrl(m_picCtrl1, filename);
}
void CFingerDlg::OnBnClickedBtnDisconnect()
{
	m_zkfpEng.EndEngine();//
	MessageBox(_T("采集器断开连接。"), _T("提示"));//显示信息
}
void CFingerDlg::OnBnClickedButton1()
{


	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"), NULL);
	CString defaultPath("databases");
	CString folderPath("outfile");

	if (!PathIsDirectory(defaultPath))  // 是否有重名文件夹
	{
		::CreateDirectory(defaultPath, 0);
	}
	if (!PathIsDirectory(folderPath))  // 是否有重名文件夹
	{
		::CreateDirectory(folderPath, 0);
	}
	if (dlgFile.DoModal() == IDOK)
	{
		strFile = dlgFile.GetPathName();
	}
	else {
		MessageBox(_T("未选中图片"), _T("提示"));
		return;
	}
	char *info = "";

	USES_CONVERSION;
	char * beginfilename = T2A(strFile);

	Step1_LoadBmpImage(beginfilename, info);
	ShowImageInCtrl(m_picCtrl1, beginfilename);
}
void CFingerDlg::OnBnClickedBtnDatabase()
{
	char info[MAX_PATH] = { 0 };//初始化显示信息
	GetDatabaseInfo(info);//获取指纹库信息
	m_staticInfo.SetWindowText(ToWideChar(info));//显示指纹库信息
}
int GaborEnhance(unsigned char* ucImg, float* fDirection, float* fFrequency, unsigned char* ucMask, unsigned char* ucImgEnhanced, int iWidth, int iHeight) {
	const float PI = 3.141592654;
	int i, j, u, v;
	int wg2 = 5;
	float sum, f, g;
	float x2, y2;
	float dx2 = 1.0 / (4.0*4.0);
	float dy2 = 1.0 / (4.0*4.0);
	memset(ucImgEnhanced, 0, iWidth*iHeight);
	for (j = wg2; j < iHeight - wg2; j++) {
		for (i = wg2; i < iWidth - wg2; i++) {
			if (ucMask[i + j * iWidth] == 0) {
				continue;
			}
			g = fDirection[i + j * iWidth];
			f = fFrequency[i + j * iWidth];
			g += PI / 2;
			sum = 0.0;
			for (v = -wg2; v <= wg2; v++) {
				for (u = -wg2; u <= wg2; u++) {
					x2 = -u * sin(g) + v * cos(g);
					y2 = u * cos(g) + v * sin(g);
					sum += exp(-0.5*(x2*x2*dx2 + y2 * y2*dy2))*cos(2 * PI*x2*f)*ucImg[(i - u) + (j - v)*iWidth];
				}
			}
			if (sum > 255.0) {
				sum = 255.0;
			}
			if (sum < 0.0) {
				sum = 0.0;
			}
			ucImgEnhanced[i + j * iWidth] = (unsigned char)sum;
		}
	}
	return 0;
}
int Step6_Mask(char *info) {
	//设置输入输出文件名
	char srcTxtFile_Img[MAX_PATH] = { STEP_TXT_3 };//图像源数据文件名
	char srcTxtFile_Dir[MAX_PATH] = { STEP_TXT_4 };//方向源数据文件名
	char srcTxtFile_Fre[MAX_PATH] = { STEP_TXT_5 };//频率源数据文件名
	char srcImgFile[MAX_PATH] = { STEP_IMG_5 };//源图文件名
	char dstTxtFile[MAX_PATH] = { STEP_TXT_6 };//结果数据文件名
	char dstImgFile[MAX_PATH] = { STEP_IMG_6 };//结果图文件名
	//读取图像参数
	int iWidth, iHeight, iDpeth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDpeth);
	//读取图像源数据
	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile_Img, image1, iWidth, iHeight);
	// 读取方向源数据
	float *direction = new float[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile_Dir, direction, iWidth, iHeight);
	//读取频率源数据
	float *frequency = new float[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile_Fre, frequency, iWidth, iHeight);
	//掩码计算
	unsigned char *mask = new unsigned char[iWidth * iHeight];
	GetMask(image1, direction, frequency, mask, iWidth, iHeight);
	//保存结果数据(TXT文件)
	SaveDataToTextFile(dstTxtFile, mask, iWidth, iHeight);
	//保存结果图像(BMP文件,仅用于显示)
	SaveDataToImageFile(srcImgFile, dstImgFile, mask);
	//释放空间
	delete[] image1;
	delete[] mask;
	delete[] direction;
	delete[] frequency;

	//返回操作成败状态
	sprintf(info, "完成掩码计算.");
	return 0;
}
void CFingerDlg::OnBnClickedBtnStep6()
{
	//初始化操作结果信息
	char info[MAX_PATH] = { 0 };
	//指纹掩码计算
	Step6_Mask(info);
	//显示操作结果信息
	m_staticInfo.SetWindowText(ToWideChar(info));
	//显示图像
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_5);
	//显示输入图像
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_6);//显示输出图像
}
int Step7_GaborEnhance(char *info) {
	char srcTxtFile_Img[MAX_PATH] = { STEP_TXT_3 };
	char srcTxtFile_Dir[MAX_PATH] = { STEP_TXT_4 };
	char srcTxtFile_Fre[MAX_PATH] = { STEP_TXT_5 };
	char srcTxtFile_Msk[MAX_PATH] = { STEP_TXT_6 };
	char srcImgFile[MAX_PATH] = { STEP_IMG_6 };
	char dstTxtFile[MAX_PATH] = { STEP_TXT_7 };
	char dstImgFile[MAX_PATH] = { STEP_IMG_7 };
	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);

	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile_Img, image1, iWidth, iHeight);

	float *direction = new float[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile_Dir, direction, iWidth, iHeight);

	float *frequency = new float[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile_Fre, frequency, iWidth, iHeight);

	unsigned char* mask = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile_Msk, mask, iWidth, iHeight);

	unsigned char* image2 = new unsigned char[iWidth*iHeight];
	GaborEnhance(image1, direction, frequency, mask, image2, iWidth, iHeight);

	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);
	SaveDataToImageFile(srcImgFile, dstImgFile, image2);

	delete[] image1;
	delete[] direction;
	delete[] frequency;
	delete[] mask;
	delete[] image2;

	sprintf(info, "完成Gabor滤波增强.");
	return 0;
}
void CFingerDlg::OnBnClickedBtnStep7()
{
	char info[MAX_PATH] = { 0 };
	Step7_GaborEnhance(info);
	m_staticInfo.SetWindowText(ToWideChar(info));
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_6);
	//显示输入图像
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_7);//显示输出图像
}
//2
int ImgDirection(unsigned char*ucImg, float * fDirc, int iWidth, int iHeight) {
	//定义变量
	const int SEMISIZ = 7;//领域窗口区域半径
	int dx[SEMISIZ * 2 + 1][SEMISIZ * 2 + 1];
	int dy[SEMISIZ * 2 + 1][SEMISIZ * 2 + 1];
	float fx, fy;

	//结果初始化
	memset(fDirc, 0, iWidth*iHeight * sizeof(float));

	//计算每一像素的脊线方向值
	for (int y = SEMISIZ+1; y < iHeight - SEMISIZ - 1; y++)//逐行遍历（除去边缘）
	{
		for (int x = SEMISIZ+1; x < iWidth - SEMISIZ - 1; x++) {//逐列便利
			//计算以当前像素为中心的领域窗口区内每一像素的梯度
			for (int j = 0; j < SEMISIZ * 2 + 1; j++) {
				for (int i = 0; i < SEMISIZ * 2 + 1; i++) {
					int index1 = (y + j - SEMISIZ)*iWidth + x + i - SEMISIZ;
					int index2 = (y + j - SEMISIZ)*iWidth + x + i - SEMISIZ-1;
					int index3 = (y + j - SEMISIZ - 1)*iWidth + x + i - SEMISIZ;
					dx[i][j] = int(ucImg[index1] - ucImg[index2]);
					dy[i][j] = int(ucImg[index1] - ucImg[index3]);
				}
			}
			//计算当前像素的脊线方向值
			fx = 0.0;
			fy = 0.0;
			for (int j = 0; j < SEMISIZ * 2 + 1; j++)
			{
				for (int i = 0; i < SEMISIZ * 2 + 1; i++)
				{
					fx += 2 * dx[i][j] * dy[i][j];
					fy += (dx[i][j] * dx[i][j] - dy[i][j] * dy[i][j]);
				}
			}
			fDirc[y*iWidth + x] = atan2(fx, fy);
		}
	}
	return 0;

}
//2
int DircLowPass(float *fDirc, float* fFitDirc, int iWidth, int iHeight) {
	//定义变量
	const int DIR_FILTER_SIZE = 2;
	int blocksize = 2 * DIR_FILTER_SIZE + 1;
	int imgsize = iWidth * iHeight;

	float *filter = new float[blocksize*blocksize];//使用5*5滤波器
	float *phix = new float[imgsize];
	float *phiy = new float[imgsize];
	float *phi2x = new float[imgsize];
	float *phi2y = new float[imgsize];

	//结果初始化
	memset(fFitDirc, 0, sizeof(float)*iWidth*iHeight);

	//设置5*5高斯低通滤波器模板
	float tempSum = 0.0;
	for (int y = 0; y < blocksize; y++) {
		for (int x = 0; x < blocksize; x++) {
			filter[y*blocksize + x] = (float)(blocksize - (abs(DIR_FILTER_SIZE - x) + abs(DIR_FILTER_SIZE - y)));
			tempSum += filter[y*blocksize + x];
		}
	}


	for (int y = 0; y < blocksize; y++) {
		for (int x = 0; x < blocksize; x++) {
			filter[y*blocksize + x] /= tempSum;
		}
	}

	//计算各像素点的方向正弦值和余弦值
	for (int y = 0; y < iHeight; y++) {
		for (int x = 0; x < iWidth; x++) {
			phix[y*iWidth + x] = cos(fDirc[y*iWidth + x]);
			phiy[y*iWidth + x] = sin(fDirc[y*iWidth + x]);
		}
	}

	//对所有像素进行方向低通滤波
	memset(phi2x, 0, sizeof(float)*imgsize);
	memset(phi2y, 0, sizeof(float)*imgsize);
	float nx, ny;
	int val;
	for (int y = 0; y < iHeight - blocksize; y++) {//逐行遍历出去边缘
		for (int x = 0; x < iWidth - blocksize; x++) {//逐列遍历除去边缘

			//对以当前像素为中心的滤波窗口内的所有像素值进行加权累加
			nx = 0.0;
			ny = 0.0;
			for (int j = 0; j < blocksize; j++) {
				for (int i = 0; i < blocksize; i++) {
					val = (x + i) + (j + y)*iWidth;
					nx += filter[j*blocksize + i] * phix[val];
					ny += filter[j*blocksize + i] * phiy[val];
				}
			}
			//将累加的结果作为当前像素的新的方向正弦值和余弦值
			val = x + y * iWidth;
			phi2x[val] = nx;
			phi2y[val] = ny;
		}
	}

	//根据加权累加结果，计算各像素的方向滤波结果值
	for (int y = 0; y < iHeight - blocksize; y++) {
		for (int x = 0; x < iWidth - blocksize; x++) {
			val = x + y * iWidth;
			fFitDirc[val] = atan2(phi2y[val], phi2x[val])*0.5;
		}
	}
	delete[] phi2y;
	delete[] phi2x;
	delete[] phiy;
	delete[] phix;

	return 0;
}
//2
int Step4_Direction(char* info) {
	//设置输入输出文件名
	char srcTxtFile[MAX_PATH] = { STEP_TXT_3 };//源数据文件名
	char srcImgFile[MAX_PATH] = { STEP_IMG_3 };//源图文件名
	char dstTxtFile[MAX_PATH] = { STEP_TXT_4 };//结果数据文件名
	char dstImgFile[MAX_PATH] = { STEP_IMG_4 };//结果图文件名
	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);
	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile, image1, iWidth, iHeight);
	float *tmpDirections = new float[iWidth*iHeight];
	ImgDirection(image1, tmpDirections, iWidth, iHeight);
	float *directions = new float[iWidth*iHeight];
	DircLowPass(tmpDirections, directions, iWidth, iHeight);
	//SaveDataToTextFile(dstTxtFile_fx, tmpDirections, iWidth, iHeight);
	SaveDataToTextFile(dstTxtFile, directions, iWidth, iHeight);
	const int DIRECTION_SCALE = 100;
	SaveDataToImageFile(srcImgFile, dstImgFile, directions, DIRECTION_SCALE);
	delete[] image1;
	delete[] tmpDirections;
	delete[] directions;
	sprintf(info, "完成方向计算。");
	return 0;
}
void CFingerDlg::OnBnClickedBtnStep4()
{
	// 初始化操作结果信息
	char info[MAX_PATH] = { 0 };

	//指纹基线方向计算
	Step4_Direction(info);

	m_staticInfo.SetWindowText(ToWideChar(info));
	//显示图像
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_3);//显示输入图像
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_4);//显示输出图像
}
//2
int Step5_Frequency(char* info) {
	char srcTxtFile_Img[MAX_PATH] = { STEP_TXT_3 };
	char srcTxtFile_Dir[MAX_PATH] = { STEP_TXT_4 };
	char srcImgFile[MAX_PATH] = { STEP_IMG_4 };
	char dstTxtFile[MAX_PATH] = { STEP_TXT_5 };
	char dstImgFile[MAX_PATH] = { STEP_IMG_5 };
	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);
	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile_Img, image1, iWidth, iHeight);
	float * direction = new float[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile_Dir, direction, iWidth, iHeight);

	float *frequency = new float[iWidth*iHeight];
	Frequency(image1, direction, frequency, iWidth, iHeight);

	SaveDataToTextFile(dstTxtFile, frequency, iWidth, iHeight);

	const int FREQUENCY_SCALE = 1000;
	SaveDataToImageFile(srcImgFile, dstImgFile, frequency, FREQUENCY_SCALE);
	delete[] image1;
	delete[] direction;
	delete[] frequency;
	sprintf(info, "频率计算完成.");
	return 0;
}
void CFingerDlg::OnBnClickedBtnStep5()
{
	//初始化操作结果信息
	char info[MAX_PATH] = { 0 };
	//基线频率计算
	Step5_Frequency(info);
	//显示操作结果信息
	m_staticInfo.SetWindowText(ToWideChar(info));
	//显示图像
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_4);//显示输入图像
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_5);//显示输出图像
}
int BinaryImg(unsigned char* ucImage, unsigned char* ucBinImage, int iWidth, int iHeight, unsigned char uThreshold) {
	unsigned char *pStart = ucImage, *pEnd = ucImage + iWidth * iHeight;
	unsigned char *pDest = ucBinImage;
	while (pStart < pEnd) {
		*pDest = *pStart > uThreshold ? 1 : 0;
		pStart++;
		pDest++;
	}
	return 0;
}
int BinaryToGray(unsigned char *ucBinImg, unsigned char *ucGrayImg, int iWidth, int iHeight) {
	unsigned char *pStart = ucBinImg, *pEnd = ucBinImg + iWidth * iHeight;
	unsigned char *pDest = ucGrayImg;

	while (pStart < pEnd) {
		*pDest = (*pStart) > 0 ? 255 : 0;
		pStart++;
		pDest++;
	}
	return 0;
}
int Step8_Binary(char *info) {
	char srcTxtFile[MAX_PATH] = { STEP_TXT_7 };
	char srcImgFile[MAX_PATH] = { STEP_IMG_7 };
	char dstTxtFile[MAX_PATH] = { STEP_TXT_8 };
	char dstImgFile[MAX_PATH] = { STEP_IMG_8 };
	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);
	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile, image1, iWidth, iHeight);

	unsigned char *image2 = new unsigned char[iWidth*iHeight];
	BinaryImg(image1, image2, iWidth, iHeight, 128);

	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);

	BinaryToGray(image2, image1, iWidth, iHeight);
	SaveDataToImageFile(srcImgFile, dstImgFile, image1);

	delete[] image1;
	delete[] image2;

	sprintf(info, "二值化完成.");
	return 0;
}
void CFingerDlg::OnBnClickedBtnStep8()
{
	char info[MAX_PATH] = { 0 };
	Step8_Binary(info);
	m_staticInfo.SetWindowText(ToWideChar(info));
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_7);//显示输入图像
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_8);//显示输出图像
}
int Thinning(unsigned char *ucBinedImg, unsigned char *ucThinnedImage, int iWidth, int iHeight, int iIterativeLimit) {
	unsigned char x1, x2, x3, x4, x5, x6, x7, x8, xp;
	unsigned char g1, g2, g3, g4;
	unsigned char b1, b2, b3, b4;
	unsigned char np1, np2, npm;
	unsigned char *pUp, *pDown, *pImg;
	int iDeletePoints = 0;

	memcpy(ucThinnedImage, ucBinedImg, iWidth*iHeight);
	for (int it = 0; it < iIterativeLimit; it++) {
		iDeletePoints = 0;
		for (int i = 1; i < iHeight - 1; i++) {
			pUp = ucBinedImg + (i - 1)*iWidth;
			pImg = ucBinedImg + i * iWidth;
			pDown = ucBinedImg + (i + 1)*iWidth;
			for (int j = 1; j < iWidth - 1; j++) {
				pUp++;
				pImg++;
				pDown++;
				if (!*pImg) {
					continue;
				}
				x6 = *(pUp - 1);
				x5 = *(pImg - 1);
				x4 = *(pDown - 1);
				x7 = *pUp;
				xp = *pImg;
				x3 = *pDown;
				x8 = *(pUp + 1);
				x1 = *(pImg + 1);
				x2 = *(pDown + 1);


				b1 = !x1 && (x2 == 1 || x3 == 1);
				b2 = !x3 && (x4 == 1 || x5 == 1);
				b3 = !x5 && (x6 == 1 || x7 == 1);
				b4 = !x7 && (x8 == 1 || x1 == 1);

				g1 = (b1 + b2 + b3 + b4) == 1;

				np1 = x1 || x2;
				np1 += x3 || x4;
				np1 += x5 || x6;
				np1 += x7 || x8;
				np2 = x2 || x3;
				np2 += x4 || x5;
				np2 += x6 || x7;
				np2 += x8 || x1;

				npm = np1 > np2 ? np2 : np1;
				g2 = npm >= 2 && npm <= 3;
				g3 = (x1 && (x2 || x3 || !x8)) == 0;
				g4 = (x5 && (x6 || x7 || !x4)) == 0;

				if (g1&&g2&&g3) {
					ucThinnedImage[iWidth*i + j] = 0;
					++iDeletePoints;
				}
			}
		}
		memcpy(ucBinedImg, ucThinnedImage, iWidth*iHeight);
		for (int i = 1; i < iHeight - 1; i++) {
			pUp = ucBinedImg + (i - 1)*iWidth;
			pImg = ucBinedImg + i * iWidth;
			pDown = ucBinedImg + (i + 1) * iWidth;
			for (int j = 1; j < iWidth - 1; j++) {
				pUp++;
				pImg++;
				pDown++;
				if (!*pImg) {
					continue;
				}
				x6 = *(pUp - 1);
				x5 = *(pImg - 1);
				x4 = *(pDown - 1);

				x7 = *pUp;
				xp = *pImg;
				x3 = *pDown;

				x8 = *(pUp + 1);
				x1 = *(pImg + 1);
				x2 = *(pDown + 1);

				b1 = !x1 && (x2 == 1 || x3 == 1);
				b2 = !x3 && (x4 == 1 || x5 == 1);
				b3 = !x5 && (x6 == 1 || x7 == 1);
				b4 = !x7 && (x8 == 1 || x1 == 1);

				g1 = (b1 + b2 + b3 + b4) == 1;

				np1 = x1 || x2;
				np1 += x3 || x4;
				np1 += x5 || x6;
				np1 += x7 || x8;

				np2 = x2 || x3;
				np2 += x4 || x5;
				np2 += x6 || x7;
				np2 += x8 || x1;

				npm = np1 > np2 ? np2 : np1;
				g2 = npm >= 2 && npm <= 3;

				g3 = (x1 && (x2 || x3 || !x8)) == 0;
				g4 = (x5 && (x6 || x7 || !x4)) == 0;

				if (g1&&g2&&g4) {
					ucThinnedImage[iWidth*i + j] = 0;
					++iDeletePoints;
				}
			}
		}

		memcpy(ucBinedImg, ucThinnedImage, iWidth*iHeight);

		if (iDeletePoints == 0) {
			break;
		}
	}

	for (int i = 0; i < iHeight; i++) {
		for (int j = 0; j < iWidth; j++) {
			if (i < 16) {
				ucThinnedImage[i*iWidth + j] = 0;
			}
			else if (i >= iHeight - 16) {
				ucThinnedImage[i*iWidth + j] = 0;
			}
			else if (j < 16) {
				ucThinnedImage[i*iWidth + j] = 0;
			}
			else if (j >= iWidth - 16) {
				ucThinnedImage[i*iWidth + j] = 0;
			}
		}
	}
	return 0;
}
int Step9_Thinning(char *info) {
	char srcTxtFile[MAX_PATH] = { STEP_TXT_8 };
	char srcImgFile[MAX_PATH] = { STEP_IMG_8 };
	char dstTxtFile[MAX_PATH] = { STEP_TXT_9 };
	char dstImgFile[MAX_PATH] = { STEP_IMG_9 };

	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);

	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile, image1, iWidth, iHeight);

	unsigned char *image2 = new unsigned char[iWidth*iHeight];
	Thinning(image1, image2, iWidth, iHeight, 200);

	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);

	BinaryToGray(image2, image1, iWidth, iHeight);
	SaveDataToImageFile(srcImgFile, dstImgFile, image1);

	delete[] image1;
	delete[] image2;

	sprintf(info, "第九步细化完成.");

	return 0;

}
void CFingerDlg::OnBnClickedBtnStep9()
{
	char info[MAX_PATH] = { 0 };
	Step9_Thinning(info);
	m_staticInfo.SetWindowText(ToWideChar(info));
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_8);//显示输入图像
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_9);//显示输出图像
}
int Extract(unsigned char *ucThinImg, unsigned char *ucMinuImg, int iWidth, int iHeight) {
	unsigned char *pDest = ucMinuImg;
	unsigned char *pUp, *pDown, *pImg;
	unsigned char x1, x2, x3, x4, x5, x6, x7, x8;
	unsigned char nc;
	int iMinuCount = 0;

	memset(pDest, 0, iWidth*iHeight);

	for (int i = 1; i < iHeight - 1; i++) {
		pUp = ucThinImg + (i - 1)*iWidth;
		pImg = ucThinImg + i * iWidth;
		pDown = ucThinImg + (i + 1)*iWidth;
		for (int j = 1; j < iWidth - 1; j++) {
			pUp++;
			pImg++;
			pDown++;
			if (!*pImg) {
				continue;
			}
			x6 = *(pUp - 1);
			x5 = *(pImg - 1);
			x4 = *(pDown - 1);
			x7 = *pUp;
			x3 = *pDown;
			x8 = *(pUp + 1);
			x1 = *(pImg + 1);
			x2 = *(pDown + 1);
			nc = x1 + x2 + x3 + x4 + x5 + x6 + x7 + x8;
			if (nc == 1) {
				pDest[i*iWidth + j] = 1;
				++iMinuCount;
			}
			else if (nc == 3) {
				pDest[i*iWidth + j] = 3;
				++iMinuCount;
			}
		}
	}
	return iMinuCount;
}
int Step10_MinuExtract(char *info) {
	char srcTxtFile[MAX_PATH] = { STEP_TXT_9 };
	char srcImgFile[MAX_PATH] = { STEP_IMG_9 };
	char dstTxtFile[MAX_PATH] = { STEP_TXT_10 };
	char dstImgFile[MAX_PATH] = { STEP_IMG_10 };

	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);

	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile, image1, iWidth, iHeight);

	unsigned char *image2 = new unsigned char[iWidth*iHeight];
	minuCount = Extract(image1, image2, iWidth, iHeight);

	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);

	BinaryToGray(image2, image1, iWidth, iHeight);
	SaveDataToImageFile(srcImgFile, dstImgFile, image1);

	delete[] image1;
	delete[] image2; sprintf(info, "第十步特征提取完成.");
	return 0;
}
void CFingerDlg::OnBnClickedBtnStep10()
{
	char info[MAX_PATH] = { 0 };
	Step10_MinuExtract(info);
	m_staticInfo.SetWindowText(ToWideChar(info));
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_9);//显示输入图像
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_10);//显示输出图像
}
struct NEIGHBOR {
	int x;
	int y;
	int type;
	float Theta;
	float Theta2Ridge;
	float Theta2ThisNibor;
	int distance;
};
struct MINUTIAE {
	int x;
	int y;
	int type;
	float theta;
	NEIGHBOR *neibors;
};
int CutEdge(MINUTIAE* minutiaes, int count, unsigned char*ucImg, int iWidth, int iHeight) {
	int minuCount = count;
	int x, y, type;
	bool del;
	int *pFlag = new int[minuCount];
	memset(pFlag, 0, sizeof(int)*minuCount);
	for (int i = 0; i < minuCount; i++) {
		y = minutiaes[i].y - 1;
		x = minutiaes[i].x - 1;
		type = minutiaes[i].type;
		del = true;
		if (x < iWidth / 2) {
			if (abs(iWidth / 2 - x) > abs(iHeight / 2 - y)) {
				while (--x >= 0) {
					if (ucImg[x + y * iWidth] > 0) {
						del = false;
						break;
					}
				}
			}
			else {
				if (y > iHeight / 2) {
					while (++y < iHeight) {
						if (ucImg[x + y * iWidth] > 0) {
							del = false;
							break;
						}
					}
				}
				else {
					while (--y == 0) {
						if (ucImg[x + y * iWidth] > 0) {
							del = false;
							break;
						}
					}
				}
			}
		}
		else {
			if (abs(iWidth / 2 - x) > abs(iHeight / 2 - y)) {
				while (++x < iWidth) {
					if (ucImg[x + y * iWidth] > 0) {
						del = false;
						break;
					}
				}
			}
			else {
				if (y > iHeight / 2) {
					while (++y < iHeight) {
						if (ucImg[x + y * iWidth] > 0) {
							del = false;
							break;
						}
					}
				}
				else {
					while (--y >= 0) {
						if (ucImg[x + y * iWidth] > 0) {
							del = false;
							break;
						}
					}
				}
			}
		}
		if (del) {
			pFlag[i] = 1;
			continue;
		}
	}
	int newCount = 0;
	for (int i = 0; i < minuCount; i++) {
		if (pFlag[i] == 0) {
			memcpy(&minutiaes[newCount], &minutiaes[i], sizeof(MINUTIAE));
			newCount++;
		}
	}
	delete[] pFlag;
	pFlag = NULL;
	return newCount;
}
int SaveMinutiae(MINUTIAE *minutiaes, int count, char *fileName) {
	FILE *fp = fopen(fileName, "wb");
	if (!fp) {
		return -1;
	}
	const static int TemplateFileFlag = 0x3571027f;
	fwrite(&TemplateFileFlag, sizeof(int), 1, fp);
	fwrite(&count, sizeof(int), 1, fp);
	for (int i = 0; i < count; i++) {
		fwrite(&(minutiaes[i]), sizeof(MINUTIAE), 1, fp);
	}
	fclose(fp);
	return 0;
}
int MinuFilter(unsigned char *minuData, unsigned char *thinData, MINUTIAE *minutiaes, int &minuCount, int iWidth, int iHeight) {
	float *dir = new float[iWidth*iHeight];
	memset(dir, 0, iWidth*iHeight * sizeof(float));
	ImgDirection(thinData, dir, iWidth, iHeight);
	unsigned char* pImg;
	unsigned char val;
	int temp = 0;
	for (int i = 1; i < iHeight - 1; i++) {
		pImg = minuData + i * iWidth;
		for (int j = 1; j < iWidth - 1; j++) {
			++pImg;
			val = *pImg;
			if (val > 0) {
				minutiaes[temp].x = j + 1;
				minutiaes[temp].y = i + 1;
				minutiaes[temp].theta = dir[i*iWidth + j];
				minutiaes[temp].type = int(val);
				++temp;
			}
		}
	}
	delete[] dir;
	minuCount = CutEdge(minutiaes, minuCount, thinData, iWidth, iHeight);
	int *pFlag = new int[minuCount];
	memset(pFlag, 0, sizeof(int)*minuCount);
	int x1, x2, y1, y2, type1, type2;
	for (int i = 0; i < minuCount; i++) {
		x1 = minutiaes[i].x;
		y1 = minutiaes[i].y;
		type1 = minutiaes[i].type;
		for (int j = i + 1; j < minuCount; j++) {
			if (pFlag[i] == 1) {
				continue;
			}
			x2 = minutiaes[j].x;
			y2 = minutiaes[j].y;
			type2 = minutiaes[j].type;

			int r = (int)sqrt(float((y1 - y2)*(y1 - y2) + (x1 - x2)*(x1 - x2)));

			if (r <= 4) {
				if (type1 == type2) {
					if (type1 == 1) {
						pFlag[i] = pFlag[j] = 1;
					}
					else {
						pFlag[j] = 1;
					}
				}
				else if (type1 == 1) {
					pFlag[i] = 1;
				}
				else {
					pFlag[j] = 1;
				}
			}
		}

	}
	int newCount = 0;
	for (int i = 0; i < minuCount; i++) {
		if (pFlag[i] == 0) {
			memcpy(&minutiaes[newCount], &minutiaes[i], sizeof(MINUTIAE));
			newCount++;
		}
	}
	delete[] pFlag;
	minuCount = newCount;
	return 0;
}
int Step11_MinuFilter(char *info) {
	const int MINU_COUNT_THRED = 4;
	if (minuCount < MINU_COUNT_THRED) {
		return -1;
	}
	char srcTxtFile_Minu[MAX_PATH] = { STEP_TXT_10 };
	char srcTxtFile_Thin[MAX_PATH] = { STEP_TXT_9 };
	char srcImgFile[MAX_PATH] = { STEP_IMG_10 };
	char dstTxtFile[MAX_PATH] = { STEP_TXT_11 };
	char dstImgFile[MAX_PATH] = { STEP_IMG_11 };
	char dstMdlFile[MAX_PATH] = { STEP_IMG_11_MDL };

	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);

	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile_Minu, image1, iWidth, iHeight);

	unsigned char *thin = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile_Thin, thin, iWidth, iHeight);

	MINUTIAE *minutiaes = new MINUTIAE[minuCount];
	memset(minutiaes, sizeof(MINUTIAE), minuCount);
	MinuFilter(image1, thin, minutiaes, minuCount, iWidth, iHeight);

	SaveMinutiae(minutiaes, minuCount, dstMdlFile);

	unsigned char *image2 = new unsigned char[iWidth*iHeight];
	memset(image2, 0, iWidth*iHeight);
	for (int i = 0; i < minuCount; i++) {
		image2[(minutiaes[i].y - 1)*iWidth + (minutiaes[i].x - 1)] = 0xff;
	}
	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);

	SaveDataToImageFile(srcImgFile, dstImgFile, image2);
	delete[] image1;
	delete[] image2;
	delete[] thin;
	delete[] minutiaes;

	sprintf(info, "第十一步特征过滤完成.");
	return 0;
}
void CFingerDlg::OnBnClickedBtnStep11()
{
	char info[MAX_PATH] = { 0 };
	Step11_MinuFilter(info);
	m_staticInfo.SetWindowText(ToWideChar(info));
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_10);//显示输入图像
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_11);//显示输出图像
}
//1
void Sort(unsigned char * data, int dsize)
{
	unsigned char temp = 0;
	for (int i = 0; i < dsize; i++) {
		for (int j = dsize - 1; j > i; j--) {
			if (data[j] < data[j - 1]) {
				temp = data[j];
				data[j] = data[j - 1];
				data[j - 1] = temp;
			}
		}
	}
}
//2
int MidFilter(unsigned char * ucImg, unsigned char * ucDstImg, int iWidth, int iHeight) {
	//第一步：结果图像数据初始化
	memset(ucDstImg, 0, iWidth*iHeight);

	//第二步：中心区域滤波(使用3*3邻域)
	unsigned char *pUp, *pDown, *pImg;//用来确定3*3邻域的三个图像数据指针
	unsigned char x[9];//3*3邻域图像数据数组
	for (int i = 1; i < iHeight - 1; i++) //遍历第二行到倒数第二行
	{
		//初始化邻域指针
		pUp = ucImg + (i - 1)*iWidth;
		pImg = ucImg + i * iWidth;
		pDown = ucImg + (i + 1)*iWidth;

		for (int j = 1; j < iWidth - 1; j++) //遍历第二列到倒数第二列
		{
			//移动邻域指针
			pUp++;
			pImg++;
			pDown++;
			//获取3*3邻域数据
			x[0] = *(pUp - 1);
			x[1] = *(pImg - 1);
			x[2] = *(pDown - 1);

			x[3] = *pUp;
			x[4] = *pImg;
			x[5] = *pDown;

			x[6] = *(pUp + 1);
			x[7] = *(pImg + 1);
			x[8] = *(pDown + 1);

			//数组排序
			Sort(x, 9);
			//结果图像数据取邻域中值
			*(ucDstImg + i * iWidth + j) = x[4];
		}
	}
	//第三步：第一行和最后一行滤波(使用2*3邻域)
	//第一行
	pDown = ucImg + iWidth;//邻域指针初始化
	for (int j = 1; j < iWidth - 1; j++) //第一行遍历第二列到倒数第二列
	{
		//获取2*3邻域数据
		x[0] = *(ucImg + j - 1);
		x[1] = *(ucImg + j);
		x[2] = *(ucImg + j + 1);

		x[3] = *(pDown + j - 1);
		x[4] = *(pDown + j);
		x[5] = *(pDown + j + 1);

		//数组排序
		Sort(x, 6);
		//结果取中值
		*(ucDstImg + j) = x[3];
	}

	//最后一行
	pUp = ucImg + iWidth * (iHeight - 2);//邻域指针初始化
	pDown = ucImg + iWidth * (iHeight - 1);//邻域指针初始化
	for (int j = 1; j < iWidth - 1; j++) //最后一行遍历第二列到倒数第二列
	{
		//获取2*3邻域数据
		x[0] = *(pDown + j - 1);
		x[1] = *(pDown + j);
		x[2] = *(pDown + j + 1);

		x[3] = *(pUp + j - 1);
		x[4] = *(pUp + j);
		x[5] = *(pUp + j + 1);

		//数组排序
		Sort(x, 6);
		//结果取中值
		*(ucDstImg + iWidth * (iHeight - 1) + j) = x[3];
	}

	//第四步：4个角点滤波(使用2*2邻域)
	//左上角点
	x[0] = *(ucImg);//获取2*2邻域
	x[1] = *(ucImg + 1);
	x[2] = *(ucImg + iWidth);
	x[3] = *(ucImg + iWidth + 1);
	Sort(x, 4);//数组排序
	*(ucDstImg) = x[2];//结果取中值
	//右上角点
	x[0] = *(ucImg + iWidth - 1);
	x[1] = *(ucImg + iWidth - 2);
	x[2] = *(ucImg + 2 * iWidth - 1);
	x[3] = *(ucImg + 2 * iWidth - 2);
	Sort(x, 4);
	*(ucDstImg + iWidth - 1) = x[2];
	//左下角点
	x[0] = *(ucImg + iWidth * (iHeight - 1));
	x[1] = *(ucImg + iWidth * (iHeight - 2));
	x[2] = *(ucImg + iWidth * (iHeight - 1) + 1);
	x[3] = *(ucImg + iWidth * (iHeight - 2) + 1);
	Sort(x, 4);
	*(ucDstImg + (iHeight - 1)*iWidth) = x[2];
	//右下角点
	x[0] = *(ucImg + iWidth * (iHeight - 0) - 1);
	x[1] = *(ucImg + iWidth * (iHeight - 1) - 1);
	x[2] = *(ucImg + iWidth * (iHeight - 0) - 2);
	x[3] = *(ucImg + iWidth * (iHeight - 1) - 2);
	Sort(x, 4);
	*(ucDstImg + (iHeight - 0)*iWidth - 1) = x[2];

	return 0;
}
//1
int Step2_MidFilter(char *info) {
	char srcTxtFile[MAX_PATH] = { STEP_TXT_1 };//源数据文件名
	char srcImgFile[MAX_PATH] = { STEP_IMG_1 };//源图文件名
	char dstTxtFile[MAX_PATH] = { STEP_TXT_2 };//结果数据文件名
	char dstImgFile[MAX_PATH] = { STEP_IMG_2 };//结果图文件名
	//读取图像参数
	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);
	//读取源数据
	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile, image1, iWidth, iHeight);
	//中值滤波
	unsigned char *image2 = new unsigned char[iWidth*iHeight];
	MidFilter(image1, image2, iWidth, iHeight);
	//保存结果数据(TXT文件)
	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);
	//保存结果图像(BMP文件，只用于显示)
	SaveDataToImageFile(srcImgFile, dstImgFile, image2);
	delete[] image1;
	delete[] image2;
	sprintf(info, "中值滤波完成.");
	return 0;
}
//1
void CFingerDlg::OnBnClickedBtnStep2()
{
	char info[MAX_PATH] = { 0 };
	Step2_MidFilter(info);
	//显示操作结果信息
	m_staticInfo.SetWindowText(ToWideChar(info));
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_1);//显示输入图像
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_2);//显示输出图像
}
//1
int  HistoNormalize(unsigned char * ucImg, unsigned char * ucNormImg, int iWidth, int iHeight)
{
	//构建源图灰度直方图
	unsigned int Histogram[256];
	memset(Histogram, 0, 256 * sizeof(int));
	for (int i = 0; i < iHeight; i++) {
		for (int j = 0; j < iWidth; j++) {
			Histogram[ucImg[i*iWidth + j]]++;
		}
	}

	//计算源图的灰度均值和方差
	double dMean = 0;
	for (int i = 1; i < 255; i++) {
		dMean += i * Histogram[i];
	}
	dMean = int(dMean / (iWidth*iHeight));
	double dSigma = 0;
	for (int i = 0; i < 255; i++) {
		dSigma += Histogram[i] * (i - dMean)*(i - dMean);
	}
	dSigma /= (iWidth*iHeight);
	dSigma = sqrt(dSigma);

	//对各像素进行均衡化操作
	double dMean0 = 128, dSigma0 = 128;//预设灰度均值和方差
	double dCoeff = dSigma0 / dSigma;//转换系数
	for (int i = 0; i < iHeight; i++) {
		for (int j = 0; j < iWidth; j++) {
			double dVal = ucImg[i*iWidth + j];
			dVal = dMean0 + dCoeff * (dVal - dMean0);
			if (dVal < 0) {
				dVal = 0;
			}
			else if (dVal > 255) {
				dVal = 255;
			}
			ucNormImg[i*iWidth + j] = (unsigned char)dVal;
		}
	}
	return 0;
}
//2
int  Step3_Normalize(char * info)
{
	char srcTxtFile[MAX_PATH] = { STEP_TXT_2 };
	char srcImgFile[MAX_PATH] = { STEP_IMG_2 };
	char dstTxtFile[MAX_PATH] = { STEP_TXT_3 };
	char dstImgFile[MAX_PATH] = { STEP_IMG_3 };

	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);

	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	ReadDataFromTextFile(srcTxtFile, image1, iWidth, iHeight);

	unsigned char *image2 = new unsigned char[iWidth*iHeight];
	HistoNormalize(image1, image2, iWidth, iHeight);

	SaveDataToTextFile(dstTxtFile, image2, iWidth, iHeight);
	SaveDataToImageFile(srcImgFile, dstImgFile, image2);

	delete[] image1;
	delete[] image2;
	sprintf(info, "直方图均衡化完成.");
	return 0;
}
//1
void CFingerDlg::OnBnClickedBtnStep3()
{
	char info[MAX_PATH] = { 0 };
	Step3_Normalize(info);
	//显示操作结果信息
	m_staticInfo.SetWindowText(ToWideChar(info));
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_2);//显示输入图像
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_3);//显示输出图像
}

char *ToChar(wchar_t *str) {
	int num = WideCharToMultiByte(0, 0, str, -1, NULL, 0, NULL, false);
	char *chStr = new char[num];
	WideCharToMultiByte(0, 0, str, -1, chStr, num, NULL, false);
	return chStr;
}
int GetNewIndexInDB() {	
	//从ndx文件中读取最后一条记录的编号
		int sNo = 0;
		char name[MAX_PATH]={ 0 }, srcFile[MAX_PATH] = { 0 }, mdlFile[MAX_PATH] = { 0 };
		FILE *index = fopen(DB_INDEX_TXT, "r");
		while (!feof(index)) {
			fscanf(index, "%d  %s  %s  %s\n", &sNo, srcFile, mdlFile, name);
		}
		fclose(index);
		sNo = sNo + 1;
		return sNo;
}
int Step12_Enroll(char* userName, char *info) {
	char srcImgFile[MAX_PATH] = {STEP_IMG_1};
	char srcMdlFile[MAX_PATH] = { STEP_IMG_11_MDL };
	int sNo = GetNewIndexInDB();
	char regName[MAX_PATH] = { 0 };
	char dstImgFile[MAX_PATH] = { 0 };
	char dstMdlFile[MAX_PATH] = { 0 };
	sprintf(regName, userName);
	sprintf(dstImgFile, "%s%d.bmp", DB_DIR, sNo);
	sprintf(dstMdlFile, "%s%d.mdl", DB_DIR, sNo);

	CopyFile(ToWideChar(srcImgFile), ToWideChar(dstImgFile), false);
	CopyFile(ToWideChar(srcMdlFile), ToWideChar(dstMdlFile), false);
	FILE *index = fopen(DB_INDEX_TXT, "a");
	fprintf(index, "%d  %s  %s  %s\n", sNo, dstImgFile, dstMdlFile,regName);
	fclose(index);
	sprintf(info, "完成特征入库");
	return 0;
}

float Angle2Points(int x1, int y1, int x2, int y2) {
	const float PI = 3.141592654;
	float diffY, diffX;
	float theta = 0.0;

	diffY = y2 - y1;
	diffX = x2 - x1;

	if (diffY < 0 && diffX>0) {
		theta = atan2(-1 * diffY, diffX);
	}
	else if (diffY < 0 && diffX < 0) {
		theta = PI - atan2(-1 * diffY, -1 * diffX);
	}
	else if (diffY > 0 && diffX < 0) {
		theta = atan2(diffY, -1 * diffX);
	}
	else if (diffY > 0 && diffX > 0) {
		theta = PI - atan2(diffY, diffX);
	}
	else if (diffX == 0) {
		theta = PI / 2;
	}
	else {
		theta = 0.0;
	}
	return theta;
}
int BuildNabors(MINUTIAE *minutiae, int minuCount) {
	const int MAX_NEIGHBOR_EACH = 10;
	int x1, x2, y1, y2;
	int *pFlag = new int[minuCount];
	for (int i = 0; i < minuCount; i++) {
		x1 = minutiae[i].x;
		y1 = minutiae[i].y;

		memset(pFlag, 0, sizeof(int)*minuCount);
		pFlag[i] = 1;
		minutiae[i].neibors = new NEIGHBOR[MAX_NEIGHBOR_EACH];
		if (minutiae[i].neibors == NULL) {
			return -1;
		}
		memset(minutiae[i].neibors, 0, sizeof(NEIGHBOR)*MAX_NEIGHBOR_EACH);

		for (int neighborNo = 0; neighborNo < MAX_NEIGHBOR_EACH; neighborNo++) {
			int minDistance = 1000;
			int minNo = 0;
			for (int j = 0; j < minuCount; j++) {
				if (pFlag[j] == 1) {
					continue;
				}
				x2 = minutiae[j].x;
				y2 = minutiae[j].y;
				int r = (int)sqrt(float((y1 - y2)*(y1 - y2) + (x1 - x2)*(x1 - x2)));

				if (r < minDistance) {
					minNo = j;
					minDistance = r;
				}
			}

			pFlag[minNo] = 1;
			minutiae[i].neibors[neighborNo].x = minutiae[minNo].x;
			minutiae[i].neibors[neighborNo].y = minutiae[minNo].y;
			minutiae[i].neibors[neighborNo].type = minutiae[minNo].type;
				minutiae[i].neibors[neighborNo].Theta = Angle2Points(minutiae[minNo].x, minutiae[minNo].y, x1, y1);

			minutiae[i].neibors[neighborNo].Theta2Ridge = minutiae[minNo].theta - minutiae[i].theta;

			minutiae[i].neibors[neighborNo].Theta2ThisNibor = minutiae[minNo].theta;

			minutiae[i].neibors[neighborNo].distance = minDistance;

		}
	}
	delete[] pFlag;
	return 0;
}
float MinuSimilarity(int iWidth, int iHeight, MINUTIAE* minutiae1, int count1, MINUTIAE* minutiae2, int count2) {
	const int MAX_SIMILAR_PAIR = 100;
	const int MAX_NEIGHBOR_EACH = 10;
	BuildNabors(minutiae1, count1);
	BuildNabors(minutiae2, count2);

	int similarPair[MAX_SIMILAR_PAIR][2];

	memset(similarPair, 0, 100 * 2 * sizeof(int));

	MINUTIAE *baseMinutiae;
	MINUTIAE *refMinutiae;

	int baseAccount, refAccount;

	if (count1 < count2) {
		baseMinutiae = minutiae1;
		baseAccount = count1;
		refMinutiae = minutiae2;
		refAccount = count2;
	}
	else {
		baseMinutiae = minutiae2;
		baseAccount = count2;
		refMinutiae = minutiae1;
		refAccount = count1;
	}

	NEIGHBOR *baseNeighbors = NULL;
	NEIGHBOR *refNeighbors = NULL;

	int similarMinutiae = 0;
	float baseTheta, refTheta;
	for (int i = 0; i < baseAccount; i++) {
		baseNeighbors = baseMinutiae[i].neibors;
		baseTheta = baseMinutiae[i].theta;
		int refSimilarNo = 0;
		int maxSimilarNerbors = 0;
		for (int j = 0; j < refAccount; j++) {
			if (refMinutiae[j].type != baseMinutiae[i].type) {
				continue;
			}
			refNeighbors = refMinutiae[j].neibors;
			refTheta = refMinutiae[j].theta;
			int thisSimilarNeigbors = 0;
			for (int m = 0; m < MAX_NEIGHBOR_EACH; m++) {
				for (int n = 0; n < MAX_NEIGHBOR_EACH; n++) {
					if (baseNeighbors[m].type != refNeighbors[n].type) {
						continue;
					}
					int dist = abs(int(baseNeighbors[m].distance - refNeighbors[n].distance));
					float theta1 = abs(float((baseNeighbors[m].Theta - baseTheta) - (refNeighbors[n].Theta - refTheta)));
					float theta2 = abs(float(baseNeighbors[m].Theta2Ridge - refNeighbors[n].Theta2Ridge));
					float theta3 = abs(float((baseNeighbors[m].Theta - baseNeighbors[m].Theta2ThisNibor) - (refNeighbors[n].Theta - refNeighbors[n].Theta2ThisNibor)));
					if (dist < 4 && theta1 < 0.15f&&theta2 < 0.15f&&theta3 < 0.15f) {
						++thisSimilarNeigbors;
						break;
					}
				}
			}
			if ((thisSimilarNeigbors >= MAX_NEIGHBOR_EACH * 3 / 10) && (similarMinutiae < MAX_SIMILAR_PAIR)) {
				similarPair[similarMinutiae][0] = i;
				similarPair[similarMinutiae][1] = refSimilarNo;
				++similarMinutiae;
			}
		}
	}

	float similarity = similarMinutiae / 8.0f;
	similarity = similarMinutiae < 2 ? 0.0f : similarity;
	similarity = similarMinutiae > 8 ? 1.0f : similarity;
	return similarity;
}
int ReadMinutiae(char* filename, MINUTIAE** minutiae) {
	FILE * fp = fopen(filename, "rb");
	if (!fp) {
		return -1;
	}
	const static int TemplateFileFlag = 0x3571027f;
	int flag;
	fread(&flag, sizeof(int), 1, fp);
	if (flag != TemplateFileFlag) {
		return -2;
	}
	int account;
	fread(&account, sizeof(int), 1, fp);
	*minutiae = new MINUTIAE[account];
	if (*minutiae == NULL) {
		return -3;
	}
	for (int i = 0; i < account; i++) {
		fread(&((*minutiae)[i]), sizeof(MINUTIAE), 1, fp);
	}

	fclose(fp);
	return account;
}
int Step12_Match(char *info) {
	char srcImgFile[MAX_PATH] = {STEP_IMG_1};
	char srcMdlFile[MAX_PATH] = { STEP_IMG_11_MDL };
	char dstImgFile[MAX_PATH] = { STEP_IMG_12 };

	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);

	MINUTIAE *minu = NULL;
	int minuAccount = ReadMinutiae(srcMdlFile, &minu);

	float similar = MinuSimilarity(iWidth, iHeight, minu, minuAccount,minu,minuAccount);

	delete[] minu;
	CopyFile(ToWideChar(srcImgFile), ToWideChar(dstImgFile), false);

	const float SIMILAR_THRED = 0.1;
	if (similar < SIMILAR_THRED) {
		sprintf(info, "匹配失败");
		return -3;
	}
	sprintf(info, "匹配成功:相似度[%.2f].", similar);
	return 0;
}
bool EmptyDB()
{
	// 打开文件
	char indexFile[MAX_PATH] = { DB_INDEX_TXT }; // 指纹库索引文件
	FILE * pFile = fopen(indexFile, "r");
	if (!pFile) //若索引文件不存在或存在异常, 则指纹库为空
	{
		return true;
	}
	// 判断指纹库是否为空(索引文件内容是否为空)
	int size = filelength(fileno(pFile)); //文件长度(以字节为单位)
	bool bEmpty = (size < 1) ? true : false; // 若索引文件内容为空，, 则指纹库为空
	//关闭文件
	fclose(pFile);
	//返回判断结果
	return bEmpty;
}
int Step12_Identify(char *info) {
	char srcImgFile[MAX_PATH] = { STEP_IMG_1 };
	char srcMdlFile[MAX_PATH] = { STEP_IMG_11_MDL };
	char dstImgFile[MAX_PATH] = { STEP_IMG_12 };
	char dstMdlFile[MAX_PATH] = { 0 };
	EmptyDB();
	int iWidth, iHeight, iDepth;

	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);

	//读取指纹特征数据

	MINUTIAE *minul = NULL, *minu2 = NULL;

	int minuAccount1 = 0, minuAccount2 = 0;

	minuAccount1 = ReadMinutiae(srcMdlFile, &minul);

	//特征识别

	int id = 0;
	char name[MAX_PATH] = { 0 }, src[MAX_PATH] = { 0 }, mdl[MAX_PATH] = { 0 };
	float maxSimilar = -1;
	int maxID = -1;
	char maxName[MAX_PATH] = { 0 }, maxSrc[MAX_PATH] = { 0 };
	FILE *index = fopen(DB_INDEX_TXT, "r");//打开指纹库索引文件
	while (!feof(index)) {
		//读取指纹记录信息(指纹编号/指纹图像文件名/特征模板文件名/登记人姓名)
		fscanf(index, "%d %s %s %s\n", &id, src, mdl, name);
		sprintf(dstMdlFile, mdl);
		minuAccount2 = ReadMinutiae(dstMdlFile, &minu2);
		//特征匹配
		float similar = MinuSimilarity(iWidth, iHeight, minul, minuAccount1, minu2, minuAccount2);
		if (similar > maxSimilar) {
			maxSimilar = similar;
			maxID = id;
			sprintf(maxName, name);
			sprintf(maxSrc, src);
		}
	}
	fclose(index);//关闭文件
	//释放内存空间
	delete[] minul;
	delete[] minu2;

	//返回识别结果
	const float SIMILAR_THRED = 0.1;//匹配相似度阈值(小于阈值则认为不匹配)if (maxID<0 II maxSimilar<SIMILAR THRED)
	if (maxID < 0 || maxSimilar < SIMILAR_THRED) {
		sprintf(info, "识别失败.");
		return -2;
	}
	CopyFile(ToWideChar(maxSrc), ToWideChar(dstImgFile), false);
	sprintf(info, "识别成功.识别结果:姓名[%s],目标指纹[%s],相似度[%.2f].", maxName, maxSrc, maxSimilar);
	return 0;
}

void CFingerDlg::OnBnClickedBtnStep12a()
{
	CEdit* pBoxOne;
	pBoxOne = (CEdit*)GetDlgItem(IDC_EDIT_NAME);
	CString str;
	pBoxOne->GetWindowText(str);
	if (str.GetLength() != 0) {
		char info[MAX_PATH] = { 0 };
		UpdateData(true);
		Step12_Enroll(ToChar(m_name.GetBuffer()), info);
		//显示操作结果信息
		m_staticInfo.SetWindowText(ToWideChar(info));
		ShowImageInCtrl(m_picCtrl1, STEP_IMG_1);//显示输入图像
		ShowImageInCtrl(m_picCtrl2, STEP_IMG_11);//显示输出图像
	}
	else
	{
		MessageBox(_T("请输入姓名"), _T("提示"));
		return;
	}
}

void CFingerDlg::OnBnClickedBtnStep12b()
{
	char info[MAX_PATH] = { 0 };
	Step12_Match(info);
	//显示操作结果信息
	Step12_Identify(info);
	m_staticInfo.SetWindowText(ToWideChar(info));
	ShowImageInCtrl(m_picCtrl1, STEP_IMG_1);//显示输入图像
	ShowImageInCtrl(m_picCtrl2, STEP_IMG_12);//显示输出图像
}
int Enroll(char * regName, char * srcImgFile, char * outImgFile, char * info, bool bSaveImg)
{
	//第0步：设置中间结果文件名
	//中间结果数据文件名
	char stepTxtFile1[MAX_PATH] = { STEP_TXT_1 };
	char stepTxtFile2[MAX_PATH] = { STEP_TXT_2 };
	char stepTxtFile3[MAX_PATH] = { STEP_TXT_3 };
	char stepTxtFile4[MAX_PATH] = { STEP_TXT_4 };
	char stepTxtFile5[MAX_PATH] = { STEP_TXT_5 };
	char stepTxtFile6[MAX_PATH] = { STEP_TXT_6 };
	char stepTxtFile7[MAX_PATH] = { STEP_TXT_7 };
	char stepTxtFile8[MAX_PATH] = { STEP_TXT_8 };
	char stepTxtFile9[MAX_PATH] = { STEP_TXT_9 };
	char stepTxtFile10[MAX_PATH] = { STEP_TXT_10 };
	char stepTxtFile11[MAX_PATH] = { STEP_TXT_11 };

	//中间结果图像文件名
	char stepImgFile1[MAX_PATH] = { STEP_IMG_1 };
	char stepImgFile2[MAX_PATH] = { STEP_IMG_2 };
	char stepImgFile3[MAX_PATH] = { STEP_IMG_3 };
	char stepImgFile4[MAX_PATH] = { STEP_IMG_4 };
	char stepImgFile5[MAX_PATH] = { STEP_IMG_5 };
	char stepImgFile6[MAX_PATH] = { STEP_IMG_6 };
	char stepImgFile7[MAX_PATH] = { STEP_IMG_7 };
	char stepImgFile8[MAX_PATH] = { STEP_IMG_8 };
	char stepImgFile9[MAX_PATH] = { STEP_IMG_9 };
	char stepImgFile10[MAX_PATH] = { STEP_IMG_10 };
	char stepImgFile11[MAX_PATH] = { STEP_IMG_11 };
	char stepImgFile12[MAX_PATH] = { STEP_IMG_12 };

	//指纹特征模板文件名
	char stepMdlFile11[MAX_PATH] = { STEP_IMG_11_MDL };

	//第1步：图像载入，读取源图数据和参数信息
	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);//读取源图参数信息
	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	unsigned char *image2 = new unsigned char[iWidth*iHeight];
	ReadBMPImgFileData(srcImgFile, image1);//读取源图数据
	memset(image2, 0, iWidth*iHeight);//结果图初始化
	if (bSaveImg)
	{
		CopyFile(ToWideChar(srcImgFile), ToWideChar(stepImgFile1), false);
		SaveDataToTextFile(stepTxtFile1, image1, iWidth, iHeight);
	}

	//第2步：中值滤波
	MidFilter(image1, image2, iWidth, iHeight);//中值滤波
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile2, image2);
		SaveDataToTextFile(stepTxtFile2, image2, iWidth, iHeight);
	}

	//第3步：直方图均衡化
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//以上一步结果为源图数据
	HistoNormalize(image1, image2, iWidth, iHeight);//直方图均衡化
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile3, image2);
		SaveDataToTextFile(stepTxtFile3, image2, iWidth, iHeight);
	}

	//第4步：方向计算
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//以上一步结果为源图数据
	float *tmpDirection = new float[iWidth*iHeight];
	float *direction = new float[iWidth*iHeight];
	ImgDirection(image1, tmpDirection, iWidth, iHeight);//方向计算
	DircLowPass(tmpDirection, direction, iWidth, iHeight);//方向低通滤波
	if (bSaveImg)
	{
		const int DIRECTION_SCALE = 100;//方向结果转换比例，仅用于结果显示
		SaveDataToImageFile(srcImgFile, stepImgFile4, direction, DIRECTION_SCALE);
		SaveDataToTextFile(stepTxtFile4, direction, iWidth, iHeight);
	}
	delete[] tmpDirection;

	//第5步：频率计算
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//以上一步结果为源图数据
	float *frequency = new float[iWidth*iHeight];
	Frequency(image1, direction, frequency, iWidth, iHeight);//频率计算
	if (bSaveImg)
	{
		const int FREQUENCY_SCALE = 100;//频率结果转换比例，仅用于结果显示
		SaveDataToImageFile(srcImgFile, stepImgFile5, frequency, FREQUENCY_SCALE);
		SaveDataToTextFile(stepTxtFile5, frequency, iWidth, iHeight);
	}

	//第6步：掩码计算
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//以上一步结果为源图数据
	unsigned char *mask = new unsigned char[iWidth*iHeight];
	GetMask(image1, direction, frequency, mask, iWidth, iHeight);//掩码计算
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile6, mask);
		SaveDataToTextFile(stepTxtFile6, mask, iWidth, iHeight);
	}

	//第7步：Gabor滤波增强
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//以上一步结果为源图数据
	GaborEnhance(image1, direction, frequency, mask, image2, iWidth, iHeight);//增强
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile7, image2);
		SaveDataToTextFile(stepTxtFile7, image2, iWidth, iHeight);
	}
	delete[] direction;
	delete[] frequency;
	delete[] mask;

	//第8步：二值化
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//以上一步结果为源图数据
	BinaryImg(image1, image2, iWidth, iHeight, 128);//二值化
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile8, image2);
		SaveDataToTextFile(stepTxtFile8, image2, iWidth, iHeight);
	}

	//第9步：细化
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//以上一步结果为源图数据
	Thinning(image1, image2, iWidth, iHeight, 128);//细化
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile9, image2);
		SaveDataToTextFile(stepTxtFile9, image2, iWidth, iHeight);
	}
	unsigned char *thin = new unsigned char[iWidth*iHeight];
	memcpy(thin, image2, sizeof(unsigned char)*iWidth*iHeight);//保存细化结果

	//第10步：特征提取
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//以上一步结果为源图数据
	int minuCount = Extract(image1, image2, iWidth, iHeight);//特征提取
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile10, image2);
		SaveDataToTextFile(stepTxtFile10, image2, iWidth, iHeight);
	}

	//第11步：特征过滤
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//以上一步结果为源图数据
	MINUTIAE *minutiaes = new MINUTIAE[minuCount];
	memset(minutiaes, sizeof(MINUTIAE), minuCount);
	MinuFilter(image1, thin, minutiaes, minuCount, iWidth, iHeight);//特征过滤
	delete[] thin;
	SaveMinutiae(minutiaes, minuCount, stepMdlFile11);//保存特征数据文件
	if (true)
	{
		memset(image2, 0, iWidth*iHeight);
		for (int i = 0; i < minuCount; i++)
		{
			image2[(minutiaes[i].y - 1)*iWidth + (minutiaes[i].x - 1)] = 0xff;
		}
		SaveDataToImageFile(srcImgFile, stepImgFile11, image2);
		SaveDataToTextFile(stepTxtFile11, image2, iWidth, iHeight);
	}
	strcpy(outImgFile, stepImgFile11);//保存特征结果图文件名

	//第12步：特征入库
	int sNo = GetNewIndexInDB();//获取数据库新指纹记录编号
	char dbImgFile[MAX_PATH] = { 0 };//数据库中源图文件名
	char dbMdlFile[MAX_PATH] = { 0 };//数据库中模板文件名
	sprintf(dbImgFile, "%s%d.bmp", DB_DIR, sNo);//设置源图文件名
	sprintf(dbMdlFile, "%s%d.mdl", DB_DIR, sNo);//设置模板文件名
	if (minuCount > 0)
	{
		//保存原始指纹图像
		CopyFile(ToWideChar(srcImgFile), ToWideChar(dbImgFile), false);

		//保存指纹特征模板文件
		CopyFile(ToWideChar(stepMdlFile11), ToWideChar(dbMdlFile), false);

		FILE *index = fopen(DB_INDEX_TXT, "a");
		fprintf(index, "%d %s %s %s\n", sNo, dbImgFile, dbMdlFile, regName);
		fclose(index);
	}
	delete[] image1;
	delete[] image2;
	delete[] minutiaes;

	sprintf(info, "指纹登记成功");
	return 0;
}
void CFingerDlg::OnBnClickedBtnStepAddimage()
{
	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"), NULL);
	CString defaultPath("databases");
	CString folderPath("outfile");

	if (!PathIsDirectory(defaultPath))  // 是否有重名文件夹
	{
		::CreateDirectory(defaultPath, 0);
	}
	if (!PathIsDirectory(folderPath))  // 是否有重名文件夹
	{
		::CreateDirectory(folderPath, 0);
	}
	if (dlgFile.DoModal() == IDOK)
	{
		strFile = dlgFile.GetPathName();
	}
	else {
		MessageBox(_T("未选中图片"), _T("提示"));
		return;
	}

	USES_CONVERSION;
	char * beginfilename = T2A(strFile);
	char info[MAX_PATH] = { 0 };
	UpdateData(true);

	//指纹登记
	bool bSaveImg = false;
	char outImgFile[MAX_PATH] = { 0 };//指纹特征结果图像文件名
	Enroll(ToChar(m_name.GetBuffer()), beginfilename, outImgFile, info, bSaveImg);
	m_staticInfo.SetWindowText(ToWideChar(info));
	ShowImageInCtrl(m_picCtrl1, beginfilename);//显示原始指纹图像
	ShowImageInCtrl(m_picCtrl2, outImgFile);//显示指纹特征图像
}

int Identify(char * srcImgFile, char * outImgFile, char * info, bool bSaveImg) {
	//第0步：设置中间结果文件名
	//中间结果数据文件名
	char stepTxtFile1[MAX_PATH] = { STEP_TXT_1 };
	char stepTxtFile2[MAX_PATH] = { STEP_TXT_2 };
	char stepTxtFile3[MAX_PATH] = { STEP_TXT_3 };
	char stepTxtFile4[MAX_PATH] = { STEP_TXT_4 };
	char stepTxtFile5[MAX_PATH] = { STEP_TXT_5 };
	char stepTxtFile6[MAX_PATH] = { STEP_TXT_6 };
	char stepTxtFile7[MAX_PATH] = { STEP_TXT_7 };
	char stepTxtFile8[MAX_PATH] = { STEP_TXT_8 };
	char stepTxtFile9[MAX_PATH] = { STEP_TXT_9 };
	char stepTxtFile10[MAX_PATH] = { STEP_TXT_10 };
	char stepTxtFile11[MAX_PATH] = { STEP_TXT_11 };

	//中间结果图像文件名
	char stepImgFile1[MAX_PATH] = { STEP_IMG_1 };
	char stepImgFile2[MAX_PATH] = { STEP_IMG_2 };
	char stepImgFile3[MAX_PATH] = { STEP_IMG_3 };
	char stepImgFile4[MAX_PATH] = { STEP_IMG_4 };
	char stepImgFile5[MAX_PATH] = { STEP_IMG_5 };
	char stepImgFile6[MAX_PATH] = { STEP_IMG_6 };
	char stepImgFile7[MAX_PATH] = { STEP_IMG_7 };
	char stepImgFile8[MAX_PATH] = { STEP_IMG_8 };
	char stepImgFile9[MAX_PATH] = { STEP_IMG_9 };
	char stepImgFile10[MAX_PATH] = { STEP_IMG_10 };
	char stepImgFile11[MAX_PATH] = { STEP_IMG_11 };
	char stepImgFile12[MAX_PATH] = { STEP_IMG_12 };

	//指纹特征模板文件名
	char stepMdlFile11[MAX_PATH] = { STEP_IMG_11_MDL };

	//判断指纹库是否为空
	EmptyDB();

	//第1步：图像载入，读取源图数据和参数信息
	int iWidth, iHeight, iDepth;
	ReadBMPImgFilePara(srcImgFile, iWidth, iHeight, iDepth);//读取源图参数信息
	unsigned char *image1 = new unsigned char[iWidth*iHeight];
	unsigned char *image2 = new unsigned char[iWidth*iHeight];
	ReadBMPImgFileData(srcImgFile, image1);//读取源图数据
	memset(image2, 0, iWidth*iHeight);//结果图初始化
	if (bSaveImg)
	{
		CopyFile(ToWideChar(srcImgFile), ToWideChar(stepImgFile1), false);
		SaveDataToTextFile(stepTxtFile1, image1, iWidth, iHeight);
	}

	//第2步：中值滤波
	MidFilter(image1, image2, iWidth, iHeight);//中值滤波
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile2, image2);
		SaveDataToTextFile(stepTxtFile2, image2, iWidth, iHeight);
	}

	//第3步：直方图均衡化
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//以上一步结果为源图数据
	HistoNormalize(image1, image2, iWidth, iHeight);//直方图均衡化
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile3, image2);
		SaveDataToTextFile(stepTxtFile3, image2, iWidth, iHeight);
	}

	//第4步：方向计算
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//以上一步结果为源图数据
	float *tmpDirection = new float[iWidth*iHeight];
	float *direction = new float[iWidth*iHeight];
	ImgDirection(image1, tmpDirection, iWidth, iHeight);//方向计算
	DircLowPass(tmpDirection, direction, iWidth, iHeight);//方向低通滤波
	if (bSaveImg)
	{
		const int DIRECTION_SCALE = 100;//方向结果转换比例，仅用于结果显示
		SaveDataToImageFile(srcImgFile, stepImgFile4, direction, DIRECTION_SCALE);
		SaveDataToTextFile(stepTxtFile4, direction, iWidth, iHeight);
	}
	delete[] tmpDirection;

	//第5步：频率计算
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//以上一步结果为源图数据
	float *frequency = new float[iWidth*iHeight];
	Frequency(image1, direction, frequency, iWidth, iHeight);//频率计算
	if (bSaveImg)
	{
		const int FREQUENCY_SCALE = 100;//频率结果转换比例，仅用于结果显示
		SaveDataToImageFile(srcImgFile, stepImgFile5, frequency, FREQUENCY_SCALE);
		SaveDataToTextFile(stepTxtFile5, frequency, iWidth, iHeight);
	}

	//第6步：掩码计算
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//以上一步结果为源图数据
	unsigned char *mask = new unsigned char[iWidth*iHeight];
	GetMask(image1, direction, frequency, mask, iWidth, iHeight);//掩码计算
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile6, mask);
		SaveDataToTextFile(stepTxtFile6, mask, iWidth, iHeight);
	}

	//第7步：Gabor滤波增强
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//以上一步结果为源图数据
	GaborEnhance(image1, direction, frequency, mask, image2, iWidth, iHeight);//增强
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile7, image2);
		SaveDataToTextFile(stepTxtFile7, image2, iWidth, iHeight);
	}
	delete[] direction;
	delete[] frequency;
	delete[] mask;

	//第8步：二值化
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//以上一步结果为源图数据
	BinaryImg(image1, image2, iWidth, iHeight, 128);//二值化
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile8, image2);
		SaveDataToTextFile(stepImgFile8, image2, iWidth, iHeight);
	}

	//第9步：细化
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//以上一步结果为源图数据
	Thinning(image1, image2, iWidth, iHeight, 128);//细化
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile9, image2);
		SaveDataToTextFile(stepTxtFile9, image2, iWidth, iHeight);
	}
	unsigned char *thin = new unsigned char[iWidth*iHeight];
	memcpy(thin, image2, sizeof(unsigned char)*iWidth*iHeight);//保存细化结果

	//第10步：特征提取
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//以上一步结果为源图数据
	int minuCount = Extract(image1, image2, iWidth, iHeight);//特征提取
	if (bSaveImg)
	{
		SaveDataToImageFile(srcImgFile, stepImgFile10, image2);
		SaveDataToTextFile(stepTxtFile10, image2, iWidth, iHeight);
	}

	//第11步：特征过滤
	memcpy(image1, image2, sizeof(unsigned char)*iWidth*iHeight);//以上一步结果为源图数据
	MINUTIAE *minutiaes = new MINUTIAE[minuCount];
	memset(minutiaes, sizeof(MINUTIAE), minuCount);
	MinuFilter(image1, thin, minutiaes, minuCount, iWidth, iHeight);//特征过滤
	delete[] thin;
	SaveMinutiae(minutiaes, minuCount, stepMdlFile11);//保存特征数据文件
	if (bSaveImg)
	{
		memset(image2, 0, iWidth*iHeight);
		for (int i = 0; i < minuCount; i++)
		{
			image2[(minutiaes[i].y - 1)*iWidth + (minutiaes[i].x - 1)] = 0xff;
		}
		SaveDataToImageFile(srcImgFile, stepImgFile11, image2);
		SaveDataToTextFile(stepTxtFile11, image2, iWidth, iHeight);
	}
	delete[] image1;
	delete[] image2;

	//第12步：特征识别
	int id = 0;
	char name[MAX_PATH] = { 0 }, src[MAX_PATH] = { 0 }, mdl[MAX_PATH] = { 0 };
	float maxSimilar = -1;
	int maxID = -1;
	char maxName[MAX_PATH] = { 0 }, maxSrc[MAX_PATH] = { 0 };
	MINUTIAE *minutiaes2 = NULL;
	int minuCount2 = 0;
	FILE *index = fopen(DB_INDEX_TXT, "r");

	while (!feof(index))
	{
		fscanf(index, "%d %s %s %s\n", &id, src, mdl, name);


		minuCount2 = ReadMinutiae(mdl, &minutiaes2);
		float similar = MinuSimilarity(iWidth, iHeight, minutiaes, minuCount, minutiaes2, minuCount2);
		if (similar > maxSimilar)
		{
			maxSimilar = similar;
			maxID = id;
			sprintf(maxName, name);
			sprintf(maxSrc, src);
		}
	}
	fclose(index);
	delete[] minutiaes;
	delete[] minutiaes2;
	const float SIMILAR_THRED = 0.1;
	if (maxID < 0 || maxSimilar < SIMILAR_THRED)
	{
		sprintf(info, "识别失败");
		return -12;
	}
	strcpy(outImgFile, maxSrc);
	if (bSaveImg)
	{
		CopyFile(ToWideChar(maxSrc), ToWideChar(stepImgFile12), false);
	}
	sprintf(info, "识别成功.识别结果:姓名[%s],目标指纹[%s],相似度[%.2f]."
		, maxName, maxSrc, maxSimilar);
	return 0;
}
void CFingerDlg::OnBnClickedBtnMatchImage()
{
	CFileDialog    dlgFile(TRUE, NULL, NULL, OFN_HIDEREADONLY, _T("Describe Files (*.bmp)|*.bmp|All Files (*.*)|*.*||"), NULL);
	CString defaultPath("databases");
	CString folderPath("outfile");

	if (!PathIsDirectory(defaultPath))  // 是否有重名文件夹
	{
		::CreateDirectory(defaultPath, 0);
	}
	if (!PathIsDirectory(folderPath))  // 是否有重名文件夹
	{
		::CreateDirectory(folderPath, 0);
	}
	if (dlgFile.DoModal() == IDOK)
	{
		strFile = dlgFile.GetPathName();
	}
	else {
		MessageBox(_T("未选中图片"), _T("提示"));
		return;
	}

	USES_CONVERSION;
	char * beginfilename = T2A(strFile);
	char info[MAX_PATH] = { 0 };
	//m_zkfpEng.SaveBitmap(ToWideChar(srcImgFile));

	//指纹登记
	bool bSaveImg = false;
	char outImgFile[MAX_PATH] = { 0 };//指纹特征结果图像文件名
	Identify(beginfilename, outImgFile, info, bSaveImg);
	m_staticInfo.SetWindowText(ToWideChar(info));
	ShowImageInCtrl(m_picCtrl1, beginfilename);//显示原始指纹图像
	ShowImageInCtrl(m_picCtrl2, outImgFile);//显示指纹特征图像
}


void CFingerDlg::OnBnClickedBtnRegister()
{
	CEdit* pBoxOne;
	pBoxOne = (CEdit*)GetDlgItem(IDC_EDIT_NAME);
	CString str;
	pBoxOne->GetWindowText(str);
	if (str.GetLength() != 0) {
		char info[MAX_PATH] = { 0 };
		UpdateData(true);
		char srcImgFile[MAX_PATH] = "cai.bmp";

		//指纹登记
		bool bSaveImg = false;
		char outImgFile[MAX_PATH] = { 0 };//指纹特征结果图像文件名
		Enroll(ToChar(m_name.GetBuffer()), srcImgFile, outImgFile, info, bSaveImg);
		m_staticInfo.SetWindowText(ToWideChar(info));
		ShowImageInCtrl(m_picCtrl1, srcImgFile);//显示原始指纹图像
		ShowImageInCtrl(m_picCtrl2, outImgFile);//显示指纹特征图像
	}
	else {

		MessageBox(_T("请输入姓名"), _T("提示"));
		return;
	}
}


void CFingerDlg::OnBnClickedBtnIdentify()
{

	char info[MAX_PATH] = { 0 };
	char srcImgFile[MAX_PATH] = "cai.bmp";
	bool bSaveImg = false;
	char outImgFile[MAX_PATH] = { 0 };//指纹特征结果图像文件名
	Identify(srcImgFile, outImgFile, info, bSaveImg);
	m_staticInfo.SetWindowText(ToWideChar(info));
	ShowImageInCtrl(m_picCtrl1, srcImgFile);//显示原始指纹图像
	ShowImageInCtrl(m_picCtrl2, outImgFile);//显示指纹特征图像
}


void CFingerDlg::OnEnChangeEditName()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
