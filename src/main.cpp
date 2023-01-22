#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>

const uint16_t LEDPIN = GPIO_Pin_9;

const uint16_t GPIO_pin_base_address = 0x0100;

GPIO_TypeDef *LEDPORT = GPIOE;

void simple_delay(uint32_t us)
{
	/* simple delay loop */
	while (us--) {
		asm volatile ("nop");
	}
}

void init(){
	/* gpio init struct */
	GPIO_InitTypeDef gpio;
	/* reset rcc */
	RCC_DeInit();
	/* enable clock GPIO */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOE, ENABLE);
	
	int addr = GPIO_pin_base_address;
	for (uint8_t i = 0; i < 8; i++)
	{
		/* use LED pin */
		gpio.GPIO_Pin = addr;
		/* mode: output */
		gpio.GPIO_Mode = GPIO_Mode_OUT;
		/* output type: push-pull */
		gpio.GPIO_OType = GPIO_OType_PP;
		/* apply configuration */
		GPIO_Init(LEDPORT, &gpio);
		
		addr+=addr;
	}
}

int main(void)
{
	init();
	/* main program loop */
	for (;;) {
		int addr = GPIO_pin_base_address;
		for (uint8_t i = 0; i < 8; i++)
		{
			/* set led on */
			GPIO_SetBits(LEDPORT, addr);
			/* delay */
			simple_delay(100000);
			/* clear led */
			GPIO_ResetBits(LEDPORT, addr);
			/* delay */
			simple_delay(100000);

			addr+=addr;	
		}
	}

	/* never reached */
	return 0;
}