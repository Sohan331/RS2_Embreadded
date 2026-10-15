/**
 * @file traffic_light_controller.ino
 * @brief Professional Non-blocking Object-Oriented Finite State Machine (FSM) Traffic Light.
 * @details Implements the modular architecture, UML class diagram, and state machine
 *          defined in system_diagram.png using clean C++ encapsulation and non-blocking timers.
 * @author Sohan
 * 
 * Hardware Pinout (Arduino Uno):
 *  - Digital Pin 8: Red LED (via 220 Ohm current-limiting resistor)
 *  - Digital Pin 6: Yellow LED (via 220 Ohm current-limiting resistor)
 *  - Digital Pin 2: Green LED (via 220 Ohm current-limiting resistor)
 *  - GND:           Common ground bus
 * 
 * State Cycle Sequence (Total: 44.5 s):
 *  1. STATE_RED:          Red ON              (Duration: 20000 ms)
 *  2. STATE_RED_YELLOW:   Red + Yellow ON     (Duration:  1500 ms)
 *  3. STATE_YELLOW:       Yellow ON           (Duration:  3000 ms)
 *  4. STATE_GREEN:        Green ON            (Duration: 20000 ms)
 */

#include <Arduino.h>

// ============================================================================
// 1. Hardware Pin Configuration & Timing Constants
// ============================================================================
constexpr uint8_t PIN_RED    = 8;
constexpr uint8_t PIN_YELLOW = 6;
constexpr uint8_t PIN_GREEN  = 2;

constexpr unsigned long DURATION_RED_MS        = 20000UL;
constexpr unsigned long DURATION_RED_YELLOW_MS =  1500UL;
constexpr unsigned long DURATION_YELLOW_MS     =  3000UL;
constexpr unsigned long DURATION_GREEN_MS      = 20000UL;

// ============================================================================
// 2. Class: Timer
//    Provides a non-blocking millis() countdown timer matching system diagram 1.3
// ============================================================================
class Timer {
private:
  unsigned long duration;
  unsigned long startTime;
  bool isRunning;

public:
  Timer() : duration(0), startTime(0), isRunning(false) {}

  void start(unsigned long durationMs) {
    duration = durationMs;
    startTime = millis();
    isRunning = true;
  }

  bool isExpired() const {
    if (!isRunning) return false;
    return (millis() - startTime >= duration);
  }

  void reset() {
    isRunning = false;
    duration = 0;
  }

  unsigned long getRemaining() const {
    if (!isRunning) return 0;
    unsigned long elapsed = millis() - startTime;
    return (elapsed >= duration) ? 0 : (duration - elapsed);
  }
};

// ============================================================================
// 3. Class: TrafficLight
//    Encapsulates each individual LED actuator matching system diagram 1.2
// ============================================================================
class TrafficLight {
private:
  uint8_t pin;
  String color;
  bool isOn;

public:
  TrafficLight(uint8_t pinNumber, const String& lightColor)
    : pin(pinNumber), color(lightColor), isOn(false) {}

  void begin() {
    pinMode(pin, OUTPUT);
    turnOff();
  }

  void turnOn() {
    digitalWrite(pin, HIGH);
    isOn = true;
  }

  void turnOff() {
    digitalWrite(pin, LOW);
    isOn = false;
  }

  void setColor(const String& newColor) {
    color = newColor;
  }

  bool getIsOn() const {
    return isOn;
  }

  const String& getColor() const {
    return color;
  }
};

// ============================================================================
// 4. State Machine Enumeration
// ============================================================================
enum class TrafficState {
  RED,
  RED_YELLOW,
  YELLOW,
  GREEN
};

// ============================================================================
// 5. Class: TrafficLightController
//    Coordinates FSM transitions and timers matching system diagram 1.1 & Section 2
// ============================================================================
class TrafficLightController {
private:
  TrafficState state;
  String currentStateName;
  Timer stateTimer;

  TrafficLight redLight;
  TrafficLight yellowLight;
  TrafficLight greenLight;

  void applyOutputs(bool redOn, bool yellowOn, bool greenOn) {
    if (redOn)    redLight.turnOn();    else redLight.turnOff();
    if (yellowOn) yellowLight.turnOn(); else yellowLight.turnOff();
    if (greenOn)  greenLight.turnOn();  else greenLight.turnOff();
  }

public:
  TrafficLightController(uint8_t rPin, uint8_t yPin, uint8_t gPin)
    : redLight(rPin, "RED"),
      yellowLight(yPin, "YELLOW"),
      greenLight(gPin, "GREEN"),
      state(TrafficState::RED),
      currentStateName("RED") {}

  void start() {
    redLight.begin();
    yellowLight.begin();
    greenLight.begin();
    changeState(TrafficState::RED);
  }

  void changeState(TrafficState newState) {
    state = newState;

    switch (state) {
      case TrafficState::RED:
        currentStateName = "RED";
        applyOutputs(true, false, false);
        stateTimer.start(DURATION_RED_MS);
        break;

      case TrafficState::RED_YELLOW:
        currentStateName = "RED_YELLOW";
        applyOutputs(true, true, false);
        stateTimer.start(DURATION_RED_YELLOW_MS);
        break;

      case TrafficState::YELLOW:
        currentStateName = "YELLOW";
        applyOutputs(false, true, false);
        stateTimer.start(DURATION_YELLOW_MS);
        break;

      case TrafficState::GREEN:
        currentStateName = "GREEN";
        applyOutputs(false, false, true);
        stateTimer.start(DURATION_GREEN_MS);
        break;
    }
  }

  void update() {
    if (stateTimer.isExpired()) {
      switch (state) {
        case TrafficState::RED:
          changeState(TrafficState::RED_YELLOW);
          break;

        case TrafficState::RED_YELLOW:
          changeState(TrafficState::YELLOW);
          break;

        case TrafficState::YELLOW:
          changeState(TrafficState::GREEN);
          break;

        case TrafficState::GREEN:
          changeState(TrafficState::RED);
          break;
      }
    }
  }

  const String& getCurrentState() const {
    return currentStateName;
  }
};

// ============================================================================
// Main Application Instance & Arduino Entry Points
// ============================================================================
TrafficLightController controller(PIN_RED, PIN_YELLOW, PIN_GREEN);

void setup() {
  Serial.begin(115200);
  controller.start();
}

void loop() {
  controller.update();
}
