//common code: =16729531; stop=16729786;
#include <Arduino.h>
const int irPin = PB4; // PB4 of attiny85 
#define led 1    // PB0 of attiny85

// I2C display connected at PB2(Pin 7 or SCL) and PB0(Pin 5 or SDA) of attiny85
#include <Tiny4kOLED.h>

void setup() {
  //Serial.begin(115200);
  pinMode(irPin, INPUT);
  pinMode(led, OUTPUT);

  oled.begin(128, 64, sizeof(tiny4koled_init_128x64br), tiny4koled_init_128x64br);
  oled.clear();
  oled.on();
  oled.setFont(FONT8X16P);  //set double font size
  oled.print("IR Remote");
  delay(2000);
  oled.clear();
}

int getIrKey(){
  int len = pulseIn(irPin,LOW);
  int key, temp;
  oled.clear();
  key = 0;
  //Serial.print("len=");
  //Serial.println(len);
  if(len > 5000) {
    for(int i=1;i<=32;i++){
      temp = pulseIn(irPin,HIGH);
      if(temp > 1000)
        key = key + (1<<(i-17));
    }
  }
  if(key < 0 )
    key = -key;

  delay(250);
  return key;
}

void loop() {
  int key = getIrKey();
  
  if(key != 0) {
    oled.setCursor(10,10);
    oled.print(key);
  }
}
