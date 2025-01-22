//This code is for attiny13
//attiny13 works at 9.6MHz default and thus len and temp values are used as 2500 and 500 respectively for NEC.
//before using this code make sure attiny85 is running at 9.6Mhz and delay(1000) means 1 sec delay. use the blink sketch to verify this.
//Refer to "readme attiny 8x slow" if you are not sure about the clock speed.
//common code: pwr=17843; stop=18098;
//common code: 0=59678; 1=62228; 2=59168 ; 3=41318 ; 4=63248 ; 5=58148 ; 6=42338 ; 7=48458 ; 8=44378 ; 9=46418 ; -=63503 ; +=43102;

#include <Arduino.h>
#define irPin 1         // PB1 of attiny85
#define Fan 0           // PB0 of attiny85
#define led_1 2         // PB2 of attiny85
#define led_2 3         // PB3 of attiny85

//uint16_t pot_values[6] = {59678, 62228, 59168, 41318, 63248, 58148};


void setup() {
    cli();  // Disable interrupts
    CLKPR = (1 << CLKPCE);  // Enable Clock Prescaler Change
    CLKPR = 0b0000;  // Set prescaler to 1 (No division, full speed)
    sei();  // Enable interrupts

    pinMode(irPin, INPUT);
    pinMode(led_1, OUTPUT);
    pinMode(led_2, OUTPUT);
    pinMode(Fan, OUTPUT);
}

uint16_t getIrKey(){
  unsigned int len = pulseIn(irPin, LOW);
  unsigned int temp = 0;
	uint16_t key = 0;
  if(len > 2500) {                      //first high bit
    for(uint8_t i=1 ; i<=32 ; i++){
      temp = pulseIn(irPin, HIGH);
      if(temp > 500)                    //proceeding low bits
        key = key + (1<<(i-17));
    }
  }
  if(key < 0 )
    key = -key;

  delay(250);
  return key;
}

void loop() {
  uint16_t key = getIrKey();

	if (key != 0)
	{
		digitalWrite(led_1, HIGH);
		delay(100);
		digitalWrite(led_1, LOW);
		delay(100);
		switch (key)
		{
		case 42338: //6
			digitalWrite(led_1, HIGH);
			break;
		case 48458: //7
			digitalWrite(led_1, LOW);
			break;
		case 44378: // 8
			digitalWrite(led_2, HIGH);
			break;
		case 46418: // 9
			digitalWrite(led_2, LOW);
			break;
		case 59678: // 0
			digitalWrite(Fan, HIGH);
			break;
		case 62228: // 1
			digitalWrite(Fan, LOW);
			break;
		}
	}
}
