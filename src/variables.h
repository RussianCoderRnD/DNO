#ifndef VARIABLES_H
#define VARIABLES_H

#include <Arduino.h> // Подключаем библиотеку Arduino

extern float LG = 1.0;
extern float PG = 2.0;
extern float LP = 3.0;
extern float PP = 4.0;
extern float STOP = 5.0;
extern float ZX = 6.0;
extern float FOG = 7.0;
extern float KZ = 8.0; // переменная с присвоеным значением
extern boolean lG, pG, lP, pP, sTOP, zX, fOG = false;
extern uint8_t BATT = 0;
extern uint8_t count = 0; // Переменная для хранения значения
extern float mit = 0.0;
extern uint8_t temp;
extern String ArrayNamesLine[] = {"LEFT_GABARIT", "RIGHT_GABARIT", "LEFT_POVOROT", "RIGHT_POVOROT", "STOP_SIGNAL", "ZADNY_XOD", "TUMANKA"};
extern float ArrayLineMit[] = {0.00, 0.00, 0.00, 0.00, 0.00, 0.00, 0.00};
extern int ArrayLinePin[] = {PinRelay_LEFT_GABARIT, PinRelay_RIGHT_GABARIT, PinRelay_LEFT_POVOROT, PinRelay_RIGHT_POVOROT, PinRelay_STOP_SIGNAL, PinRelay_ZADNY_XOD, PinRelay_TUMANKA}; // 24, 22, 23, 27, 25, 26, 28

#endif