#include "analyse.h"
#include "JY901.h"

struct STime		stcTime;
struct SAcc 		stcAcc;
struct SGyro 		stcGyro;
struct SAngle 	stcAngle;
struct SMag 		stcMag;
struct SDStatus stcDStatus;
struct Speed stcSpeed;

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
				printf("accData: %.3f,%.3f,%.3f \n",(float)stcAcc.a[0]/32768*16,(float)stcAcc.a[1]/32768*16,(float)stcAcc.a[2]/32768*16);
				break;
			}
			case 0x52:	memcpy(&stcGyro,&ucData[2],8);break;
			case 0x53:	memcpy(&stcAngle,&ucData[2],8);break;
			case 0x54:	memcpy(&stcMag,&ucData[2],8);break;
			case 0x55:	memcpy(&stcDStatus,&ucData[2],8);break;
		}
		len=0;//清空缓存区
	}
}

void acc2speed(void)
{
	stcSpeed.current_speed[0] = stcSpeed.last_speed[0] + (float)stcAcc.a[0]/32768*16 * 0.01;//每10ms采样一次
	stcSpeed.current_speed[1] = stcSpeed.last_speed[1] + (float)stcAcc.a[1]/32768*16 * 0.01;
	stcSpeed.current_speed[2] = stcSpeed.last_speed[2] + (float)stcAcc.a[2]/32768*16 * 0.01;
	printf("speed: %.3f,%.3f,%.3f \n", stcSpeed.current_speed[0], stcSpeed.current_speed[1], stcSpeed.current_speed[2]);
}
