
// PCIEDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PCIE.h"
#include "PCIEDlg.h"
#include "afxdialogex.h"
#include "PCIEDLL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
/******************************************************/
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


// CPCIEDlg �Ի���



CPCIEDlg::CPCIEDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPCIEDlg::IDD, pParent)

	, m_DataSnd(_T(""))
	, m_DataRcv(_T(""))
	, m_DataBir(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPCIEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SND, m_DataSnd);
	DDX_Text(pDX, IDC_EDIT_RCV, m_DataRcv);
	DDX_Text(pDX, IDC_EDIT_BIDIR, m_DataBir);
	DDX_Control(pDX, IDC_EDIT_SND, m_EditCtl_Snd);
	DDX_Control(pDX, IDC_EDIT_RCV, m_EditCtl_Rcv);
	DDX_Control(pDX, IDC_EDIT_BIDIR, m_EditCtl_Bir);
}

BEGIN_MESSAGE_MAP(CPCIEDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_PCTOFPGA, &CPCIEDlg::OnBnClickedPctofpga)
	ON_BN_CLICKED(IDC_FPGATOPC, &CPCIEDlg::OnBnClickedFpgatopc)
	ON_BN_CLICKED(IDC_BIDIR, &CPCIEDlg::OnBnClickedBidir)
	ON_BN_CLICKED(IDC_BTN_ABOUT, &CPCIEDlg::OnBnClickedBtnAbout)
	ON_BN_CLICKED(IDC_BTN_STOP, &CPCIEDlg::OnBnClickedBtnStop)
END_MESSAGE_MAP()


// CPCIEDlg ��Ϣ�������
CRITICAL_SECTION cs;
BOOL CPCIEDlg::OnInitDialog()
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
	m_InitPCIE=0x04;
	m_StatusSel = 0x00;
	hDev = NULL;

	m_nBtnStatus = -1;

	UpdateData(FALSE);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPCIEDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CPCIEDlg::OnPaint()
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
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPCIEDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
  
 


void CPCIEDlg::OnBnClickedPctofpga()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DWORD dwStatus;
	CString strStatus;
	UINT32 i;

	GetDlgItem(IDC_PCTOFPGA)->EnableWindow(FALSE);//
	GetDlgItem(IDC_FPGATOPC)->EnableWindow(TRUE);
	GetDlgItem(IDC_BIDIR)->EnableWindow(TRUE);
   // pcie_inital();
	m_StatusSel = 0x01; //���ͣ�����



	m_PCIEThread =::AfxBeginThread(PCIe_SpeedThread,this, THREAD_PRIORITY_NORMAL);	//

}


void CPCIEDlg::OnBnClickedFpgatopc()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DWORD dwStatus;
	CString strStatus;
	UINT32 i;
	

	GetDlgItem(IDC_PCTOFPGA)->EnableWindow(TRUE);//
	GetDlgItem(IDC_FPGATOPC)->EnableWindow(FALSE);
	GetDlgItem(IDC_BIDIR)->EnableWindow(TRUE);
 
	m_StatusSel = 0x02; //���ͣ�����

	//this->PostMessage(m_PCIEThread->m_nThreadID,WM_SEND_MSG,1);
m_PCIEThread =::AfxBeginThread(PCIe_SpeedThread,this, THREAD_PRIORITY_NORMAL);	//
	

}


void CPCIEDlg::OnBnClickedBidir()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	DWORD dwStatus;
	//CString strStatus;
	UINT32 i;

	GetDlgItem(IDC_PCTOFPGA)->EnableWindow(TRUE);//
	GetDlgItem(IDC_FPGATOPC)->EnableWindow(TRUE);
	GetDlgItem(IDC_BIDIR)->EnableWindow(FALSE);
	

	m_StatusSel = 0x03; //���ͣ�����



m_PCIEThread =::AfxBeginThread(PCIe_SpeedThread,this, THREAD_PRIORITY_NORMAL);	//
}


//void CPCIEDlg::OnStnClickedPicture()
//{
//	// TODO: �ڴ���ӿؼ�֪ͨ����������
//}


void CPCIEDlg::OnBnClickedBtnAbout()
{
// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAboutDlg dlg;
	 dlg.DoModal();

}


void CPCIEDlg::OnBnClickedBtnStop()
{

	m_StatusSel = 0x00;
	 Sleep(1000);
	GetDlgItem(IDC_PCTOFPGA)->EnableWindow(TRUE);//
 	GetDlgItem(IDC_FPGATOPC)->EnableWindow(TRUE);
	GetDlgItem(IDC_BIDIR)->EnableWindow(TRUE);
	 
	GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);

}

UINT PCIe_SpeedThread(LPVOID lparam)
{
	CPCIEDlg* PCIE_Test = (CPCIEDlg*)lparam;
	UINT32 Tim;
	CString strStatus;

	pcie_inital();





	if (PCIE_Test == NULL)
	{
	PCIE_Test->GetDlgItem(IDC_PCTOFPGA)->EnableWindow(TRUE);//
 	PCIE_Test->GetDlgItem(IDC_FPGATOPC)->EnableWindow(TRUE);
	PCIE_Test->GetDlgItem(IDC_BIDIR)->EnableWindow(TRUE);
		
		return 0;
	}
	for(Tim=0;Tim<10000;Tim++)
	{
    if(0x00==PCIE_Test->m_StatusSel)
	{
		 PCIEClose( hDev);
		 PCIE_Test->m_InitPCIE=0x0;
	break;
	}
 
	else if((0x01==PCIE_Test->m_StatusSel))
	{

	PCIE_Test->m_InitPCIE=0x1;
	PCIE_Test->GetDlgItem(IDC_PCTOFPGA)->EnableWindow(FALSE);//
 	PCIE_Test->GetDlgItem(IDC_FPGATOPC)->EnableWindow(FALSE);
	PCIE_Test->GetDlgItem(IDC_BIDIR)->EnableWindow(FALSE);
    PCIEspeed_DmaPerformance(hDev, 1, Len_PCIE_Single, TRUE, 0x00,1);//toFPGA 100M
	strStatus.Format("%8.2f",sP_buf[0]);
	PCIE_Test->m_DataSnd=strStatus;
	PCIE_Test->m_EditCtl_Snd.SetSel(-1,-1);
    PCIE_Test->m_EditCtl_Snd.ReplaceSel(PCIE_Test->m_DataSnd+"\r\n"); 

	}
	 else if(0x02==PCIE_Test->m_StatusSel)
	{
	PCIE_Test->m_InitPCIE=0x1;
	PCIE_Test->GetDlgItem(IDC_PCTOFPGA)->EnableWindow(FALSE);//
 	PCIE_Test->GetDlgItem(IDC_FPGATOPC)->EnableWindow(FALSE);
	PCIE_Test->GetDlgItem(IDC_BIDIR)->EnableWindow(FALSE);
    PCIEspeed_DmaPerformance(hDev, 2, Len_PCIE_Single, TRUE, 0x00,1);//toPC
 	strStatus.Format("%8.2f",sP_buf[1]);
	PCIE_Test->m_DataRcv=strStatus;
	PCIE_Test->m_EditCtl_Rcv.SetSel(-1,-1);
    PCIE_Test->m_EditCtl_Rcv.ReplaceSel(PCIE_Test->m_DataRcv+"\r\n");
	}
	else if(0x03==PCIE_Test->m_StatusSel)
	{
	PCIE_Test->m_InitPCIE=0x1;
	PCIE_Test->GetDlgItem(IDC_PCTOFPGA)->EnableWindow(FALSE);//
 	PCIE_Test->GetDlgItem(IDC_FPGATOPC)->EnableWindow(FALSE);
	PCIE_Test->GetDlgItem(IDC_BIDIR)->EnableWindow(FALSE);
	PCIEspeed_DmaPerformance(hDev, 3,Len_PCIE_Single, TRUE,0x00,1);//BIDIR;
    strStatus.Format("%8.2f,    %8.2f",sP_buf[0],sP_buf[1]);
	PCIE_Test->m_DataBir=strStatus;
	PCIE_Test->m_EditCtl_Bir.SetSel(-1,-1);
    PCIE_Test->m_EditCtl_Bir.ReplaceSel(PCIE_Test->m_DataBir+"\r\n"); 
	PCIEspeed_DmaPerformance(hDev, 3,Len_PCIE_Single, TRUE,0x00,1);//BIDIR;
	}
	}
/*	if(0x00==PCIE_Test->m_StatusSel)
	{
	
     PCIEClose( hDev);
	}*/
	return 1;
}