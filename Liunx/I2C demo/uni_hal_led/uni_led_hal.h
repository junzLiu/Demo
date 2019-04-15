#ifndef __UNI_LED_HAL_H__
#define __UNI_LED_HAL_H__

#ifndef NULL
#define NULL (void *)0
#endif

#ifndef likely
#define likely(x) __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)
#endif


#define NONE         "\033[m\n"  
#define RED          "\033[0;31m"
#define GREEN        "\033[0;32m"


typedef enum stream_mode {
	STREAM_LOOP = 0,
	STREAM_SHAKE,
}stream_mode_t; 


/******************************
Function: uni_hal_led_stream
args:
	@mode 			0: stream loop, 1  stream shake
	@stream_times   1~n: times
			0:  running always
return:
    0: success
    -1: fail
******************************/
extern int uni_hal_led_stream(enum stream_mode mode,int stream_times);




/******************************
Function: uni_hal_led_breath
Description: start led breath with arg breath_times
args:
	@breath_times   1~n: times 
			0:  running always
return:
    0: success
    -1: fail
******************************/
extern int uni_hal_led_breath(int breath_times);


/******************************
Function: 	uni_hal_led_stop
Description: stop the led if it is run in stream or breath
return:
    0: success
    -1: fail
******************************/
extern int uni_hal_led_stop(void);



#endif
