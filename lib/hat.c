#include "hat.h"

const PMOD_t PMODA = {
    .GPIO_PORTS = {GPIOA, GPIOB, GPIOC, 0},
    .PIN_PORTS = {GPIOC, GPIOB, GPIOA, GPIOA, GPIOB, GPIOA, GPIOA, GPIOA},
    .PIN_NUMS = {7, 12, 11, 12, 6, 7, 6, 5},
};
const PMOD_t PMODB = {
    .GPIO_PORTS = {GPIOA, GPIOB, GPIOC, GPIOD},
    .PIN_PORTS = {GPIOA, GPIOA, GPIOC, GPIOC, GPIOA, GPIOB, GPIOD, GPIOC},
    .PIN_NUMS = {1, 15, 12, 10, 0, 7, 2, 11}
};
const PMOD_t PMODC = {
    .GPIO_PORTS = {GPIOC, 0, 0, 0},
    .PIN_PORTS = {GPIOC, GPIOC, GPIOC, GPIOC},
    .PIN_NUMS = {0, 1, 2, 3, 0xFF, 0xFF, 0xFF, 0xFF}
};

void init_gpio(GPIO_TypeDef* GPIOx){
    switch((unsigned int)GPIOx){
        case (unsigned int)GPIOA:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
            break;
        case (unsigned int)GPIOB:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
            break;
        case (unsigned int)GPIOC:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
            break;
        case (unsigned int)GPIOD:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
            break;
        case (unsigned int)GPIOE:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
            break;
        case (unsigned int)GPIOF:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
            break;
        case (unsigned int)GPIOG:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
            break;
        default:
    }
    return;
}
void init_pmod(PMOD_t pmod){
    for(int i = 0; i < 4; i++){
        if(pmod.GPIO_PORTS[i] != 0){
            init_gpio(pmod.GPIO_PORTS[i]);
        }else{
            break;
        }
    }
}