
#ifndef _UNI_I2C_HAL_H_
#define _UNI_I2C_HAL_H_

#if defined(__cplusplus)
extern "C" {
#endif


extern int uni_i2c_close();
extern int uni_i2c_open(char *dev_name, int slave_id, int timeout, int retry);
extern int uni_i2c_read(unsigned char *buff, int ByteNo);
extern int uni_i2c_write(unsigned char *buff, int ByteNo);
extern int uni_i2c_read_chipid( unsigned char *buff, int ByteNo);


#if defined(__cplusplus)
}  /* extern "C" */
#endif

#endif 