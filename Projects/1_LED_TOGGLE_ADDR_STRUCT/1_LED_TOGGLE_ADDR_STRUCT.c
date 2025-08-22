/* Author: John D.
 * Date: August 20, 2025
 * Description: Turn on the LED with a Push of Button, but this time with structures
 *
 * Where is LED connected?
 * Port A
 * Pin: 5

 *  */
#include <stdint.h>
#define PERIPH_BASE ( 0x40000000UL) // unsigned length
#define AHB1_PERIPH_OFFSET  (0x00020000UL)
#define AHB1_PERIPH_BASE	(PERIPH_BASE + AHB1_PERIPH_OFFSET)

#define GPIOA_OFFSET 	(0x0000UL)
#define GPIOA_BASE (AHB1_PERIPH_BASE + GPIOA_OFFSET)

#define RCC_OFFSET (0x3800UL)
#define RCC_BASE (AHB1_PERIPH_BASE + RCC_OFFSET) // we need RCC to enable clock access GPIO A, we need pin 5 for GPIO A


#define AHB1EN_R_OFFSET (0x30UL) // enable R offset
#define RCC_AHB1EN_R  (*(volatile unsigned int *)   (RCC_BASE + AHB1EN_R_OFFSET))

#define MODE_R_OFFSET (0x00UL)
#define GPIOA_MODE_R (*(volatile unsigned int *)   (GPIOA_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET (0x14UL)
#define GPIOA_OD_R  (*(volatile unsigned int *)  (GPIOA_BASE + OD_R_OFFSET))

#define GPIOAEN		(1U << 0) // SHIFT 1 TO position 1

#define PIN5 (1U<<5) // set 5 to 1
#define LED_PIN PIN5

#define __IO volatile // this is new,



//typedef struct
//{
//
//}GPIO_TypeDef;


//typedef struct
//{
//	__IO uint32_t MODER; // GPIO port mode register
////	__IO uint32_t  OTYPER; //output type register
////	__IO uint32_t OSPEEDR; //output speed register
////	__IO uint32_t PUPDR;//  pull up pull down register
////	__IO uint32_t IDR; // input data register
//	uint32_t DUMMY[4] //array of four 32bit type data bits, doing so, can delete the commented above
//	__IO uint32_t ODR; //output data register
//};

//now
typedef struct
{
	volatile uint32_t MODER;
	volatile uint32_t DUMMY[4];
	volatile uint32_t ODR;
} GPIO_TypeDef;;
// now RCC registe, for RCC we only need AHB1 Enable Register, so you can delete everything after AHB1ENR;

typedef struct
{
	volatile uint32_t DUMMY[12];
	volatile uint32_t AHB1ENR;
	// everything after is deleted because you'll never reach past this, unless you need the registers
} RCC_TypeDef;

#define RCC		((RCC_TypeDef*) RCC_BASE) // these are called type cast
#define GPIOA ((GPIO_TypeDef*) GPIOA_BASE)
int main(void)
{

//	RCC_AHB1EN_R |= GPIOAEN;
	RCC->AHB1ENR |= GPIOAEN; // arrow operator

//	GPIOA_MODE_R |= (1U<<10) ;
//	GPIOA_MODE_R &=~(1U<<1);

	GPIOA->MODER |= (1U<<10); //set bit 10 to 1
	GPIOA->MODER &=~ (1U<<11); //set bit 11 to 0
	while (1)
	{
//		GPIOA_OD_R ^= LED_PIN;
		GPIOA->ODR ^= LED_PIN;
		for (int i=0; i<1e5;i++){}
	}
}
