#ifdef PCIEDLL_EXPORTS
#define PCIEDLL_API __declspec(dllexport)
#else
#define PCIEDLL_API __declspec(dllimport)
#endif
#include "wdc_lib.h"
 PCIEDLL_API WDC_DEVICE_HANDLE hDev;//PCIE�豸���
 PCIEDLL_API DWORD pcie_inital(void);//����ֵ0���ɹ�
 PCIEDLL_API double sP_buf[2];//sP_buf[0]��PC��д��AX7103��PCIE���ٶ�ֵ��sP_buf[1]��PC����ȡAX7103��PCIE���ٶ�ֵ��
//PCIEDLL_API void DeviceClose(WDC_DEVICE_HANDLE hDev);
PCIEDLL_API DWORD PCIEClose(WDC_DEVICE_HANDLE hDev);//�ر�PCIE�豸 ����ֵ0���ɹ�
PCIEDLL_API DWORD PCIE_LibUninit(void);//Uninitialize WDC libraries ����ֵ0���ɹ�
/***************************************************************************************************
PCIEDLL_API DWORD writetofpga ( WDC_DEVICE_HANDLE hDev,BYTE *bufin,UINT64 u64Offset,UINT32 Totalnum)
���ܣ�д�뵽AX7103��PCIE����
����ֵ0���ɹ�
hDev:PCIE�豸���
buf:�洢��д�����ݵĻ�����
u64Offset��д���׵�ַƫ����
Totalnum:��д����ֽ���
******************************************************************************************************/
PCIEDLL_API DWORD writetofpga ( WDC_DEVICE_HANDLE hDev,BYTE *bufin,UINT64 u64Offset,UINT32 Totalnum);
/***************************************************************************************************
PCIEDLL_API DWORD writetoPC( WDC_DEVICE_HANDLE hDev,BYTE *bufin,UINT64 u64Offset,UINT32 Totalnum)
���ܣ�����AX7103��PCIE���ݵ�PC
����ֵ0���ɹ�
hDev:PCIE�豸���
buf:�洢��������ݵĻ�����
u64Offset���������ݵ��׵�ַƫ����
Totalnum:��������ֽ���
******************************************************************************************************/
PCIEDLL_API DWORD writetoPC ( WDC_DEVICE_HANDLE hDev,BYTE *bufin,UINT64 u64Offset,UINT32 Totalnum);
/***************************************************************************************************
PCIEDLL_API void PCIEspeed_DmaPerformance(WDC_DEVICE_HANDLE hDev, DWORD dwOption,DWORD dwBytes, BOOL fPolling,UINT64 u64Offset,DWORD dwSeconds)
���ܣ�AX7103��PCIE���ٺ���
����ֵ����
hDev:PCIE�豸���
dwOption:1:д��AX7103,2:��ȡAX7103��3��˫��
dwBytes:д��/��ȡ���ֽ���
fPolling:1��Ч��������Ч(����)
u64Offset��д��/�������ݵ��׵�ַƫ����
dwSeconds:��ȡ��д��ʱ�����õ�λ����)
******************************************************************************************************/
PCIEDLL_API void PCIEspeed_DmaPerformance(WDC_DEVICE_HANDLE hDev, DWORD dwOption,DWORD dwBytes, BOOL fPolling,UINT64 u64Offset,DWORD dwSeconds);