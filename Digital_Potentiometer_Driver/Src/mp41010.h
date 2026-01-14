/*
 * mp41010.h
 *
 *  Created on: Jan 12, 2026
 *      Author: janec
 */

#ifndef MP41010_H_
#define MP41010_H_

void mcp41010_on(){
	GPIOA-> ODR &= ~(0x1 << 4);
}

void mcp41010_off(){
	GPIOA-> ODR |= (0x1 << 4);
}

void spi_write(uint8_t c){
	while(!(SPI1->SR & SPI_SR_TXE)){;}

	//do przetestowania, wysyłasz (0x11 << 8) | c, wtedy jest od razu komenda i dane
	SPI1->DR = c;
	while((SPI1->SR & SPI_SR_BSY)){;}

}

void mp41010_set_value(uint8_t data){
	spi_write(0x11);//Command line to start sending data
	spi_write(data);
}

#endif /* MP41010_H_ */
