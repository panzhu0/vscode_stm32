#include "stm32f10x.h"
#include "MyI2C.h"
#include "6050_Reg.h"

#define MPU6050_ADDRESS 0xD0

void MPU6050_WaitEvent(I2C_TypeDef* I2Cx, uint32_t I2C_EVENT){
    uint32_t Timeout;
    Timeout = 10000;

    while(I2C_CheckEvent(I2Cx,I2C_EVENT) !=SUCCESS){
        Timeout--; 
        if(Timeout==0) break;
    };
};

void MPU6050_WriteReg(uint8_t RegAddr,uint8_t Data){
    uint32_t Timeout;
    Timeout = 10000;

    // Start
    I2C_GenerateSTART(I2C2,ENABLE);
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);

    // Send Addr
    I2C_Send7bitAddress(I2C2,MPU6050_ADDRESS,I2C_Direction_Transmitter);
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

    // Send Data
    I2C_SendData(I2C2,RegAddr);
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTING);// EV8: write Byte(no last one)

    I2C_SendData(I2C2,Data);
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED);    // EV8_2 last Byte

    // Stop
    I2C_GenerateSTOP(I2C2,ENABLE);
}

uint8_t MPU6050_ReadReg(uint8_t RegAddr){
    uint8_t Data;

    // Start
    I2C_GenerateSTART(I2C2,ENABLE);
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);

    // Send Addr
    I2C_Send7bitAddress(I2C2,MPU6050_ADDRESS,I2C_Direction_Transmitter);
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED);

    // Send RegAddr
    I2C_SendData(I2C2,RegAddr);
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_TRANSMITTED);   // EV8: write Byte(Last one)

    // Read Reg (Restart & read)
    I2C_GenerateSTART(I2C2,ENABLE);
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_MODE_SELECT);

    I2C_Send7bitAddress(I2C2,MPU6050_ADDRESS,I2C_Direction_Receiver);
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED);

    // Before last byte: set NACK & STOP
    I2C_AcknowledgeConfig(I2C2,DISABLE);    // NACK
    I2C_GenerateSTOP(I2C2,ENABLE);          // STOP
    MPU6050_WaitEvent(I2C2,I2C_EVENT_MASTER_BYTE_RECEIVED);

    Data = I2C_ReceiveData(I2C2);

    I2C_AcknowledgeConfig(I2C2,ENABLE);     // SET ACK

    return Data;
}


void MPU6050_Init(void){
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_AF_OD;
    init.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
    init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB,&init);

    I2C_InitTypeDef i2c_init;
    i2c_init.I2C_Ack = I2C_Ack_Enable;
    i2c_init.I2C_AcknowledgedAddress= I2C_AcknowledgedAddress_7bit;
    i2c_init.I2C_ClockSpeed = 50000;    // 50KHz
    i2c_init.I2C_DutyCycle = I2C_DutyCycle_2;    // Only work in quick-mode (CLK >100KHz)
    i2c_init.I2C_Mode = I2C_Mode_I2C;
    i2c_init.I2C_OwnAddress1 = 0x00;
    I2C_Init(I2C2,&i2c_init);
    I2C_Cmd(I2C2,ENABLE);

    MPU6050_WriteReg(MPU6050_PWR_MGMT_1,0x01);
    MPU6050_WriteReg(MPU6050_PWR_MGMT_2,0x00);
    MPU6050_WriteReg(MPU6050_SMPLRT_DIV,0x09);  // 10 
    MPU6050_WriteReg(MPU6050_CONFIG,0x06);  

    MPU6050_WriteReg(MPU6050_GYRO_CONFIG,0x18);  
    MPU6050_WriteReg(MPU6050_ACCEL_CONFIG,0x18);  
}

uint8_t MPU6050_GetID(void){
    return MPU6050_ReadReg(MPU6050_WHO_AM_I);
}

void MPU6050_GetData(int16_t *AccX,int16_t *AccY,int16_t *AccZ,
                    int16_t *GyroX,int16_t *GyroY,int16_t *GyroZ)
{
    uint8_t DataH,DataL;

    // Case1: Read each one

    DataH = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_XOUT_L);
    *AccX = DataH<<8 | DataL;

    DataH = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_YOUT_L);
    *AccY = DataH<<8 | DataL;

    DataH = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_ACCEL_ZOUT_L);
    *AccZ = DataH<<8 | DataL;

    DataH = MPU6050_ReadReg(MPU6050_GYRO_XOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_GYRO_XOUT_L);
    *GyroX= DataH<<8 | DataL;

    DataH = MPU6050_ReadReg(MPU6050_GYRO_YOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_GYRO_YOUT_L);
    *GyroY= DataH<<8 | DataL;

    DataH = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_H);
    DataL = MPU6050_ReadReg(MPU6050_GYRO_ZOUT_L);
    *GyroZ= DataH<<8 | DataL;
}
