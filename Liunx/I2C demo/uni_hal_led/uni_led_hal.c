#include <stdio.h>
#include <poll.h>
#include <pthread.h>
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
#include <pthread.h>
#include <stdint.h>
#include <sys/time.h>
#include <semaphore.h>
#include <unistd.h>

#include "uni_led_hal.h"

#include "esmtAD82584F.h"

#define I2C_DEV    "/dev/i2c-1"
#define I2C_24CXX_ADDR  0x50 /* 0x58 for 0x24c64 or 0x50 for 24c128*/
#define REG_OFFSET    	0x0
#define WRITE_VALUE     0x5a

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


static pthread_t led_thread_id;
static bool led_main_loop;


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


int uni_4mic_i2c_open(char *dev_name, int slave_id, int timeout, int retry)
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

int uni_4mic_i2c_close(void)
{
    if(0 > i2c_fd){
        printf("wrong i2c_fd=%d.\n", i2c_fd);
        return -1;
    }
    
    close(i2c_fd);
    i2c_fd = -1;
    return 0;
}

int uni_4mic_i2c_read_reg(uint16_t reg, uint16_t *val)
{

    
    return 0;
}

int uni_4mic_i2c_write_reg(uint16_t reg, uint16_t val)
{
    int ret;
    struct i2c_rdwr_ioctl_data_ext ioctl_data;
    struct i2c_rdwr_ioctl_data_ext *data = &ioctl_data;
    struct i2c_msg_ext  xfer[2];
    uint8_t buf[2];
    uint16_t slave_id = i2c_slave_id;

    //printf("%s  slave_id %d \n", __func__, slave_id);
    if(0 >= slave_id) {
        printf("%s: wrong slave_id=%d\n", __func__, slave_id);
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
      
	//printf("buf[0] 0x%x buf[1] 0x%x  buf[2] 0x%x  buf[3] 0x%x  \n",buf[0] ,buf[1],buf[2],buf[3]);  
    ret = ioctl(i2c_fd, I2C_RDWR, data);
    if(0 > ret){
        printf("%s: ioctl I2C_RDWR failed, %s\n", __func__, strerror(errno));
        return -1;
    }

    return 0;
}

int uni_4mic_i2c_update_bits(uint16_t reg, uint16_t mask, uint16_t val)
{

    return 0;
}

int uni_4mic_i2c_read_buf(uint8_t *buf, int size)
{

    
    return 0;
}

int uni_4mic_i2c_write_buf(uint8_t *buf, int size)
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
void _uni_delay_usec(int s) {
  struct timeval temp;
  temp.tv_sec = 0;
  temp.tv_usec = s * 1000;
  select(0, NULL, NULL, NULL, &temp);
}


void _uni_delay() {
  struct timeval temp;
  temp.tv_sec = 0;
  temp.tv_usec = 100 * 1000;
  select(0, NULL, NULL, NULL, &temp);
}


static inline int s_light_one_led_500ms(uint16_t reg,uint16_t val)
{
	if( reg >= 0x20 && reg <= 0x2f ) {
		uni_4mic_i2c_write_reg(reg,val); /* open a led */
		_uni_delay_usec(50);
		uni_4mic_i2c_write_reg(reg,0); /* close a led */
		return 0;
	}

	return -1;
}
/* (0x20,21,22), (0x23,24,25), (0x26,27,28), (0x29,2a,2b),(0x2c,2d,3e)*/
#if 0
static inline int s_light_all_led_500ms(uint16_t val)
{
	uint16_t reg_index,reg;
	for(reg_index=0x20; reg_index<= 0x2f; reg_index+=3) {
		uni_4mic_i2c_write_reg(reg_index,val);
	}
	_uni_delay_usec(500);

	for(reg_index=0x21; reg_index<= 0x2f; reg_index+=3) {
		uni_4mic_i2c_write_reg(reg_index,val);
	}
	_uni_delay_usec(500);

	for(reg_index=0x22; reg_index<= 0x2f; reg_index+=3) {
		uni_4mic_i2c_write_reg(reg_index,val);
	}
	_uni_delay_usec(500);

	return 0;
}
#endif

#define LED_RESET_GPIO	8

static inline int uni_led_gpio_reset(int onoff)
{
	FILE *fp = NULL;
	char cmd[128] = {0};

	sprintf(cmd,"/sys/class/gpio/gpio%d/value",LED_RESET_GPIO);
	if((fp = fopen(cmd,"w")) == NULL) {
		fprintf(stderr,"open %s failed: %s\n", cmd, strerror(errno));
           return -1;
	}

	fprintf(fp,"%d",0);
	fflush(fp);

	if(onoff) {
		_uni_delay();
		_uni_delay();
		fprintf(fp,"%d",1);
	}

	fclose(fp);

	return 0;
}
int  uni_hal_led_open(void)
{
	FILE *fp = NULL;
	char cmd[128] = {0};

	if( 0 != uni_4mic_i2c_open("/dev/i2c-1", 0x5b, 1, 3) ) {
		fprintf(stderr,"open /dev/i2c-2 fail!\n");
		return -1;
	}
	
	if(access("/sys/class/gpio/gpio8",R_OK) == 0){ /* dir exist */
		return uni_led_gpio_reset(1);
	} else {
		sprintf(cmd,"/sys/class/gpio/export");
		if((fp = fopen(cmd,"w")) == NULL) {
			fprintf(stderr,"open %s failed: %s\n", cmd, strerror(errno));
			return -1;
		}
		fprintf(fp,"%d",LED_RESET_GPIO);
        	fclose(fp);

		sprintf(cmd,"/sys/class/gpio/gpio%d/direction",LED_RESET_GPIO);
		if((fp = fopen(cmd,"w")) == NULL) {
			printf("open %s failed: %s\n", cmd, strerror(errno));
			return -1;
		}
		fputs("out",fp);
		fclose(fp);
		return uni_led_gpio_reset(1);
	}

	return 0;
}

int uni_hal_led_close(void)
{
	uni_4mic_i2c_close();

	return uni_led_gpio_reset(0);
}


static void led_thread_routine_exit(void *args)
{
	int *times = (int*)args;
	uni_hal_led_close();
	led_thread_id = -1;

	led_main_loop = false;
	*times = 0;
	printf("[%s] led stopped loop:%d!\n",__func__,led_main_loop);
}


struct led_stream {
	enum stream_mode mode;
	int stream_times;
}led_paoma;


static void *led_stream_routine(void *arg)
{
	struct led_stream *led_paomao = (struct led_stream *)arg;
	uint16_t reg_index;
	int stream_times;

	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	pthread_cleanup_push(led_thread_routine_exit, &led_paomao->stream_times);

	stream_times = led_paomao->stream_times;
	printf("[%s] times:%d,led_main_loop:%d\n",__func__,stream_times,led_main_loop);
	
	while(led_main_loop) {

		if ( led_paomao->mode ==STREAM_LOOP ) {
			for(reg_index=0x20; reg_index<= 0x2f; reg_index++) {
				s_light_one_led_500ms(reg_index,0x3f);
			}
		} else if ( led_paomao->mode == STREAM_SHAKE) {
			for(reg_index=0x20; reg_index<= 0x2f; reg_index++) {
				s_light_one_led_500ms(reg_index,0x3f);
			}

			for(reg_index=0x2f; reg_index>= 0x20; reg_index--) {
				s_light_one_led_500ms(reg_index,0x3f);
			}
			
		}

		if(stream_times) { /* if times == 0 , it always running. */
			if(!(--stream_times))
				break;
		}
		
	}

	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	pthread_cleanup_pop(1);

	return NULL;
}



/******************************
Function: uni_hal_led_stream
args:
	@mode 			STREAM_LOOP: loop stream, STREAM_SHAKE:  stream led shake
	@stream_times   : 1~n times 
					: 0  running always
return:
    0: success
    -1: fail
******************************/

int uni_hal_led_stream(enum stream_mode mode,int stream_times)
{

	if(stream_times < 0 )
		return -1;

	if( uni_hal_led_open() != 0 )
		return -1;
#if 0
	while(count++ < 20) {
		uni_4mic_i2c_write_reg( 0x55, 0x55);
		uni_4mic_i2c_write_reg( 0xaa, 0xaa);
		uni_4mic_i2c_write_reg( 0x55, 0xaa);
		uni_4mic_i2c_write_reg( 0xaa, 0x55);
		_uni_delay();
	}
#endif
 	uni_4mic_i2c_write_reg(0x12,0x00);   /* OUT4~9 config as LED mode */
	uni_4mic_i2c_write_reg(0x12,0x00);   //OUT4~9配置为呼吸灯模式	 
	uni_4mic_i2c_write_reg(0x13,0x00);   /* OUT0~3 config as LED mode */
	uni_4mic_i2c_write_reg(0x13,0x00);   //OUT0~3配置为呼吸灯模式
	//uni_4mic_i2c_write_reg(0x20,0x3f);	//OUT0口调光，调光等级为0-255。OUT0~OUT9的调光指令依次为0x20~0x29. 写0关闭
	//for(reg_index=0x20; reg_index<= 0x2f; reg_index++) {
		//uni_4mic_i2c_write_reg(reg_index,0x3f);
	//}


#if 1
	printf("[%s] times:%d,led_main_loop:%d\n",__func__,stream_times,led_main_loop);

	if(led_main_loop ) {
		uni_hal_led_close();
		fprintf(stderr,"[%s] led already open in an other thread\n",__func__);
		return -1;
	}

	led_main_loop = true;
	led_paoma.mode 	= mode;
	led_paoma.stream_times = stream_times;
	if (pthread_create(&led_thread_id, NULL, led_stream_routine, &led_paoma) == -1)
   	{
         fprintf(stderr,"create init_pcm_id error!\n");
         return -1;
   	}
   	pthread_detach(led_thread_id);

#else
	uint16_t reg_index;
	int i;

	if( mode == STREAM_LOOP ) {
		for(i = 0 ;i < stream_times; i++) {
			for(reg_index=0x20; reg_index<= 0x2f; reg_index++) {
				s_light_one_led_500ms(reg_index,0x3f);
			}
		}
	} else if ( mode == STREAM_SHAKE) {
		for(i = 0 ;i < stream_times; i+=2) {
			for(reg_index=0x20; reg_index<= 0x2f; reg_index++) {
				s_light_one_led_500ms(reg_index,0x3f);
			}

			for(reg_index=0x2f; reg_index>= 0x20; reg_index--) {
				s_light_one_led_500ms(reg_index,0x3f);
			}
		}
	}

	uni_hal_led_close();
#endif

	return 0;
}


#define BREATH_MAX_STEP 66
static unsigned char breath_step[BREATH_MAX_STEP]={0,0,3,6,9,12,
                                 15,18,21,24,27,
                                 30,34,38,42,46,
                                 50,54,60,66,72,
                                 78,84,92,102,115,
                                 125,135,145,160,180,
                                 210,255,255,210,
                                 180,160,145,135,125,
                                 115,102,92,84,78,
                                 72,66,60,54,50,
                                 46,42,38,34,30,
                                 27,24,21,18,15,
                                 12,9,6,3,0,0};


static void *led_breath_routine(void *arg)
{
	int *times = (int*)arg;
	uint16_t reg_index;
	int i;


	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	pthread_cleanup_push(led_thread_routine_exit, arg);

	printf("[%s] times:%d,led_main_loop:%d\n",__func__,*times,led_main_loop);
	
	while(led_main_loop) {
		
		for( i = 0; i < BREATH_MAX_STEP -1; i++) {
			/* light all led with breath_step[i] value*/
			for(reg_index=0x20; reg_index<= 0x2f; reg_index++) {
				//s_light_one_led_500ms(reg_index,breath_step[i]);
				uni_4mic_i2c_write_reg(reg_index,breath_step[i]); /* open a led */
			}
			_uni_delay_usec(30);
		}

		if(*times) { /* if times == 0 , it always running. */
			if(!(--*times))
				break;
		}
		
	}

	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	pthread_cleanup_pop(1);

	return NULL;
}

static int b_times;
int uni_hal_led_breath(int breath_times)
{
	//uint16_t reg_index;
	//int times,i;

	if( breath_times < 0 )
			return -1;

	if( uni_hal_led_open() != 0 )
		return -1;

	uni_4mic_i2c_write_reg(0x12,0x00);   //OUT4~9配置为呼吸灯模式
	uni_4mic_i2c_write_reg(0x12,0x00);   //OUT4~9配置为呼吸灯模式	 
	uni_4mic_i2c_write_reg(0x13,0x00);   //OUT0~3配置为呼吸灯模式
	uni_4mic_i2c_write_reg(0x13,0x00);   //OUT0~3配置为呼吸灯模式

#if 1

	if(led_main_loop ) {
		uni_hal_led_close();
		fprintf(stderr,"[%s] led already open in an other thread\n",__func__);
		return -1;
	}

	led_main_loop = true;
	b_times = breath_times;
	if (pthread_create(&led_thread_id, NULL, led_breath_routine, &b_times) == -1)
   	{
         fprintf(stderr,"create init_pcm_id error!\n");
         return -1;
   	}
   	pthread_detach(led_thread_id);

#else
	for( times = 0; times < breath_times; times++) {
		for( i = 0; i < BREATH_MAX_STEP -1; i++) {
			/* light all led with breath_step[i] value*/
			for(reg_index=0x20; reg_index<= 0x2f; reg_index++) {
				//s_light_one_led_500ms(reg_index,breath_step[i]);
				uni_4mic_i2c_write_reg(reg_index,breath_step[i]); /* open a led */
			}
			_uni_delay_usec(30);
		}
	}
	uni_hal_led_close();
#endif


	return 0;
}


int uni_hal_led_stop(void)
{
	if( !led_main_loop ) {
		return -1;
	}

	//printf("[%s] 111 led_thread_id:%d\n",__func__,led_thread_id);
	led_main_loop = false;

	if(led_thread_id != -1 ) {
		printf("[%s] waitting thread stopped ....\n",__func__);
		pthread_cancel(led_thread_id);
		//pthread_join(led_thread_id, NULL);
	}

	//printf("[%s] exit led_thread_id:%d\n",__func__,led_thread_id);

	return 0;
}

