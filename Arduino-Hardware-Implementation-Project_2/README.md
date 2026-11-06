# Arduino Hardware Implementation — Smart Traffic Light System (Task 4)

Real-hardware implementation of **Task 2 (Traffic Light System with Pedestrian Crossing)** built and tested in the lab on an **Arduino Uno (ATmega328P)**.

---

## 🎥 Live Hardware Demonstration (1080p HD, Silent)

<p align="center">
  <a href="https://raw.githubusercontent.com/Sohan331/RS2_Embreadded/main/Arduino-Hardware-Implementation-Project_2/Demo.mp4">
    <img src="docs/demo_preview.gif" alt="Arduino Smart Traffic Light Hardware Demo" width="680">
  </a>
</p>

<p align="center">
  <a href="https://raw.githubusercontent.com/Sohan331/RS2_Embreadded/main/Arduino-Hardware-Implementation-Project_2/Demo.mp4">
    <img src="https://img.shields.io/badge/%E2%96%B6_Open_%2F_Download_Full_Quality_Video-Demo.mp4-D90429?style=for-the-badge" alt="Open or Download Demo.mp4">
  </a>
</p>

---

## 🛠️ Circuit & Simulation

- **Task 2 Tinkercad Simulation:** [Open Tinkercad Circuit](https://www.tinkercad.com/things/lw6mdx8b40G-copy-of-pr2-update-traffic-light-system?sharecode=GDI3W6okflb5UjewmtQqD8fbNvfhd8kKurzvTqLfaIY)

### Real Lab Breadboard Setup
<p align="center">
  <img src="docs/hardware_circuit.jpg" alt="Real Arduino Breadboard Circuit" width="650">
</p>

### Task 2 Tinkercad Reference Circuit
<p align="center">
  <img src="docs/tinkercad_circuit.png" alt="Tinkercad Circuit" width="650">
</p>

---

## 🔌 Pin Mapping

Both the simulation and the real Arduino hardware share the exact same pin assignment:

| Component | Arduino Pin | Variable | Mode |
| :--- | :---: | :---: | :---: |
| **Vehicle Red LED** | `Pin 13` | `red` | `OUTPUT` |
| **Vehicle Yellow LED** | `Pin 12` | `yellow` | `OUTPUT` |
| **Vehicle Green LED** | `Pin 11` | `green` | `OUTPUT` |
| **Pedestrian Green LED** | `Pin 10` | `pl_green` | `OUTPUT` |
| **Pedestrian Red LED** | `Pin 7` | `pl_red` | `OUTPUT` |
| **Pedestrian Pushbutton** | `Pin 2` | `pl_button` | `INPUT` |

---

## 🔄 Mapping Task 2 (Diagrams & Simulation) to Real Hardware

| Task 2 Artifact | Target Hardware Realization (Arduino Uno) |
| :--- | :--- |
| **Tinkercad Simulation** (`docs/tinkercad_circuit.png`) | Wired identically on the lab breadboard (`Pins 13, 12, 11, 10, 7, 2`) with 220 Ω LED resistors and a pull-down resistor on the button. |
| **State Machine Diagram** (`docs/system_diagram.png`) | Each state (`Red 5 s` → `Red+Yellow` → `Yellow` → `Green` → `Yellow`) maps directly to `loop()`, and the pedestrian sub-state machine (`2 s` wait + `7 s` walk) maps to `pedestrianCrossing()`. |
| **Class Diagram** (Mermaid model below) | Mapped to lightweight Arduino C++ primitives: `setup()`/`loop()`/`pedestrianCrossing()` act as the controller, `digitalWrite()` drives the LEDs, `digitalRead()`/`attachInterrupt()` reads the button, and `delay()` manages phase timing. |

### State Machine Diagram
- **Versionable Source (XML):** [`docs/traffic_light_diagram.drawio`](docs/traffic_light_diagram.drawio)

<p align="center">
  <img src="docs/system_diagram.png" alt="System State Machine Diagram" width="700">
</p>

### Class Diagram Mapping (Versionable Mermaid)

```mermaid
classDiagram
    class TrafficLightController {
        +setup()
        +loop()
        +pedestrianCrossing()
    }
    class VehicleLight {
        +int redPin = 13
        +int yellowPin = 12
        +int greenPin = 11
    }
    class PedestrianLight {
        +int greenPin = 10
        +int redPin = 7
    }
    class PushButton {
        +int buttonPin = 2
        +readState()
    }
    class Timer {
        +delayMs(ms)
    }

    TrafficLightController --> VehicleLight : controls
    TrafficLightController --> PedestrianLight : controls
    TrafficLightController --> PushButton : reads / interrupts
    TrafficLightController --> Timer : uses
```

---

## 🔘 Button Input: Polling vs. Interrupt Implementation

To compare the two approaches for retrieving button presses on the same hardware (`Pin 2` / `INT0`):

1. **Interrupt Implementation (This Folder — Task 4):** [`src/traffic_light_controller/traffic_light_controller.ino`](src/traffic_light_controller/traffic_light_controller.ino)
2. **Polling Implementation (Task 2 Folder):** [`../Traffic Light Project_2/traffic_light_controller.ino`](../Traffic%20Light%20Project_2/traffic_light_controller.ino)

| Aspect | Polling (`Traffic Light Project_2`) | Hardware Interrupt (`Arduino-Hardware-Implementation-Project_2`) |
| :--- | :--- | :--- |
| **Mechanism** | Calls `digitalRead(pl_button)` at fixed checkpoints in `loop()`. | Uses `attachInterrupt(digitalPinToInterrupt(pl_button), buttonPressed, RISING)`. |
| **During `delay()`** | CPU is blocked; short button presses during `delay()` are **missed**. | Hardware interrupt `INT0` fires immediately even during `delay()`, setting `volatile bool pedestrianRequest = true`. |
| **Resetting Request** | Overwritten on the next `digitalRead(pl_button)` call. | Reset (`pedestrianRequest = false`) at the end of `pedestrianCrossing()` once served. |
| **User Experience** | Pedestrian must hold the button until a checkpoint is reached. | A single brief button tap at any moment is captured and served at the next safe phase. |

---

## 📁 Project Structure

Versionable text/XML formats (`.ino`, `.md`, `.drawio`) are organized in a clean folder hierarchy:

```text
Arduino-Hardware-Implementation-Project_2/
├── README.md                                  # Project documentation & Mermaid class diagram
├── Demo.mp4                                   # Muted 1080p hardware demonstration video
├── docs/
│   ├── demo_preview.gif                       # Inline auto-playing preview for GitHub
│   ├── hardware_circuit.jpg                   # Lab Arduino & breadboard photo
│   ├── tinkercad_circuit.png                  # Task 2 Tinkercad schematic
│   ├── system_diagram.png                     # State machine diagram overview
│   └── traffic_light_diagram.drawio           # Versionable Draw.io XML source
└── src/
    └── traffic_light_controller/
        └── traffic_light_controller.ino       # Interrupt-based hardware sketch (INT0 on Pin 2)
```

