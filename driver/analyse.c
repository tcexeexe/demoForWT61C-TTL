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
 * @brief 返回加速度
 * @return 加速度
 */
struct SAcc read_acc()
{
	return stcAcc;
}

void CopeSerial2Data(uint8_t ucData[], uint8_t len)
{
	if (ucData[0]!=0x55) //数据头不对，则重新开始寻找0x55数据头
	{
		printf("Data header is incorrect \n");
		return;
	}
	if (len<11) 
	{
		printf("Data length is too short \n");
		return;
	}//数据不满11个，则返回
	else
	{
		switch(ucData[1])//判断数据是哪种数据，然后将其拷贝到对应的结构体中，有些数据包需要通过上位机打开对应的输出后，才能接收到这个数据包的数据
		{
			case 0x50:	memcpy(&stcTime,&ucData[2],8);break;//memcpy为编译器自带的内存拷贝函数，需引用"string.h"，将接收缓冲区的字符拷贝到数据结构体里面，从而实现数据的解析。
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
		len=0;//清空缓存区
	}
}

