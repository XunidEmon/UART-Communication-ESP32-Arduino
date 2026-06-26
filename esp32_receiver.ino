/*
 * ESP32 - The Listener 👂
 * Receives messages from Arduino Uno
 */

#define RX2_PIN 16  // The "ear" pin that listens

void setup() {
  // Show messages on computer screen
  Serial.begin(115200);
  
  // Start listening to Arduino Uno
  Serial2.begin(9600, SERIAL_8N1, RX2_PIN, -1);
  
  Serial.println("====================================");
  Serial.println("ESP32 is now LISTENING...");
  Serial.println("Waiting for messages from Uno");
  Serial.println("====================================");
}

void loop() {
  // Check if Uno sent something
  if (Serial2.available()) {
    
    // Read the whole message
    String message = Serial2.readStringUntil('\n');
    message.trim();  // Clean up extra spaces
    
    // Show it on computer screen
    Serial.print("📩 Received: ");
    Serial.println(message);
  }
  
  delay(100);  // Small pause
}