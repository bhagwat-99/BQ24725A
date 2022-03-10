#include "i2c_custom.h"

//slave address
const unsigned char slave_address = 0x09;
char *i2c_bus =  "/dev/apalis-i2c1";


int main()
{

i2c_init(i2c_bus);

unsigned char* data_to_read;
// unsigned char data_to_write[2];
// data_to_write[0]=0x00;
// data_to_write[0]=0x00;



//read manufacturing id at 0xFEH
unsigned char reg = 0xFE;
data_to_read = i2c_read(slave_address, reg);


printf("Manufacturing ID     %x",*(data_to_read+1));
printf("%x",*data_to_read);

//read device id at 0xFFH
reg = 0xFF;
data_to_read = i2c_read(slave_address, reg);

printf("data_to_read [1]  %x",*(data_to_read+1));
printf("%x",*data_to_read);


// //register to write 0x14
// reg = 0x14;
// data_to_write[0]=0x00;//lsb
// data_to_write[1]=0x04;//msb
// i2c_write_custom(&fd_i2c ,slave_address, reg, &data_to_write );

// //register to write 0x15
// reg = 0x15;
// data_to_write[0]=0x00;//lsb
// data_to_write[1]=0x38;//msb
// i2c_write_custom(&fd_i2c ,slave_address, reg, &data_to_write );


i2c_close();
}
