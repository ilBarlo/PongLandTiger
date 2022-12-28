/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <stdio.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"
#include "../CollisionManager.h"
#include "../adc/adc.h"


/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

extern Rect gameover2;
extern Rect gameover;
extern Rect paddle2;
extern Rect paddle;
extern Rect l_paddle;
extern Rect r_paddle;
extern Rect top_l_paddle;
extern Rect top_r_paddle;
extern Rect ball;
extern Rect* walls[4];
extern char score_in_text1[5];
extern volatile uint16_t score1;
extern char score_in_text2[5];
extern volatile uint16_t score2;
extern volatile uint8_t isGameOver;
extern volatile uint16_t start_position;
volatile uint16_t bestscore = 0;
// volatile uint16_t var_position = 0;
char best_score_in_text[5];
int i = 0;
int c = 0;

void TIMER0_IRQHandler (void)
{
	static int timer = 0;
	int position = paddle2.x;
	timer ++;
	c ++;
	
	if (timer == 2){
			
				/* ADC management */
				NVIC_EnableIRQ(ADC_IRQn);
				ADC_start_conversion();	
			
		if(!rectCollision(&ball, gameover2)){

			if(!rectCollision(&ball, gameover)){
			if(!rectCollision(&ball, paddle2)){
			if(!rectCollision(&ball, paddle)) {
				if(!rectCollision(&ball, l_paddle)) {
					if(!rectCollision(&ball, r_paddle)) {
						if(!rectCollision(&ball, top_l_paddle)) {
							if(!rectCollision(&ball, top_r_paddle)) {
					for(i = 0; i < 3; i++) {
						if(rectCollision(&ball, *(walls[i]))) {
							sprintf(score_in_text1, "%d", score1);
							GUI_Text(10, 160, (uint8_t *) score_in_text1, White, Black);
							sprintf(score_in_text2, "%d", score2);
							GUI_Text(MAX_X - 15, 160, (uint8_t *) score_in_text2, White, Black);
							break;}
									}}}
								}
							}
						}
					}
				}
			} else {
				sprintf(score_in_text1, "%d", score1);
				GUI_Text(10, 160, (uint8_t *) score_in_text1, White, Black);
				sprintf(score_in_text2, "%d", score2);
				GUI_Text(MAX_X - 15, 160, (uint8_t *) score_in_text2, White, Black);
			}
			clearRect(&ball);
			drawRect(ball, Green);
			
			if (c > 10) {
				
				if (paddle2.x >= MAX_X - 50 || paddle2.x <= 40){
					paddle2.x_velocity *= -1;
				}
				
				position = position + 10;
				position = position * paddle2.x_velocity;
				clearPaddle(&paddle2, position);
				drawRect(paddle2, Green);
				c = 0;
			}
			
			if (isGameOver == 0x01){
				clearRect(&ball);
				clearPaddle(&top_l_paddle, 0);
				clearPaddle(&l_paddle, 0);
				clearPaddle(&paddle, 0);
				clearPaddle(&r_paddle, 0);
				clearPaddle(&top_r_paddle, 0);
				clearPaddle(&paddle2, 0);
				
				sprintf(score_in_text1, "%d", score1);
				GUI_Text(10, 160, (uint8_t *) score_in_text1, White, Black);
				sprintf(score_in_text2, "%d", score2);
				GUI_Text(MAX_X - 15, 160, (uint8_t *) score_in_text2, White, Black);
				
				if (score1 > score2){
					GUI_Text_Reverse(90, 145, (uint8_t *) "esoL uoY", White, Black);
					GUI_Text(85, 160, (uint8_t *) "You Win", White, Black);
				} else {
					GUI_Text_Reverse(90, 145, (uint8_t *) "Win uoY", White, Black);
					GUI_Text(80, 160, (uint8_t *) "You Lose", White, Black);
				}
				
				GUI_Text(50, 200, (uint8_t *) "  Press INT0 to  ", Black, Green);
				GUI_Text(50, 215, (uint8_t *) "start a new game ", Black, Green);
				
				// Repositioning of the paddle for the new game
				paddle.x = MAX_X/2 - 22;
				l_paddle.x = MAX_X/2 - 30;
				r_paddle.x = MAX_X/2 - 12;
				top_l_paddle.x = MAX_X/2 - 38;
				top_r_paddle.x = MAX_X/2 - 6;
				paddle2.x = MAX_X/2 - 22;
				
				// Repositioning of the ball for the new game
				ball.x = MAX_X -12;
				ball.y = 160;
				ball.x_velocity = -1;
				ball.y_velocity = 1;
				

				disable_timer(0);
			}
			timer = 0;
	}
	
  LPC_TIM0->IR = 1;			/* clear interrupt flag */
	
  return;
}


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


void TIMER1_IRQHandler (void)
{
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
** Function name:		Timer2_IRQHandler
**
** Descriptions:		Timer/Counter 2 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/


void TIMER2_IRQHandler (void)
{
  LPC_TIM2->IR = 1;			/* clear interrupt flag */
  return;
}
/******************************************************************************
**                            End Of File
******************************************************************************/
