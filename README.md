# RS2 Embedded Systems Repository

Welcome to the **RS2 Embedded Systems** repository. This repository organizes embedded systems projects, firmware implementations, circuit designs, and lab deliverables.

---

## Projects Directory

### 🚦 [Traffic Light Project 1](./Traffic%20Light%20Project_1)
An automated traffic control system developed for the **Arduino Uno (ATmega328P)**. The project models an automated four-phase junction signal using an object-oriented **Finite State Machine (FSM)** architecture and non-blocking timers.

- **Folder:** [`Traffic Light Project_1/`](./Traffic%20Light%20Project_1)
- **Documentation:** [Read Project Documentation & Specifications](./Traffic%20Light%20Project_1/README.md)
- **Firmware Sketches:**
  - Production FSM: [`Traffic Light Project_1/src/traffic_light_controller/`](./Traffic%20Light%20Project_1/src/traffic_light_controller/)
  - Sequential Baseline: [`Traffic Light Project_1/src/baseline_delay/`](./Traffic%20Light%20Project_1/src/baseline_delay/)
- **Schematics & Diagrams:** [`Traffic Light Project_1/docs/`](./Traffic%20Light%20Project_1/docs/)
- **Simulation:** [Tinkercad Circuit](https://www.tinkercad.com/things/83Owepj9sud-traffic-light-simulation)
- **License:** [MIT License](./Traffic%20Light%20Project_1/LICENSE)

---

## Repository Structure

```text
RS2_Embreadded/
├── README.md                         # Main repository landing overview
└── Traffic Light Project_1/          # Traffic light controller project
    ├── .gitignore                    # Project-level gitignore
    ├── LICENSE                       # MIT License
    ├── README.md                     # Detailed project documentation & specs
    ├── docs/                         # Schematics, system diagrams & Draw.io models
    │   ├── circuit_diagram.png
    │   ├── system_diagram.png
    │   └── EmbeddedPractical.drawio
    └── src/                          # Arduino firmware sketches
        ├── baseline_delay/
        │   └── baseline_delay.ino
        └── traffic_light_controller/
            └── traffic_light_controller.ino
```

---

## License

Each project in this repository is released under its respective license. See [`Traffic Light Project_1/LICENSE`](./Traffic%20Light%20Project_1/LICENSE) for the Traffic Light Controller project.
