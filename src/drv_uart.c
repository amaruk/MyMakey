/*
 ============================================================================
 Name        : fox_uart.c
 Author      : Fox
 Version     :
 Copyright   : Fox is copyleft.
 Description : Hello World in C, Ansi-style

 http://blog.csdn.net/wangzhen209/article/details/32715467
 http://blog.csdn.net/zhanghuiliang/article/details/2467040
 http://blog.sina.com.cn/s/blog_4673bfa50100b5y4.html
 http://www.cnblogs.com/chengmin/p/3818133.html
 http://blog.csdn.net/w282529350/article/details/7386616
 ============================================================================
 */

#include "common.h"

static int _uart_fd;

int speed_arr[] =
{ B38400, B19200, B9600, B4800, B2400, B1200, B300,
B38400, B19200, B9600, B4800, B2400, B1200, B300, };
int name_arr[] =
{ 38400, 19200, 9600, 4800, 2400, 1200, 300, 38400, 19200, 9600, 4800, 2400,
		1200, 300, };
void set_speed(int fd, int speed)
{
	int i;
	int status;
	struct termios Opt;
	tcgetattr(fd, &Opt);
	for (i = 0; i < sizeof(speed_arr) / sizeof(int); i++)
	{
		if (speed == name_arr[i])
		{
			tcflush(fd, TCIOFLUSH);   //Update the options and do it NOW
			cfsetispeed(&Opt, speed_arr[i]);
			cfsetospeed(&Opt, speed_arr[i]);
			status = tcsetattr(fd, TCSANOW, &Opt);
			if (status != 0)
				perror("tcsetattr fd1");
			return;
		}
		tcflush(fd, TCIOFLUSH);
	}
}

int set_Parity(int fd, int databits, int stopbits, int parity)
{
	struct termios options;
	if (tcgetattr(fd, &options) != 0)
	{
		perror("SetupSerial 1");
		return (FALSE);
	}
	options.c_cflag &= ~CSIZE;
	switch (databits)
	{
	case 7:
		options.c_cflag |= CS7;
		break;
	case 8:
		options.c_cflag |= CS8;
		break;
	default:
		fprintf(stderr, "Unsupported data size\n");
		return (FALSE);
	}
	switch (parity)
	{
	case 'n':
	case 'N':
		options.c_cflag &= ~PARENB; /* Clear parity enable */
		options.c_iflag &= ~INPCK; /* Enable parity checking */
		break;
	case 'o':
	case 'O':
		options.c_cflag |= (PARODD | PARENB);
		options.c_iflag |= INPCK; /* Disnable parity checking */
		break;
	case 'e':
	case 'E':
		options.c_cflag |= PARENB; /* Enable parity */
		options.c_cflag &= ~PARODD;
		options.c_iflag |= INPCK; /* Disnable parity checking */
		break;
	case 'S':
	case 's': /*as no parity*/
		options.c_cflag &= ~PARENB;
		options.c_cflag &= ~CSTOPB;
		break;
	default:
		fprintf(stderr, "Unsupported parity\n");
		return (FALSE);
	}

	switch (stopbits)
	{
	case 1:
		options.c_cflag &= ~CSTOPB;
		break;
	case 2:
		options.c_cflag |= CSTOPB;
		break;
	default:
		fprintf(stderr, "Unsupported stop bits\n");
		return (FALSE);
	}
	/* Set input parity option */
	if (parity != 'n')
		options.c_iflag |= INPCK;
	options.c_cc[VTIME] = 150; // 15 seconds
	options.c_cc[VMIN] = 0;

	tcflush(fd, TCIFLUSH); /* Update the options and do it NOW */
	if (tcsetattr(fd, TCSANOW, &options) != 0)
	{
		perror("SetupSerial 3");
		return (FALSE);
	}
	return (TRUE);
}
int open_dev(char *Dev)
{
	int fd = open(Dev, O_RDWR);         //| O_NOCTTY | O_NDELAY
	if (-1 == fd)
	{
		perror("Can't Open Serial Port");
		return -1;
	}
	else
		return fd;

}

int drv_uart_kill(void)
{
	close(_uart_fd);
	return TRUE;
}

/* Transmit bytes */
int drv_uart_putchars(const unsigned char * ptr, int n)
{
	return write(_uart_fd, ptr, n);
}

/* Receive bytes */
int drv_uart_getchars(unsigned char * ptr)
{
	int nread = 0;
	if ((nread = read(_uart_fd, ptr, 512)) > 0)
	{
		//printf("\nLen %d ", nread);
		*(ptr + nread) = '\0';
		printf("rtn [%s]\n", ptr);
	}
	return nread;
}

int drv_uart_init(char *dev_name, int speed, int databits, int stopbits,
		int parity)
{

	printf("Opening %s\n", dev_name);
	_uart_fd = open_dev(dev_name);

	if (_uart_fd > 0)
	{
		set_speed(_uart_fd, speed);
	}
	else
	{
		printf("ERROR: Can't Open Serial Port!\n");
		return FALSE;
	}

	if (set_Parity(_uart_fd, databits, stopbits, parity) == FALSE) // 8浣嶆暟鎹紝闈炰袱浣嶇殑鍋滄浣嶏紝涓嶄娇鐢ㄥ鍋舵牎楠� 锛屼笉鍏佽杈撳叆濂囧伓鏍￠獙
	{
		printf("ERROR: Set Parity Error\n");
		return FALSE;
	}

	return TRUE;
}
