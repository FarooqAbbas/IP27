#include "WiFi.h"
#include <String>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif

//for esp 32 
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);
const char* ssid = "";
const char* password = "";
char c;
String str;
const char* str1="";
WiFiServer wifiServer(80);

void u8g2_prepare(void) {
  u8g2.setFont(u8g2_font_6x10_tf);
  u8g2.setFontRefHeightExtendedText();
  u8g2.setDrawColor(1);
  u8g2.setFontPosTop();
  u8g2.setFontDirection(0);
}
void setup() {
  Serial.begin(115200);
  u8g2.begin();
  delay(1000);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi..");
        }
  Serial.println("Connected to the WiFi network");
  Serial.println(WiFi.localIP());
  wifiServer.begin();
}
void loop() {
  WiFiClient client = wifiServer.available();
  if (client) {
      while (client.connected()) {
            while (client.available()>0) {
                c = client.read();
                Serial.write(c);
                str=String(str+c);
                str1=str.c_str();
                Serial.println(str1);
				disp(str1);
      }
            delay(10);
      }
      client.stop();
      Serial.println("Client disconnected");
    }
  
}
void disp(const char * st) {
	const char * str2;
	str2 = st;

	u8g2.clearBuffer();
	u8g2_prepare();
	u8g2.drawStr(0, 0, str2);
	u8g2.drawStr(0, 10, str2);
	u8g2.sendBuffer();
}
