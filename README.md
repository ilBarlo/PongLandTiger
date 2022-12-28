# Pong on LandTiger V2.0 NXP LPC1768
The game called "Pong" is made for the Computer Architecture course in 2021/22 and it reproduces the behaviour of the classic table tennis-themed arcade game called Pong.

## The Board
The LandTiger V2.0 NXP LPC1768 ARM development board used for this project is available on Keil uVision: it is based on a second-generation ARM Cortex-M3 microcontroller designed for embedded system applications, suitable for instrumentation, industrial communications, motor control, lighting control, alarm systems, and other fields.

## The Game
In this multi-player version of the game, the player must not let the ball fall below the paddle. The bottom paddle is driven by the first player, and it can only move horizontally. The first player operates it through the potentiometer available in the LandTigerboard. On the contrary, the top paddle is driven by the second player. It is fully automatic and, when the play starts, it only moves horizontally at a constant speed. Every time the ball falls below one’s paddle, the other player’s score is incremented by 1. The game ends as soon as one player scores 5 points. The user should start the game by pressing the button KEY1. To pause the game and later resume it, the user should press the button KEY2. In case of game over, to prepare a new game the player should press the INT0 button, followed by KEY1 to start it.
