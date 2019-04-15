#include <poll.h>
#include <pthread.h>
#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/time.h>
#include <semaphore.h>
#include <unistd.h>
#include <string.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>

#include "esmtAD82584F.h"

#define I2C_DEV    "/dev/i2c-1"
#define I2C_24CXX_ADDR  0x50 /* 0x58 for 0x24c64 or 0x50 for 24c128*/
#define REG_OFFSET    0x0
#define WRITE_VALUE         0x5a
#if 0
#define I2C_SMBUS_READ 1
#define I2C_SMBUS_WRITE 0
union  i2c_smbus_data {
 unsigned  char byte;
 unsigned short word;
 unsigned char block[256]; /* block[0] is used for length */
          /* and one more for user-space compatibility */
};
struct i2c_smbus_ioctl_data {
 unsigned char read_write;
 unsigned char command;
 unsigned int size;
 struct i2c_smbus_data  *data;
};
#endif


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


int uni_i2c_open(char *dev_name, int slave_id, int timeout, int retry)
{
    int ret;
    
    i2c_dev = dev_name;
    i2c_slave_id = slave_id;
    
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
        
    ioctl(i2c_fd, I2C_RETRIES, retry);
    if(0 > ret){
        printf("%s: ioctl I2C_RETRIES retry=%d failed, %s\n", __func__, retry, strerror(errno));
        close(i2c_fd);
        return -1;
    }
    
    return 0;
}

int uni_i2c_close(void)
{
    if(0 > i2c_fd){
        printf("wrong i2c_fd=%d.\n", i2c_fd);
        return -1;
    }
    
    close(i2c_fd);
    i2c_fd = -1;
    return 0;
}



int uni_i2c_write_reg(uint16_t reg, uint16_t val)
{
    int ret;
    struct i2c_rdwr_ioctl_data_ext ioctl_data;
    struct i2c_rdwr_ioctl_data_ext *data = &ioctl_data;
    struct i2c_msg_ext  xfer[2];
    uint8_t buf[2];
    uint16_t slave_id = i2c_slave_id;

   // printf("%s  slave_id %d \n", __func__, slave_id);
    if(0 >= slave_id){
        printf("%s: wrong slave_id=%d.\n", __func__, slave_id);
        return -1;
    }    

    data->nmsgs = 1;
    data->msgs = xfer;
    
    data->msgs[0].addr = slave_id;
    data->msgs[0].flags = 0;
    data->msgs[0].len = 2;
    data->msgs[0].buf = buf;
   // buf[0] = (reg >> 8) & 0xff;
  //  buf[1] = val & 0xff;
   buf[0] = reg;
    buf[1] = val;
    
  //  buf[2] = (val >> 8) & 0xff;
  //  buf[3] = val & 0xff;
      
     // printf("buf[0] 0x%x buf[1] 0x%x  buf[2] 0x%x  buf[3] 0x%x  \n",buf[0] ,buf[1],buf[2],buf[3]);  
    ret = ioctl(i2c_fd, I2C_RDWR, data);
    if(0 > ret){
        printf("%s: ioctl I2C_RDWR failed, %s\n", __func__, strerror(errno));
        return -1;
    }

    return 0;
}





int uni_i2c_write_buf(uint8_t *buf, int size)
{
    int ret;
    struct i2c_rdwr_ioctl_data_ext ioctl_data;
    struct i2c_rdwr_ioctl_data_ext *data = &ioctl_data;
    struct i2c_msg_ext  xfer[2];
    uint16_t slave_id = i2c_slave_id;

    if(0 >= slave_id){
        printf("%s: wrong slave_id=%d.\n", __func__, slave_id);
        return -1;
    }    

    data->nmsgs = 1;
    data->msgs = xfer;
    
    data->msgs[0].addr = slave_id;
    data->msgs[0].flags = 0;
    data->msgs[0].len = size;
    data->msgs[0].buf = buf;
        
    ret = ioctl(i2c_fd, I2C_RDWR, data);
    if(0 > ret){
        printf("%s: ioctl I2C_RDWR failed, %s\n", __func__, strerror(errno));
        return -1;
    }

    return 0;
}



int uni_i2c_read( unsigned char *buff, int ByteNo)
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

#if 1
    if((access("/userdata/debug_uni_i2c",F_OK))!=-1) {
        printf("file exists.\n");
        int i;
        printf("uni_i2c__read 0x%02x:",buftmp[0]);
        for (i = 0; i < ByteNo; i++)
        {
          printf(" 0x%02x ",buff[i]);
        }
        printf("\n");

    } 
#endif

    return 0;
}

unsigned char _i2c_write(unsigned char sub_addr, unsigned char *buff, int ByteNo)
{

    return 0;
}

int uni_i2c_write(unsigned char *buff, int ByteNo)
{
   uint8_t p=0;
   int y = 0;
   if(ByteNo>256){
 	  printf("uni_i2c_write data_len error \n");
   	return -1;
   }

  struct timeval temp;
  for(;y<ByteNo;y++)
  {
  	
      p = y;
      
	  //	printf("%d 0x%x   %x\n", y,y,p);
	  	
	 if((access("/userdata/debug_uni_i2c",F_OK))!=-1) {
        printf("file exists.\n");
        printf("%d 0x%x   %x\n", y,y,p);
        

    }
    
	  	uni_i2c_write_reg(p, buff[y] );
      //sleep(1);
      
              temp.tv_sec = 0;
       // temp.tv_usec = 500 * 1000;
        temp.tv_usec = 10* 1000;

        select(0, NULL, NULL, NULL, &temp);

	}
   return 0;
}


int uni_i2c_read_chipid( unsigned char *buff, int ByteNo)
{
    int fd, ret;
    unsigned char buftmp[32] = {0};
    struct i2c_rdwr_ioctl_data i2c_data;

    //----------------------------------
    unsigned char device_addr = 0x00;
    unsigned char sub_addr = 0x80;

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
    
    device_addr = 0x58;

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
   // close(fd);

#if 1
    if((access("/userdata/debug_uni_i2c",F_OK))!=-1) {
        printf("file exists.\n");
        int i;
        printf("uni_i2c__read_chipid 0x%02x:",buftmp[0]);
        for (i = 0; i < ByteNo; i++)
        {
          printf(" 0x%02x ",buff[i]);
        }
        printf("\n");

    }
#endif

    return 0;
}
