
// PCIEDlg.h : ͷ�ļ�
//

#pragma once

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
	CString m_Path_Snd;
	CString m_Path_Rev;;
	void Pic_Show_Snd(void);
	void Pic_Show_Rev(void);
	int numquad; //��ɫ����
 int flagOpen; //��־�Ƿ��bmp
 BITMAPINFO* pbi; //��¼ͼ��ϸ��
 BYTE* lpbuf; //ͼ������
 
 RGBQUAD* quad; //��ɫ��
 BITMAPFILEHEADER bf;//�ļ�ͷ
 BITMAPINFOHEADER bi; //��Ϣͷ
 CBitmap m_bmp;
 afx_msg void OnBnClickedButtonPcieSnd();
 afx_msg void OnBnClickedButtonBrowse();
 afx_msg void OnBnClickedBtnAbout();
};
