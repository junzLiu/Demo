#ifndef __TTY_IO_H__
#define __TTY_IO_H__

#ifdef __cplusplus
extern "C" {
#endif

extern int set_tty_params(int fd, long baudr, char par, int bit  , int stopb, int hwf, int swf);
extern int tty_recv_buffer(int fd, unsigned char *buf, unsigned int count);
extern int tty_send_buffer(int fd,const unsigned char *buf,unsigned int count);

extern int args_check(int argc,const char *argv[]);

extern int disconect_4G(int fd);
extern int dial_4G_net(int fd);

extern void show_help(void);

#ifdef __cplusplus
}
#endif

#endif
