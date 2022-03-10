#ifndef I2C_CUSTOM_H
#define I2C_CUSTOM_H

#include <stdio.h> // printf()
#include <sys/types.h> // open()
#include <sys/stat.h> // open()
#include <fcntl.h> // open()
#include <sys/ioctl.h> // ioctl()
#include <errno.h> // errno
#include <string.h> // strerror()
#include <unistd.h> // close()
#include <linux/i2c-dev.h> // struct i2c_msg
#include <linux/i2c.h> // struct i2c_rdwr_ioctl_data

void i2c_init(char *i2c_bus);
void i2c_close(void);

__uint16_t i2c_read(unsigned char slave_addr, unsigned char reg);

int i2c_write(unsigned char slave_addr, unsigned char reg, unsigned char low_byte, unsigned char high_byte );


#endif