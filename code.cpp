#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD. Set the address to 0x27 or 0x3F depending on your I2C module
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define pins
const int sensorPin = 2;      // IR sensor input pin
const int ledPin = 8;         // LED output
const int buzzerPin = 9;      // Buzzer output

void setup() {
  // Set pin modes
  pinMode(sensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  // Start serial communication
  Serial.begin(9600);

  // Initialize LCD
  lcd.init();
  lcd.backlight();

  // Initial display
  lcd.setCursor(0, 0);
  lcd.print("Railway Track");
  lcd.setCursor(0, 1);
  lcd.print(" Monitoring...");
  delay(2000); // Wait for 2 seconds
  lcd.clear();
}

void loop() {
  int sensorValue = digitalRead(sensorPin);

  if (sensorValue == LOW) {
    // Crack detected
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("!! WARNING !!");
    lcd.setCursor(0, 1);
    lcd.print("Crack Detected");

    Serial.println("\u26A0\uFE0F Crack Detected on Track!");

  } else {
    // Track is safe
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Track Status:");
    lcd.setCursor(0, 1);
    lcd.print("All Clear");

    Serial.println("\u2705 Track is Safe.");
  }

  delay(1000); // Wait for 1 second before next reading
}
