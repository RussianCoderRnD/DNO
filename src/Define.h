#ifndef DEFINE_H

#define OLED_WIDTH 128 // Ширина OLED дисплея, в пикселях
#define OLED_HEIGHT 64 // Высота OLED дисплея, в пикселях

#define Pin_MIT A0                // Пин для снятия показаний датчика тока (используется аналоговый вход A0)
#define PinRelay_LEFT_GABARIT D8  // Пин реле для управления левыми габаритами
#define PinRelay_RIGHT_GABARIT D7 // Пин реле для управления правыми габаритами
#define PinRelay_LEFT_POVOROT D6  // Пин реле для управления левым поворотником
#define PinRelay_RIGHT_POVOROT D4 //D1 Пин реле для управления правым поворотником
#define PinRelay_STOP_SIGNAL D5   // Пин реле для управления стоп-сигналом
#define PinRelay_ZADNY_XOD D0     // Пин реле для управления задним ходом
#define PinRelay_TUMANKA D3       // Пин реле для управления противотуманками
#define Relay_current_volt D8     // Пин реле для управления подачей напряжения на измерительную схему
#define WiFi_Status D8            // D2 Пин для индикации состояния WiFi

#endif 
