 /*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_adc.c
** Last modified Date:  20184-12-30
** Last Version:        V1.00
** Descriptions:        functions to manage A/D interrupts
** Correlated files:    adc.h
**--------------------------------------------------------------------------------------------------------       
*********************************************************************************************************/

#include "lpc17xx.h"
#include "adc.h"
#include "../timer/timer.h"
#include "../GLCD/GLCD.h"
#include "../CollisionManager.h"

/*----------------------------------------------------------------------------
  A/D IRQ: Executed when A/D Conversion is ready (signal from ADC peripheral)
 *----------------------------------------------------------------------------*/

unsigned short AD_current;   
unsigned short AD_last = 0xFF;     /* Last converted value               */

volatile uint16_t start_position; 
extern Rect paddle;
extern Rect l_paddle;
extern Rect r_paddle;
extern Rect top_l_paddle;
extern Rect top_r_paddle;

void ADC_IRQHandler(void) {
	
	static uint16_t lastThree[3] = {0,0,0};
	static int index = 0;
	NVIC_DisableIRQ(ADC_IRQn);
	
	AD_current = ((LPC_ADC->ADGDR>>4) & 0xFFF);/* Read Conversion Result */
	start_position= AD_current*196/0xFFF + 5; 
	
	lastThree[index] = start_position;
	index++;
	index = index % 3;
	
  if(lastThree[0] == lastThree[1] && lastThree[1] == lastThree[2]){
		
		clearPaddle(&top_l_paddle, start_position);
		clearPaddle(&l_paddle, start_position + 8);
		clearPaddle(&paddle, start_position + 16);
		clearPaddle(&r_paddle, start_position + 26);
		clearPaddle(&top_r_paddle, start_position + 34);

		drawRect(top_l_paddle, Green);
		drawRect(l_paddle, Green);
		drawRect(paddle, Green);
		drawRect (r_paddle, Green);
		drawRect(top_r_paddle, Green);

  }	
	
}
