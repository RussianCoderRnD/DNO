// WiFiAP.cpp
#include "WiFiAP.h"      // Включение заголовочного файла WiFiAP.h
#include <ArduinoJson.h> // Включение библиотеки ArduinoJson для работы с JSON

void handleRoot();  // Объявление функции обработчика для корневого URL
void handleRes();   // Объявление функции обработчика для URL /res
void handleCount(); // Объявление функции обработчика для URL /count

void WiFiAP()
{
  /* Инициализация точки доступа (AP) */
  if (WiFi.softAP(ssid, password))
  {
    WiFi.softAPConfig(local_ip, gateway, subnet); // Настройка IP, шлюза и маски подсети для точки доступа
    Serial.println();
    Serial.print("Точка доступа создана с именем: "); // Вывод имени точки доступа
    Serial.println(ssid);
    Serial.print("IP-адрес: "); // Вывод IP-адреса точки доступа
    Serial.println(WiFi.softAPIP());
    IPAddress ip = WiFi.softAPIP(); // Получение IP-адреса точки доступа

    /* Настройка маршрутов для веб-сервера */
    server.on("/", HTTP_GET, handleRoot);       // Регистрация обработчика для корневого URL
    server.on("/count", HTTP_GET, handleCount); // Регистрация обработчика для URI /count
    server.on("/res", HTTP_GET, handleRes);     // Регистрация обработчика для URL /res
    server.begin();                             // Запуск веб-сервера
  }
  else
  {
    Serial.println(F("Error: The access point could not be created")); // Сообщение об ошибке создания точки доступа
    ESP.restart();                                                     // Перезапуск ESP в случае ошибки
  }
}
