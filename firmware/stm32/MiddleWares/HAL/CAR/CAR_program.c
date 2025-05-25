#include "CAR_interface.h"
#include "../../MCAL/TIMR/TIM_interface.h"
#include "../../MCAL/GPIO/GPIO_interface.h"

TIM_TypeDef *TimxLeft_global;
TIM_TypeDef *TimxRight_global;
uint8_t ChannelLeft_global;
uint8_t ChannelRight_global;
GPIO_TypeDef *DirPin1_global;
GPIO_TypeDef *DirPin2_global;
uint8_t Dir1pinNumber_global;
uint8_t Dir2pinNumber_global;

void CAR_init(TIM_TypeDef *TimxLeft ,uint8_t ChannelLeft, float FrequencyLeft ,GPIO_TypeDef *DirPin1,uint8_t Dir1pinNumber,TIM_TypeDef *TimxRight ,uint8_t ChannelRight, float FrequencyRight, GPIO_TypeDef *DirPin2,uint8_t Dir2pinNumber) {
    DirPin1_global = DirPin1;
    DirPin2_global = DirPin2;
    Dir1pinNumber_global= Dir1pinNumber;
    Dir2pinNumber_global=Dir2pinNumber;
    GPIO_pinMode(DirPin1,Dir1pinNumber,OUTPUT);
    GPIO_pinMode(DirPin2,Dir2pinNumber,OUTPUT);
    TimxLeft_global = TimxLeft;
    TimxRight_global = TimxRight;
    ChannelLeft_global = ChannelLeft;
    ChannelRight_global= ChannelRight;
    TIM_initPWM(TimxLeft, ChannelLeft , FrequencyLeft);
    TIM_initPWM(TimxRight , ChannelRight , FrequencyRight);


}
void CAR_forward(float Speed){
    TIM_writePWM(TimxRight_global , ChannelRight_global , Speed);
    TIM_writePWM(TimxLeft_global , ChannelLeft_global , Speed);
    GPIO_digitalWrite(DirPin1_global,Dir1pinNumber_global,HIGH);
    GPIO_digitalWrite(DirPin2_global,Dir2pinNumber_global,LOW);



}
void CAR_backwards(float Speed){
    TIM_writePWM(TimxRight_global , ChannelRight_global , Speed);
    TIM_writePWM(TimxLeft_global , ChannelLeft_global , Speed);
    GPIO_digitalWrite(DirPin1_global,Dir1pinNumber_global,LOW);
    GPIO_digitalWrite(DirPin2_global,Dir2pinNumber_global,HIGH);
}
void CAR_right(float Speed){
    TIM_writePWM(TimxRight_global , ChannelRight_global , 0);
    TIM_writePWM(TimxLeft_global , ChannelLeft_global , Speed);
    GPIO_digitalWrite(DirPin1_global,Dir1pinNumber_global,HIGH);
    GPIO_digitalWrite(DirPin2_global,Dir2pinNumber_global,LOW);

}
void CAR_left(float Speed){
    TIM_writePWM(TimxRight_global , ChannelRight_global , Speed);
    TIM_writePWM(TimxLeft_global , ChannelLeft_global , 0);
    GPIO_digitalWrite(DirPin1_global,Dir1pinNumber_global,HIGH);
    GPIO_digitalWrite(DirPin2_global,Dir2pinNumber_global,LOW);

}
void CAR_stop(){
    TIM_writePWM(TimxRight_global , ChannelRight_global , 0);
    TIM_writePWM(TimxLeft_global , ChannelLeft_global , 0);
}
