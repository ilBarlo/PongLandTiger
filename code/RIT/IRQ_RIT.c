/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../GLCD/GLCD.h"
#include "../timer/timer.h"
#include "../TouchPanel/TouchPanel.h"
#include "../CollisionManager.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

int key2=0;
int key1=0;
int int0=0;
extern int pause;
extern int reset;

void RIT_IRQHandler (void)
{	
	
	/* Button management - KEY1 */
	if(key1 > 1){ 
		if((LPC_GPIO2->FIOPIN & (1<<11)) == 0){	/* KEY1 pressed */	
			switch(key1){
				case 2:
					GUI_Text(50, 180, (uint8_t *) " 																				", Black, Black);
					enable_timer(0);
					pause = 1;
					reset_RIT();
					break;
				default:
					break;
			}
			key1++;
		}
		else {	/* button released */
			key1=0;	
			disable_RIT();
			reset_RIT();
			NVIC_EnableIRQ(EINT1_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 22);     /* External interrupt 0 pin selection */
		}
	}
	else {
		if(key1 == 1)
			key1++;
	}
	
	/* Button management - KEY2 */
	if(key2 > 1){ 
		if((LPC_GPIO2->FIOPIN & (1<<12)) == 0){	/* KEY2 pressed */		
			switch(key2){
				case 2:
						if (pause == 1){
							disable_timer(0);
							pause = 0;
							GUI_Text(95, 160, (uint8_t *) "Pause", White, Black);
						} else if (pause == 0){
							enable_timer(0);
							pause++;
							GUI_Text(95, 160, (uint8_t *) "       ", White, Black);
						}
						reset_RIT();
					break;
				default:
					break;
			}
			key2++;
		}
		else {	/* button released */
			disable_RIT();
			reset_RIT();
			key2=0;			
			NVIC_EnableIRQ(EINT2_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 24);     /* External interrupt 0 pin selection */
		}
	}
	else {
		if(key2 == 1)
			key2++;
	}
	
	/* Button management - INT0 */
	if(int0 > 1){ 
		if((LPC_GPIO2->FIOPIN & (1<<10)) == 0){	/* INT0 pressed */				
			switch(int0){
				case 2:
					if (isGameOver == 1){
						reset++;
						reset_timer(0);
						reset_RIT();
					}
					break;
				default:
					break;
			}
			int0++;
		}
		else {	/* button released */
			int0=0;			
			NVIC_EnableIRQ(EINT0_IRQn);							 /* enable Button interrupts			*/
			LPC_PINCON->PINSEL4    |= (1 << 20);     /* External interrupt 0 pin selection */
		}
	}
	else {
		if (int0 == 1)
			int0++;
	}
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
