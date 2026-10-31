# Arduino Hardware Implementation — Traffic Light System (Task 3)

[![Platform: Arduino Uno](https://img.shields.io/badge/Platform-Arduino%20Uno-00979D?logo=arduino&logoColor=white)](https://www.arduino.cc/)
[![Language: C++](https://img.shields.io/badge/Language-C%2B%2B-00599C?logo=c%2B%2B&logoColor=white)](https://isocpp.org/)
[![Simulation: Tinkercad](https://img.shields.io/badge/Task%201%20Simulation-Tinkercad-blue?logo=autodesk&logoColor=white)](https://shorturl.at/akzd5)

Real-hardware implementation of the **Task 1 Traffic Light System** built and tested in the Embedded Systems Lab on an **Arduino Uno (Joy-IT R3DIP / ATmega328P)**. This folder demonstrates how the realized state machine diagram, class diagram, and Tinkercad simulation map directly onto the physical target hardware.

---

## 🎥 Hardware Demonstration & Lab Setup

- **Video Demo (18 s, silent):** [Watch `demo.mp4`](./demo.mp4) — captures one complete 17-second traffic light cycle on the physical board (`Red` → `Red + Yellow` → `Yellow` → `Green` → `Yellow` → `Red`).

### Real Breadboard Circuit
![Real Arduino Hardware Circuit](docs/Arduino%20Implementation_Circuit%20.jpeg)

---

## 🔌 Pin Mapping & Signal Timing

### Hardware Pinout

| Arduino Pin | Variable | Component | Mode | Notes |
| :--- | :---: | :--- | :---: | :--- |
| **Pin 8** | `red` | Red LED | `OUTPUT` | Connected via 220 Ω resistor |
| **Pin 6** | `yellow` | Yellow LED | `OUTPUT` | Connected via 220 Ω resistor |
| **Pin 2** | `green` | Green LED | `OUTPUT` | Connected via 220 Ω resistor |
| **GND** | — | Common Ground | — | Breadboard negative rail |

### Implemented Cycle Sequence (17 s Total)

| Step | Phase | Active LED(s) | Duration |
| :---: | :--- | :--- | :---: |
| **1** | Stop | Red | `4 s` |
| **2** | Prepare | Red + Yellow | `2 s` |
| **3** | Transition | Yellow | `2 s` |
| **4** | Go | Green | `7 s` |
| **5** | Caution | Yellow | `2 s` |

---

## 🔄 Mapping Task 1 (Diagrams & Simulation) to Real Hardware

| Task 1 Artifact | Real Target System Mapping (Lab Arduino) |
| :--- | :--- |
| **Tinkercad Simulation** ([View Circuit](https://shorturl.at/akzd5)) | Directly replicated on the physical breadboard using identical digital pins (`8`, `6`, `2`), 220 Ω current-limiting resistors, and common ground return. |
| **State Machine Diagram** (`docs/system_diagram.png`) | Each diagram state (`Red`, `Red + Yellow`, `Yellow`, `Green`) maps directly to a sequential state block in `loop()`, including the return `Yellow` warning transition before `Red`. Phase durations were adjusted (`4 s / 2 s / 2 s / 7 s / 2 s`) for practical lab observation. |
| **Class Diagram** (`TrafficLightController`, `TrafficLight`, `Timer`) | Mapped to lightweight native Arduino primitives on the ATmega328P: `setup()`/`loop()` handles controller sequencing (`TrafficLightController`), `pinMode()`/`digitalWrite()` controls each LED pin (`TrafficLight`), and `delay()` enforces deterministic phase intervals (`Timer`). |

### Realized State Sequence (Versionable Mermaid Model)

```mermaid
stateDiagram-v2
    [*] --> Red: setup()
    Red --> Red_Yellow: 4 s
    Red_Yellow --> Yellow_1: 2 s
    Yellow_1 --> Green: 2 s
    Green --> Yellow_2: 7 s
    Yellow_2 --> Red: 2 s

    Red: Red ON
    Red_Yellow: Red + Yellow ON
    Yellow_1: Yellow ON
    Green: Green ON
    Yellow_2: Yellow ON
```

### Task 1 System Diagrams (State Machine & Class Diagram)

- **Editable Source (Versionable XML):** [`docs/EmbeddedPractical.drawio`](docs/EmbeddedPractical.drawio)

![System Diagram](docs/system_diagram.png)

---

## 📁 Project Structure & File Formats

Version-friendly text/XML formats (`.ino`, `.md`, Mermaid, `.drawio`) are organized alongside hardware verification media:

```text
Arduino-Hardware-Implementation-Project_1/
├── README.md                                  # Documentation & Mermaid state diagram
├── demo.mp4                                   # 18-second silent hardware demo video
├── docs/
│   ├── EmbeddedPractical.drawio               # Versionable Draw.io diagram source (XML)
│   ├── system_diagram.png                     # State machine & class diagram overview
│   └── Arduino Implementation_Circuit .jpeg   # Physical lab breadboard wiring photo
└── src/
    └── traffic_light_controller/
        └── traffic_light_controller.ino       # Target Arduino Uno firmware sketch
```

---

## 💻 Uploading to the Arduino

1. Connect the **Arduino Uno** to your PC via USB.
2. Open [`src/traffic_light_controller/traffic_light_controller.ino`](src/traffic_light_controller/traffic_light_controller.ino) in the Arduino IDE.
3. Select **Arduino Uno** under **Tools > Board**, choose your **Port**, and click **Upload**.
