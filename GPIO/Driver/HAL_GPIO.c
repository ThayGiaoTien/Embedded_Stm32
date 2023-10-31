#include"HAL_GPIO.h"


uint32_t PINPOS[16] ={0x00, 0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C		// CRL
			, 0x00, 0x04, 0x08, 0x0C, 0x10, 0x14, 0x18, 0x1C};	// CRH


static void config_pin(GPIO_TypeDef* port, uint32_t pinNumber,
		uint32_t modeType)
{
	// Determine pin is on CRH or CRL
	if(pinNumber>=8)
	{
		// CRH
		switch(modeType)
		{
			// Config mode by writng to control register low. 
			case OUTPUT_GEN_PURPOSE | INPUT_ANALOG  :
				port->CRH &= (1<<CNF_POS_BIT2);
				port->CRH |= (1<<CNF_POS_BIT1);
				break;
			case OUTPUT_OD | INPUT_FLOATING  :
				port->CRH &= ((1<<CNF_POS_BIT1)|(1<<CNF_POS_BIT2));
				break;
			case OUTPUT_ALT_FUNCTION | INPUT_PU_PD  :
				port->CRH |= (0x02<<CNF_POS_BIT1);
				break;
			case OUTPUT_ALT_FUNCTION_OD  :
				port->CRH |= (0x03<<CNF_POS_BIT1);
				break;
		}
	}
	else 
	{
		// CRL
		switch(modeType)
		{
			// Config mode by writng to control register low. 
			case OUTPUT_GEN_PURPOSE | INPUT_ANALOG  :
				port->CRL &= (1<<CNF_POS_BIT2);
				port->CRL |= (1<<CNF_POS_BIT1);
				break;
			case OUTPUT_OD | INPUT_FLOATING  :
				port->CRL &= ((1<<CNF_POS_BIT1)|(1<<CNF_POS_BIT2));
				break;
			case OUTPUT_ALT_FUNCTION | INPUT_PU_PD  :
				port->CRL |= (0x02<<CNF_POS_BIT1);
				break;
			case OUTPUT_ALT_FUNCTION_OD  :
				port->CRL |= (0x03<<CNF_POS_BIT1);
				break;
		}
	}
	
}

static void config_pin_speed(GPIO_TypeDef* port, uint32_t pinNumber, uint32_t pinSpeed, uint32_t pinMode)
{
	if(pinNumber>=8)
	{
		// CRH 
		if(pinMode== INPUT_MODE)
		{
			// Reset 2 MODE pins
			port->CRH &= ((1<<PINPOS[pinNumber])| (1<<(PINPOS[pinNumber]+1)));
		}
		else
		{
			// Set speed
			port->CRH |= pinSpeed<<(PINPOS[pinNumber]);
		}
	}
	else
	{
		// CRL
		if(pinMode== INPUT_MODE)
		{
			// Reset 2 MODE pins
			port->CRL &= (1<<PINPOS[pinNumber]| (1<<(PINPOS[pinNumber]+1)));
		}
		else
		{
			// Set speed
			port->CRL |= pinSpeed<<(PINPOS[pinNumber]);
		}
	}
}

void gpio_write(GPIO_TypeDef* port, uint32_t pinNumer, uint32_t state)
{
	if(state)
	{
		// Set bit
		port->BSRR = (1<<pinNumer);
	}
	else 
	{
		// Reset bit
		port->BSRR = (1<<(pinNumer+16));
	}
}

void gpio_toggle(GPIO_TypeDef* port, uint32_t pinNumber)
{
	port->ODR ^= (1<<pinNumber);
}

void gpio_init(GPIO_TYPE gpioType)
{
	// Check the port to initialize clock for it. 
	if(gpioType.port == PORTA) GPIO_CLOCK_ENABLE_PORTA;
	if(gpioType.port == PORTB) GPIO_CLOCK_ENABLE_PORTB;
	if(gpioType.port == PORTC) GPIO_CLOCK_ENABLE_PORTC;
	if(gpioType.port == PORTD) GPIO_CLOCK_ENABLE_PORTD;
	
	// config pin mode
	config_pin(gpioType.port, gpioType.pin, gpioType.mode_type);
	
	// config input mode or speed in output mode
	config_pin_speed(gpioType.port,gpioType.pin, gpioType.speed, gpioType.mode);
	
}


/*=====================INTERRUPT GPIO===================*/
void config_gpio_interrupt(GPIO_TypeDef* port, uint32_t pinNumber, edge_select edge)
{
	// First Enable AFIO clock
	RCC->APB2ENR |=RCC_APB2ENR_AFIOEN;//(1<<0)
	
	// Now checking for the port and pin
	if(port== GPIOA)
	{
		switch(pinNumber)
		{
			case 0:
				AFIO->EXTICR[0]= AFIO_EXTICR1_EXTI0_PA;
				break;
			case 1:
				AFIO->EXTICR[0]= AFIO_EXTICR1_EXTI1_PA;
				break;
			case 2:
				AFIO->EXTICR[0]= AFIO_EXTICR1_EXTI2_PA;
				break;
			case 3:
				AFIO->EXTICR[0]= AFIO_EXTICR1_EXTI3_PA;
				break;
			case 4: 
				AFIO->EXTICR[1]= AFIO_EXTICR2_EXTI4_PA;
				break;
			case 5: 
				AFIO->EXTICR[1]= AFIO_EXTICR2_EXTI5_PA;
				break;
			case 6: 
				AFIO->EXTICR[1]= AFIO_EXTICR2_EXTI6_PA;
				break;
			case 7: 
				AFIO->EXTICR[1]= AFIO_EXTICR2_EXTI7_PA;
				break;
			case 8: 
				AFIO->EXTICR[2]= AFIO_EXTICR3_EXTI8_PA;
				break;
			case 9: 
				AFIO->EXTICR[2]= AFIO_EXTICR3_EXTI9_PA;
				break;
			case 10: 
				AFIO->EXTICR[2]= AFIO_EXTICR3_EXTI10_PA;
				break;
			case 11: 
				AFIO->EXTICR[2]= AFIO_EXTICR3_EXTI11_PA;
				break;
			case 12: 
				AFIO->EXTICR[3]= AFIO_EXTICR4_EXTI12_PA;
				break;
			case 13: 
				AFIO->EXTICR[3]= AFIO_EXTICR4_EXTI13_PA;
				break;
			case 14: 
				AFIO->EXTICR[3]= AFIO_EXTICR4_EXTI14_PA;
				break;
			case 15: 
				AFIO->EXTICR[3]= AFIO_EXTICR4_EXTI15_PA;
				break;
		}
	}
	if(port== GPIOB)
	{
		switch(pinNumber)
		{
			case 0:
				AFIO->EXTICR[0]= AFIO_EXTICR1_EXTI0_PB;
				break;
			case 1:
				AFIO->EXTICR[0]= AFIO_EXTICR1_EXTI1_PB;
				break;
			case 2:
				AFIO->EXTICR[0]= AFIO_EXTICR1_EXTI2_PB;
				break;
			case 3:
				AFIO->EXTICR[0]= AFIO_EXTICR1_EXTI3_PB;
				break;
			case 4: 
				AFIO->EXTICR[1]= AFIO_EXTICR2_EXTI4_PB;
				break;
			case 5: 
				AFIO->EXTICR[1]= AFIO_EXTICR2_EXTI5_PB;
				break;
			case 6: 
				AFIO->EXTICR[1]= AFIO_EXTICR2_EXTI6_PB;
				break;
			case 7: 
				AFIO->EXTICR[1]= AFIO_EXTICR2_EXTI7_PB;
				break;
			case 8: 
				AFIO->EXTICR[2]= AFIO_EXTICR3_EXTI8_PB;
				break;
			case 9: 
				AFIO->EXTICR[2]= AFIO_EXTICR3_EXTI9_PB;
				break;
			case 10: 
				AFIO->EXTICR[2]= AFIO_EXTICR3_EXTI10_PB;
				break;
			case 11: 
				AFIO->EXTICR[2]= AFIO_EXTICR3_EXTI11_PB;
				break;
			case 12: 
				AFIO->EXTICR[3]= AFIO_EXTICR4_EXTI12_PB;
				break;
			case 13: 
				AFIO->EXTICR[3]= AFIO_EXTICR4_EXTI13_PB;
				break;
			case 14: 
				AFIO->EXTICR[3]= AFIO_EXTICR4_EXTI14_PB;
				break;
			case 15: 
				AFIO->EXTICR[3]= AFIO_EXTICR4_EXTI15_PB;
				break;
		}
	}
	if(port== GPIOC)
	{
		switch(pinNumber)
		{
			case 0:
				AFIO->EXTICR[0]= AFIO_EXTICR1_EXTI0_PC;
				break;
			case 1:
				AFIO->EXTICR[0]= AFIO_EXTICR1_EXTI1_PC;
				break;
			case 2:
				AFIO->EXTICR[0]= AFIO_EXTICR1_EXTI2_PC;
				break;
			case 3:
				AFIO->EXTICR[0]= AFIO_EXTICR1_EXTI3_PC;
				break;
			case 4: 
				AFIO->EXTICR[1]= AFIO_EXTICR2_EXTI4_PC;
				break;
			case 5: 
				AFIO->EXTICR[1]= AFIO_EXTICR2_EXTI5_PC;
				break;
			case 6: 
				AFIO->EXTICR[1]= AFIO_EXTICR2_EXTI6_PC;
				break;
			case 7: 
				AFIO->EXTICR[1]= AFIO_EXTICR2_EXTI7_PC;
				break;
			case 8: 
				AFIO->EXTICR[2]= AFIO_EXTICR3_EXTI8_PC;
				break;
			case 9: 
				AFIO->EXTICR[2]= AFIO_EXTICR3_EXTI9_PC;
				break;
			case 10: 
				AFIO->EXTICR[2]= AFIO_EXTICR3_EXTI10_PC;
				break;
			case 11: 
				AFIO->EXTICR[2]= AFIO_EXTICR3_EXTI11_PC;
				break;
			case 12: 
				AFIO->EXTICR[3]= AFIO_EXTICR4_EXTI12_PC;
				break;
			case 13: 
				AFIO->EXTICR[3]= AFIO_EXTICR4_EXTI13_PC;
				break;
			case 14: 
				AFIO->EXTICR[3]= AFIO_EXTICR4_EXTI14_PC;
				break;
			case 15: 
				AFIO->EXTICR[3]= AFIO_EXTICR4_EXTI15_PC;
				break;
		}
	}
	if(port== GPIOD)
	{
		switch(pinNumber)
		{
			case 0:
				AFIO->EXTICR[0]= AFIO_EXTICR1_EXTI0_PD;
				break;
			case 1:
				AFIO->EXTICR[0]= AFIO_EXTICR1_EXTI1_PD;
				break;
			case 2:
				AFIO->EXTICR[0]= AFIO_EXTICR1_EXTI2_PD;
				break;
			case 3:
				AFIO->EXTICR[0]= AFIO_EXTICR1_EXTI3_PD;
				break;
			case 4: 
				AFIO->EXTICR[1]= AFIO_EXTICR2_EXTI4_PD;
				break;
			case 5: 
				AFIO->EXTICR[1]= AFIO_EXTICR2_EXTI5_PD;
				break;
			case 6: 
				AFIO->EXTICR[1]= AFIO_EXTICR2_EXTI6_PD;
				break;
			case 7: 
				AFIO->EXTICR[1]= AFIO_EXTICR2_EXTI7_PD;
				break;
			case 8: 
				AFIO->EXTICR[2]= AFIO_EXTICR3_EXTI8_PD;
				break;
			case 9: 
				AFIO->EXTICR[2]= AFIO_EXTICR3_EXTI9_PD;
				break;
			case 10: 
				AFIO->EXTICR[2]= AFIO_EXTICR3_EXTI10_PD;
				break;
			case 11: 
				AFIO->EXTICR[2]= AFIO_EXTICR3_EXTI11_PD;
				break;
			case 12: 
				AFIO->EXTICR[3]= AFIO_EXTICR4_EXTI12_PD;
				break;
			case 13: 
				AFIO->EXTICR[3]= AFIO_EXTICR4_EXTI13_PD;
				break;
			case 14: 
				AFIO->EXTICR[3]= AFIO_EXTICR4_EXTI14_PD;
				break;
			case 15: 
				AFIO->EXTICR[3]= AFIO_EXTICR4_EXTI15_PD;
				break;
		}
	}
		
	// Detect edge mode 
	if(edge== RISING_EDGE)
		EXTI->RTSR|=(1<<pinNumber);
	if(edge==FALLING_EDGE)
		EXTI->FTSR |= (1<<pinNumber);
	if(edge==RISING_FALLING_EDGE)
	{
		EXTI->RTSR|=(1<<pinNumber);
		EXTI->FTSR |= (1<<pinNumber);
	}
	
	// Enable AFIO clock
	
	RCC->APB2ENR |= (1<<0);
}

void enable_gpio_interrupt(uint32_t pinNumber, IRQn_Type irqNumber)
{
	// Enable interrupt mask regiser
	EXTI->IMR |= (1<<pinNumber);
	// enable interrupt in NVIC
	NVIC_EnableIRQ(irqNumber);
}

void clear_gpio_interrupt(uint32_t pinNumber)
{
	EXTI->PR |= (1<<pinNumber);
}
