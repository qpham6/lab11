#include <stdint.h>
#include "mcc_generated_files/i2c1.h"

const uint8_t charTable[] = 
{
    0x00, 0x82, 0x21, 0x00, 0x00, 0x00, 0x00, 0x02, 0x39, 0x0F, 0x00, 0x00, 0x00, 0x40, 0x80, 0x00,
    0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7f, 0x6f, 0x00, 0x00, 0x00, 0x48, 0x00, 0x53,
    0x00, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71, 0x6F, 0x76, 0x06, 0x1E, 0x00, 0x38, 0x00, 0x54, 0x3F,
    0x73, 0x67, 0x50, 0x6D, 0x78, 0x3E, 0x00, 0x00, 0x00, 0x6E, 0x00, 0x39, 0x00, 0x0F, 0x00, 0x08, 
    0x63, 0x5F, 0x7C, 0x58, 0x5E, 0x7B, 0x71, 0x6F, 0x74, 0x02, 0x1E, 0x00, 0x06, 0x00, 0x54, 0x5C,
    0x73, 0x67, 0x50, 0x6D, 0x78, 0x1C, 0x00, 0x00, 0x00, 0x6E, 0x00, 0x39, 0x30, 0x0F, 0x00, 0x00 
};

void writeData(uint8_t address, uint8_t data) {
    I2C1_MESSAGE_STATUS status = I2C1_MESSAGE_PENDING;
    I2C1_MasterWrite(&data, 1, address, &status );
    while(status == I2C1_MESSAGE_PENDING);
}

void TM1650_init() {

    writeData(0x24, 1 ); // initializes the display
    writeData(0x34, 0 );
    writeData(0x35, 0 );
    writeData(0x36, 0 );
    writeData(0x37, 0 );
}

void TM1650_setDigit(uint8_t digit, uint8_t data)
{
     writeData(digit + 0x34, charTable[data - 32]);
}

static int i = 0;

/*void putch(char letter){
    if (letter == '\r') {
        i=0;
    }
    else{
    TM1650_setDigit(i, letter);
    i++;
    }
}
*/

void TM1650_fastPrintNum(uint16_t num) {
    uint16_t p;
    
    i = 0;
    for(int i = 3; i>=0; i--){
        p = num % 10;
         TM1650_setDigit(i, p + 48);
         num = num / 10;
    }
}