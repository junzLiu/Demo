#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <poll.h>
#include <syslog.h>

struct pollfd fds[1];

int tty_send_buffer(int fd,const unsigned char *buf,unsigned int count)
{
	int ret;

	if( !buf || count <=0 )
	{
		fprintf(stderr,"input arg error: no data send!\n");
		return -1;
	}

        ret = write(fd, buf, count);
        fsync(fd);
        //printf("--%s:%d  send buffer length = %d\n",__func__,__LINE__,ret);

	return ret;
}

int tty_recv_buffer(int fd, unsigned char *buf, unsigned int count)
{
#ifdef __DEBUG__
	//printf("enter %s:%d\n",__func__,__LINE__);
#endif
	int poll_ret = -1,len = -1;

	if( !buf || count <=0 )
	{
                fprintf(stderr,"[%s:%d] input arg error:buf=%p,count=%d\n",__func__,__LINE__,buf,count);
		return -1;
	}


#if 1
	fds[0].fd       =  fd;
	fds[0].events   =  POLLIN | POLLPRI;

	/*limit 2000 ms timeout,avoid long time block*/
	poll_ret = poll(fds,1,2000);
	if(poll_ret == 0)
	{
                fprintf(stderr,"read timeout\n");
		return -2;
	}
        else if( poll_ret == -1 )
        {
                fprintf(stderr,"[%s:%d] poll error:%s\n",__func__,__LINE__,strerror(errno));
		return -3;
        }
#endif
	/*there are data can be read,if come to here.*/
	int oflags = 0;

        oflags = fcntl(fd,F_GETFL);
        fcntl(fd,F_SETFL,oflags|O_NONBLOCK);

        memset(buf, 0, count );
        len = read(fd, buf, count);
        if( len == -1)
        {
                fprintf(stderr,"[%s:%d] read error:%s\n",__func__,__LINE__,strerror(errno));
        }

        fcntl(fd,F_SETFL,oflags);

#ifdef __DEBUG__
	//printf("exit %s:%d\n",__func__,__LINE__);
#endif
	return len;
}

int set_tty_params(int fd, long baudr, char par, int bit  , int stopb, int hwf, int swf)
{
        unsigned int speed;
        struct termios newtty;
	int ret = -1;

        ret = tcgetattr(fd, &newtty);
	if( ret != 0 )
	{
		//fprintf(stderr,"%s:%d tcgetattr error:%s\n",__func__,__LINE__,strerror(errno) );
		return -1;
	}

        /*set baud rate*/
        switch(baudr)
        {
                case 2400:      speed = B2400; break;
                case 9600:      speed = B9600; break;
                case 19200:     speed = B19200; break;
                case 38400:     speed = B38400; break;
                case 57600:     speed = B57600; break;
                case 115200:    speed = B115200; break;
                case 230400:    speed = B230400; break;
                default:        speed = B38400; break;
        }

        ret = cfsetispeed(&newtty, (speed_t)speed);
        ret = cfsetospeed(&newtty, (speed_t)speed);

	/*set trans bits*/
        switch (bit)
        {
                case 5:
                        newtty.c_cflag |= (newtty.c_cflag & ~CSIZE) | CS5;
                        break;
                case 6:
                        newtty.c_cflag |= (newtty.c_cflag & ~CSIZE) | CS6;
                        break;
                case 7:
                        newtty.c_cflag |= (newtty.c_cflag & ~CSIZE) | CS7;
                        break;
                case '8':
                default:
                        newtty.c_cflag |= (newtty.c_cflag & ~CSIZE) | CS8;
                        break;
        }
        /* Set into raw, no echo mode */
        newtty.c_iflag =  IGNBRK;
        newtty.c_lflag = 0;
        newtty.c_oflag = 0;
        newtty.c_cflag |= CLOCAL | CREAD;
        newtty.c_cc[VMIN] = 1;
        newtty.c_cc[VTIME] = 5;

	/*set parity*/
        newtty.c_cflag &= ~(PARENB | PARODD);
        switch(par)
        {
                case 'E':
                        newtty.c_cflag |= PARENB;
                        newtty.c_iflag |= (INPCK | ISTRIP);
                        break;
                case 'O':
                        newtty.c_cflag |= PARENB;
                        newtty.c_cflag |= PARODD;
                        newtty.c_iflag |= (INPCK | ISTRIP);
                        break;
                case 'N':
                default:
                        //newtty.c_cflag &= ~(PARENB | PARODD); /*have set in above*/
                        break;
        }
        /*set stop bit*/
        if (stopb == 2)
	{
                newtty.c_cflag |= CSTOPB;
	}
        else
	{
                newtty.c_cflag &= ~CSTOPB;
	}

        /*set software flow contrl*/
        if (swf)
	{
                newtty.c_iflag |= IXON | IXOFF;
	}
        else
	{
                newtty.c_iflag &= ~(IXON|IXOFF|IXANY);
	}

	ret = tcsetattr(fd, TCSANOW, &newtty);
	if( ret != 0)
	{
		//fprintf(stderr,"%s tcsetattr error:%s\n",__func__,strerror(errno) );
		//perror("tcsetattr error");
		return -1;
	}
        /*set hard flow contrl*/
        //setHardwareFlow(fd, hwf); //no need

        return 0;
}
