/*
 * Note.cpp
 *
 *  Created on: 22 Sep 2016
 *      Author: 100647740
 *
 *  Code to Initialise the Pins for FTM and Ground and code
 *  for the appropriate FTM channel Interrupt Handler and for
 *  the setNotePeriod function.
 */

#include <stdio.h>
#include "system.h"
#include "derivative.h"
#include "utilities.h"
#include "Delay.h"

#define SYSTEM_CLOCK_FREQUENCY 	(48000000UL)
// Choice of prescale value (FTM1_SC.PS)
#define FTM1_PRESCALE_MASK 		(0)
#define FTM1_PRESCALE_VALUE 	(1<<FTM1_PRESCALE_MASK)
#define FTM1_CLK_FREQUENCY 		(SYSTEM_CLOCK_FREQUENCY/FTM1_PRESCALE_VALUE)
#define ONE_MICROSECOND 		(FTM1_CLK_FREQUENCY/1000000)

// Choice of FTM Channel
#define FTM_CHANNEL_NUM (1)

#define FTM_PIN_NUM 	(13)
#define FTM_FN 			(3)
#define GND_NUM 		(10)
#define GND_FN 			(1<<GND_NUM)
#define GPIO_FN 		(1)

static uint16_t half_period;

/**
* Initialise the note playing system before first use
* This Configures the two pins being used for the FTM
* and Ground. PTA13 as FTM, PTC10 as Ground (Low).
* Also enables the FTM1 interrupts in NVIC.
*/
void initialiseNotes(){
	//Turn clock on for ports A and C
	SIM->SCGC5 |= SIM_SCGC5_PORTA_MASK;
	SIM->SCGC5 |= SIM_SCGC5_PORTC_MASK;
	//Setup pins
	PORTA->PCR[FTM_PIN_NUM] = PORT_PCR_MUX(FTM_FN)|PORT_PCR_DSE_MASK;
	PORTC->PCR[GND_NUM] = PORT_PCR_MUX(GPIO_FN)|PORT_PCR_DSE_MASK|PORT_PCR_PE_MASK|PORT_PCR_PS_MASK;
	//Set PTC10 to ground
	GPIOC->PDDR |= GND_FN;
	GPIOC->PCOR = GND_FN;
	// Enable clock to FTM
	SIM->SCGC6|= SIM_SCGC6_FTM1_MASK;
	// Common registers
	FTM1->SC= FTM_SC_CLKS(0);
	FTM1->CNTIN= 0;
	FTM1->CNT= 0;
	FTM1->MOD= 0xFFFF;
	// Channel registers -OC-Toggle
	FTM1->CONTROLS[FTM_CHANNEL_NUM].CnSC=
	FTM_CnSC_CHIE_MASK|FTM_CnSC_MS(1)|FTM_CnSC_ELS(1);
	FTM1->CONTROLS[FTM_CHANNEL_NUM].CnV=
	FTM1->CNT + 100; // trigger at now+100
	FTM1->SC= FTM_SC_CLKS(1)|FTM_SC_PS(FTM1_PRESCALE_MASK);
	// Enable FTM1 interrupts in NVIC
	NVIC_EnableIRQ(FTM1_IRQn);
}

/**
 * FTM channel 1 Interrupt Handler.
 * This checks if the Interrupt is from the correct channel,
 * clears the interrupt flag and sets the interrupt to
 * re-trigger at T + half period.
 */
void FTM1_IRQHandler(void){
	// The pin is toggled by hardware
	if((FTM1->CONTROLS[FTM_CHANNEL_NUM].CnSC& FTM_CnSC_CHF_MASK) != 0) {
	// Clear the interrupt request from FTM1.Ch0
	FTM1->CONTROLS[FTM_CHANNEL_NUM].CnSC=
	FTM_CnSC_CHIE_MASK|FTM_CnSC_MS(1)|FTM_CnSC_ELS(1);
	// Re-trigger at T+halfPeriod
	FTM1->CONTROLS[FTM_CHANNEL_NUM].CnV += half_period;
	}

	if(FTM1->STATUS != 0) {
	// Unhandled interrupt -die here for debug
	__asm__("bkpt");
	}
}

/**
* Changes the period of the current note being played
*
* @param period - Period of note in timer 'ticks'
*
* @note This function returns immediately.
* This function just halves the period supplied.
* The note is played by interrupt driven code.
*/
void setNotePeriod(uint16_t period){
	//Calculate the Half Period of the supplied Period.
	half_period = period/2;
}
