#ifndef HAT_H
#define HAT_H

#include "stm32f446xx.h"

typedef struct{
    GPIO_TypeDef* GPIO_PORTS[4];
    GPIO_TypeDef* PIN_PORTS[8];
    uint8_t PIN_NUMS[8];
}PMOD_t;

typedef enum{
    INPUT = 0U,
    OUTPUT = 1U,
    AF = 2U,
    ANALOG = 3U
}PIN_MODE;

typedef enum{
    NO_PULL = 0U,
    PULL_UP = 1U,
    PULL_DOWN = 2U
}PIN_PULL;

typedef enum{
    PUSH_PULL = 0U,
    OPEN_DRAIN = 1U
}PIN_OUTPUT_TYPE;

typedef enum{
    LOW = 0U,
    HIGH = 1U
}PIN_VALUE;

extern const PMOD_t PMOD_A;
extern const PMOD_t PMOD_B;
extern const PMOD_t PMOD_C;

void init_gpio(GPIO_TypeDef* GPIOx);
void init_pmod(PMOD_t pmod);
void set_pin_mode(GPIO_TypeDef* GPIOx, uint8_t pin, PIN_MODE mode);
void set_pin_pull(GPIO_TypeDef* GPIOx, uint8_t pin, PIN_PULL pull);
void set_output_type(GPIO_TypeDef* GPIOx, uint8_t pin, PIN_OUTPUT_TYPE type);
void write_pin(GPIO_TypeDef* GPIOx, uint8_t pin, PIN_VALUE value);
uint8_t read_pin(GPIO_TypeDef* GPIOx, uint8_t pin);

#endif //HAT_H