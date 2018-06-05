
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
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedMfclink1();
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
ON_BN_CLICKED(IDC_MFCLINK1, &CAboutDlg::OnBnClickedMfclink1)
END_MESSAGE_MAP()


// CPCIEDlg �Ի���



CPCIEDlg::CPCIEDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPCIEDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPCIEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPCIEDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_ABOUT, &CPCIEDlg::OnBnClickedBtnAbout)
	ON_WM_DESTROY()
	ON_WM_CLOSE()
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)//�˴�Ϊ��Ӳ���
	ON_WM_SIZE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CPCIEDlg ��Ϣ�������

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


	 //---------------------------������ʾ---------------------------------//
    m_nid.cbSize  = (DWORD)sizeof(NOTIFYICONDATA);
    m_nid.hWnd    = this->m_hWnd;

    m_nid.uID     = IDR_MAINFRAME;
    m_nid.uFlags  = NIF_ICON | NIF_MESSAGE | NIF_TIP ;
    m_nid.uCallbackMessage = WM_SHOWTASK;             // �Զ������Ϣ����
    m_nid.hIcon   = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
    strcpy_s(m_nid.szTip, "Pcie to hdmi");                
    Shell_NotifyIcon(NIM_ADD, &m_nid);                // �����������ͼ��
		lpbuf=(BYTE*)HeapAlloc(GetProcessHeap(),0,8294454);
		//pcie_inital();
		n_StExe=0;
		m_PCIEThread =::AfxBeginThread(PCIe_GetScreen,this, THREAD_PRIORITY_NORMAL);
	   return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

LRESULT CPCIEDlg::OnShowTask(WPARAM wParam, LPARAM lParam)
{
     if(wParam != IDR_MAINFRAME) return 1;
 
     switch(lParam)
     {
     case WM_RBUTTONUP:               //�Ҽ�����ʱ�����˵�
         {
              LPPOINT lpoint = new tagPOINT;
              ::GetCursorPos(lpoint);                    // �õ����λ��
              CMenu menu;
              menu.CreatePopupMenu();                    // ����һ������ʽ�˵�
              menu.AppendMenu(MF_STRING, WM_DESTROY, "�˳�");//Appends a new item to the end ofthis menu         
              menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x ,lpoint->y,this);
              HMENU hmenu = menu.Detach();
              menu.DestroyMenu();
              delete lpoint;
              break;
         }
     case WM_LBUTTONDBLCLK:                            // ˫������Ĵ���
         this->ShowWindow(SW_SHOWNORMAL);         // ��ʾ������ 
         break;
     }
 
     return 0;
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
void CAboutDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CPCIEDlg::OnBnClickedBtnAbout()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAboutDlg dlg;
	 dlg.DoModal();

}




void CAboutDlg::OnBnClickedMfclink1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CPCIEDlg::OnDestroy()
{
	 n_StExe=1;	
	 m_nid.cbSize  = (DWORD)sizeof(NOTIFYICONDATA);
    m_nid.hWnd    = this->m_hWnd;
    m_nid.uID     = IDR_MAINFRAME;
    m_nid.uFlags  = NIF_ICON | NIF_MESSAGE | NIF_TIP ;
    m_nid.uCallbackMessage = WM_SHOWTASK;             // �Զ������Ϣ����
    m_nid.hIcon   = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
   // strcpy(m_nid.szTip, " PCIE");                // 
    Shell_NotifyIcon(NIM_DELETE,&m_nid); //��������ɾ��ͼ��, &m_nid);                // �����������ͼ��
	Sleep(1000);
	CDialogEx::OnDestroy();

}

void CPCIEDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	n_StExe=1;
	CDialogEx::OnClose();
}


void CPCIEDlg::SC_Aqure(void)
{
	HCURSOR hCursor;
	POINT ptCursor;
	int xHotspot, yHotspot;
	 
int width=GetSystemMetrics(SM_CXSCREEN);
 int height=GetSystemMetrics(SM_CYSCREEN);
CDC *pdeskdc = GetDesktopWindow()->GetDC();    
CRect re;  
//��ȡ���ڵĴ�С  
GetDesktopWindow()->GetClientRect(&re);  
CBitmap bmp;  
bmp.CreateCompatibleBitmap(pdeskdc , re.Width() , re.Height());  
//����һ�����ݵ��ڴ滭�� 
CDC memorydc;  
memorydc.CreateCompatibleDC(pdeskdc);
while(1)
	{
CBitmap *pold = memorydc.SelectObject(&bmp);  
//����ͼ��  
memorydc.BitBlt(0,0,re.Width() ,re.Height(), pdeskdc , 0,0,SRCCOPY | CAPTUREBLT) ;

 CURSORINFO CursorInfo;
	CursorInfo.cbSize = sizeof(CursorInfo);
	if (! ::GetCursorInfo(& CursorInfo))
	{
		//AfxMessageBox("error1");
		;
	}
	hCursor = CursorInfo.hCursor;
	ptCursor = CursorInfo.ptScreenPos;

	// ��ȡ����ͼ������
	ICONINFO IconInfo;
	if (! ::GetIconInfo(hCursor, & IconInfo))
		if (! ::GetCursorInfo(& CursorInfo))
	{
		//AfxMessageBox("error2");
		;
	}
	xHotspot = (LONG)IconInfo.xHotspot;
	yHotspot = (LONG)IconInfo.yHotspot;

	if (IconInfo.hbmMask)
		::DeleteObject(IconInfo.hbmMask);
	if (IconInfo.hbmColor)
		::DeleteObject(IconInfo.hbmColor);

		DEVMODEA mode;
	memset(& mode, 0, sizeof(mode));
	mode.dmSize = sizeof(mode);
	m_Settings.nLeft   = mode.dmPosition.x;
	m_Settings.nTop    = mode.dmPosition.y;
	m_Settings.nWidth  = mode.dmPelsWidth;
	m_Settings.nHeight = mode.dmPelsHeight;
	m_Settings.nBitsPerPel = mode.dmBitsPerPel;
	int xLeft = ptCursor.x - xHotspot - m_Settings.nLeft;
		int yTop  = ptCursor.y - yHotspot - m_Settings.nTop;
	::DrawIconEx(memorydc, xLeft, yTop, hCursor, 0, 0, 0, NULL, DI_NORMAL | DI_COMPAT);
    memorydc.SelectObject(pold);  

	 BITMAP bit;  
    bmp.GetBitmap(&bit);  
  
    //���� ͼ���С����λ��byte��  
    DWORD size = bit.bmWidthBytes * bit.bmHeight ; 
	::GetBitmapBits(bmp, size,lpbuf); 
	WriteFrame1080ptofpga(hDev,lpbuf,66355200);
	 if(n_StExe==1)
		{
		  break;
		}
}//while

}

UINT PCIe_GetScreen(LPVOID lparam)
{   
	CString strStatus; 
	CPCIEDlg* PCIE_Test = (CPCIEDlg*)lparam;
	if (PCIE_Test == NULL)
	{
		return 0;
	}
	    pcie_inital();
	while(1)

	 {

		  if(PCIE_Test->n_StExe==1)
		   {
			   //
			   PCIEClose(hDev);
			   HeapFree(GetProcessHeap(), 0, PCIE_Test->lpbuf);
			 break;
		   } 
		   PCIE_Test->SC_Aqure();
		
	 }
	return 0;
}


void CPCIEDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: �ڴ˴������Ϣ����������
	  if (nType == SIZE_MINIMIZED)
     {
         ShowWindow(SW_HIDE);//������С������������ͼ��
     }
}
