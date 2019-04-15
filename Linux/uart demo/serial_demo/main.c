#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/file.h>

#include "tty_io.h"
#include "main.h"

/* #define SERIAL_DEV             "/dev/ttyUSB2" */
/* #define SERIAL_DEV_TElEOM      "/dev/ttyUSB0" */
/* #define SERIAL_DEV             "/dev/ttyUSB1" */
#define SERIAL_DEV             "/dev/ttyS1"
#define SERIAL_DEV_TElECOM      "/dev/ttyUSB3"
#define BUFFER_LEN             512

unsigned char buffer[BUFFER_LEN];


char *user_apn;
const char **gargv;
static int fd = -1;

int main(int argc,const char *argv[])
{
	int ret = -1;
        int s,q;
	/* const char *testbuff = "this is a test buffer"; */
	/* const char testbuff[] = "this is a test buffer"; */
	const char *testbuff = argv[1];

        if( tty_dev_init() != 0 )
        {
                ret = -2;
                goto out_return;
        }


	//send
	//int tty_send_buffer(int fd,const unsigned char *buf,unsigned int count)
	ret = tty_send_buffer(fd,testbuff, strlen(testbuff)+1);
	printf("ret = %d\n",ret);

	//recv
	//int tty_recv_buffer(int fd, unsigned char *buf, unsigned int count)
	
	/* ret = tty_recv_buffer(fd, buffer,BUFFER_LEN);	 */
	/* printf("[%s] recv buffer:%s\n", __func__,buffer); */

out_return:
        tty_dev_exit();

        return ret;
}

int tty_dev_init(void)
{
        char *pfilename = NULL;
        int ret = -1;

        if( (fd = open(SERIAL_DEV,O_RDWR) ) < 0 )
        {
                fprintf(stderr,"open file %s error:%s",pfilename,strerror(errno));
                return -2;
        }

        printf("[%s:%d] flock success!\n",__func__,__LINE__);
	/* ret = set_tty_params(fd,115200,'N', 8, 1, 0, 0); */
	ret = set_tty_params(fd,9600,'N', 8, 1, 0, 0);

        if( ret != 0 )
            close(fd);

        return ret; /*on success ,return 0*/
}

void tty_dev_exit()
{
        close(fd);
}

static int dial_sccess(const char *buffer)
{
        const char *str = "QCRMCALL: 1, V4";
        char *p = NULL;

        p = strcasestr(buffer,str);
        if( p == NULL )
                return -1;
        else
                return 0;
}

static int query_qcrmcall_status(int fd)
{
        int ret = -1;
        char *pcmd = "at$qcrmcall?\r";
        char buff[BUFFER_LEN];
        memset(buff,0,BUFFER_LEN);
        ret = at_cmd_send_recv(pcmd,buff,10,fd);
        if( ret == 0)
        {
                ret = dial_sccess(buff);
                if( ret == 0)
                {
                    printf("query 4G net success!\n");
                }
        }
        return ret;
}

//"at+cgdcont=1,\"ip\",\"cmnet\"\r",/*register APN*/

int args_check(int argc,const char *argv[])
{
        int len = 0;
        if( argc < 2 )
        {
                fprintf(stderr,"command args error. help info:\n");
                show_help();
                return -1;
        }
        if( strcmp(argv[1],"-h") == 0 \
           || strcmp(argv[1],"--help") ==0 )
        {
                show_help();
                return -2;
        }

        /* "at+cgdcont=1,\"ip\",\"cmnet\"\r",[>register APN<] */
        if( argc >= 3 )
        {
                len = strlen(argv[2]) + 4;
                user_apn = (char *)malloc(len);
                if(user_apn)
                {
                        memset(user_apn,0,len);
                        *user_apn = '\"';
                        memcpy(user_apn+1,argv[2],strlen(argv[2]));
                        memcpy(user_apn+strlen(argv[2])+1,"\"\r",2);
                        printf("user APN : %s\n",argv[2]);
                }
        }
        gargv = argv;

        return 0;
}

void show_help(void)
{
	printf("usege: ./dial4G  <opertions> [APN]\n");
	printf("opertions are : on, off,stat,-r -h, --help\n");
	printf("eg: \n\t./dial4G  on\t\t//dial on\n");
	printf("\n\t./dial4G  on cmnet\n");
	printf("\t./dial4G  off\t\t//dial off\n");
        printf("\t./dial4G stat\t\t//get netstat\n");
        printf("\t./dial4G -r  \t\t//reset rf\n");
	printf("\t./dial4G  -h\n");
}
