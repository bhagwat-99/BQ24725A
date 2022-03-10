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
void i2c_close();

//write to i2c slave
// void i2c_write_custom(unsigned char slave_addr, unsigned char reg, unsigned char *data_to_write );
void i2c_write_custom(unsigned char slave_addr, unsigned char reg);


//read from slave
unsigned char * i2c_read(unsigned char slave_addr, unsigned char reg);


#endif