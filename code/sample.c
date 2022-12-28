/****************************************Copyright (c)****************************************************
**                                      
**                                     PONG - The Game
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Francesco Pio Barletta (mat. 296114)
** Modified date:           2021-12-28
** Version:                 v2.1
** Descriptions:            Pong - The Game
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "CollisionManager.h"
#include "adc/adc.h"
#include "button_EXINT/button.h"
#include "RIT/RIT.h"

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif

// Vertical walls
Rect wall1 = { 0, 0, 5, MAX_Y, V_WALL };
Rect wall2 = { MAX_X - 5, 0, 5, MAX_Y, V_WALL };

// Gameover
Rect gameover = { 0, MAX_Y - 10, MAX_X, 29, GAME_OVER };
Rect gameover2 = { 0, 10, MAX_X, 10, GAME_OVER2 };

// Ball with speed
Rect ball = { MAX_X - 12, 160, 5, 5, BALL, 45.0, -1, 1};

// Paddle
Rect top_l_paddle = { MAX_X/2 - 38, MAX_Y - 22, 8, 10, TOP_LEFT_PADDLE, 0, 1, 0 };
Rect l_paddle = { MAX_X/2 - 30, MAX_Y - 22, 8, 10, PADDLE_LEFT, 0, 1, 0 };
Rect paddle = { MAX_X/2 - 22, MAX_Y - 22, 20, 10, PADDLE_CENTER, 0, 1, 0 };
Rect r_paddle = { MAX_X/2 - 12, MAX_Y - 22, 8, 10, PADDLE_RIGHT, 0, 1, 0 };
Rect top_r_paddle = { MAX_X/2 - 6, MAX_Y - 22, 8, 10, TOP_RIGHT_PADDLE, 0, 1, 0 };

// Paddle 2
Rect paddle2 = { MAX_X/2 - 22, 22, 36, 10, PADDLE_CENTER, 0, 1, 0 };

Rect* walls[3] = { &wall1, &wall2, &gameover };

char score_in_text1[5] = "";
char score_in_text2[5] = "";
volatile uint16_t score1 = 0;
volatile uint16_t score2 = 0;
volatile uint8_t isGameOver;

int reset;

int main(void)
{
	while(1){
		
		int i = 0;	
		reset = 0;
		isGameOver = 0;
		SystemInit();  															/* System Initialization (i.e., PLL)  */
		BUTTON_init();
		
		LCD_Initialization();
		LCD_Clear(Black);
		
		ADC_init();																	/* ADC Initialization									*/
		
		// Reset of the score
		score1 = 0;
		score2 = 0;
		
		for(i = 0; i < 3; i++) {
			drawRect(*(walls[i]), Blue);
		}
		
		drawRect(ball, Yellow);
		drawRect(paddle, Green);
		drawRect (l_paddle, Green);
		drawRect (r_paddle, Green);
		drawRect (top_l_paddle, Green);
		drawRect (top_r_paddle, Green);
		drawRect(paddle2, Green);
		
		// Intro 
		GUI_Text(50, 180, (uint8_t *) "Press KEY1 to start", White, Black);
		// Cast score text
		sprintf(score_in_text1, "%d", score1);
		GUI_Text(10, 160, (uint8_t *) score_in_text1, White, Black);
		
		sprintf(score_in_text2, "%d", score2);
		GUI_Text(MAX_X - 15, 160, (uint8_t *) score_in_text2, White, Black);
		

		init_timer(0, 0x98968 ); 										/* 25ms * 25MHz = 6.25*10^5 = 0x1312D0 --> used for the ball and paddle  */
		init_RIT(0x186A0);													/* RIT Initialization 1 msec       	*/
		
		 while (!reset) {                          			/* Loop forever                       */	
			__ASM("wfi");
		}
		
	}
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
