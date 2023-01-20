#include <stm32f30x_gpio.h>
#include <stm32f30x_rcc.h>

const uint16_t LEDPIN = GPIO_Pin_9;

const uint16_t leds_pins[] = {
	GPIO_Pin_8,
	GPIO_Pin_9,
	GPIO_Pin_10,
	GPIO_Pin_11,
	GPIO_Pin_12,
	GPIO_Pin_13,
	GPIO_Pin_14,
	GPIO_Pin_15
};

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

	for (uint8_t i = 0; i < sizeof(leds_pins)/sizeof(uint16_t); ++i)
	{
		/* use LED pin */
		gpio.GPIO_Pin = leds_pins[i];
		/* mode: output */
		gpio.GPIO_Mode = GPIO_Mode_OUT;
		/* output type: push-pull */
		gpio.GPIO_OType = GPIO_OType_PP;
		/* apply configuration */
		GPIO_Init(LEDPORT, &gpio);
	}
}

int main(void)
{
	init();
	/* main program loop */
	for (;;) {
		for (uint8_t i = 0; i < sizeof(leds_pins)/sizeof(uint16_t); ++i)
		{
			/* set led on */
			GPIO_SetBits(LEDPORT, leds_pins[i]);
			/* delay */
			simple_delay(100000);
			/* clear led */
			GPIO_ResetBits(LEDPORT, leds_pins[i]);
			/* delay */
			simple_delay(100000);	
		}
	}

	/* never reached */
	return 0;
}