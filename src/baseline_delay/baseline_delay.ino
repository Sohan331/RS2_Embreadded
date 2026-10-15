/**
 * @file baseline_delay.ino
 * @brief Sequential Arduino traffic light controller implementation using delay().
 * @author Sohan
 * 
 * Hardware Pinout (Arduino Uno):
 *  - Digital Pin 8: Red LED (via 220 Ohm current-limiting resistor)
 *  - Digital Pin 6: Yellow LED (via 220 Ohm current-limiting resistor)
 *  - Digital Pin 2: Green LED (via 220 Ohm current-limiting resistor)
 *  - GND:           Common ground rail
 * 
 * Cycle Timing (44.5 s full period):
 *  - Phase 1 (RED):           20.0 s
 *  - Phase 2 (RED + YELLOW):   1.5 s  (Pre-green transition)
 *  - Phase 3 (YELLOW):         3.0 s  (Warning / caution phase)
 *  - Phase 4 (GREEN):         20.0 s
 */

// Pin definitions
const int redPin    = 8;
const int yellowPin = 6;
const int greenPin  = 2;

void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  // Phase 1: Red light ON for 20 seconds
  digitalWrite(redPin, HIGH);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, LOW);
  delay(20000);

  // Phase 2: Red + Yellow lights ON for 1.5 seconds (Transition effect)
  digitalWrite(redPin, HIGH);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(greenPin, LOW);
  delay(1500);

  // Phase 3: Yellow light ON for 3 seconds (Warning phase)
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, HIGH);
  digitalWrite(greenPin, LOW);
  delay(3000);

  // Phase 4: Green light ON for 20 seconds
  digitalWrite(redPin, LOW);
  digitalWrite(yellowPin, LOW);
  digitalWrite(greenPin, HIGH);
  delay(20000);
}
