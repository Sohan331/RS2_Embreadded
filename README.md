# RS2 Embedded Systems Repository

Welcome to the **RS2 Embedded Systems** repository. This repository organizes embedded systems projects, firmware implementations, circuit designs, and lab deliverables.

---

## Projects Directory

### 🚦 [Traffic Light Project 1](./Traffic%20Light%20Project_1)
An automated traffic control system developed for the **Arduino Uno (ATmega328P)**. The project models an automated multi-phase junction signal cycling sequentially through Red, Red + Yellow, Yellow, and Green states.

- **Folder:** [`Traffic Light Project_1/`](./Traffic%20Light%20Project_1)
- **Documentation:** [Read Project Documentation & Specifications](./Traffic%20Light%20Project_1/README.md)
- **Firmware Sketch:** [`Traffic Light Project_1/src/traffic_light_controller/traffic_light_controller.ino`](./Traffic%20Light%20Project_1/src/traffic_light_controller/traffic_light_controller.ino)
- **Schematics & Diagrams:** [`Traffic Light Project_1/docs/`](./Traffic%20Light%20Project_1/docs/)
- **Simulation:** [Tinkercad Circuit](https://shorturl.at/akzd5)
- **License:** [MIT License](./Traffic%20Light%20Project_1/LICENSE)

---

### 🚸 [Traffic Light Project 2](./Traffic%20Light%20Project_2)
An interactive smart traffic control system featuring an on-demand pedestrian crossing routine. Developed for the **Arduino Uno (ATmega328P)**, this project coordinates vehicular traffic signals alongside dedicated pedestrian stop/walk indicators and a push-button crossing request.

- **Folder:** [`Traffic Light Project_2/`](./Traffic%20Light%20Project_2)
- **Documentation:** [Read Project Documentation & Sequence Diagram](./Traffic%20Light%20Project_2/README.md)
- **Firmware Sketch:** [`Traffic Light Project_2/traffic_light_controller.ino`](./Traffic%20Light%20Project_2/traffic_light_controller.ino)
- **Schematics & Diagrams:** Included in [`Traffic Light Project_2/`](./Traffic%20Light%20Project_2) ([Draw.io Source](https://drive.google.com/file/d/1IKe1vXCG48pYgHF-5uRdoNBxFWU_hF1x/view?usp=sharing))
- **Simulation:** [Tinkercad Circuit](https://www.tinkercad.com/things/lw6mdx8b40G-copy-of-pr2-update-traffic-light-system?sharecode=GDI3W6okflb5UjewmtQqD8fbNvfhd8kKurzvTqLfaIY)

---

### 🔧 [Arduino Hardware Implementation — Project 1 (Task 3)](./Arduino-Hardware-Implementation-Project_1)
Lab hardware realization of the Task 1 Traffic Light System on a physical **Arduino Uno (ATmega328P)**, demonstrating the mapping from state machine/class diagrams and Tinkercad simulation to the real target board.

- **Folder:** [`Arduino-Hardware-Implementation-Project_1/`](./Arduino-Hardware-Implementation-Project_1)
- **Documentation & Live Preview:** [View Hardware Demo, Circuit & Mapping](./Arduino-Hardware-Implementation-Project_1/README.md)
- **Firmware Sketch:** [`Arduino-Hardware-Implementation-Project_1/src/traffic_light_controller/traffic_light_controller.ino`](./Arduino-Hardware-Implementation-Project_1/src/traffic_light_controller/traffic_light_controller.ino)
- **Diagrams & Circuit Photo:** [`Arduino-Hardware-Implementation-Project_1/docs/`](./Arduino-Hardware-Implementation-Project_1/docs/)
- **Video Demo (18 s, silent):** [Download / Watch `demo.mp4`](https://raw.githubusercontent.com/Sohan331/RS2_Embreadded/main/Arduino-Hardware-Implementation-Project_1/demo.mp4)

---

### 🔧 [Arduino Hardware Implementation — Project 2 (Task 4)](./Arduino-Hardware-Implementation-Project_2)
Lab hardware realization of the Task 2 Smart Traffic Light System with Pedestrian Crossing on a physical **Arduino Uno (ATmega328P)**, comparing polling-based and interrupt-based button handling.

- **Folder:** [`Arduino-Hardware-Implementation-Project_2/`](./Arduino-Hardware-Implementation-Project_2)
- **Documentation & Live Preview:** [View Hardware Demo, Mapping & Polling vs. Interrupt Comparison](./Arduino-Hardware-Implementation-Project_2/README.md)
- **Firmware Sketch (Interrupt-Based):** [`Arduino-Hardware-Implementation-Project_2/src/traffic_light_controller/traffic_light_controller.ino`](./Arduino-Hardware-Implementation-Project_2/src/traffic_light_controller/traffic_light_controller.ino)
- **Diagrams & Circuit Photo:** [`Arduino-Hardware-Implementation-Project_2/docs/`](./Arduino-Hardware-Implementation-Project_2/docs/)
- **Video Demo (1080p, silent):** [Download / Watch `Demo.mp4`](https://raw.githubusercontent.com/Sohan331/RS2_Embreadded/main/Arduino-Hardware-Implementation-Project_2/Demo.mp4)

---

## License

Each project in this repository is released under its respective license. See [`Traffic Light Project_1/LICENSE`](./Traffic%20Light%20Project_1/LICENSE) for the Traffic Light Controller project.
