
// newvisualDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "newvisual.h"
#include "newvisualDlg.h"
#include "afxdialogex.h"
#include "WOLFNSHEEP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern World *w=new World;//�����ⲿ����

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CnewvisualDlg �Ի���




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


// CnewvisualDlg ��Ϣ�������

BOOL CnewvisualDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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



	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CnewvisualDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}

	/*��ʼ������ʾ*/
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
	/*��ʼѭ��*/
	for(i=0;i<M;i++){
		for(j=0;j<M;j++){
			switch(w->gridType(j,i)){ //ע��i��j�Ƿ��ģ���Ȼ�����
			case 0:dc.SelectObject(&bai);break;
			case 1:dc.SelectObject(&yang);break;
			case 2:dc.SelectObject(&lang);break;
			}
			pDC->BitBlt(i*W1,j*h,W1,h,&dc,0,0,SRCCOPY);
		}
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CnewvisualDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CnewvisualDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	w->SimulateOneStep(); //һ��ģ��
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
	/*��ʼѭ��*/
	for(i=0;i<M;i++){
		for(j=0;j<M;j++){
			switch(w->gridType(j,i)){ //ע��i��j�Ƿ��ģ���Ȼ�����
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}


void CnewvisualDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
