#ifndef VARIABLES_H
#define VARIABLES_H

#include <Arduino.h> // Подключаем библиотеку Arduino

float LG = 1.0;
float PG = 2.0;
float LP = 3.0;
float PP = 4.0;
float STOP = 5.0;
float ZX = 6.0;
float FOG = 7.0;
float KZ = 8.0; // переменная с присвоеным значением
boolean lG, pG, lP, pP, sTOP, zX, fOG = false;
uint8_t BATT = 0;
uint8_t count = 0; // Переменная для хранения значения
float mit = 0.0;
uint8_t temp;
String ArrayNamesLine[] = {"LEFT_GABARIT", "RIGHT_GABARIT", "LEFT_POVOROT", "RIGHT_POVOROT", "STOP_SIGNAL", "ZADNY_XOD", "TUMANKA"};
float ArrayLineMit[] = {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
int ArrayLinePin[] = {PinRelay_LEFT_GABARIT, PinRelay_RIGHT_GABARIT, PinRelay_LEFT_POVOROT, PinRelay_RIGHT_POVOROT, PinRelay_STOP_SIGNAL, PinRelay_ZADNY_XOD, PinRelay_TUMANKA}; // 24, 22, 23, 27, 25, 26, 28

#endif