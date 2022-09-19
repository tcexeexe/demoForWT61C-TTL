#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#include "dev_usart.h"// #include "./driver/dev_usart.h"
#include "log.h"// #include "./driver/log.h"

int32_t pc_fd;
static uint32_t read_buf_size;

/**
 * 打开上位机通信端口
 */
int32_t pc_open(const uint32_t read_buf)
{
	//打开串口设备
	pc_fd = open("/dev/ttyUSB0", O_RDWR|O_NOCTTY);

	if(pc_fd < 0){ return pc_fd; }

	//配置串口速率等参数
	{
	    set_speed(pc_fd, 115200);
	}
	

	set_Parity(pc_fd, 8, 1, 'N', 2 * 10);

	read_buf_size = read_buf;

	return pc_fd;
}


/**
 * 等待上位机下发的信息
 */
int32_t pc_read(uint8_t *recv_data, uint32_t *recv_len)
{
	const int32_t bytes = read(pc_fd, recv_data, read_buf_size);

	if(bytes > 0)
	{
		*recv_len = bytes;
		return 0;
	}
	else
	{
		return -1;
	}
}

static uint8_t PCRecvbuff[4096] = { 0x00 };	//接收缓冲区原始数据
static uint32_t PCRecvLen = 0;	//接收缓冲区原始数据长度


static void processRecvDataPc(void)
{

	int i;
	int read_len = 0;
    PCRecvLen = 0;
	int package_len = 0;
	
	read_again:
	pc_read(PCRecvbuff + PCRecvLen, &read_len);
	PCRecvLen += read_len;
    // printf("datalu len %d\n", read_len);

    if (read_len > 0) {
	    if (PCRecvbuff[0] == 0x58) {
		    if (PCRecvLen >= 3) {
			    package_len = (PCRecvbuff[1] << 8)  + PCRecvbuff[2] + 3 + 1 + 2;
		        if (PCRecvLen < package_len) {
				    goto read_again;
		        }
		
		    }else {
			        goto read_again;
		    }
	    }
    }
	

	if (0 < PCRecvLen <= 1024)
	{
		// printf("PCRecvLenlu : %d\n", PCRecvLen);
		#if 1
		// for (i = 0; i < PCRecvLen; i++)
		// {
		// 	printf("%02x", PCRecvbuff[i]);
		// }
		// printf("\n");
        #endif
		
		//PCRecvLen = 0;
	}
}

void main(void)
{

    int32_t ret = 0;
    ret = pc_open(1024);

    printf("open tty ret = %d\n", ret);
    if(ret < 0)
    {
        printf("open fail\n");
        return;
    }

	while(1)
	{

		processRecvDataPc();//从串口读取数据
		CopeSerial2Data(PCRecvbuff, PCRecvLen);

		// processRecvDataPc();
		usleep(150000);
	}
	printf("over\n");
}

 
