//common code: PWR=FFA25D; 0=FFB04F;
//ir sensor connected to PB1

#include <Arduino.h>
#include "IrNec.h" // include the library

#define led D2    // PB2 of attiny85


void setup() {
  Serial.begin(115200);
  
  nsIrNec::begin(D5) ;  // MUST BE EXTERNAL INTERRUPT PIN
  pinMode(led, OUTPUT);
  
}

void loop() {
  nsIrNec::loop() ;   // check for new data

  if ( nsIrNec::dataOut != 0 ) {
    // // print raw data
    // for ( uint8_t i = 0 ; i < 32 ; i++ )   {
    //   Serial.print( bitRead( nsIrNec::dataRaw, i ) ) ;
    //   if ( (i+1) % 8 == 0  ) Serial.print(' ' ) ;
    // }

    // print interpreted data then reset it
    Serial.println(nsIrNec::dataOut,HEX) ;
    if (nsIrNec::dataOut == 0xFFA25D) {
      digitalWrite(led, HIGH);
      delay(100);
      digitalWrite(led, LOW);
    }
    Serial.println();
    nsIrNec::dataOut = 0 ; //clear
  }
}