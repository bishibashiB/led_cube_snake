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
    matrix.begin();
    matrix.fillScreen(0);
    matrix.show();
}

void loop()
{
    extern const std::array<PanelCfg, TileNum_X * TileNum_Y> PanelArray;
    static SnakeWorld<Matrix_X, Matrix_Y, TileNum_X, TileNum_Y> world{PanelArray, matrix};
    static SnakeGame<Matrix_X, Matrix_Y, TileNum_X, TileNum_Y> game{world};
    if (Serial.available())
    {
        char terminator = '\n';
        String readData = Serial.readStringUntil(terminator);
        const unsigned char* charReadData = (const unsigned char*)readData.c_str();
        SerialCmd cmd = (SerialCmd)charReadData[0];

        switch (cmd)
        {
        case SerialCmd::ADD_PLAYER:
        {
            Serial.write("ADD_PLAYER ");
            Serial.write(charReadData[1]);
            game.AddPlayer(charReadData[1],
                           {charReadData[2], charReadData[3], charReadData[4]},
                           {charReadData[5], charReadData[6], charReadData[7]});
        }
        break;
        case SerialCmd::REMOVE_PLAYER:
        {
            Serial.write("REMOVE_PLAYER ");
            Serial.write(charReadData[1]);
            game.RemovePlayer(charReadData[1]);
        }
        break;
        case SerialCmd::ITERATE_STEP:
        {
            Serial.write("ITERATE_STEP ");
            game.IterateWorld();
        }
        break;
        case SerialCmd::DIR_CMD_PLAYER:
        {
            Serial.write("DIR_CMD_PLAYER ");
            Serial.write(charReadData[1]);
            Direction d;
            if (charReadData[2] == 'r')
            {
                d = Direction::Right;
            }
            else if (charReadData[2] == 'l')
            {
                d = Direction::Left;
            }
            else
            {
                Serial.write(" unsupported direction");
                break;
            }

            Serial.write(charReadData[2]);

            game.ChangePlayerDirection(charReadData[1], d);
        }
        break;
        default:
            Serial.write("unknown command received ");
            Serial.write(charReadData[0]);
            Serial.write(charReadData[1]);
            break;
        }

        // confirm processing done, will trigger next data transmission
        Serial.write('\n');
    }
}