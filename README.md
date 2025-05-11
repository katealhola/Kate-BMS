# Kate-BMS
11.5.2025   A lot of refactoring, JK-Bms support, support for dual battery/BMS

Open smart BMS monitor

Supporter bms:
JK-bms ( jikong bms )
AntBms


Libraries used
- TFT_eSPI
- ESP8266_SSD1306 4.0.0    ESP8266_and_ESP32_Oled_Driver_for_SSD1306_display
- Esp32 WiFi,SD,FS,SPI,SPIFFS
- PubSubClient 2.7
- ArduinoJson 6.11.2

=== Notify ===
TFT_eSPI has some configuration defaults hard wired to librry User_Setup.h file. Please comment them out, they will mesh up configs set up by project
