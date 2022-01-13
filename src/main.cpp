#include <Arduino.h>

#undef max
#undef min
#include <stdio.h>
#include <iostream>
using namespace std;
extern "C"
{
  int _write(int fd, char *ptr, int len)
  {
    (void)fd;
    return Serial.write(ptr, len);
  }
}

enum class SerialCmd : int
{
  ADD_PLAYER = 1,     // " 1Byte number / ID,  2x3Byte color head / body "
  REMOVE_PLAYER = 2,  // "1Byte number/ID"
  ITERATE_STEP = 3,   // 0Byte, ... all players
  DIR_CMD_PLAYER = 4, // "1Byte number/ID, 1Byte NEW rel. direction ('r', 'l')"
};

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  if (Serial.available())
  {
    char terminator = '\n';
    String readData = Serial.readStringUntil(terminator);

    switch ((SerialCmd)readData.c_str()[0])
    {
    case SerialCmd::ADD_PLAYER:
      Serial.write("ADD_PLAYER ");
      Serial.write(readData.c_str()[1]);
      addPlayer(readData.c_str()[1]);
      break;
    case SerialCmd::REMOVE_PLAYER:
      Serial.write("REMOVE_PLAYER ");
      Serial.write(readData.c_str()[1]);
      removePlayer(readData.c_str()[1]);
      break;
    case SerialCmd::ITERATE_STEP:
      Serial.write("ITERATE_STEP ");
      iterateWorld();
      break;
    case SerialCmd::DIR_CMD_PLAYER:
      Serial.write("DIR_CMD_PLAYER ");
      Serial.write(readData.c_str()[1]);
      changePlayerDirection(readData.c_str()[1]);
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