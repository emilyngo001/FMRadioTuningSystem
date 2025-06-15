#include <LiquidCrystal.h>

// Define digital pins for preset buttons and strongest station button
#define PRESET1    2
#define PRESET2    3
#define PRESET3    4
#define PRESET4    5
#define STRONGEST  6

// Define analog pin for tuning from the potentiometer
#define TUNING_PIN A0

// Initializing LCD with RS, EN, D4, D5, D6, D7 pinout
const int rs = 23, en = 25, d4 = 27, d5 = 29, d6 = 31, d7 = 33;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Last potentiometer value
int lastPotVal = -1;

void setup() {
  // Starting serial communication with laptop
  Serial.begin(9600);

  // Set all button pins as inputs with internal pull-up resistors
  pinMode(PRESET1, INPUT_PULLUP);
  pinMode(PRESET2, INPUT_PULLUP);
  pinMode(PRESET3, INPUT_PULLUP);
  pinMode(PRESET4, INPUT_PULLUP);
  pinMode(STRONGEST, INPUT_PULLUP);

  // Initializing the LCD and display start screen
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("FM Radio Tuner");
  delay(1000);
}

void loop() {
  // Checking which button is pressed and corresponding it with serial command so that 
  // it can be used for serial communication to interact with the python script
  if (digitalRead(PRESET1) == LOW) {
    Serial.println("PRESET1");
    delay(100);
  } else if (digitalRead(PRESET2) == LOW) {
    Serial.println("PRESET2");
    delay(100);
  } else if (digitalRead(PRESET3) == LOW) {
    Serial.println("PRESET3");
    delay(100);
  } else if (digitalRead(PRESET4) == LOW) {
    Serial.println("PRESET4");
    delay(100);
  } else if (digitalRead(STRONGEST) == LOW) {
    Serial.println("STRONGEST");
    delay(100);
  }

  // Read potentiometer and send if changed
  int potVal = analogRead(TUNING_PIN);
  if (abs(potVal - lastPotVal) > 4) {
    lastPotVal = potVal;
    Serial.print("POT:");
    Serial.println(potVal);
  }

  // Check for incoming serial messages from the python script
  if (Serial.available()) {
    String line = Serial.readStringUntil('\n');
    lcd.clear();

    // Based on the python script serial messages, it will display Tuning, Loading, Scanning, FM
    if (line.startsWith("TUNING:")) {
      lcd.setCursor(0, 0);
      lcd.print("Tuning:");
      lcd.setCursor(0, 1);
      lcd.print(line.substring(7));
    } else if (line.startsWith("LOADING:")) {
      lcd.setCursor(0, 0);
      lcd.print("Loading:");
      lcd.setCursor(0, 1);
      lcd.print(line.substring(8));
    } else if (line.startsWith("SCANNING:")) {
      lcd.setCursor(0, 0);
      lcd.print("Scanning:");
      lcd.setCursor(0, 1);
      lcd.print(line.substring(9));
    } else if (line.startsWith("FM:")) {
      lcd.setCursor(0, 0);
      lcd.print("FM");
      lcd.setCursor(0, 1);
      lcd.print(line.substring(3));
    } else {
      lcd.setCursor(0, 0);
      lcd.print(line);
    }
  }

  delay(100);  // delay so that there isn't any overlapping
}