
#include "WiFi.h"
#include <String>
#include <U8g2lib.h>
#ifdef U8X8_HAVE_HW_SPI
#include <SPI.h>
#include <U8x8lib.h>
#endif
#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif


//U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 15, /* data=*/ 4, /* reset=*/ 16); for esp32
U8X8_SSD1306_128X64_NONAME_SW_I2C u8x8(/* clock=*/ 22, /* data=*/ 21); //for groove oled
const char* ssid     = "";
const char* password = "";

/* create a server and listen on port 8088 */
WiFiServer server(80);
void setup()
{
    Serial.begin(115200);
    u8x8.begin(); 
    u8x8.setFont(u8x8_font_chroma48medium8_r);
    //u8x8.drawString(0, 1, "IP PROJECT 27");
    Serial.print("Connecting to ");
    Serial.println(ssid);
    /* connecting to WiFi */
    WiFi.begin(ssid, password);
    /*wait until ESP32 connect to WiFi*/
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected with IP address: ");
    Serial.println(WiFi.localIP());
    /* start Server */
    server.begin();
}
void loop(){
    /* listen for client */
    WiFiClient client = server.available(); 
    
    uint8_t data[30]; 
    if (client) {                   
      Serial.println("new client");         
      /* check client is connected */           
     while (client.connected()) { 
        //if(client.connected()) {        
          if (client.available()) {
              int len = client.read(data, 30);
              if(len < 30){
                  data[len] = '\0';  
              }else {
                  data[30] = '\0';
              }    

              Serial.print("client sent: ");            
              Serial.println((char *)data);               
              //u8x8.drawString(0, 1, "Pick Items");
              u8x8.drawString(0,1, (char *)data);
          }
      } 
    }
}
