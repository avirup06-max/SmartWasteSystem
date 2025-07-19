#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP32Servo.h>

// OLED setup
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Pins
#define TRIG_PIN 5
#define ECHO_PIN 18
#define IR_SENSOR 19
#define SERVO_PIN 21
#define GREEN_LED 25
#define RED_LED 26
#define BUZZER 27

Servo lidServo;

void setup() {
  Serial.begin(115200);
 
  // Initialize I2C
  Wire.begin(23, 22); // REQUIRED for Wokwi + ESP32


  // Pin modes
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(IR_SENSOR, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  lidServo.attach(SERVO_PIN);

  // OLED setup
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("OLED failed"));
    while (1);
  }
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(0, 0);
  display.println("Smart Dustbin Ready");
  display.display();

  lidServo.write(0); // Start closed
}

long getDistanceCM() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  long duration = pulseIn(ECHO_PIN, HIGH);
  return duration * 0.034 / 2; // cm
}

void loop() {
  long distance = getDistanceCM();
  bool isFull = digitalRead(IR_SENSOR);

  if (distance <= 30) {
    // Person detected
    lidServo.write(90); // Open
    digitalWrite(GREEN_LED, HIGH);
    digitalWrite(RED_LED, LOW);
  } else {
    // No one nearby
    lidServo.write(0); // Close
    digitalWrite(GREEN_LED, LOW);
    digitalWrite(RED_LED, HIGH);
  }

  // OLED display
  display.clearDisplay();
  display.setCursor(0, 0);

  if (isFull == LOW) {
    // Bin Full (Assuming active-low IR sensor)
    display.println("Status: FULL");
    digitalWrite(BUZZER, HIGH);
  } else {
    display.println("Status: Ready");
    digitalWrite(BUZZER, LOW);
  }

  display.setCursor(0, 20);
  display.print("Distance: ");
  display.print(distance);
  display.println(" cm");

  display.display();
  delay(500);
}