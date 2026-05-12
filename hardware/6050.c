#include "stm32f10x.h"
#include "MyI2C.h"

#define MPU6050_ADDRESS 0xD0

void MPU6050_WriteReg(uint8_t RegAddr,uint8_t Data){
    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS);
    MyI2C_RecvAck();

    MyI2C_SendByte(RegAddr);
    MyI2C_RecvAck();
    MyI2C_SendByte(Data);
    MyI2C_RecvAck();

    MyI2C_Stop();
}

uint8_t MPU6050_ReadReg(uint8_t RegAddr){
    uint8_t Data;

    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS);
    MyI2C_RecvAck();
    MyI2C_SendByte(RegAddr);
    MyI2C_RecvAck();

    MyI2C_Start();
    MyI2C_SendByte(MPU6050_ADDRESS | 0x01);
    MyI2C_RecvAck();

    Data = MyI2C_RecvByte();
    MyI2C_SendAck(1);

    MyI2C_Stop();

    return Data;
}


void MPU6050_Init(void){
    MyI2C_Init();
}
