// Code by Dave Gettler, 15 Sept. 2024
// Arduino Uno connected to HC-SR04 sensor, passive buzzer, and 0.96" OLED screen
// Displays the distance regardless of whether it's below or above 50 cm
// Buzzes if object is detected within 50 cm


// Connect the Trigger pin of the HC-SR04 sensor to digital pin 9 (trigPin).
// Connect the Echo pin of the HC-SR04 sensor to digital pin 10 (echoPin).
// Connect the Buzzer to digital pin 8.
// Ensure the OLED display is connected properly (SDA to A4, SCL to A5 for Arduino Uno).

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 64  // OLED display height, in pixels

// Create the OLED display object
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1); // -1 for reset pin not used

const int trigPin = 9; // Trigger pin of HC-SR04 connected to digital pin 9
const int echoPin = 10; // Echo pin of HC-SR04 connected to digital pin 10
const int buzzer = 8;

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // Initialize with I2C address 0x3C
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);

  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(buzzer, OUTPUT);
  
  digitalWrite(trigPin, LOW);
  digitalWrite(buzzer, LOW);
    
  Serial.begin(9600);
}

void loop() {
  // Display alternating messages
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Back up!");
  display.display();
  
  delay(1000);
  
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Or else!");
  display.display();
  
  delay(1000);

  // Read distance from HC-SR04 sensor
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2; // Calculate distance in cm

  // Display distance on the OLED
  display.clearDisplay();
  display.setCursor(0, 0);
  display.print("Distance: ");
  display.print(distance);
  display.println(" cm");
  display.display();
  
  // Sound buzzer if distance is less than 50 cm
  if (distance < 50) {
    tone(buzzer, 500);
  } else {
    noTone(buzzer);
  }

  // Serial output
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | ");
  Serial.print(distance / 2.54);
  Serial.println(" in");

  delay(2000);
}
