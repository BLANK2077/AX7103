
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
BYTE* bufinout = new BYTE[1024*1024*60];
BYTE* lpbuf = new BYTE[1024*1024*60];
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
//	afx_msg void OnEnChangeNetaddress1();
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
//	ON_EN_CHANGE(IDC_NETADDRESS1, &CAboutDlg::OnEnChangeNetaddress1)
ON_BN_CLICKED(IDC_MFCLINK1, &CAboutDlg::OnBnClickedMfclink1)
END_MESSAGE_MAP()


// CPCIEDlg �Ի���



CPCIEDlg::CPCIEDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPCIEDlg::IDD, pParent)
	, m_Path_Snd(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPCIEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PATH, m_Path_Snd);
}

BEGIN_MESSAGE_MAP(CPCIEDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_PCIE_SND, &CPCIEDlg::OnBnClickedButtonPcieSnd)
	ON_BN_CLICKED(IDC_BUTTON_BROWSE, &CPCIEDlg::OnBnClickedButtonBrowse)
	ON_BN_CLICKED(IDC_BTN_ABOUT, &CPCIEDlg::OnBnClickedBtnAbout)
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
	memset(bufinout, 0, sizeof(BYTE)*1024*1024*60);
	//memset(lpbuf, 0, sizeof(BYTE)*1024*1024*60);
	bi.biSizeImage=0x1000;
	hDev = NULL;
	flagOpen=0;
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
void CPCIEDlg::Pic_Show_Snd(void)
{
	CWnd *pWnd=GetDlgItem(IDC_PICTURE);//���pictrue�ؼ����ڵľ��
	CRect rect;
	pWnd->GetClientRect(&rect);//���pictrue�ؼ����ڵľ�������
	CDC *pDC=pWnd->GetDC();//���pictrue�ؼ���DC

	IStream *pStm=NULL;
	CFileStatus fstatus;
	CFile file;
	LONG cb;

	IPicture *pPic;//������ʾͼƬ�Ľӿڣ�����ʾjpg��ʽͼƬ��
	CString m_sPath=m_Path_Snd;//������Ҫ��ʾ��ͼƬ
	//��ͼ���ļ�����ȡ�ļ��ֽ���
	if(file.Open(m_sPath,CFile::modeRead) && file.GetStatus(m_sPath,fstatus) 
		&& ((cb=fstatus.m_size)!=-1))
	{
	 //����ȫ�ִ洢�ռ�
     HGLOBAL hGlobal=GlobalAlloc(GMEM_MOVEABLE,cb);
	 LPVOID pvData=NULL;
	 if(hGlobal!=NULL)
	 {
	  //���������ڴ��
      if((pvData=GlobalLock(hGlobal))!=NULL)
	  {
	   //�����ļ����ڴ滺����
       file.Read(pvData,cb);
	   GlobalUnlock(hGlobal);
	   CreateStreamOnHGlobal(hGlobal,true,&pStm);
	  }
	 }
	 UpdateData(FALSE);
	}

	//װ��ͼ���ļ�
	if(SUCCEEDED(OleLoadPicture(pStm,fstatus.m_size,TRUE,IID_IPicture,(LPVOID*)&pPic)))
	{
     OLE_XSIZE_HIMETRIC hmWidth;
     OLE_XSIZE_HIMETRIC hmHeight;
	 pPic->get_Width(&hmWidth);//���ͼ����ʵ���
	 pPic->get_Height(&hmHeight);//���ͼ����ʵ�߶�
	 //�ڿؼ�����ʾͼƬ	
	 pPic->Render(*pDC,0,0,rect.Width(),rect.Height(),0,hmHeight,hmWidth,-hmHeight,NULL);
     pPic->Release();
	}
}
void CPCIEDlg::Pic_Show_Rev(void)
{
	CWnd *pWnd=GetDlgItem(IDC_PICTURE_REV);//���pictrue�ؼ����ڵľ��
	CRect rect;
	pWnd->GetClientRect(&rect);//���pictrue�ؼ����ڵľ�������
	CDC *pDC=pWnd->GetDC();//���pictrue�ؼ���DC

	IStream *pStm=NULL;
	CFileStatus fstatus;
	CFile file;
	LONG cb;

	IPicture *pPic;//������ʾͼƬ�Ľӿڣ�����ʾjpg��ʽͼƬ��
	CString m_sPath=m_Path_Rev;//������Ҫ��ʾ��ͼƬ
	//��ͼ���ļ�����ȡ�ļ��ֽ���
	if(file.Open(m_sPath,CFile::modeRead) && file.GetStatus(m_sPath,fstatus) 
		&& ((cb=fstatus.m_size)!=-1))
	{
	 //����ȫ�ִ洢�ռ�
     HGLOBAL hGlobal=GlobalAlloc(GMEM_MOVEABLE,cb);
	 LPVOID pvData=NULL;
	 if(hGlobal!=NULL)
	 {
	  //���������ڴ��
      if((pvData=GlobalLock(hGlobal))!=NULL)
	  {
	   //�����ļ����ڴ滺����
       file.Read(pvData,cb);
	   GlobalUnlock(hGlobal);
	   CreateStreamOnHGlobal(hGlobal,true,&pStm);
	  }
	 }
	}

	//װ��ͼ���ļ�
	if(SUCCEEDED(OleLoadPicture(pStm,fstatus.m_size,TRUE,IID_IPicture,(LPVOID*)&pPic)))
	{
     OLE_XSIZE_HIMETRIC hmWidth;
     OLE_XSIZE_HIMETRIC hmHeight;
	 pPic->get_Width(&hmWidth);//���ͼ����ʵ���
	 pPic->get_Height(&hmHeight);//���ͼ����ʵ�߶�
	 //�ڿؼ�����ʾͼƬ	
	 pPic->Render(*pDC,0,0,rect.Width(),rect.Height(),0,hmHeight,hmWidth,-hmHeight,NULL);
     pPic->Release();
	}
}
// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPCIEDlg::OnPaint()
{
	Pic_Show_Snd();
	Pic_Show_Rev();
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
  
 
void CPCIEDlg::OnBnClickedButtonBrowse()
{
// TODO: �ڴ���ӿؼ�֪ͨ����������
CFileDialog dlg( TRUE, "", NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, "bmp�ļ�(*.bmp)|*.bmp|�����ļ�(*.*)|*.*||" );
dlg.m_ofn.lpstrTitle = "���ļ�";

CFile file;
//���ļ��Ի���
if(dlg.DoModal()==IDOK)
{
m_Path_Snd=dlg.GetPathName();

if(file.Open(m_Path_Snd,CFile::modeRead|CFile::shareDenyNone,NULL)==0)
{
//��ȡ�ļ�ʧ��
AfxMessageBox("��ȡ�ļ�ʧ��");
return;
}
//��ȡ�ļ�ͷ
file.Read(&bf,sizeof(bf));
//�ж��Ƿ���BMP �ļ�
if(bf.bfType!=0x4d42)//'BM'
{
AfxMessageBox("��BMP �ļ���");
return;
}
//�ж��ļ��Ƿ���
if(file.GetLength()!=bf.bfSize)
{
AfxMessageBox("�ļ�����");
return;
}
//���ļ���Ϣͷ
file.Read(&bi,sizeof(bi));
//�����ɫ����Ŀ
numquad=0;
if(bi.biBitCount<24)
{
numquad=1<<bi.biBitCount;
}
//Ϊͼ����Ϣpbi ����ռ�
pbi=(BITMAPINFO*)HeapAlloc(GetProcessHeap(),0,sizeof(BITMAPINFOHEADER)+numquad*sizeof(RGBQUAD));
memcpy(pbi,&bi,sizeof(bi));
quad=(RGBQUAD*)((BYTE*)pbi+sizeof(BITMAPINFOHEADER));
//��ȡ��ɫ��
if(numquad!=0)
{
file.Read(quad,sizeof(RGBQUAD)*numquad);
}
//Ϊͼ����������ռ�
bi.biSizeImage=bf.bfSize-bf.bfOffBits;
lpbuf=(BYTE*)HeapAlloc(GetProcessHeap(),0,bi.biSizeImage);
//��ȡͼ������
file.Read(lpbuf,bi.biSizeImage);
//ͼ���ȡ��ϣ��ر��ļ������ñ�־
DWORD i;
//for(i=1000;i<7500000;i++)
//lpbuf[i]=0x00;
memset(bufinout, 0, sizeof(BYTE)*1024*1024*60);
file.Close();
flagOpen=1;
}
Pic_Show_Snd();
}

void CPCIEDlg::OnBnClickedButtonPcieSnd()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	if(!flagOpen)
	{
		AfxMessageBox("��ѡ��bmpͼƬ");
	}
	else{
	pcie_inital();
	writetofpga (hDev,lpbuf,0x00,bi.biSizeImage);

	writetoPC(hDev,lpbuf,0x00,bi.biSizeImage);
    PCIEClose(hDev);
	int nPt = m_Path_Snd.ReverseFind('.');
	CString file_L = m_Path_Snd.Left(nPt);
	CString file_R = m_Path_Snd.Right( m_Path_Snd.GetLength() - nPt);
	file_L += _T("-pcie.bmp");
m_Path_Rev=file_L;
CFile file;
CFileException fe;

if (!file.Open(m_Path_Rev, CFile::modeCreate | CFile::modeReadWrite |
CFile::shareExclusive, &fe))
{
// ʧ��
	AfxMessageBox("����ʧ��");
return;
}

file.SeekToBegin();
file.Write(&bf,sizeof(bf));
file.Write(&bi,sizeof(bi));
if(numquad!=0)
{
file.Write(quad,sizeof(RGBQUAD)*numquad);
}
file.Write(lpbuf,bi.biSizeImage);
file.Close();
Pic_Show_Rev();
	flagOpen=0;
}
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
