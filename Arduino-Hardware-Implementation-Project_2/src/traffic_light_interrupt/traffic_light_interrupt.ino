int red = 13;
int yellow = 12;
int green = 11;

int pl_green = 10;
int pl_red = 7;
int pl_button = 2; // External Interrupt pin INT0 on Arduino Uno

volatile bool button_pressed = false;

void handleButtonPress() {
  button_pressed = true;
}

void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

  pinMode(pl_green, OUTPUT);
  pinMode(pl_red, OUTPUT);
  pinMode(pl_button, INPUT);

  attachInterrupt(digitalPinToInterrupt(pl_button), handleButtonPress, RISING);
}

void loop() {
  // RED
  digitalWrite(red, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);

  digitalWrite(pl_red, HIGH);
  digitalWrite(pl_green, LOW);

  delay(5000);

  if (button_pressed) {
    pedestrianCrossing();
  }

  // YELLOW
  digitalWrite(red, HIGH);
  delay(2000);
  digitalWrite(yellow, HIGH);
  delay(2000);
  digitalWrite(red, LOW);
  digitalWrite(yellow, HIGH);
  delay(2000); // yellow totally will be high for 4seconds.

  // GREEN
  digitalWrite(yellow, LOW);
  digitalWrite(green, HIGH);
  if (button_pressed) {
    delay(5000);
  } else {
    delay(12000);
  }

  // Transition back to RED (with pedestrian crossing if requested)
  digitalWrite(green, LOW);
  digitalWrite(yellow, HIGH);
  delay(2000);

  if (button_pressed) {
    pedestrianCrossing();
  }
}

void pedestrianCrossing() {
  button_pressed = false;

  // Vehicles stop
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(red, HIGH);

  // Pedestrians will be waiting for 2 seconds
  digitalWrite(pl_red, HIGH);
  digitalWrite(pl_green, LOW);
  delay(2000);

  // Pedestrians cross for 7 seconds
  digitalWrite(pl_red, LOW);
  digitalWrite(pl_green, HIGH);
  delay(7000);

  // Pedestrians stop
  digitalWrite(pl_green, LOW);
  digitalWrite(pl_red, HIGH);
}
