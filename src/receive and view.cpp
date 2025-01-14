//ir sensor connected to PB1
//generic remote: pwr=FFA25D; 0=FFB04F; 1=FF30CF; 2=FF18E7; 3=FF7A85; 4=FF10EF ; 5=FF38C7 ; 6=FF5AA5 ;  //HEX
//generic remote: pwr=-23971; 0=-20401; 1=12495; 2=6375; 3=31365; //DEC
/*
 * Light Weight NEC Infrared decoder using interrupt instead of timer.
 *
 * 04_06_2019 v0_05 namespace model
 *
 */

#include "IrNec.h"
int16_t mssg;

void setup() {
  Serial.begin(115200);
  // Set to the pin number of an external interrupt pin and connect the IR receiver to it.
  // Uno/Nano etc. : pin2 or pin3
  // ATTINY841 : pin1 (PB1)
  // ESP8266 : Any GPIO pin apart from GPIO16
  // see attachInterrupt() for other examples and more details
  nsIrNec::begin(D5) ;  // MUST BE EXTERNAL INTERRUPT PIN 
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
    Serial.println(nsIrNec::dataOut,DEC) ;
    Serial.println(mssg);
    mssg = nsIrNec::dataOut;
    nsIrNec::dataOut = 0 ; //clear
  }
}
