// #include <Arduino.h>  
// #define IR_PIN D5  // Pin connected to IR receiver
// #define LED_PIN D2 // Pin connected to LED

// void setup() {
//   Serial.begin(115200);
//   pinMode(IR_PIN, INPUT);
//   pinMode(LED_PIN, OUTPUT);
//   digitalWrite(D2, HIGH);
//   delay(1000);
//   digitalWrite(D2, LOW);
// }


// // Function to decode NEC protocol
// unsigned long decodeNEC() {
//   unsigned long data = 0;

//   // Wait for the start signal (9ms high + 4.5ms low)
//   if (pulseIn(IR_PIN, LOW, 12000) < 8500) return 0; // Adjusted timing
//   if (pulseIn(IR_PIN, HIGH, 6000) < 4000) return 0; // Adjusted timing

//   // Read 32 bits of data
//   for (int i = 0; i < 32; i++) {
//     unsigned long pulseLength = pulseIn(IR_PIN, LOW, 2000);
//     if (pulseLength > 1600) {        // Logical '1'
//       data = (data << 1) | 1;
//     } else if (pulseLength > 400) { // Logical '0'
//       data = (data << 1);
//     } else {
//       return 0; // Invalid signal
//     }
//   }

//   return data;
// }

// void loop() {
//   unsigned long irData = decodeNEC();
//   if (irData == 0xFFA25D) { // Check for NEC code 0xFFA25D
//     digitalWrite(LED_PIN, HIGH);
//     delay(100);
//     digitalWrite(LED_PIN, LOW);
//   }
//   Serial.println(irData, HEX);
//   delay(1000) ;
// }

