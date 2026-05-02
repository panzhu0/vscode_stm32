#include "stm32f10x.h"
#include "OLED.h"
#include "Serial.h"

int main(void){
    OLED_Init();
    Serial_Init();
    // Byte
    // Serial_SendBy('a');

    // Array
    // uint8_t MyArray[] = {0x41,0x42,'c','d'};
    // Serial_SendArray(MyArray,4);

    // Str
    // Serial_SendString("Hello world! \r\n \r\n Ni Hao!");

    // Num
    Serial_SendNum(12345,5);

    while (1){};
}
