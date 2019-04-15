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


#include <errno.h>
#include <stdint.h>
#include <unistd.h>

#include "uni_led_hal.h"


static void uni_led_stop_handler(int sig)
{
	printf("[%s] stop led\n",__func__);
	uni_hal_led_stop();
}

static void uni_led_open_handler(int sig)
{
	printf("[%s] open led\n",__func__);
	uni_hal_led_stream(STREAM_LOOP,1);
}


int main(int argc,const char *argv[])
{
	int times;
	if (argc != 3 ) {
		fprintf(stderr,RED"useage: %s <[stream|breath]> <times> "NONE,argv[0]);
		return -1;
	}

	times = strtoul(argv[2],NULL,10);

	struct sigaction sigact0 = { .sa_handler = uni_led_stop_handler };
	struct sigaction sigact1 = { .sa_handler = uni_led_open_handler };
	sigaction(SIGUSR1, &sigact0, NULL);
	sigaction(SIGUSR2, &sigact1, NULL);

	printf(GREEN"test %d times .... "NONE,times);

	if (strcmp(argv[1],"stream") == 0 ) {
		uni_hal_led_stream(STREAM_LOOP,times);
	} else {
		uni_hal_led_breath(times);
	}

	while(1) {
		sleep(1);
	}

	return (0);
}
