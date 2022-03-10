
#include "i2c_custom.h"

int fd_i2c = -1; // i2c bus file descriptor
const char *i2c_bus = "/dev/apalis-i2c1";
unsigned char slave_address = 0x09;
unsigned char reg;


int i2c_init(void)
{
    if ((fd_i2c = open(i2c_bus, O_RDWR)) < 0)
    {
        printf("Failed to open apalis-i2c1.");
        return -1;
    }
    return fd_i2c;
}

void i2c_close(void) 
{
    close(fd_i2c);
}

// Write to an I2C slave device's register:
int i2c_write(unsigned char slave_addr, unsigned char reg, unsigned char low_byte, unsigned char high_byte )
{
    struct i2c_msg msgs[1];
    struct i2c_rdwr_ioctl_data msgset[1];

    unsigned char outbuf[3];

    outbuf[0] = reg;
    outbuf[1] = low_byte;
    outbuf[2] = high_byte;

    msgs[0].addr = slave_addr;
    msgs[0].flags = 0;// 0 for write 
    msgs[0].len = 3;
    msgs[0].buf = outbuf;

    msgset[0].msgs = msgs;
    msgset[0].nmsgs = 1;

    if (ioctl(fd_i2c, I2C_RDWR, &msgset) < 0) {
        perror("ioctl(I2C_RDWR) in i2c_write");
        return -1;
    }

    return 0;
}


// Read the given I2C slave device's register and return the read value in `*result`:
__uint16_t i2c_read(unsigned char slave_addr, unsigned char reg) 
{
    unsigned char outbuf[1];
    unsigned char inbuf[2];

    outbuf[0]=reg;
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

    if (ioctl(fd_i2c, I2C_RDWR, &msgset) < 0) {
        perror("ioctl(I2C_RDWR) in i2c_read");
        return -1;
    }
        printf("inbuf[0] %x\n",inbuf[0]);
        printf("inbuf[1] %x\n",inbuf[1]);
    __uint16_t reg_value = inbuf[1]*256 + inbuf[0] ;
    return reg_value;
}

int main()
{
        i2c_init();

        reg=0x14;
        unsigned char low_byte = 0x00;
        unsigned char high_byte = 0x04;
        i2c_write(slave_address, reg, low_byte, high_byte );//writing configuration register

        reg=0x15;
        low_byte = 0x00;
        high_byte = 0x38;
        i2c_write(slave_address, reg, low_byte, high_byte );//writing configuration register

        // sleep(1);
        reg = 0x14;
        i2c_read(slave_address, reg);//reading result register

        reg = 0x15;
        i2c_read(slave_address, reg);//reading result register

    //float Lux = reg_value * 0.0576 ; // gain = 1 and integration time = 100ms multiplication factor = 0.0576

   // printf("Light Intensity : %.2f Lux \n",Lux);
    i2c_close();
    return 0;
}




// #include "i2c_custom.h"

// //slave address
// unsigned char slave_address = 0x09;
// char *i2c_bus =  "/dev/apalis-i2c1";


// int main()
// {

// i2c_init(i2c_bus);

// unsigned char* data_to_read;
// unsigned char data_to_write[2];




// //read manufacturing id at 0xFEH
// unsigned char reg = 0xFE;
// data_to_read = i2c_read(slave_address, reg);
// printf("Manufacturing ID     %x",*(data_to_read+1));
// printf("%x\n",*data_to_read);

// //read device id at 0xFFH
// reg = 0xFF;
// data_to_read = i2c_read(slave_address, reg);
// printf("Device ID  %x",*(data_to_read+1));
// printf("%x\n",*data_to_read);



// //register to write 0x14
// reg = 0x14;
// data_to_write[1]=0x04;//msb
// data_to_write[0]=0x00;//lsb

// // i2c_write_custom(slave_address, reg, data_to_write );
// i2c_write_custom(slave_address, reg,data_to_write);

// //register to write 0x15
// reg = 0x15;
// data_to_write[1]=0x38;//msb
// data_to_write[0]=0x00;//lsb

// // i2c_write_custom(slave_address, reg, data_to_write );
// i2c_write_custom(slave_address, reg,data_to_write);

// i2c_close();

// }
