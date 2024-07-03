#ifndef LIBRARIES_H
#define LIBRARIES_H

#include <Arduino.h>           // Основная библиотека для Arduino
#include <ESP8266WiFi.h>       // Библиотека для работы с WiFi на ESP8266
#include <ESP8266WebServer.h>  // Библиотека для веб-сервера на ESP8266
#include <Wire.h>              // Библиотека для работы с I2C
#include <Adafruit_GFX.h>      // Библиотека для работы с графикой (основная библиотека Adafruit для графических дисплеев)
#include <Adafruit_SSD1306.h>  // Библиотека для работы с дисплеем SSD1306
#include <define.h>            // Файл с инструкциями #define (здесь содержатся все макросы и константы)
#include <variables.h>         // Файл с объявлением переменных (здесь объявляются глобальные переменные)
#include <blinks.h>            // Файл с функцией blinks (здесь содержится реализация функции для мигания светодиодом)
#include <MyOTA.h>             // Обновление ПО через воздух (OTA) (здесь реализуется обновление прошивки по воздуху)
#include <WiFiAP.h>            // Настройка точки доступа (AP) WiFi (здесь содержится код для настройки WiFi точки доступа)

#endif 