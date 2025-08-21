/* Author: John D.
 * Date: August 20, 2025
 * Description: Turn on the LED with a Push of Button
 *
 * Where is LED connected?
 * Port A
 * Pin: 5
 *
 *Bus -> Boundary Address -> Peripheral
 *
 *  */

#define PERIPH_BASE ( 0x40000000UL)
#define AHB1_PERIPH_OFFSET  (0x00020000UL)
#define AHB1_PERIPH_BASE	(PERIPH_BASE + AHB1_PERIPH_OFFSET)

#define GPIOA_OFFSET 	(0x0000UL)
#define GPIOA_BASE (AHB1_PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET (0x3800UL)
#define RCC_BASE (AHB1_PERIPH_BASE + RCC_OFFSET) 


#define AHB1EN_R_OFFSET (0x30UL) 
#define RCC_AHB1EN_R  (*(volatile unsigned int *)   (RCC_BASE + AHB1EN_R_OFFSET))

#define MODE_R_OFFSET (0x00UL)
#define GPIOA_MODE_R (*(volatile unsigned int *)   (GPIOA_BASE + MODE_R_OFFSET))


#define OD_R_OFFSET (0x14UL)
#define GPIOA_OD_R  (*(volatile unsigned int *)  (GPIOA_BASE + OD_R_OFFSET))

#define GPIOAEN		(1U << 0) 

#define PIN5 (1U<<5) 
#define LED_PIN PIN5

int main(void)
{
	//1. enable clock access to GPIOA
	//2. set PA5 as output pin
	//
	RCC_AHB1EN_R |= GPIOAEN;

	GPIOA_MODE_R |= (1U<<10) ;//set bit 10 to 1
	GPIOA_MODE_R &=~(1U<<1); //sets 11 to 0  &=~ is invert
	while (1) // infinite loop
	{
		//3. set PA5 HIGH
		//GPIOA_OD_R |= LED_PIN;

		//4. TOGGLE ON AND OFF
		GPIOA_OD_R ^= LED_PIN;
		for (int i=0; i<1e5;i++){}
	}
}