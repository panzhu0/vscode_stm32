#include "stm32f10x.h"
#include "Delay.h"

#define SCL_PORT GPIOB
#define SCL_PIN GPIO_Pin_10
#define SDA_PIN GPIO_Pin_11

void MyI2C_W_SCL(uint8_t BitVal){
    GPIO_WriteBit(SCL_PORT,SCL_PIN,(BitAction)BitVal);
    Delay_us(10);
}

void MyI2C_W_SDA(uint8_t BitVal){
    GPIO_WriteBit(SCL_PORT,SDA_PIN,(BitAction)BitVal);
}

uint8_t MyI2C_R_SDA(void){
    uint8_t BitVal;
    BitVal = GPIO_ReadInputDataBit(SCL_PORT,SDA_PIN);
    Delay_us(10);
    return BitVal;
}


// Software I2C
void MyI2C_Init(void){
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);

    GPIO_InitTypeDef init;
    init.GPIO_Mode = GPIO_Mode_Out_OD;
    init.GPIO_Pin = SCL_PIN | SDA_PIN;
    init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(SCL_PORT,&init);

    GPIO_SetBits(SCL_PORT,SCL_PIN| SDA_PIN);
}



void MyI2C_Start(void){
    MyI2C_W_SDA(1);
    MyI2C_W_SCL(1);
    MyI2C_W_SDA(0);
    MyI2C_W_SCL(0);
}

void MyI2C_Stop(void){
    MyI2C_W_SDA(0);
    MyI2C_W_SCL(1);
    MyI2C_W_SDA(1);
}

void MyI2C_SendByte(uint8_t Byte){
    uint8_t i;
    for(i=0;i<8;i++){
        MyI2C_W_SDA(Byte & (0x80 >> i));
        MyI2C_W_SCL(1);
        MyI2C_W_SCL(0);
    }
}

uint8_t MyI2C_RecvByte(void){

    // Wait for slave & receive Data
    uint8_t i,Byte=0x00;

    MyI2C_W_SDA(1);
    for(i=0;i<8;i++){
        MyI2C_W_SCL(1);
        if(MyI2C_R_SDA() == 1) Byte |= (0x80>>i);
        MyI2C_W_SCL(0);
    }

    return Byte;
}

void MyI2C_SendAck(uint8_t AckBit){
    MyI2C_W_SDA(AckBit);    // Master: put ACK
    MyI2C_W_SCL(1);         // Slave: read
    MyI2C_W_SCL(0);         
}

uint8_t MyI2C_RecvAck(void){
    uint8_t AckBit;
    MyI2C_W_SDA(1);         // Master: release 
    MyI2C_W_SCL(1);         // Slave: put ACK
    AckBit = MyI2C_R_SDA(); // Master: read
    MyI2C_W_SCL(0);         
    return AckBit;
}


