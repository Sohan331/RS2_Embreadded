# Arduino Traffic Light Controller (FSM)

[![Platform: Arduino Uno](https://img.shields.io/badge/Platform-Arduino%20Uno-00979D?logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![Language: C++](https://img.shields.io/badge/Language-C%2B%2B-00599C?logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Architecture: FSM](https://img.shields.io/badge/Architecture-Finite%20State%20Machine-orange)](#system-architecture--fsm-design)
[![Simulation: Tinkercad](https://img.shields.io/badge/Simulated%20on-Tinkercad-blue?logo=autodesk&logoColor=white)](https://www.tinkercad.com/things/83Owepj9sud-traffic-light-simulation)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

An embedded traffic control system developed for the **Arduino Uno (ATmega328P)**. The project models an automated four-phase junction signal using an object-oriented **Finite State Machine (FSM)** architecture and non-blocking timers.

A baseline sequential implementation is also provided for pedagogical comparison.

---

## Table of Contents

- [Overview](#overview)
- [Cycle Timing & Signal Sequence](#cycle-timing--signal-sequence)
- [Hardware & Circuit Design](#hardware--circuit-design)
  - [Pin Mapping](#pin-mapping)
  - [Electrical Specifications & Resistor Sizing](#electrical-specifications--resistor-sizing)
  - [Circuit Diagram](#circuit-diagram)
- [System Architecture & FSM Design](#system-architecture--fsm-design)
  - [State Transition Model](#state-transition-model)
  - [UML Class Diagram](#uml-class-diagram)
  - [System Architecture Diagram](#system-architecture-diagram)
- [Firmware Implementation](#firmware-implementation)
- [Simulation & CAD Assets](#simulation--cad-assets)
- [Repository Structure](#repository-structure)
- [Getting Started](#getting-started)
- [License](#license)

---

## Overview

Road traffic controllers require deterministic timing, failsafe light transitions, and modular software design. This project realizes a full 4-phase traffic cycle totaling **44.5 seconds**:

1. **Red** (Stop): 20.0 s
2. **Red + Yellow** (Pre-green transition): 1.5 s
3. **Yellow** (Caution / Warning): 3.0 s
4. **Green** (Proceed): 20.0 s

Both the hardware schematic and state machine architecture were validated in Autodesk Tinkercad and formalized with UML class models.

---

## Cycle Timing & Signal Sequence

| Phase | State Name | Active LEDs | Duration | Purpose / Vehicle Meaning |
|:---:|:---|:---:|:---:|:---|
| **1** | `STATE_RED` | **Red** | `20.0 s` | Traffic stop / cross-traffic clearance |
| **2** | `STATE_RED_YELLOW` | **Red + Yellow** | `1.5 s` | Driver preparation before green |
| **3** | `STATE_YELLOW` | **Yellow** | `3.0 s` | Warning / caution transition |
| **4** | `STATE_GREEN` | **Green** | `20.0 s` | Right-of-way granted / traffic flow |

$$\text{Total Cycle Duration} = 20.0\,\text{s} + 1.5\,\text{s} + 3.0\,\text{s} + 20.0\,\text{s} = \mathbf{44.5\,\text{s}}$$

---

## Hardware & Circuit Design

### Pin Mapping

| Arduino Pin | Variable Name | Component | Direction | Current Limiter | Description |
|---|---|---|---|---|---|
| **Digital Pin 8** | `PIN_RED` | Red 5 mm LED | `OUTPUT` | $220\,\Omega$ | Red stop indicator |
| **Digital Pin 6** | `PIN_YELLOW` | Yellow 5 mm LED | `OUTPUT` | $220\,\Omega$ | Yellow caution indicator |
| **Digital Pin 2** | `PIN_GREEN` | Green 5 mm LED | `OUTPUT` | $220\,\Omega$ | Green proceed indicator |
| **GND** | — | Breadboard bus | — | — | Common cathode return |

### Electrical Specifications & Resistor Sizing

The Arduino Uno supplies $V_{CC} = 5.0\,\text{V}$ from its ATmega328P I/O pins (max $40\,\text{mA}$ per pin absolute maximum, recommended $\le 20\,\text{mA}$). Standard current-limiting resistors were calculated using Ohm's Law:

$$R = \frac{V_{CC} - V_F}{I_F}$$

* Forward Voltage ($V_F$): $\approx 2.0\,\text{V}$
* Target Forward Current ($I_F$): $\approx 13.6\,\text{mA}$
* Ideal Resistance: $R = \frac{5.0 - 2.0}{0.0136} \approx 220\,\Omega$

Standard $220\,\Omega \pm 5\%$ (Red-Red-Brown-Gold) through-hole resistors protect each LED diode from overcurrent.

### Circuit Diagram

![Circuit Diagram](docs/circuit_diagram.png)

> Interactive Tinkercad Circuit: [View Simulation](https://www.tinkercad.com/things/83Owepj9sud-traffic-light-simulation)

---

## System Architecture & FSM Design

### State Transition Model

```mermaid
stateDiagram-v2
    [*] --> RED: System Boot / Reset
    RED --> RED_YELLOW: Timer Expired (20.0 s)
    RED_YELLOW --> YELLOW: Timer Expired (1.5 s)
    YELLOW --> GREEN: Timer Expired (3.0 s)
    GREEN --> RED: Timer Expired (20.0 s)
```

### UML Class Diagram

The production firmware separates concerns between hardware actuators, non-blocking timing primitives, and high-level state arbitration:

```mermaid
classDiagram
    class Timer {
        -duration : unsigned long
        -startTime : unsigned long
        -isRunning : bool
        +start(durationMs : unsigned long) void
        +isExpired() bool
        +reset() void
        +getRemaining() unsigned long
    }

    class TrafficLight {
        -pin : uint8_t
        -color : String
        -isOn : bool
        +begin() void
        +turnOn() void
        +turnOff() void
        +setColor(newColor : String) void
        +getIsOn() bool
        +getColor() String
    }

    class TrafficLightController {
        -state : TrafficState
        -currentStateName : String
        -stateTimer : Timer
        -redLight : TrafficLight
        -yellowLight : TrafficLight
        -greenLight : TrafficLight
        -applyOutputs(redOn, yellowOn, greenOn) void
        +start() void
        +changeState(newState : TrafficState) void
        +update() void
        +getCurrentState() String
    }

    TrafficLightController --> "1" Timer : manages
    TrafficLightController --> "3" TrafficLight : controls
```

### System Architecture Diagram

![System Architecture and Class Diagram](docs/system_diagram.png)

* Full-resolution drawing: [Google Drive Link](https://drive.google.com/file/d/1RoIWKrtxsQdbZA15A9k0wHQC-ORTJWj-/view)
* Draw.io Editable Source: [`docs/EmbeddedPractical.drawio`](docs/EmbeddedPractical.drawio)

---

## Firmware Implementation

The repository includes two implementations under [`src/`](src/):

1. **Production FSM (`src/traffic_light_controller/traffic_light_controller.ino`)**:
   - Encapsulated into `TrafficLightController`, `TrafficLight`, and `Timer` classes.
   - Non-blocking `millis()` architecture avoids CPU stalls.
   - Extensible for sensor inputs (e.g., pedestrian crossing buttons, inductive loops).

2. **Sequential Baseline (`src/baseline_delay/baseline_delay.ino`)**:
   - Classical linear prototype using sequential `delay()` calls.
   - Ideal for initial hardware bring-up and breadboard continuity checks.

---

## Simulation & CAD Assets

* **Tinkercad Simulation**: [https://www.tinkercad.com/things/83Owepj9sud-traffic-light-simulation](https://www.tinkercad.com/things/83Owepj9sud-traffic-light-simulation)
* **High-Resolution Diagram (Drive)**: [Full Size System Diagram](https://drive.google.com/file/d/1RoIWKrtxsQdbZA15A9k0wHQC-ORTJWj-/view)
* **Draw.io Schematic Source**: [`docs/EmbeddedPractical.drawio`](docs/EmbeddedPractical.drawio)

---

## Repository Structure

```text
RS2_Embreadded/
├── .gitignore
├── LICENSE
├── README.md
├── docs/
│   ├── circuit_diagram.png         # Breadboard wiring and pin connections
│   ├── system_diagram.png          # UML class & state machine diagrams
│   └── EmbeddedPractical.drawio    # Editable diagram source
└── src/
    ├── traffic_light_controller/
    │   └── traffic_light_controller.ino  # Modular OOP non-blocking FSM
    └── baseline_delay/
        └── baseline_delay.ino            # Sequential prototype sketch
```

---

## Getting Started

### Hardware Requirements

* 1 × Arduino Uno R3 (or compatible ATmega328P board)
* 1 × Breadboard & jumper wires
* 1 × Red 5 mm LED
* 1 × Yellow 5 mm LED
* 1 × Green 5 mm LED
* 3 × $220\,\Omega$ Resistors ($\frac{1}{4}\,\text{W}$)
* 1 × USB Type-A to Type-B cable

### Flashing via Arduino IDE

1. Clone this repository:
   ```bash
   git clone https://github.com/Sohan331/RS2_Embreadded.git
   ```
2. Open either sketch:
   - For the modular FSM version: open `src/traffic_light_controller/traffic_light_controller.ino`.
   - For the sequential baseline: open `src/baseline_delay/baseline_delay.ino`.
3. Under **Tools > Board**, select **Arduino Uno**.
4. Under **Tools > Port**, select your board's COM port.
5. Click **Upload** ($\rightarrow$).

---

## License

This project is released under the [MIT License](LICENSE).