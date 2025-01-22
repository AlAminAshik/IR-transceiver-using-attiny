// #include <Arduino.h>
// #define led_1 2         // PB2 of attiny85
// #define led_2 3         // PB3 of attiny85


// void setup(){   
//     cli();  // Disable interrupts
//     CLKPR = (1 << CLKPCE);  // Enable Clock Prescaler Change
//     CLKPR = 0b0000;  // Set prescaler to 1 (No division, full speed)
//     sei();  // Enable interrupts

//     pinMode(led_1, OUTPUT);
//     pinMode(led_2, OUTPUT);
// }

// void loop(){
//     digitalWrite(led_1, HIGH);
//     delay(1000);
//     digitalWrite(led_1, LOW);
//     delay(1000);
//     digitalWrite(led_2, HIGH);
//     delay(1000);
//     digitalWrite(led_2, LOW);
//     delay(1000);
// }