int red = 13;
int yellow = 12;
int green = 11;

int pl_green = 10;
int pl_red = 7;
int pl_button = 2;

int button_state = LOW;

void setup() {
  pinMode(red, OUTPUT);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);

  pinMode(pl_green, OUTPUT);
  pinMode(pl_red, OUTPUT);
  pinMode(pl_button, INPUT);
}

void loop() {
  // RED
  digitalWrite(red, HIGH);
  digitalWrite(yellow, LOW);
  digitalWrite(green, LOW);

  digitalWrite(pl_red, HIGH);
  digitalWrite(pl_green, LOW);

  delay(5000);

  button_state = digitalRead(pl_button);

  switch (button_state) {
    case HIGH:
      pedestrianCrossing();
      break;

    case LOW:
      break;
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
  button_state = digitalRead(pl_button);
  switch (button_state) {
    case LOW:
      digitalWrite(yellow, LOW);
      digitalWrite(green, HIGH);
      delay(7000);
    case HIGH:
      digitalWrite(yellow, LOW);
      digitalWrite(green, HIGH);
      delay(5000);
  }

  button_state = digitalRead(pl_button);

  switch (button_state) {
    case HIGH:
      digitalWrite(green, LOW);
      digitalWrite(yellow, HIGH);
      delay(2000);
      pedestrianCrossing();
      break;

    case LOW:
      digitalWrite(green, LOW);
      digitalWrite(yellow, HIGH);
      delay(2000);
      break;
  }
}

void pedestrianCrossing() {
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
