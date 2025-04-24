#include "Timer_Driver.h"

void initializeTimer(GPTIMR_RegDef_t* timer, GPTimer_Config_t config) {

	timerClockControl(timer, ENABLE);

	uint32_t temp;

	temp = config.clockDivisionSelection;
	timer->CR1 &= ~(0x3 << CLOCK_DIVISION_CR1_OFFSET);
	timer->CR1 |= (temp << CLOCK_DIVISION_CR1_OFFSET);

	temp = config.centerAlignModeSelection;
	timer->CR1 &= ~(0x3 << CENTER_ALIGNED_CR1_OFFSET);
	timer->CR1 |= (temp << CENTER_ALIGNED_CR1_OFFSET);

	temp = config.timerCountDownEnable;
	timer->CR1 &= ~(0x1 << TIM_COUNT_DIRECTION_CR1_OFFSET);
	timer->CR1 |= (temp << TIM_COUNT_DIRECTION_CR1_OFFSET);

	temp = config.autoReloadBufferEnable;
	timer->CR1 &= ~(0x1 << TIM_ARR_BUFFER_CR1_OFFSET);
	timer->CR1 |= (temp << TIM_ARR_BUFFER_CR1_OFFSET);

	temp = config.onePulseModeEnable;
	timer->CR1 &= ~(0x1 << ONE_PULSE_MODE_CR1_OFFSET);
	timer->CR1 |= (temp << ONE_PULSE_MODE_CR1_OFFSET);

	temp = config.updateDisable;
	timer->CR1 &= ~(0x1 << TIM_UPDATE_DISABLE_CR1_OFFSET);
	timer->CR1 |= (temp << TIM_UPDATE_DISABLE_CR1_OFFSET);

	temp = config.interruptUpdateEnable;
	timer->DIER &= ~(0x1 << TIM_UPDATE_INTERRUPTS_DIER_OFFSET);
	timer->DIER |= (temp << TIM_UPDATE_INTERRUPTS_DIER_OFFSET);

	timer->PSC &= (0x0);
	timer->PSC |= (config.prescalerValue);

	timer->ARR &= (0x0);
	timer->ARR |= (config.autoReloadValue);

	if(config.interruptUpdateEnable) {
		setTimerInterrupt(timer, ENABLE);
	}

	else {
		setTimerInterrupt(timer, DISABLE);
	}

}


void timerClockControl(GPTIMR_RegDef_t* timer, uint8_t valueToWrite) {

	uint16_t timerNum = timerReturnNum(timer);

	switch(timerNum) {

		case TIM2_TIMER_NUM:

			if(valueToWrite == ENABLE) {

				TIMx_CLK_ENABLE(TIM2_APB1ENR_BIT_OFFSET);
			}

			else if(valueToWrite == DISABLE) {

				TIMx_CLK_DISABLE(TIM2_APB1ENR_BIT_OFFSET);
			}

			break;
	}
}

void startTimer(GPTIMR_RegDef_t* timer) {

	timer->CR1 |= (ENABLE << COUNTER_ENABLE_CR1_OFFSET);

}

void stopTimer(GPTIMR_RegDef_t* timer) {

	timer->CR1 &= ~(ENABLE << COUNTER_ENABLE_CR1_OFFSET);

}

void resetTimer(GPTIMR_RegDef_t* timer) {

	timer->CNT &= 0;
}

void setTimerInterrupt(GPTIMR_RegDef_t* timer, uint8_t valueToWrite) {

	uint16_t timerNum = timerReturnNum(timer);

	switch(timerNum) {

		case TIM2_TIMER_NUM:

			if(valueToWrite == ENABLE) {

				enableIRQ(TIM2_IRQ_NUM);
			}

			else if(valueToWrite == DISABLE) {

				disableIRQ(TIM2_IRQ_NUM);
			}

			break;
	}
}

void setTimerARR(GPTIMR_RegDef_t* timer, uint32_t newARRValue) {

	timer->ARR = newARRValue;
}

void setTimerCount(GPTIMR_RegDef_t* timer, uint32_t newCountValue) {

	timer->CNT = newCountValue;
}

uint16_t timerReturnNum(GPTIMR_RegDef_t* timer) {

	if(timer == TIM2) {

		return TIM2_TIMER_NUM;
	}

	else {

		return -1;
	}
}

uint32_t returnTimerARR(GPTIMR_RegDef_t* timer) {

	return timer->ARR;
}

uint32_t returnTimerValue(GPTIMR_RegDef_t* timer) {

	return timer->CNT;
}
