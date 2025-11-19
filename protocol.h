#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <Wire.h>
#include <Arduino.h>

void readI2C(char **args, int argc);
void writeI2C(char **args, int argc);
void scanI2C(char **args, int argc);

void readI2C(char **args, int argc)
{
  if(argc != 2)
  { Serial.println("[ERROR] Usage: readI2C(addr, reg)"); return; }

  int8_t addr = (int8_t)strtol(args[0], NULL, 16);
  int8_t reg = (int8_t)strtol(args[1], NULL, 16);

  Wire.beginTransmission(addr);
  Wire.write(reg);

  if(Wire.endTransmission() != 0)
  { Serial.println("[ERROR] No ACK."); return; }

  Wire.requestFrom(addr, (uint8_t)1);
  if(Wire.available()) Serial.println(Wire.read());
  else Serial.println("[ERROR] No data recieved.");
}

void writeI2C(char **args, int argc)
{
  if(argc != 3)
  { Serial.println("[ERROR] Usage: writeI2C(addr, reg, val)"); return; }

  int8_t addr = (int8_t)strtol(args[0], NULL, 16);
  int8_t reg = (int8_t)strtol(args[1], NULL, 16);
  int8_t val = (int8_t)strtol(args[2], NULL, 16);

  Wire.beginTransmission(addr);
  Wire.write(reg);
  Wire.write(val);

  if(Wire.endTransmission() != 0)
  { Serial.println("[ERROR] Failed to write."); }
  else Serial.println("Written.");
}

void scanI2C(char **args, int argc)
{
  Serial.println("Scanning...");
  for(int8_t addr = 1; addr < 127; addr++)
  {
    Wire.beginTransmission(addr);
    if(Wire.endTransmission() == 0)
    {
      Serial.print("Device at 0x");
      Serial.println(addr, HEX);
    }
  }

  Serial.println("Scan complete.");
}

#endif
