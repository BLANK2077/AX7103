
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
#include "SDL.h"
#pragma comment(lib,"d3d9.lib")
//#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"d3dx9.lib")
#pragma comment(lib ,"SDL2.lib")  

#define HAS_BORDER	 0



const int screen_w=1920,screen_h=1080;
const int pixel_w=1920,pixel_h=1080;

//Refresh Event
#define REFRESH_EVENT  (SDL_USEREVENT + 1)

int thread_exit=0;

int refresh_video(void *opaque){
	while (thread_exit==0) {
		SDL_Event event;
		event.type = REFRESH_EVENT;
		SDL_PushEvent(&event);
	}
	return 0;
}
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

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
		lpbuf=(BYTE*)HeapAlloc(GetProcessHeap(),0,8294454);
		//pcie_inital();
		n_StExe=0;
		m_PCIEThread =::AfxBeginThread(PCIe_video,this, THREAD_PRIORITY_NORMAL);
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
		
		 Sleep(1000);
		
		  
	CDialogEx::OnDestroy();

}
void CPCIEDlg::SDL_video()
{

     //�õ���ʾ����С
   int   cx,cy;
   cx   =   GetSystemMetrics(SM_CXSCREEN);
   cy   =   GetSystemMetrics(SM_CYSCREEN);
    CRect   rcTemp;
    rcTemp.BottomRight()   =   CPoint(cx,   cy);
    rcTemp.TopLeft()   =   CPoint(0,   0);
    MoveWindow(&rcTemp);
GetDlgItem(IDC_PICTURE_REV)->MoveWindow(m_rect_PICURE_CONTROL.left ,m_rect_PICURE_CONTROL.top,
				cx,cy );
  GetDlgItem(IDC_PICTURE_REV)->GetWindowRect(&m_rect_PICURE_CONTROL);//��ȡ�ؼ��������Ļ��λ��
ScreenToClient(m_rect_PICURE_CONTROL);//ת��Ϊ�Ի����ϵ����λ��
m_width_PICURE_CONTROL = m_rect_PICURE_CONTROL.right - m_rect_PICURE_CONTROL.left;  //widthΪbutton�Ŀ�
m_height_PICURE_CONTROL = m_rect_PICURE_CONTROL.bottom - m_rect_PICURE_CONTROL.top; //heightΪbutton�ĸ�



if(SDL_Init(SDL_INIT_VIDEO)) {  
		AfxMessageBox( "Could not initialize SDL - %s\n"); 
		return ;
	} 

	SDL_Window *screen; 
	screen = SDL_CreateWindowFrom( (void *)( GetDlgItem(IDC_PICTURE_REV)->GetSafeHwnd() ) );
	if(!screen) {  
		printf("SDL: could not create window - exiting:%s\n",SDL_GetError());  
		return ;
	}
	SDL_Renderer* sdlRenderer = SDL_CreateRenderer(screen, -1, SDL_RENDERER_ACCELERATED);
	Uint32 pixformat=0;
	pixformat= SDL_PIXELFORMAT_ARGB8888;  
SDL_Texture* sdlTexture = SDL_CreateTexture(sdlRenderer,pixformat, SDL_TEXTUREACCESS_STREAMING,pixel_w,pixel_h);


	int border=0;
#if HAS_BORDER
		border=30;
#endif
	SDL_Rect sdlRect;  
	sdlRect.x = 0+border;  
	sdlRect.y = 0+border;  
	sdlRect.w = screen_w-border*2;  
	sdlRect.h = screen_h-border*2;  
	
	SDL_Thread *refresh_thread = SDL_CreateThread(refresh_video,NULL,NULL);
	SDL_Event event;
	DWORD addrspace;
	
DWORD n_msta=0xff;
addrspace=UserIntInit(hDev);
while(1)
	{
    if(0x01==ReadUserInt_reg(hDev,addrspace))
	{
		//writetoPC(hDev,lpbuf,0,8294400);//lpbuf���ͽ��տ�//��ַ��2073600);
		ReadFrame1080ptoPC(hDev,lpbuf,0);
	}
	else if (0x02==ReadUserInt_reg(hDev,addrspace))
	{
		//writetoPC(hDev,lpbuf,16588800,8294400);//lpbuf���ͽ��տ�//��ַ��2073600);
		ReadFrame1080ptoPC(hDev,lpbuf,16588800);//lpbuf���ͽ��տ�//��ַ��2073600);
	}
	else if (0x03==ReadUserInt_reg(hDev,addrspace))
	{
		//writetoPC(hDev,lpbuf,33177600,8294400);//lpbuf���ͽ��տ�//��ַ��2073600);
		ReadFrame1080ptoPC(hDev,lpbuf,33177600);//lpbuf���ͽ��տ�//��ַ��2073600);

	}
	else if (0x00==ReadUserInt_reg(hDev,addrspace))
	{
		//writetoPC(hDev,lpbuf,49766400,8294400);//lpbuf���ͽ��տ�//��ַ��2073600);
		ReadFrame1080ptoPC(hDev,lpbuf,49766400);
	}
	
	 if(n_StExe==1)
		{
		

		
			break;

		}
	
SDL_WaitEvent(&event);
if(event.type==REFRESH_EVENT){
			
			SDL_UpdateTexture( sdlTexture, NULL, lpbuf, pixel_w*4); 
			SDL_RenderClear( sdlRenderer );   
			SDL_RenderCopy( sdlRenderer, sdlTexture, NULL, &sdlRect);  
			SDL_RenderPresent( sdlRenderer );
			
		}
}//while

}


void CPCIEDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	n_StExe=1;
	CDialogEx::OnClose();
}




UINT PCIe_video(LPVOID lparam)
{   
	CString strStatus; 
	CPCIEDlg* PCIE_Test = (CPCIEDlg*)lparam;
    pcie_inital();
	if (PCIE_Test == NULL)
	{
		return 0;
	}
	while(1)

	 {

		  if(PCIE_Test->n_StExe==1)
		   {
			   //
			   PCIEClose(hDev);
			   HeapFree(GetProcessHeap(), 0, PCIE_Test->lpbuf);
			 break;
		   } 
		//  PCIE_Test->Get_Screen();
		  PCIE_Test->SDL_video();
		// cnt_Pic++;
	 }
	return 0;
}
