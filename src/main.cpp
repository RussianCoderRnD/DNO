/**/

//---------------- БИБЛИОТЕКИ START ---------------------
#include <libraries.h>


#include <ArduinoJson.h>      // Подключение библиотеки ArduinoJson
//----------------- БИБЛИОТЕКИ END-----------------------

//-------------------- DEFINE START ---------------------
const char *ssid = "ESP8266_AP";   // Имя сети (SSID)
const char *password = "12345678"; // Пароль сети


//-------------------- DEFINE END -----------------------

//------------ СОЗДАНИЕ ЭКЗЕМПЛЯРА START ----------------
// Создание объекта OLED дисплея, подключенного через I2C
Adafruit_SSD1306 oled(OLED_WIDTH, OLED_HEIGHT, &Wire, -1);

IPAddress local_ip(192, 168, 4, 1); // Локальный IP-адрес
IPAddress gateway(192, 168, 4, 1);  // Шлюз
IPAddress subnet(255, 255, 255, 0); // Маска подсети

ESP8266WebServer server(80); // Веб-сервер на ESP8266
//------------- СОЗДАНИЕ ЭКЗЕМПЛЯРА END -----------------


//----------------- СПИСОК ФУНКЦИЙ START-----------------
void SPrint(String text); // Функция вывода данных на OLED дисплей
void handleCount();       // Обработчик запроса на получение значения count
void handleRoot();
void handleRes();
void MIT_measurement();    // функция измерения тока
void NameLinePin(uint8_t); //
void testLine();
void Choice();
//----------------- СПИСОК ФУНКЦИЙ END ------------------

//--------------------- SETUP START ---------------------
void setup(void)
{
  Serial.begin(115200); // открываем порт для связи с ПК

  for (size_t i = 0; i < 8; i++)
  {
    pinMode(ArrayLinePin[i], OUTPUT);
  }
  for (size_t i = 0; i < 6; i++)
  {
    digitalWrite(ArrayLinePin[i], HIGH);
  }

  digitalWrite(Relay_current_volt, LOW);
  digitalWrite(WiFi_Status, LOW);

  // Инициализация OLED дисплея с I2C адресом 0x3C
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    Serial.println(F("Ошибка инициализации SSD1306 OLED дисплея"));
    while (true)
      ; // Остановка работы устройства в случае ошибки
  }

  oled.clearDisplay();      // очистка дисплея
  oled.setTextSize(1);      // установка размера текста
  oled.setTextColor(WHITE); // установка цвета текста

   WiFiAP(); /* Инициализация точки доступа (AP) */
  MyOTA();  /* Настройка OTA */
}
//--------------------- SETUP END ----------------------

//------------------- LOOP START -----------------------
void loop(void)
{
  server.handleClient(); // Обработка клиентских запросов
  Choice();
}
//--------------------- LOOP END ----------------------

//========== Функция для вывода текста на OLED дисплей
void SPrint(String text)
{
  static int i = 0; // Статическая переменная для хранения позиции по вертикали
  
  
  if (i > 60)
  {
    i = 0;
    oled.clearDisplay(); // Очищаем дисплей
    oled.display();      // Выводим на OLED дисплей
  }
  oled.setCursor(0, i); // Устанавливаем позицию текста
  oled.println(text);   // Выводим текст
  oled.display();       // Обновляем дисплей
  i += 9;
}

//========== Обработчик запроса "/res"
void handleRes()
{
      oled.clearDisplay(); // Очищаем дисплей
    oled.display();      // Выводим на OLED дисплей
  count = 0;
  digitalWrite(Relay_current_volt, LOW);
  BATT = (analogRead(A0) / 1023.0) * 100.0;
  delay(250);
  testLine();
  // Создаем JSON объект
  StaticJsonDocument<200> jsonDoc;

  // Добавляем переменные в JSON объект
  jsonDoc["LG"] = ArrayLineMit[0];
  jsonDoc["PG"] = ArrayLineMit[1];
  jsonDoc["LP"] = ArrayLineMit[2];
  jsonDoc["PP"] = ArrayLineMit[3];
  jsonDoc["STOP"] = ArrayLineMit[4];
  jsonDoc["ZX"] = ArrayLineMit[5];
  jsonDoc["FOG"] = ArrayLineMit[6];
  jsonDoc["BATT"] = BATT;

  // Преобразуем JSON объект в строку
  String jsonString;
  serializeJson(jsonDoc, jsonString);

  // Отправляем JSON клиенту
  server.send(200, "application/json", jsonString);
  Serial.println("jsonString " + jsonString);
  oled.clearDisplay();        // Очищаем дисплей
  oled.setCursor(0, 0);       // Устанавливаем позицию текста
  oled.println("jsonString"); // Выводим текст
  oled.setCursor(0, 15);      // Устанавливаем позицию текста
  oled.println(jsonString);   // Выводим текст
  oled.display();             // Обновляем дисплей
}

//========== Обработчик запроса "/count"
void handleCount()
{    oled.clearDisplay(); // Очищаем дисплей
    oled.display();      // Выводим на OLED дисплей
  String message = "";
  if (server.hasArg("count"))
  {
    count = server.arg("count").toInt(); // Получаем значение параметра count и конвертируем в int
    message = "Значение count установлено: " + String(count);
    Serial.println("Значение count установлено: " + String(count));
    SPrint("count: ");
    SPrint(String(count));
  }
  else
  {
    message = "Ошибка: параметр count отсутствует или неверный формат";
    Serial.println("Ошибка: параметр count отсутствует или неверный формат");
    SPrint("Error: The count");
    SPrint("parameter is missing ");
    SPrint(" or the format ");
    SPrint("is incorrect");
  }
  server.send(200, "text/plain", message);
}

//========== Обработчик корневого запроса "/"
void handleRoot()
{
  server.send(200, "text/plain", "Привет от ESP8266!");
  Serial.println("Привет от ESP8266!");
  SPrint("Hi, this is ESP8266!");
}

// ========== NameLinePin(uint8_t Nam_LINE)
void NameLinePin(uint8_t Nam_LINE)
{ /* функция принимает номер пина реле:
   - привинтивно выключаем реле,
   - создаём и инициализируем переменные в "0"
   - включаем реле
   - создаём масив для цекличной записи значений и вычисление среднего значения
   */

  digitalWrite(Relay_current_volt, HIGH);
  uint8_t mVperAmp = 66;
  int RawValue = 0;
  uint16_t ACSoffset = 2650; // 2462
  float Voltage = 0.00;
  float Amps = 0.00;
  float mit2 = 0.00;
  digitalWrite(Nam_LINE, LOW); // устанавливаем состояние как HIGH тем самым включаем линию
  float arrTemp[10];           // записываем в массив измеренный вцикле mit
  int sizeArrTemps = sizeof(arrTemp) / sizeof(float *) / 2;
  delay(500);
  for (int i = 0; i < sizeArrTemps;)
  {
    RawValue = analogRead(Pin_MIT);
    // для вычисления mit мы значения полученные с аналогово входа делим на 1024 и умножаем на половину опорного напряжения умножнную на два
    // затем отполученного отнимаем половину опорногонапряжения и делим на чуствительность датчика тока (ACS712)
    mit = ((((RawValue / 1023.0) * (ACSoffset * 2)) - ACSoffset) / mVperAmp); // для полу
    int p = 0;
    p++;
    if (mit >= KZ) // вслучае KZ выходим изцикла   && p == 2
    {
      for (int ii = 0; ii < sizeArrTemps;)
      {
        arrTemp[ii] = mit; // в случае KZ запмисываем в массив с номером ячейки на линии которой KZ записываем mit, чтобы алгаритм не включал эту линию
        ii++;
      }
      break;
    }
    arrTemp[i] = mit;
    i++;
    delay(25);
  }

  mit2 = 0;
  // через цикл суммируем значения всехячеек масива и делим на колличество ячеек тем свмым получаем среднее значение
  for (int r = 0; r < sizeArrTemps; r++)
  {
    mit2 += arrTemp[r];
  }
  mit = mit2 / sizeArrTemps;
  // искключаем диапазон в котором "шумит" датчик Холла
  if (mit <= 0.16)
  {
    mit = 0.00;
  }
  digitalWrite(Nam_LINE, HIGH); // устанавливаем состояние как LOW тем самым выключаем
  digitalWrite(Relay_current_volt, LOW);
}

// ========== testLine() 
void testLine()
{
  oled.clearDisplay();      // очистка дисплея
  for (int y = 0; y < 7;)
  {
    blinks(50, 50, 1);
    NameLinePin(ArrayLinePin[y]);
    ArrayLineMit[y] = mit;
    Serial.println();
    Serial.print(ArrayNamesLine[y]);
    Serial.print(" - ");
    Serial.print(ArrayLineMit[y]);
    Serial.println();
    SPrint(ArrayNamesLine[y] + " - " + ArrayLineMit[y]);
    y++;
  }
}

// ========== Menu() 
void Choice()
{
  if (count == 0)
  {
    digitalWrite(PinRelay_LEFT_GABARIT, HIGH);
    digitalWrite(PinRelay_RIGHT_GABARIT, HIGH);
    digitalWrite(PinRelay_LEFT_POVOROT, HIGH);
    digitalWrite(PinRelay_RIGHT_POVOROT, HIGH);
    digitalWrite(PinRelay_STOP_SIGNAL, HIGH);
    digitalWrite(PinRelay_ZADNY_XOD, HIGH);
    digitalWrite(PinRelay_TUMANKA, HIGH);
  }

  if (count == 1 && ArrayLineMit[0] != KZ)
  {
    digitalWrite(PinRelay_LEFT_GABARIT, LOW);
  }
  else
  {
    digitalWrite(PinRelay_LEFT_GABARIT, HIGH);
  }

  if (count == 2 && ArrayLineMit[1] != KZ)
  {
    digitalWrite(PinRelay_RIGHT_GABARIT, LOW);
  }
  else
  {
    digitalWrite(PinRelay_RIGHT_GABARIT, HIGH);
  }

  if (count == 3 && ArrayLineMit[2] != KZ)
  {
    digitalWrite(PinRelay_LEFT_POVOROT, LOW);
  }
  else
  {
    digitalWrite(PinRelay_LEFT_POVOROT, HIGH);
  }

  if (count == 4 && ArrayLineMit[3] != KZ)
  {
    digitalWrite(PinRelay_RIGHT_POVOROT, LOW);
  }
  else
  {
    digitalWrite(PinRelay_RIGHT_POVOROT, HIGH);
  }

  if (count == 5 && ArrayLineMit[4] != KZ)
  {
    digitalWrite(PinRelay_STOP_SIGNAL, LOW);
  }
  else
  {
    digitalWrite(PinRelay_STOP_SIGNAL, HIGH);
  }

  if (count == 6 && ArrayLineMit[5] != KZ)
  {
    digitalWrite(PinRelay_ZADNY_XOD, LOW);
  }
  else
  {
    digitalWrite(PinRelay_ZADNY_XOD, HIGH);
  }

  if (count == 7 && ArrayLineMit[6] != KZ)
  {
    digitalWrite(PinRelay_TUMANKA, LOW);
  }
  else
  {
    digitalWrite(PinRelay_TUMANKA, HIGH);
  }
}
