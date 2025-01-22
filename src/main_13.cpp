//This code is for attiny13
//attiny13 works at 9.6MHz default and thus len and temp values are used as 2500 and 500 respectively for NEC.
//before using this code make sure attiny85 is running at 9.6Mhz and delay(1000) means 1 sec delay. use the blink sketch to verify this.
//Refer to "readme attiny 8x slow" if you are not sure about the clock speed.
//common code: pwr=17843; stop=18098;
//common code: 0=59678; 1=62228; 2=59168 ; 3=41318 ; 4=63248 ; 5=58148 ; 6=42338 ; 7=48458 ; 8=44378 ; 9=46418 ; -=63503 ; +=43102;

#include <Arduino.h>
#define ir_PIN 4         // PB1 of attiny85
#define ZC_PIN 1        // Zero Crossing Detection (ZCD) pin //has interrupt and PWM
#define Fan_PIN 0           // PB0 of attiny85  //Has PWM
#define led_1_PIN 2         // PB2 of attiny85
#define led_2_PIN 3         // PB3 of attiny85

// Speed levels (lower values = faster speed)
const int speedLevels[5] = {180, 130, 90, 50, 10};  // Phase delay values //180 means off

volatile int speedIndex = 0;  // Current speed level index (0 to 4)
volatile int firingDelay = speedLevels[speedIndex];

void zeroCrossISR() {
    delayMicroseconds(firingDelay);
    digitalWrite(Fan_PIN, HIGH);
    delayMicroseconds(10);  // Short pulse to trigger TRIAC
    digitalWrite(Fan_PIN, LOW);
}


void setup() {
    cli();  // Disable interrupts
    CLKPR = (1 << CLKPCE);  // Enable Clock Prescaler Change
    CLKPR = 0b0000;  // Set prescaler to 1 (No division, full speed)
    sei();  // Enable interrupts

    pinMode(ir_PIN, INPUT_PULLUP);
    pinMode(led_1_PIN, OUTPUT);
    pinMode(led_2_PIN, OUTPUT);
    pinMode(Fan_PIN, OUTPUT);
    attachInterrupt(digitalPinToInterrupt(ZC_PIN), zeroCrossISR, RISING);
}

uint16_t getIrKey(){
  unsigned int len = pulseIn(ir_PIN, LOW);
  unsigned int temp = 0;
	uint16_t key = 0;
  if(len > 2500) {                      //first high bit
    for(uint8_t i=1 ; i<=32 ; i++){
      temp = pulseIn(ir_PIN, HIGH);
      if(temp > 500)                    //proceeding low bits
        key = key + (1<<(i-17));
    }
  }
  if(key < 0 )
    key = -key;

  delay(500);
  return key;
}

void loop() {
  uint16_t key = getIrKey();

	if (key != 0)
	{
	switch (key)
    {
    case 59678: // 0
        speedIndex = 0;
        break;
    case 62228: // 1
        speedIndex = 1;
        break;
    case 59168: // 2
        speedIndex = 2;
        break;
    case 41318: // 3
        speedIndex = 3;
        break;
    case 63248: // 4
        speedIndex = 4;
        break;
    case 58148: // 5
            digitalWrite(led_1_PIN, HIGH);
        break;
    case 42338: // 6
            digitalWrite(led_1_PIN, LOW);
        break;
    case 48458: // 7
            digitalWrite(led_2_PIN, HIGH);
        break;
    case 44378: // 8
            digitalWrite(led_2_PIN, LOW);
        break;
    }
    firingDelay = speedLevels[speedIndex]; //update speed
    }
}
