/****************************************Copyright (c)****************************************************
**                                      
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               CollisionManager.h
**
**--------------------------------------------------------------------------------------------------------
** Created by:              Francesco Pio Barletta
** Created date:            2021-12-15
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:            	Francesco Pio Barletta 
** Modified date:           2022-02-01 
** Version:                 v2.1
** Descriptions:            Up to date
**
*********************************************************************************************************/

#ifndef _COLLISION_MANAGER_H_
#define _COLLISION_MANAGER_H_

/* Includes ------------------------------------------------------------------*/
#include <math.h>
#include <stdint.h>
#include "GLCD/GLCD.h" 

/* External variables ---------------------------------------------------------*/
extern volatile uint16_t score1;
extern volatile uint16_t score2;
extern volatile uint8_t isGameOver;
extern volatile uint16_t start_position;

/* Private typedef -----------------------------------------------------------*/
typedef enum {
	V_WALL, H_WALL, BALL, PADDLE_LEFT, PADDLE_CENTER, PADDLE_RIGHT, TOP_LEFT_PADDLE, TOP_RIGHT_PADDLE, GAME_OVER, GAME_OVER2, NO_COLL
} RectType;

typedef struct {
	uint16_t x;
	uint16_t y;
	uint16_t width;
	uint16_t height;
	RectType type;
	
	// variables only for the ball and paddle
	float_t angle;
	int16_t x_velocity;
	int16_t y_velocity;
} Rect;

/* Private function prototypes -----------------------------------------------*/	
void drawRect(Rect r, uint16_t color);
void clearRect(Rect* r);
void clearPaddle(Rect* r, uint16_t start_position);
uint8_t rangeIntersect(uint16_t min0, uint16_t max0, uint16_t min1, uint16_t max1);
uint8_t rectCollision(Rect* ball, Rect r);

#endif

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/


