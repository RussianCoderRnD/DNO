#include "blinks.h"

void blinks(int del, int del2, int8_t coun) {
  for (size_t i = 0; i < coun; i++) {
    digitalWrite(WiFi_Status, LOW);  // Включить светодиод (LOW соответствует включенному состоянию, так как обычно используется инверсия логики)
    delay(del);                      // Подождать заданное время (del миллисекунд)
    digitalWrite(WiFi_Status, HIGH); // Выключить светодиод (HIGH соответствует выключенному состоянию)
    delay(del2);                     // Подождать заданное время (del2 миллисекунд)
  }
}

