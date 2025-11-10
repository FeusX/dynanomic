#ifndef NTOP_H
#define NTOP_H

#include <Arduino.h>

static int free_ram()
{
  extern int16_t __heap_start, *__brkval;
  int16_t v;

  return (int16_t)&v - (__brkval == 0 ? (int16_t)&__heap_start : (int16_t)__brkval);
}

static void ntop(char **args, int argc)
{
  const unsigned long test = 1000000UL;
  unsigned long start = micros();
  unsigned long busy_time = 0;
  unsigned long end = micros();

  while(micros() - start < test)
  {
    unsigned long before = micros();
    delayMicroseconds(50);
    unsigned long after = micros();
    busy_time += (after - before);
    delayMicroseconds(100);
  }

  unsigned long total = micros() - start;

  Serial.println("[NTOP]");
  Serial.print("CPU: ");
  Serial.print(100.0 * busy_time / total);
  Serial.println("%");

  Serial.print("RAM: ");
  Serial.print(2048 - free_ram());
  Serial.println(" bytes");

  Serial.println("[NTOP]");
}

#endif
