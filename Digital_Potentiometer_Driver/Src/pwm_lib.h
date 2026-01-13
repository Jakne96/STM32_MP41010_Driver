#ifndef PWM_LIB_H_
#define PWM_LIB_H_

/*
 * This sets PWM on the PB04 pin on STMF401RE nucleo board
 * It uses TIM3_CH1
 */
void pwm_init(){
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;

	GPIOB->MODER &= ~(0x3 << 2*4);
	GPIOB->MODER |= (0x2 << 2*4);

	GPIOB->AFR[0] &= ~(0xF << 4*4);
	GPIOB->AFR[0] |= (0x2 << 4*4);

	TIM3->PSC = 15;
	TIM3->ARR = 2000;
	TIM3->CNT = 0;
	TIM3->CCR1 = 0;
	TIM3->CCMR1 |= (0x1 << 3)|
			(0x6 << 4);
	TIM3->CCER |= (0x1 << 0);
	//TIM3->DIER |= (1 << 0) ;
	//NVIC_SetPriority(TIM3_IRQn,1);
	//NVIC_EnableIRQ(TIM3_IRQn);
	TIM3->CR1 |= 1;
}

void pwm_set(int filling){
	TIM3->CCR1 = filling;
}

#endif /* MP41010_H_ */
