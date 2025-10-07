#ifndef HAT_H
#define HAT_H

#include "stm32f446xx.h"

typedef struct{
    GPIO_TypeDef* GPIO_PORTS[3];
    GPIO_TypeDef* PIN_PORTS[8];
    uint8_t PIN_NUMS[8];
}PMOD_t;

typedef enum{
    SERVO1 = 0,
    SERVO2 = 1,
    SERVO3 = 2
}SERVO_t;

extern const PMOD_t PMOD_A;
extern const PMOD_t PMOD_B;
extern const PMOD_t PMOD_C;

void init_gpio(GPIO_TypeDef* GPIOx);
void init_pmod(PMOD_t pmod);


#endif // HAT_H