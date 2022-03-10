
#include "i2c_custom.h"


char *i2c_bus = "/dev/apalis-i2c1";
unsigned char slave_address = 0x09;
unsigned char reg;


// int i2c_init(void)
// {
//     if ((fd_i2c = open(i2c_bus, O_RDWR)) < 0)
//     {
//         printf("Failed to open apalis-i2c1.");
//         return -1;
//     }
//     return fd_i2c;
// }



int main()
{
        i2c_init(i2c_bus);

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
