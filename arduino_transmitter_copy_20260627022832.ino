/*
 * Arduino Uno - The Speaker 📢
 * Sends messages to ESP32 every 2 seconds
 */

int counter = 0;  // This will count 1, 2, 3, 4...

void setup() {
  Serial.begin(9600);  // Start talking at "speed 9600"
}

void loop() {
  counter = counter + 1;  // Add 1 to counter

  // Send message to ESP32
  Serial.print("Hello ESP32! Number: ");
  Serial.println(counter);

  delay(2000);  // Wait 2 seconds before sending again
}