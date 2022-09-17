#include "analyse.h"
#include "JY901.h"

struct STime		stcTime;
struct SAcc 		stcAcc;
struct SGyro 		stcGyro;
struct SAngle 	stcAngle;
struct SMag 		stcMag;
struct SDStatus stcDStatus;
struct SPress 	stcPress;
struct SLonLat 	stcLonLat;
struct SGPSV 		stcGPSV;
struct SQ       stcQ;

/**
 * @brief ���ؼ��ٶ�
 * @return ���ٶ�
 */
struct SAcc read_acc()
{
	return stcAcc;
}

void CopeSerial2Data(uint8_t ucData[], uint8_t len)
{
	if (ucData[0]!=0x55) //����ͷ���ԣ������¿�ʼѰ��0x55����ͷ
	{
		printf("Data header is incorrect \n");
		return;
	}
	if (len<11) 
	{
		printf("Data length is too short \n");
		return;
	}//���ݲ���11�����򷵻�
	else
	{
		switch(ucData[1])//�ж��������������ݣ�Ȼ���俽������Ӧ�Ľṹ���У���Щ���ݰ���Ҫͨ����λ���򿪶�Ӧ������󣬲��ܽ��յ�������ݰ�������
		{
			case 0x50:	memcpy(&stcTime,&ucData[2],8);break;//memcpyΪ�������Դ����ڴ濽��������������"string.h"�������ջ��������ַ����������ݽṹ�����棬�Ӷ�ʵ�����ݵĽ�����
			case 0x51:	
			{
				memcpy(&stcAcc,&ucData[2],8);
				printf("accData: %d,%d,%d \n",stcAcc.a[0],stcAcc.a[1],stcAcc.a[2]);
				break;
			}
			case 0x52:	memcpy(&stcGyro,&ucData[2],8);break;
			case 0x53:	memcpy(&stcAngle,&ucData[2],8);break;
			case 0x54:	memcpy(&stcMag,&ucData[2],8);break;
			case 0x55:	memcpy(&stcDStatus,&ucData[2],8);break;
			case 0x56:	memcpy(&stcPress,&ucData[2],8);break;
			case 0x57:	memcpy(&stcLonLat,&ucData[2],8);break;
			case 0x58:	memcpy(&stcGPSV,&ucData[2],8);break;
			case 0x59:	memcpy(&stcQ,&ucData[2],8);break;
		}
		len=0;//��ջ�����
	}
}

