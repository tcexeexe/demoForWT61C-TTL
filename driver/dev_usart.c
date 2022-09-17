#include "dev_usart.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <termios.h>

const int speed_arr[] = {B115200, B57600, B38400, B19200, B9600, B4800, B2400, B1200};
const int speed_name_arr[] = {115200, 57600, 38400, 19200,  9600,  4800,  2400, 1200};


void set_speed(uint32_t fd, uint32_t speed)
{
	uint32_t i;
	uint32_t status;
    struct termios options;

    tcgetattr(fd, &options);

    //设置串口波特率
    for(i =  0; i < sizeof(speed_arr) / sizeof(uint32_t); ++i)
    {
	   	if(speed == speed_name_arr[i])
	   	{
	   	    tcflush(fd, TCIOFLUSH);

		    cfsetispeed(&options, speed_arr[i]);
		    cfsetospeed(&options, speed_arr[i]);

		    status = tcsetattr(fd, TCSANOW, &options);
		    if (status != 0)
		    {
				perror("tcsetattr fd1");
		    }

		    return;
     	}

		tcflush(fd, TCIOFLUSH);
    }
}

int set_Parity(uint32_t fd, uint32_t bits, uint32_t stop, uint32_t parity, uint32_t timeout_sec)
{
    struct termios options;

    if(tcgetattr(fd, &options) != 0)
    {
		perror("SetupSerial 1");
		return(false);
    }
    options.c_cflag &= ~CSIZE;

    //设置每个字节位数
    switch (bits)
    {
	    case 7:
			options.c_cflag |= CS7;
			break;
	    case 8:
			options.c_cflag |= CS8;
			break;
	    	default:
			fprintf(stderr,"Unsupported data size\n");
			return (false);
    }

    //设置奇偶校验
    switch (parity)
    {
	    case 'n':
	    case 'N':
			options.c_cflag &= ~PARENB;
			options.c_iflag &= ~INPCK;
			break;
	    case 'o':
	    case 'O':
			options.c_cflag |= (PARODD | PARENB);
			options.c_iflag |= INPCK;
			break;
	    case 'e':
	    case 'E':
			options.c_cflag |= PARENB;
			options.c_cflag &= ~PARODD;
			options.c_iflag |= INPCK;
			break;
	    case 'S':
	    case 's':
			options.c_cflag &= ~PARENB;
			options.c_cflag &= ~CSTOPB;
			break;
	    default:
			fprintf(stderr,"Unsupported parity\n");
			return (false);
    }

    //停止位
    switch (stop)
    {
	    case 1:
			options.c_cflag &= ~CSTOPB;
			break;
	    case 2:
			options.c_cflag |= CSTOPB;
			break;
	    default:
			fprintf(stderr,"Unsupported stop bits\n");
			return (false);
    }

	options.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	options.c_oflag &= ~OPOST;
	options.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);

    if (parity != 'n')
    {
    		options.c_iflag |= INPCK;
    }

    if(! timeout_sec)
    {
		options.c_cc[VTIME] = 0;

		options.c_cc[VMIN] = 5;
    }
    else
    {
		options.c_cc[VTIME] = timeout_sec;	//100ms

		options.c_cc[VMIN] = 0;
    }

	tcflush(fd, TCIFLUSH);
    if (tcsetattr(fd, TCSANOW, &options) != 0)
    {
		perror("SetupSerial 3");
		return (false);
    }

    return (true);
}


void bwton_clear_com_buff(uint32_t fd) {
     tcflush(fd, TCIOFLUSH);
}


