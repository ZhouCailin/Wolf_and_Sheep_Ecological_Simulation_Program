
// newvisualDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "newvisual.h"
#include "newvisualDlg.h"
#include "afxdialogex.h"
#include "WOLFNSHEEP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern World *w=new World;//核心外部变量

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CnewvisualDlg 对话框




CnewvisualDlg::CnewvisualDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CnewvisualDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CnewvisualDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, M_edit1);
}

BEGIN_MESSAGE_MAP(CnewvisualDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CnewvisualDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CnewvisualDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON2, &CnewvisualDlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CnewvisualDlg 消息处理程序

BOOL CnewvisualDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	bai.LoadBitmapW(IDB_BITMAP1);
	lang.LoadBitmapW(IDB_BITMAP2);
	yang.LoadBitmapW(IDB_BITMAP3);

	Sheep* Sarr[5];
	Wolf* Warr[2];

	Sarr[0]=new Sheep(w,0,0);
	Sarr[1]=new Sheep(w,1,3);
	Sarr[2]=new Sheep(w,2,2);
	Sarr[3]=new Sheep(w,3,1);
	Sarr[4]=new Sheep(w,4,3);

	w->setAt(0,0,Sarr[0]);
	w->setAt(1,3,Sarr[1]);
	w->setAt(2,2,Sarr[2]);
	w->setAt(3,1,Sarr[3]);
	w->setAt(4,3,Sarr[4]);

	Warr[0]=new Wolf(w,1,1);
	Warr[1]=new Wolf(w,3,3);

	w->setAt(1,1,Warr[0]);
	w->setAt(3,3,Warr[1]);



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CnewvisualDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CnewvisualDlg::OnPaint()
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

	/*初始狼羊显示*/
	CDC *pDC=GetDC();
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&yang);
	BITMAP bm;
	yang.GetBitmap(&bm);
	CRect rect;
	GetClientRect(&rect);

	int W=rect.Width(),H=rect.Height();
	int W1=bm.bmWidth,h=bm.bmHeight;
	
	int i,j;
	/*开始循环*/
	for(i=0;i<M;i++){
		for(j=0;j<M;j++){
			switch(w->gridType(j,i)){ //注意i和j是反的，不然结果反
			case 0:dc.SelectObject(&bai);break;
			case 1:dc.SelectObject(&yang);break;
			case 2:dc.SelectObject(&lang);break;
			}
			pDC->BitBlt(i*W1,j*h,W1,h,&dc,0,0,SRCCOPY);
		}
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CnewvisualDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CnewvisualDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	w->SimulateOneStep(); //一步模拟
	CDC *pDC=GetDC();
	CDC dc;
	dc.CreateCompatibleDC(pDC);
	dc.SelectObject(&yang);
	BITMAP bm;
	yang.GetBitmap(&bm);
	CRect rect;
	GetClientRect(&rect);

	int W=rect.Width(),H=rect.Height();
	int W1=bm.bmWidth,h=bm.bmHeight;
	
	int i,j;
	/*开始循环*/
	for(i=0;i<M;i++){
		for(j=0;j<M;j++){
			switch(w->gridType(j,i)){ //注意i和j是反的，不然结果反
			case 0:dc.SelectObject(&bai);break;
			case 1:dc.SelectObject(&yang);break;
			case 2:dc.SelectObject(&lang);break;
			}
			pDC->BitBlt(i*W1,j*h,W1,h,&dc,0,0,SRCCOPY);
		}
	}
}


void CnewvisualDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}


void CnewvisualDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	int i,j;
	CString str;
	M_edit1.GetWindowText(str);
	CFile file;
	file.Open(str,CFile::modeCreate|CFile::modeWrite|CFile::modeNoTruncate,NULL);
	for(i=0;i<M;i++){
		for(j=0;j<M;j++){
			switch(w->gridType(i,j)){
			case 0:file.Write("[ ]",strlen("[ ]"));break;
			case 1:file.Write("[O]",strlen("[O]"));break;
			case 2:file.Write("[X]",strlen("[X]"));break;
			}
		}
		file.Write("\n",strlen("\n")); 
	}
	file.Close();

}
