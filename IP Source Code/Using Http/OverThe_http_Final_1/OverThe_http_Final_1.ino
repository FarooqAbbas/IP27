#include <Arduino.h>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
#include "WiFi.h"
#include "ESPAsyncWebServer.h"
 
const char* ssid = "your SSID";
const char* password =  "your password";
const char* PARAM_MESSAGE = "message";
  
AsyncWebServer server(80);
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
        //Serial.write(data[i]);
        //Serial.println();
 //################################################################################  
    Serial.println(data[i]);    
    // k must be in the form of  char * to be get printed on OLED      
  }  
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_logisoso62_tn);
    
    //u8g2.drawStr(0,63,string1);  //its fine
    u8g2.drawStr(0,63,(char *)data) ;  
   } while ( u8g2.nextPage() );  
 //################################################################################### 
    Serial.println();
    request->send(200);
    }); 
   server.begin();
} 
void loop(){
}
