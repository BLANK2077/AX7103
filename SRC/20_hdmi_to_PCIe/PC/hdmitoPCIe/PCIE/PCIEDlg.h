
// PCIEDlg.h : ͷ�ļ�
//

#pragma once
int refresh_video(void *opaque);
UINT PCIe_video(LPVOID lparam);
// CPCIEDlg �Ի���
class CPCIEDlg : public CDialogEx
{
// ����
public:
	CPCIEDlg(CWnd* pParent = NULL);	// ��׼���캯��

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
	CWinThread *   m_PCIEThread; 
	BYTE *lpbuf;
	void SDL_video(void);
 CRect m_rect_PICURE_CONTROL;            //���������ʼ����λ��
int m_width_PICURE_CONTROL;             //��������Ŀ�
int m_height_PICURE_CONTROL;            //��������ĸ�
 unsigned char n_StExe;
 afx_msg void OnBnClickedBtnAbout();
 afx_msg void OnDestroy();
 afx_msg void OnClose();
};
