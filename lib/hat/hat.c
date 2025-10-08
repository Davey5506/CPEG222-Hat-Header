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

SSD_t SSD = {
    .GPIO_PORTS = {GPIOA, GPIOB, GPIOC},
    .DATA_PIN_PORTS = {GPIOB, GPIOB, GPIOB, GPIOB, GPIOA, GPIOA, GPIOB, GPIOB},
    .DATA_PINs = {4, 14, 5, 13, 10, 9, 1, 10},
    .SELECT_PIN_PORTS = {GPIOC, GPIOB, GPIOA, GPIOB},
    .SELECT_PINs = {4, 2, 8, 15},
    .ACTIVE_DIGIT = 0b0001
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
            break;
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

void set_pin_mode(GPIO_TypeDef* GPIOx, uint8_t pin, PIN_MODE mode){
    GPIOx->MODER &= ~(0x3 << (pin * 2));
    GPIOx->MODER |= (mode << (pin * 2));
    return;
}

void set_pin_pull(GPIO_TypeDef* GPIOx, uint8_t pin, PIN_PULL pull){
    GPIOx->PUPDR &= ~(0x3 << (pin * 2));
    GPIOx->PUPDR |= (pull << (pin * 2));
    return;
}

void set_output_type(GPIO_TypeDef* GPIOx, uint8_t pin, PIN_OUTPUT_TYPE type){
    GPIOx->OTYPER &= ~(0x1 << pin);
    GPIOx->OTYPER |= (type << pin);
    return;
}

void write_pin(GPIO_TypeDef* GPIOx, uint8_t pin, PIN_VALUE value){
    GPIOx->ODR &= ~(0x1 << pin);
    GPIOx->ODR |= (value << pin);
    return;
}

uint8_t read_pin(GPIO_TypeDef* GPIOx, uint8_t pin){
    return (GPIOx->IDR >> pin) & 0x1;
}

void init_ssd(uint16_t num, uint16_t reload_time){
    for(int i = 0; i < 3; i++){
        init_gpio(SSD.GPIO_PORTS[i]);
    }
    for(int i = 0; i < 8; i++){
        set_pin_mode(SSD.DATA_PIN_PORTS[i], SSD.DATA_PINs[i], OUTPUT);
    }
    for(int i = 0; i < 4; i++){
        set_pin_mode(SSD.SELECT_PIN_PORTS[i], SSD.SELECT_PINs[i], OUTPUT);
    }

    RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
    TIM7->DIER |= TIM_DIER_UIE;
    TIM7->PSC = SYSTEM_FREQ / (160000 - 1);
    TIM7->ARR = reload_time;
    NVIC_EnableIRQ(TIM7_IRQn);
    NVIC_SetPriority(TIM7_IRQn, 20); 
    TIM7->CR1 |= TIM_CR1_CEN;
}

// ISRs
void TIM7_IRQHandler(void){
    TIM7->SR &= ~TIM_SR_UIF;
    SSD.ACTIVE_DIGIT = (SSD.ACTIVE_DIGIT << 1) > 0x8 ? 0b0001 : SSD.ACTIVE_DIGIT << 1;
}