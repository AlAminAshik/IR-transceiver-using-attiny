// //common code: pwr=16729531; stop=16729786; //esp
// //common code: pwr=17843; stop=18098; //attiny85
// //common code: 0=59678; 1=62228; 2=59168 ; 3=41318 ; 4=63248 ; 5=58148 ; 6=42338 ; 7=48458 ; 8=44378 ; 9=46418 ; -=63503 ; +=43102; //attiny85

// #include <Arduino.h>
// #define irPin 1       // PB1 of attiny85
// #define led 3         // PB3 of attiny85
// uint16_t key;

// // I2C display connected at PB2(Pin 7 or SCL) and PB0(Pin 5 or SDA) of attiny85
// #include <Tiny4kOLED.h>

// void setup() {
//   //Serial.begin(115200);
//   pinMode(irPin, INPUT);
//   pinMode(led, OUTPUT);

//   oled.begin(128, 64, sizeof(tiny4koled_init_128x64br), tiny4koled_init_128x64br);
//   oled.setOffset(3, 0);
//   oled.clear();
//   oled.on();
//   oled.setFont(FONT8X16P);  //set double font size
//   oled.print("OK");
//   delay(2000);
//   oled.clear();
// }

// uint16_t getIrKey(){
//   unsigned int len = pulseIn(irPin, LOW);
//   unsigned int temp = 0;
//   key = 0;
//   //Serial.println(len);
//   if(len > 5000) {
//     for(uint8_t i=1 ; i<=32 ; i++){
//       temp = pulseIn(irPin, HIGH);
//       if(temp > 1000)
//         key = key + (1<<(i-17));
//     }
//   }
//   if(key < 0 )
//     key = -key;

//   delay(250);
//   return key;
// }

// void loop() {
//   getIrKey();
  
//   if(key != 0) {
//     //Serial.println(key);
//     oled.clear();
//     oled.setCursor(20,10);
//     oled.print(key);
//     if(key == 167){
//       digitalWrite(led, HIGH);
//     }
//     else if(key == 16729){
//       digitalWrite(led, LOW);
//     }
//   }
// }
