#include "i2c_custom.h"

//file descriptor
int fd_i2c = -1;
unsigned char inbuf[2];

void i2c_init(char *i2c_bus)
{
   
    if ((fd_i2c = open(i2c_bus, O_RDWR)) < 0)
    {
        printf("Failed to open apalis-i2c1.");
        
    }

}

void i2c_close() 
{
    close(fd_i2c);
}



unsigned char * i2c_read(unsigned char slave_addr, unsigned char reg) 
{
        unsigned char outbuf[1];
        

        outbuf[0]= reg;
        inbuf[0] = 0;
        inbuf[1] = 0;


        struct i2c_msg msgs[2];
        struct i2c_rdwr_ioctl_data msgset[1];

        msgs[0].addr = slave_addr;
        msgs[0].flags = 0;
        msgs[0].len = 1;
        msgs[0].buf = outbuf;

        msgs[1].addr = slave_addr;
        msgs[1].flags = I2C_M_RD;
        msgs[1].len = 2;
        msgs[1].buf = inbuf;

        msgset[0].msgs = msgs;
        msgset[0].nmsgs = 2;

        if(ioctl(fd_i2c, I2C_RDWR, &msgset) < 0) {
                perror("ioctl(I2C_RDWR) in i2c_read");
                
        }
        
        return inbuf;
}


void i2c_write_custom(unsigned char slave_addr, unsigned char reg, unsigned char *data_to_write )
{
    struct i2c_msg msgs[1];
    struct i2c_rdwr_ioctl_data msgset[1];

    unsigned char outbuf[3];

    outbuf[0] = reg;
    outbuf[1] = *data_to_write;
    outbuf[2] = *(data_to_write+1);

    msgs[0].addr = slave_addr;
    msgs[0].flags = 0;// 0 for write 
    msgs[0].len = 2;
    msgs[0].buf = outbuf;

    msgset[0].msgs = msgs;
    msgset[0].nmsgs = 1;

    if (ioctl(fd_i2c, I2C_RDWR, &msgset) < 0) {
        perror("ioctl(I2C_RDWR) in i2c_write");
    }

}