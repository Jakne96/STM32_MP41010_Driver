/***************************************************************************//**

*
*******************************************************************************/
#include "stm32f4xx.h"

#include "mp41010.h"
#define DELAY_COUNT    ( 830000 )   /* delay count */
/***************************************************************************//**
  \details  Providing Delay by running empty for loop
  \return   void
  \retval   none
*******************************************************************************/
static void delay( void )
{
    uint32_t i = 0;
    for( i=0; i<=DELAY_COUNT; i++ );
}

void spi_init(){
	//Clock enable for GPIOA
		RCC->AHB1ENR |= (0x1 << 0); //Albo (RCC_AHB1ENR_GPIOAEN);
		//Clock enable for SPI1 i to jest AF05 jak coś
		RCC->APB2ENR |= (0x1 << 12);

		//Pin setup w alternate mode PA5 PA6 PA7
		GPIOA->MODER &= ~((0x3 << 2*4)|
				(0x3 << 2*5)|
				(0x3 << 2*6)|
				(0x3 << 2*7));
		GPIOA->MODER |= (0x1 << 2*4) |
				(0x2 << 2*5) |
				(0x2 << 2*6) |
				(0x2 << 2*7);
		GPIOA->AFR[0] &= ~((0xF << 4*5)|
				(0xF << 4*6)|
				(0xF << 4*7));
		GPIOA->AFR[0] |= (0x5 << 4*5)|
				(0x5 << 4*6)|
				(0x5 << 4*7);


	SPI1->CR1 &= ~((0x1 << 11)|
				(0x1 << 1)|
				(0x1 << 0)|
				(0x7 << 3)|
				(0X1 << 7)|
				(0X1 << 8)|
				(0X1 << 9)|
				(0X1 << 2)|
				(0X1 << 6));

		SPI1->CR1 |= (0x0 << 11)|
				(0x0 << 1)|
				(0x0 << 0)|
				(0x0 << 3)|
				(0x0 << 7)|
				(0x1 << 8)|
				(0x1 << 9)|
				(0x1 << 2)|
				(0x1 << 6);
}

int main(void)
{

	spi_init();

  /* Endless loop */

  while(1)
  {
	  for(uint8_t i = 0; i < 128; i++){

	  mcp41010_on();
	  mp41010_set_value(i);
	  mcp41010_off();
	  delay();
	  }
  }
}

/*
 * TODO: Zrobić funkcje SPI init
 * Zrobić funkcje GPIO init DONE
 * W spi write, dodać na początku spi_write(0x11), czyli komende żeby ustawić nową wartość DONE
 * Można pomyśleć też o shutdown, można ale czy trzeba?
 * też to że __nazwa_potencjometru write, on, off i może shutdown z tą komendą
 * Dodać tutaj PWM i np sterowanie diodą albo czymś innym
 *
 */
