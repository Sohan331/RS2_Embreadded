int red = 13;
int yellow = 12;
int green = 11;

int pl_green = 10;
int pl_red = 7;
int pl_button = 2;

volatile bool pedestrianRequest = false;   // the flag: false = 0, true = 1

void buttonPressed() {          // the ISR: keep it tiny
  pedestrianRequest = true;
}

void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

  pinMode(pl_green, OUTPUT);
  pinMode(pl_red, OUTPUT);
  pinMode(pl_button, INPUT);

  attachInterrupt(digitalPinToInterrupt(pl_button), buttonPressed, RISING);
}

void loop() {
  // RED
  digitalWrite(red, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);

  digitalWrite(pl_red, HIGH);
  digitalWrite(pl_green, LOW);

  delay(5000);

  switch (pedestrianRequest) {
    case true:
      pedestrianCrossing();
      break;

    case false:
      break;
  }

  // RED + YELLOW, then YELLOW
  digitalWrite(red, HIGH);
  delay(2000);
  digitalWrite(yellow, HIGH);
  delay(2000);
  digitalWrite(red, LOW);
  digitalWrite(yellow, HIGH);
  delay(2000);

  // GREEN
  digitalWrite(yellow, LOW);
  digitalWrite(green, HIGH);

  switch (pedestrianRequest) {
    case true:
      delay(5000);      // someone is waiting -> shorter green
      break;

    case false:
      delay(7000);
      break;
  }

  // GREEN -> YELLOW
  digitalWrite(green, LOW);
  digitalWrite(yellow, HIGH);
  delay(2000);

  switch (pedestrianRequest) {
    case true:
      pedestrianCrossing();
      break;

    case false:
      break;
  }
}

void pedestrianCrossing() {
  // Vehicles stop
  digitalWrite(green, LOW);
  digitalWrite(yellow, LOW);
  digitalWrite(red, HIGH);

  // Pedestrians wait 2 seconds
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

  pedestrianRequest = false;   // work is done -> reset the flag (your f = 0)
}
