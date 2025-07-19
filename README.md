# SmartWasteSystem
Making Waste management smarter with ESP32 and Sensors 

A contactless, sensor-based smart dustbin system that detects user presence, checks bin fill status, and displays real-time information using an OLED screen, with LED and buzzer indicators. Built using ESP32 for reliable performance and expandability.

## Features

- Proximity detection using ultrasonic sensor
- Automatic lid opening via servo motor
- Trash level detection using IR sensor
- Real-time status display on OLED
- Green and red LED indicators for bin state
- Buzzer alert when the bin is full

## Components Used

- ESP32 Dev Board  
- HC-SR04 Ultrasonic Sensor  
- IR Proximity Sensor  
- SG90 Servo Motor  
- SSD1306 OLED Display (I2C)  
- Green & Red LEDs (with 220Ω resistors)  
- Active Buzzer  
- Breadboard and Jumper Wires  

## Pin Configuration

| Component        | ESP32 Pin |
|------------------|-----------|
| Ultrasonic TRIG  | GPIO5     |
| Ultrasonic ECHO  | GPIO18    |
| IR Sensor        | GPIO19    |
| Servo Motor      | GPIO21    |
| OLED SDA         | GPIO23    |
| OLED SCL         | GPIO22    |
| Green LED        | GPIO25    |
| Red LED          | GPIO26    |
| Buzzer           | GPIO27    |

## Required Libraries

Make sure the following libraries are installed in your Arduino IDE or added in libraries.txt (for Wokwi users):

- Adafruit_GFX  
- Adafruit_SSD1306  
- ESP32Servo  
- Wire  

##Logic Overview

cpp
Copy
Edit
if (distance <= 30) {
  lidServo.write(90); // Open lid
  digitalWrite(GREEN_LED, HIGH);
} else {
  lidServo.write(0);  // Close lid
  digitalWrite(RED_LED, HIGH);
}

if (isFull == LOW) {
  display.println("Status: FULL");
  digitalWrite(BUZZER, HIGH);
}
If an object (e.g., a user) is detected within 30 cm, the lid opens and the green LED turns on.

If no object is nearby, the lid stays closed and the red LED is turned on.

If the IR sensor detects the bin is full (active LOW), the buzzer is activated and the OLED shows "Status: FULL".

##Diagram

<img width="539" height="495" alt="image" src="https://github.com/user-attachments/assets/d71c1d8a-f375-41f2-9e2b-0f8ded3a31bc" />


##Setup Instructions
Connect all components as per the pin configuration.

Upload the code to your ESP32 board using the Arduino IDE.

Power the ESP32 using USB or a suitable power supply.

Observe the OLED screen and system behavior.

##Example OLED Output
makefile
Copy
Edit
Status: Ready
Distance: 25 cm
If the bin is full:

makefile
Copy
Edit
Status: FULL
Distance: 28 cm

Author
Avirup Bhunia



