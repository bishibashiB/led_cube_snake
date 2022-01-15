#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>

#define Matrix_X (16)
#define Matrix_Y (16)
#define TileNum_X (5)
#define TileNum_Y (1)
#define LED_COUNT (Matrix_X * Matrix_Y * TileNum_X * TileNum_Y)

#define sizeX (Matrix_X * TileNum_X)
#define sizeY (Matrix_Y * TileNum_Y)
// #define systemTickDelayMS 1
// #define stepTransitionStates 20


#endif // CONFIG_H
