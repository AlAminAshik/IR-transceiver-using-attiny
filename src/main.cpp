//ir sensor connected to PB1

#include <Arduino.h>
#include <IRremote.hpp> // include the library

const uint16_t IR_SEND_PIN = DD1; // PB1 of attiny85
#define menuButton DD2    // PB2 of attiny85


void setup() {
    IrSender.begin(IR_SEND_PIN); // Start with IR_SEND_PIN -which is defined in PinDefinitionsAndMore.h- as send pin
    pinMode(menuButton, INPUT_PULLUP);
}

void loop() {
  if (digitalRead(menuButton) == LOW){
      delay(100);
      if (digitalRead(menuButton) == LOW){
          //Serial.println("AC turn on");
          uint64_t tRawData[]={0x41006000008FC3, 0x5845002000};
          IrSender.sendPulseDistanceWidthFromArray(38, 8950, 4600, 550, 1700, 550, 600, &tRawData[0], 104, PROTOCOL_IS_LSB_FIRST, 0, 0);
      }
  }
}