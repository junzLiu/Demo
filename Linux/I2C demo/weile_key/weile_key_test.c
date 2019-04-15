#include <stdio.h>
#include <poll.h>
#include <signal.h>
#include <stdbool.h>

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <time.h>

#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include <sys/ioctl.h>
#include <errno.h>
#include <stdint.h>
#include <sys/time.h>
#include <semaphore.h>
#include <unistd.h>

#define NONE         "\033[m\n"  
#define RED          "\033[0;31m"
#define GREEN        "\033[0;32m"


#define I2C_DEV    "/dev/i2c-0"
#define WEILE_KEY_ADDR  0x2d /* 0x20 */

#define REG_OFFSET    	0x0
#define WRITE_VALUE     0x5a

static char *i2c_dev = NULL;
static int i2c_slave_id = 0;
static int i2c_fd = -1;


struct i2c_msg_ext {
	uint16_t addr;	/* slave address			*/
	uint16_t flags;
	uint16_t len;		/* msg length				*/
	uint8_t *buf;		/* pointer to msg data			*/
	uint32_t scl_rate;		/* add by kfx */
};

struct i2c_rdwr_ioctl_data_ext {
	struct i2c_msg_ext  *msgs;	/* pointers to i2c_msgs */
	__u32 nmsgs;			/* number of i2c_msgs */
};



int uni_key_i2c_open(char *dev_name, int slave_id, int timeout, int retry)
{
    int ret;
    
    i2c_dev = dev_name;
    i2c_slave_id = slave_id;

	if( i2c_fd > 0 ) {
		fprintf(stderr,RED"device is busy "NONE);
		return -1;
	}
    
    i2c_fd = open(i2c_dev, O_RDWR);
    if(0 > i2c_fd){
        printf("%s: failed to open %s\n", __func__, i2c_dev);
        return -1;
    }

    ret = ioctl(i2c_fd, I2C_TIMEOUT, timeout);
    if(0 > ret){
        printf("%s: ioctl I2C_TIMEOUT timeout=%d failed, %s\n", __func__, timeout, strerror(errno));
        close(i2c_fd);
        return -1;
    }
        
    ret = ioctl(i2c_fd, I2C_RETRIES, retry);
    if(0 > ret){
        printf("%s: ioctl I2C_RETRIES retry=%d failed, %s\n", __func__, retry, strerror(errno));
        close(i2c_fd);
        return -1;
    }
    
    return 0;
}


int uni_key_i2c_read( unsigned char *buff, int ByteNo)
{
    int fd, ret;
    unsigned char buftmp[32] = {0};
    struct i2c_rdwr_ioctl_data i2c_data;

    //----------------------------------
    unsigned char device_addr = 0x00;
    unsigned char sub_addr = 0x00;

    //init
    fd = i2c_fd;
    if (fd<0)
    {
        printf("not have /dev/i2c-0 t\r\n");
        return -1;
    }

    i2c_data.nmsgs = 2;
    i2c_data.msgs = (struct i2c_msg *)malloc(i2c_data.nmsgs *sizeof(struct i2c_msg));
    if (i2c_data.msgs == NULL)
    {
        printf("malloc error");
        close(fd);
        return -1;
    }

    ioctl(fd, I2C_TIMEOUT, 1);
    ioctl(fd, I2C_RETRIES, 2);
    
    device_addr = i2c_slave_id;

    //write reg
    memset(buftmp, 0, 32);
    buftmp[0] = sub_addr;
    i2c_data.msgs[0].len = 1;
    i2c_data.msgs[0].addr = device_addr;
    i2c_data.msgs[0].flags = 0;     // 0: write 1:read
    i2c_data.msgs[0].buf = buftmp;
    //read data
    i2c_data.msgs[1].len = ByteNo;
    i2c_data.msgs[1].addr = device_addr;
    i2c_data.msgs[1].flags = 1;     // 0: write 1:read
    i2c_data.msgs[1].buf = buff;


    ret = ioctl(fd, I2C_RDWR, (unsigned long)&i2c_data);
    if (ret < 0)
    {
        printf("read data %x %x error\r\n", device_addr, sub_addr);
        close(fd);
        free(i2c_data.msgs);
        return 1;
    }
    free(i2c_data.msgs);
  //  close(fd);


    return 0;
}


int uni_key_close(void)
{
	if(0 > i2c_fd){
        printf("wrong i2c_fd=%d.\n", i2c_fd);
        return -1;
    }
    
    close(i2c_fd);
    i2c_fd = -1;
	return 0;
}

int main(int argc, const char *argv[])
{
	int ret;
	unsigned char buff[16] = {0};

	ret = uni_key_i2c_open(I2C_DEV, WEILE_KEY_ADDR, 1, 3);


	while(1) {
		ret = uni_key_i2c_read(buff,2);/* read two bytes, keycode && ~keycode */
		if( ret == 0 ) {
			printf("read keycode:0x%02x  ~keycode:0x%02x\n",buff[0],buff[1]);
		}
		usleep(200000);/* 100ms */
	}

	uni_key_close();

	return 0;
}
