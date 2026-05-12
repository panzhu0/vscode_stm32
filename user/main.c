#include "stm32f10x.h"
#include "OLED.h"
#include "string.h"
#include "6050.h"

int main(void){
    OLED_Init();
    MPU6050_Init();

    // Read ID
    uint8_t ID = MPU6050_ReadReg(0x75);
    OLED_ShowHexNum(1,1,ID,2);

    // End sleep
    MPU6050_WriteReg(0x6B,0x00);

    // Write to Reg and read it .
    MPU6050_WriteReg(0x19,0xAB);
    ID= MPU6050_ReadReg(0x19);
    OLED_ShowHexNum(2,1,ID,2);

    while(1){};
}
