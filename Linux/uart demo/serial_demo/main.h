#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

int tty_dev_init(void);
void tty_dev_exit(void);
int args_check(int argc,const char *argv[]);
int dis_conect_4G(int fd);
int dial_4G_net(int fd);
void show_help(void);
int _read_net_state(int fd);
int _read_csq(int fd,int *rssi,int *rxlevel);
int cops_stat(int fd);
int _reset_rf(int fd);
int ps_srv_domain(int fd);

#ifdef __cplusplus
}
#endif

#endif
