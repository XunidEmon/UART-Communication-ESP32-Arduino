# UART-Communication-ESP32-Arduino
Learn how ESP32 and Arduino talk to each other using just 2 wires! Super simple beginner guide with full explanation.


# 📡 How ESP32 and Arduino Talk to Each Other (UART)

> **A super simple guide for beginners - Just 2 wires and 2 codes!**

---

## 🤔 What's This All About?

Have you ever wondered how two electronic devices can talk to each other? 

Think of it like two friends talking on the phone:
- One **speaks** 📢 (sends data)
- One **listens** 👂 (receives data)

That's exactly what UART (Universal Asynchronous Receiver-Transmitter) does! Just with **2 wires** instead of a phone.

---


After reading this, you'll know:
- How to connect ESP32 and Arduino Uno with just 2 wires
- How to send data from Arduino Uno to ESP32
- How to receive and display that data on your computer
- What baud rate means and why it matters

---

## What You Need

| Component | How Many |
|-----------|----------|
| ESP32 board | 1 |
| Arduino Uno | 1 |
| Jumper wires (male to female) | 2 |
| USB cables (for both boards) | 2 |


---

## Let's Connect Them!

### Just 2 Wires - Super Simple!

```
        Arduino Uno                      ESP32
       (The Speaker)                (The Listener)
    
    ┌──────────────────┐          ┌──────────────────┐
    │                  │          │                  │
    │   TX (Pin 1) ────┼──────────┼─ GPIO 16 (RX2)  │
    │                  │          │                  │
    │   GND ───────────┼──────────┼─ GND            │
    │                  │          │                  │
    └──────────────────┘          └──────────────────┘
```

### Connection Explained 

| Arduino Uno Pin | Connect To | ESP32 Pin | What This Does |
|-----------------|------------|-----------|----------------|
| **TX** (Pin 1) | → | **GPIO 16** | This is the "speaking" wire - Uno talks, ESP32 listens |
| **GND** | → | **GND** | This connects their "ground" - like holding hands |

> ⚠️ **Important Rule:** TX always goes to RX!
> 
> 
> - Uno's **T**ransmit goes to ESP32's **R**eceive
> - **T** → **R** (not T → T!)

---

## 💻 Code 1: Arduino Uno (The One That Talks)

**File:** `Arduino_Transmitter/arduino_transmitter.ino`

```cpp
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
```

### What This Code Does:

| Line | Plain English |
|------|---------------|
| `int counter = 0;` | Creates a counter starting at 0 |
| `Serial.begin(9600);` | Starts communication at 9600 speed |
| `counter = counter + 1;` | Each time, counter goes up by 1 |
| `Serial.print("Hello ESP32! Number: ");` | Sends the text |
| `Serial.println(counter);` | Sends the number and moves to next line |
| `delay(2000);` | Waits 2 seconds before sending again |

---

## 💻 Code 2: ESP32 (The One That Listens)

**File:** `ESP32_Receiver/esp32_receiver.ino`

```cpp
/*
 * ESP32 - The Listener 
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
```

### What This Code Does:

| Line | Plain English |
|------|---------------|
| `#define RX2_PIN 16` | Tells ESP32 which pin to listen on |
| `Serial.begin(115200);` | Shows messages on computer at 115200 speed |
| `Serial2.begin(9600, SERIAL_8N1, RX2_PIN, -1);` | Starts listening to Uno at 9600 speed |
| `Serial2.available()` | Checks if Uno sent anything |
| `Serial2.readStringUntil('\n')` | Reads the whole message |
| `Serial.println(message)` | Shows the message on computer |

---

##  How It Works (Step by Step)

### The Flow:

```
1️⃣ Start Both Devices
   ┌────────────┐          ┌────────────┐
   │ Arduino Uno│          │   ESP32    │
   │ "I'm ready!"│          │ "I'm ready!"│
   └────────────┘          └────────────┘

2️⃣ Uno Sends First Message
   ┌────────────┐          ┌────────────┐
   │ Arduino Uno│ ──────► │   ESP32    │
   │ "Hello! 1" │   UART   │  receives  │
   └────────────┘          └────────────┘

3️⃣ ESP32 Shows It
   ┌────────────┐          ┌────────────┐
   │   ESP32    │          │ Computer   │
   │ "Hello! 1" │ ──────► │  Screen    │
   └────────────┘          │📩Received:1│
                            └────────────┘

4️⃣ Repeat Every 2 Seconds
   Counter goes: 1 → 2 → 3 → 4 → 5...
```

---

##  What You'll See

### ESP32 Serial Monitor:
```
====================================
ESP32 is now LISTENING...
Waiting for messages from Uno
====================================
📩 Received: Hello ESP32! Number: 1
📩 Received: Hello ESP32! Number: 2
📩 Received: Hello ESP32! Number: 3
📩 Received: Hello ESP32! Number: 4
📩 Received: Hello ESP32! Number: 5
📩 Received: Hello ESP32! Number: 6
```

### Arduino Uno Serial Monitor:
```
Hello ESP32! Number: 1
Hello ESP32! Number: 2
Hello ESP32! Number: 3
Hello ESP32! Number: 4
Hello ESP32! Number: 5
```

---

## 🛠️ Step-by-Step Setup Guide

### Step 1: Connect Hardware
```
Arduino Uno TX (Pin 1) → ESP32 GPIO 16 (RX2)
Arduino Uno GND        → ESP32 GND
```

### Step 2: Upload Code to Arduino Uno
1. Open `arduino_transmitter.ino` in Arduino IDE
2. Select **Tools → Board → Arduino Uno**
3. Select correct **Port**
4. Click **Upload** (→) button

### Step 3: Upload Code to ESP32
1. Open `esp32_receiver.ino` in Arduino IDE
2. Select **Tools → Board → ESP32 Dev Module**
3. Select correct **Port**
4. Click **Upload** (→) button

### Step 4: Open Serial Monitor
1. For ESP32: **Tools → Serial Monitor** (set baud to **115200**)
2. For Uno: **Tools → Serial Monitor** (set baud to **9600**)
3. Watch messages appear!

---

## 🔧 Common Problems and Fixes

| Problem | Why It Happens | How to Fix |
|---------|----------------|------------|
| **No messages appear** | Wrong wiring | Check: TX→RX (not TX→TX) |
| **Strange symbols like "⸮⸮⸮"** | Baud rate mismatch | Both must be 9600! |
| **ESP32 screen is blank** | Wrong baud rate on Serial Monitor | Set to 115200 |
| **Uno screen is blank** | Wrong baud rate on Serial Monitor | Set to 9600 |

### Quick Checklist:
- [ ] Did you connect TX to RX? (Not TX to TX!)
- [ ] Did you connect GND to GND?
- [ ] Did you set both devices to 9600 baud?
- [ ] Are both devices powered on?
- [ ] Did you upload the right code to each device?

---

##  Want to Customize It?

### Change the Message:
```cpp
// Change this line
Serial.print("Hello ESP32! Number: ");
// To this
Serial.print(" Sensor Reading: ");
```

### Change the Speed:
```cpp
// Both devices must match!
Serial.begin(9600);  // Can be 9600, 115200, etc.
```

### Send Sensor Data Instead:
```cpp
int sensorValue = analogRead(A0);  // Read sensor
Serial.println(sensorValue);        // Send it
```

---

## 🎓 Key Terms Explained

| Term | What It Means | Easy Analogy |
|------|---------------|--------------|
| **UART** | How two devices talk with 2 wires | Like two people talking |
| **TX** | Transmit - Sends data | The person speaking |
| **RX** | Receive - Listens for data | The person listening |
| **Baud Rate** | Speed of communication | How fast they talk |
| **Serial** | Arduino's way to send data | Uno's voice |
| **Serial2** | ESP32's way to receive data | ESP32's ears |

---


---

##  What's Next?

Once you understand this, try these:

| Project | What You'll Do |
|---------|----------------|
| 📊 **Send Sensor Data** | Send temperature/humidity readings |
| 🎮 **Control Things** | Send commands to turn on/off devices |
| ☁️ **IoT Projects** | Send data to the internet |
| 📱 **Two-Way Talk** | Both devices send AND receive |
| 🏠 **Smart Home** | Control appliances remotely |

---
