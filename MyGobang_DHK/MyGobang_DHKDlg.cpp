
// MyGobang_DHKDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MyGobang_DHK.h"
#include "MyGobang_DHKDlg.h"
#include "afxdialogex.h"
#include "MainGobang.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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

public:
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CMyGobang_DHKDlg �Ի���




CMyGobang_DHKDlg::CMyGobang_DHKDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyGobang_DHKDlg::IDD, pParent)
{
	/*m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);*/
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CMyGobang_DHKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MainTable, picMain);
}

BEGIN_MESSAGE_MAP(CMyGobang_DHKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_Start, &CMyGobang_DHKDlg::OnBnClickedButtonStart)
	ON_WM_LBUTTONDOWN()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_Machine, &CMyGobang_DHKDlg::OnBnClickedButtonMachine)
	ON_WM_MOUSEMOVE()
	ON_BN_CLICKED(IDC_BUTTON_Withdraw, &CMyGobang_DHKDlg::OnBnClickedButtonWithdraw)
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()


// CMyGobang_DHKDlg ��Ϣ�������

BOOL CMyGobang_DHKDlg::OnInitDialog()
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
	((CButton *)GetDlgItem(IDC_RADIO_Normol))->SetCheck(true);//Ĭ��ѡ�б�׼����
	bIsReady=false;
	bIsMachine=false;
	bDrawPieces=false;
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CMyGobang_DHKDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMyGobang_DHKDlg::OnPaint()
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
	//��������
	CDC *pDC;
	pDC=picMain.GetDC();//��ȡ�ÿؼ��Ļ���
	if(bIsReady&&!bDrawPieces)
	{
		CRect rect;
		picMain.GetClientRect(&rect);//��ȡ�ؼ���С
		if (((CButton *)GetDlgItem(IDC_RADIO_Normol))->GetCheck())
		{
			gobang.DrawMainTable(pDC,&rect,15);//��׼����
		}
		if (((CButton *)GetDlgItem(IDC_RADIO_Middle))->GetCheck())
		{
			gobang.DrawMainTable(pDC,&rect,17);//17*17����
		}
		if (((CButton *)GetDlgItem(IDC_RADIO_Large))->GetCheck())
		{
			gobang.DrawMainTable(pDC,&rect,19);//19*19����
		}
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMyGobang_DHKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//��ʼ��ť
void CMyGobang_DHKDlg::OnBnClickedButtonStart()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	bIsReady=true;
	bIsMachine=false;
	bWithdraw=true;
	OnPaint();//����������ɺ� �ٻ�������
	gobang.SetPieces();
	SetTimer(1, 40, NULL);
	MessageBox(_T("��������"));
}

//����ƶ�����
void CMyGobang_DHKDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CPoint pt;
	CRect rect;
	GetDlgItem(IDC_MainTable)->GetWindowRect(&rect);//��ȡ�ؼ���Ļ����
	GetCursorPos(&pt);//��ȡ���������(��Ļ��������)
	pt.x-=rect.left;//ת��Ϊ�ؼ�������
	pt.y-=rect.top;
	CDC *pDC=picMain.GetDC();//��ȡ�ÿؼ��Ļ���
	if(bIsReady)
	{
		gobang.DrawRectangle(pDC,pt);
	}
	
	CDialogEx::OnMouseMove(nFlags, point);
}

//���������
void CMyGobang_DHKDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	if(!bIsReady)
	{
		MessageBox(_T("���ȵ����ʼ��"));
	}
	if(bIsReady)
	{
		CRect rect;
	    GetDlgItem(IDC_MainTable)->GetWindowRect(&rect);//��ȡ�ؼ���Ļ����
		CPoint pt;
		GetCursorPos(&pt);//��ȡ���������(��Ļ��������)
		CDC *pDC=picMain.GetDC();//��ȡ�ÿؼ��Ļ���
		gobang.DrawPieces(pDC,rect,pt);//��������
		//SetTimer(1,40,NULL);
		if(bIsMachine)
		{
			gobang.MachineDraw(pDC);//��������
		}
		if(gobang.Success())//ִ��ʤ���жϺ���
		{
			KillTimer(1);
			gobang.ReplayMark(pDC);
			bIsReady=false;
		}
	}
	CDialogEx::OnLButtonDown(nFlags, point);
}

//�˻��Կ�
void CMyGobang_DHKDlg::OnBnClickedButtonMachine()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(_T("��ع������ڲ�����"));
	//bIsReady=true;
	//bIsMachine=true;
	//bWithdraw=true;
	//OnPaint();//����������ɺ� �ٻ�������
	//gobang.SetPieces();
}

//ˢ�¼�ʱ��
void CMyGobang_DHKDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDC *pDC=picMain.GetDC();//��ȡ�ÿؼ��Ļ���
	CRect rect;
	GetDlgItem(IDC_MainTable)->GetWindowRect(&rect);//��ȡ�ؼ���Ļ����
	switch(nIDEvent)
	{
	case 1:
		gobang.KeepPieces(pDC,rect,15);
		break;
	}
	CDialogEx::OnTimer(nIDEvent);
}



//���尴ť
void CMyGobang_DHKDlg::OnBnClickedButtonWithdraw()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	bool bBlack;
	if(bWithdraw)
	{
		CDC *pDC=picMain.GetDC();//��ȡ�ÿؼ��Ļ���
	    if(gobang.ClearPieces(pDC,bBlack))//������һ������
		{
			bWithdraw=false;//ֻ�����һ����
		}
		else
		{
			MessageBox(_T("����û�����壡"));
		}
	}
	else if(bIsReady)
	{
		MessageBox(_T("��ֻ�ܻ�һ���壡"));
	}
}

//�ı������״
BOOL CMyGobang_DHKDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CPoint pos;
	GetCursorPos(&pos);  //��ȡ��ǰ���λ��

	CRect rc;
	GetDlgItem(IDC_MainTable)->GetWindowRect(&rc); 
	if (rc.PtInRect(pos)) //�������������Χ֮��
	{
		SetCursor(LoadCursor(NULL,IDC_HAND)); //���ó���״
		return TRUE; 
	}
	GetDlgItem(IDC_BUTTON_Withdraw)->GetWindowRect(&rc); 
	if((rc.PtInRect(pos))&&((!bWithdraw)||(!bIsReady)))
	{
		SetCursor(LoadCursor(NULL,IDC_NO));
		return TRUE; 
	}
	return CDialogEx::OnSetCursor(pWnd, nHitTest, message);
}
