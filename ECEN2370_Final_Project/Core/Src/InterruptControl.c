#include "InterruptControl.h"

void enableIRQ(uint8_t IRQNumber) {

	if(IRQNumber < 32) {

		NVIC->ISER[0] |= (1 << IRQNumber);
	}
};

void disableIRQ(uint8_t IRQNumber) {

	if(IRQNumber < 32) {

		NVIC->ICER[0] |= (1 << IRQNumber);
	}
}

void clearPendingIRQ(uint8_t IRQNumber) {

	if(IRQNumber < 32) {
		NVIC->ICPR[0] = (1 << IRQNumber);
	}
}

void clearPendingEXTI(uint8_t pinNumber) {

	EXTI->PR |= (1 << pinNumber);
}

void clearPendingTIM2() {

	TIM2->SR &= ~(CLEAR_TIM << TIM_UIF_OFFSET);
}
