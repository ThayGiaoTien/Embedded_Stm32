#ifndef _HAL_GPIO
#define _HAL_GPIO

/*First thing to do with the header file is define it to macro
#ifndef _HAL_GPIO
#define _HAL_GPIO
….
….
#endif
*/
#include"stm32f10x.h"

//Redefine PORT
#define PORTA GPIOA
#define PORTB GPIOB
#define PORTC GPIOC
#define PORTD GPIOD

//Define MODE  
#define INPUT_MODE ((uint32_t)0x00)
#define OUTPUT_MODE ((uint32_t)0x01)

//Define CNF accordingly
#define INPUT_ANALOG  	((uint32_t)0X00)
#define INPUT_FLOATING	 ((uint32_t)0X01)
#define INPUT_PU_PD		 ((uint32_t)0X02)

#define OUTPUT_GEN_PURPOSE 	((uint32_t)0X00)
#define OUTPUT_OD			 ((uint32_t)0X01)
#define OUTPUT_ALT_FUNCTION 	((uint32_t)0X02)
#define OUTPUT_ALT_FUNCTION_OD	 ((uint32_t)0X03)

//Define speed/slew rate	
#define SPEED_2MHZ ((uint32_t)0x02)
#define SPEED_10MHZ ((uint32_t)0x01)
#define SPEED_50MHZ ((uint32_t)0x03)

//Define clock enabling.
#define GPIO_CLOCK_ENABLE_ALT_FUNC (RCC->APB2ENR |= (1<<0))
#define GPIO_CLOCK_ENABLE_PORTA (RCC->APB2ENR |= (1<<2))
#define GPIO_CLOCK_ENABLE_PORTB (RCC->APB2ENR |= (1<<3))
#define GPIO_CLOCK_ENABLE_PORTC (RCC->APB2ENR |= (1<<4))
#define GPIO_CLOCK_ENABLE_PORTD	(RCC->APB2ENR |= (1<<5))


//Create arr PINPOS[16] to get to the first bit in MODE 0x00, 0x04, 0x04, 0x0C… 
uint32_t PINPOS[16];

//So to get  to the first bit it CNF, we just need to shift left by 2(<<2). 
#define CNF_POS_BIT1 (PINPOS[pinNumber]+2)
#define CNF_POS_BIT2 (PINPOS[pinNumber]+3)

//Define a structure to send all of our setting to  some function we are going 
//to write later on. Struct GPIO_TYPE will include port, pin, mode, mode_type, pull, speed, alt_func.

typedef struct {
	GPIO_TypeDef* port;
	uint32_t pin;
	uint32_t mode; 
	uint32_t mode_type;
	uint32_t pull;
	uint32_t speed;
	uint32_t alt_func;
} GPIO_TYPE;


/*====================CONFIGURATION GPIO================*/
// Setting CNF mode type for GPIO pin
static void config_pin(GPIO_TypeDef* port, uint32_t pinNumber,
		uint32_t modeType);
// Setting input mode or output mode 	at given speed
static void config_pin_speed(GPIO_TypeDef* port, uint32_t pinNumber,
		uint32_t pinSpeed, uint32_t pinMode);

/*=======================GPIO_USER_PIN_FUNCTION=========================*/
// Write state to pin using BSSR. 0-LOW, 1-HIGH.
void gpio_write(GPIO_TypeDef* port, uint32_t pinNumer, uint32_t state);
// Toggle^ state of GPIO pin using ODR .
void gpio_toggle(GPIO_TypeDef* port, uint32_t pinNumber);

// GPIO initialize function( which take GPIO_TYPE struct as input params)
void gpio_init(GPIO_TYPE gpioType);

#endif
