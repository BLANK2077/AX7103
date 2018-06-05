
// PCIEDlg.h : ͷ�ļ�
//

#pragma once
UINT PCIe_GetScreen(LPVOID lparam);
struct tagScreenSettings
{
	int nLeft;        // ������չ ��ƫ��
	int nTop;         // ������չ ��ƫ��
	int nWidth;       // ��Ļ�ֱ��� ���
	int nHeight;      // ��Ļ�ֱ��� �߶�
	int nBitsPerPel;  // ��ɫ����
};
// CPCIEDlg �Ի���
#define WM_SHOWTASK WM_USER+1
class CPCIEDlg : public CDialogEx
{
// ����
public:
	CPCIEDlg(CWnd* pParent = NULL);	// ��׼���캯��
	NOTIFYICONDATA m_nid;
// �Ի�������
	enum { IDD = IDD_PCIE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	tagScreenSettings m_Settings;  // ��Ļ����
	CWinThread *   m_PCIEThread; 
	BYTE *lpbuf;
 unsigned char n_StExe;
 void SC_Aqure(void);
 afx_msg void OnBnClickedBtnAbout();
 afx_msg void OnDestroy();
 afx_msg void OnClose();
 afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam);
 afx_msg void OnSize(UINT nType, int cx, int cy);
};
