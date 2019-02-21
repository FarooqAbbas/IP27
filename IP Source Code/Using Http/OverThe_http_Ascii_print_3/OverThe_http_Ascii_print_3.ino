#include <Arduino.h>
#include <U8g2lib.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
#include "WiFi.h"
#include "ESPAsyncWebServer.h"

// 
const char* ssid = "Your SSID";
const char* password =  "password";
const char* PARAM_MESSAGE = "message";
   int num;
   int k;
AsyncWebServer server(80);
char *buf[7];
char m_str[3];
  char s[100];
  char *string1;
  String l;
  char *myChar;
  char myCharToDisplay;

U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16);  //for esp32
//U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ 22, /* data=*/ 21);  // for groove oled
 
void setup(){
  Serial.begin(115200);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  } 
  Serial.println(WiFi.localIP());
  u8g2.begin();
 
  server.on("/hello", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(200, "text/plain", "Hello World");
  });
  
  server.on("/post", HTTP_POST, [](AsyncWebServerRequest *request){      
        String message;
        if (request->hasParam(PARAM_MESSAGE, true)) {
            message = request->getParam(PARAM_MESSAGE, true)->value();
        } else {
            message = "No message sent";
        }
        request->send(200, "text/plain", "Hello, POST: " + message);
    },NULL,[](AsyncWebServerRequest * request, uint8_t *data, size_t len, size_t index, size_t total){
      for (size_t i = 0; i < len; i++) {
        Serial.write(data[i]);
        //Serial.println();
 //################################################################################ 
    Serial.println(data[i]);
    int k=int(data[i])-48;  
    myCharToDisplay=char(k);    
    // k must be in the form of  char * to be get printed on OLED  
    Serial.println(k);
    string1 = itoa_simple(s, data[i]);    
  }  
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_logisoso62_tn);
    // this drawStr function require third parameter to be in the form of const char *
    // but data we are receiving is int form of int * 
    // so i am facing issue in this conversion.
    u8g2.drawStr(0,63,data[i]);  //its fine
    //u8g2.drawStr(0,63,myChar) ;  
   } while ( u8g2.nextPage() );  
 //###################################################################################
      Serial.println(); 
      request->send(200);
      });
       
      server.begin();
}
static char *itoa_simple_helper(char *dest, int i) {
  if (i <= -10) {
    dest = itoa_simple_helper(dest, i/10);
  }
  *dest++ = '0' - i%10;
  return dest;
}

char *itoa_simple(char *dest, int i) {
  char *s = dest;
  if (i < 0) {
    *s++ = '-';
  } else {
    i = -i;
  }
  *itoa_simple_helper(s, i) = '\0';
  return dest;
}
 
void loop(){
}
