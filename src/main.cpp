#include <Arduino.h>
#include <pins_arduino.h>
#include <Adafruit_GFX.h> // Core graphics library
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>


#include "config.h"
#include "snake_types.hpp"
#include "snake_game.hpp"

#include <stdio.h>
#include <iostream>

#include <array>


//////////////////////////
//       OBJECTS        //
//////////////////////////
namespace
{
// Definition of the LED Matrix Object
// #define LedPin D2 //esp8266
#define Pin 27 //@ ESP32

Adafruit_NeoMatrix matrix(
    sizeX, sizeY, Pin, NEO_MATRIX_TOP + NEO_MATRIX_LEFT + NEO_MATRIX_COLUMNS + NEO_MATRIX_ZIGZAG, NEO_GRB + NEO_KHZ800);
} // namespace


void setup()
{
    Serial.begin(115200);
}

void loop()
{
    extern const std::array<PanelCfg, TileNum_X * TileNum_Y> PanelArray;
    SnakeWorld<Matrix_X, Matrix_Y, TileNum_X, TileNum_Y> world{PanelArray, matrix};
    SnakeGame<Matrix_X, Matrix_Y, TileNum_X, TileNum_Y> game{world};
    if (Serial.available())
    {
        char terminator = '\n';
        String readData = Serial.readStringUntil(terminator);

        switch ((SerialCmd)readData.c_str()[0])
        {
        case SerialCmd::ADD_PLAYER:
            Serial.write("ADD_PLAYER ");
            Serial.write(readData.c_str()[1]);
            game.AddPlayer(readData.c_str()[1],
                           {readData.c_str()[2], readData.c_str()[3], readData.c_str()[4]},
                           {readData.c_str()[5], readData.c_str()[6], readData.c_str()[7]});
            break;
        case SerialCmd::REMOVE_PLAYER:
            Serial.write("REMOVE_PLAYER ");
            Serial.write(readData.c_str()[1]);
            game.RemovePlayer(readData.c_str()[1]);
            break;
        case SerialCmd::ITERATE_STEP:
            Serial.write("ITERATE_STEP ");
            game.IterateWorld();
            break;
        case SerialCmd::DIR_CMD_PLAYER:
            Serial.write("DIR_CMD_PLAYER ");
            Serial.write(readData.c_str()[1]);
            game.ChangePlayerDirection(readData.c_str()[1], (Direction)readData.c_str()[2]);
            break;
        default:
            Serial.write("unknown command received ");
            Serial.write(readData.c_str()[0]);
            Serial.write(readData.c_str()[1]);
        }

        // confirm processing done, will trigger next data transmission
        Serial.write('\n');
    }
}