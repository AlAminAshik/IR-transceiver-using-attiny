//ir sensor connected to PB1
//generic remote: pwr=FFA25D; 0=FFB04F; 1=FF30CF; 2=FF18E7; 3=FF7A85; 4=FF10EF ; 5=FF38C7 ; 6=FF5AA5 ;
/*
 * Light Weight NEC Infrared decoder using interrupt instead of timer.
 *
 * 04_06_2019 v0_05 namespace model
 *
 */

#include "IrNec.h"
#include <ss_oled.h>

char mssg;

//for oled
// Use -1 for the Wire library default pins
#define SDA_PIN -1
#define SCL_PIN -1
#define RESET_PIN -1
#define OLED_ADDR -1
// don't rotate the display
#define FLIP180 0
// don't invert the display
#define INVERT 0
// Bit-Bang the I2C bus
#define USE_HW_I2C 0
#define MY_OLED OLED_64x32
#define OLED_WIDTH 64
#define OLED_HEIGHT 32
SSOLED ssoled;
int rc;

void setup() {
  Serial.begin(115200);
  // Set to the pin number of an external interrupt pin and connect the IR receiver to it.
  // Uno/Nano etc. : pin2 or pin3
  // ATTINY841 : pin1 (PB1)
  // ESP8266 : Any GPIO pin apart from GPIO16
  // see attachInterrupt() for other examples and more details
  nsIrNec::begin(D5) ;  // MUST BE EXTERNAL INTERRUPT PIN 

  //for oled
  rc = oledInit(&ssoled, MY_OLED, OLED_ADDR, FLIP180, INVERT, USE_HW_I2C, SDA_PIN, SCL_PIN, RESET_PIN, 400000L); // use standard I2C bus at 400Khz
  if (rc != OLED_NOT_FOUND)
  {
    char *msgs[] = {(char *)"SSD1306 @ 0x3C", (char *)"SSD1306 @ 0x3D",(char *)"SH1106 @ 0x3C",(char *)"SH1106 @ 0x3D",(char *)"SH1107 @ 0x3C",(char *)"SH1107 @ 0x3D"};
    oledFill(&ssoled, 0, 1);
    oledWriteString(&ssoled, 0,0,0,msgs[rc], FONT_NORMAL, 0, 1);
    delay(2000);
  }
}

void loop() {

  nsIrNec::loop() ;   // check for new data

  if ( nsIrNec::dataOut != 0 ) {
    // // print raw data in bin format
    // for ( uint8_t i = 0 ; i < 32 ; i++ )   {
    //   Serial.print( bitRead( nsIrNec::dataRaw, i ) ) ;
    //   if ( (i+1) % 8 == 0  ) Serial.print(' ' ) ;
    // }
    // Serial.println();

    // print interpreted data then reset it
    Serial.println(nsIrNec::dataOut,HEX) ;
    Serial.println();
    mssg = nsIrNec::dataOut;
    nsIrNec::dataOut = 0 ; //clear
  }

  oledFill(&ssoled, 0x0, 1);
  oledWriteString(&ssoled, 0,16,0,(char *)mssg, FONT_NORMAL, 0, 0);
}
