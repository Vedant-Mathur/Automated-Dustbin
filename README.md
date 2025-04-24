# ♻️ Distance-Based Automated Dustbin

An embedded system mini-project for ICT 2223, designed to promote hygiene and hands-free waste disposal using proximity detection and automated lid control.

---

## 📘 Overview

The **Distance-Based Automated Dustbin** uses the LPC1768 ARM Cortex-M3 microcontroller to automate the opening and closing of a dustbin lid. It detects users via ultrasonic sensing and provides feedback using a 16x2 LCD. This smart dustbin supports contactless operation for enhanced hygiene and convenience.

---

## 🎯 Objectives

- Automate waste disposal using distance sensing.
- Promote hands-free operation to reduce contamination.
- Demonstrate embedded systems' role in smart hygiene tech.

---

## 🌟 Features

- 🧍 **Proximity Detection** (≤ 30 cm) via HCSR04 ultrasonic sensor.
- ⚙️ **Stepper Motor Control** for smooth lid opening and closing.
- 📺 **LCD Status Display** with messages like *"Lid Opening..."*.
- 🔋 **Low-Power, Compact Design** using LPC1768.

---

## 🛠️ Hardware Components

| Component                  | Description                                               |
|---------------------------|-----------------------------------------------------------|
| LPC1768 Microcontroller   | ARM Cortex-M3-based MCU used for control logic.           |
| HCSR04 Ultrasonic Sensor  | Measures distance to detect approaching users.            |
| Stepper Motor (28BYJ-48)  | Rotates lid open/closed, driven by ULN2003 module.        |
| LCD Display (16x2)        | Displays system feedback and status messages.             |
| Power Supply              | Provides regulated 3.3V/5V and optionally 12V for motors.  |
| Connecting Wires          | FRC, jumper wires for clean signal and power routing.     |

---

## 🔌 Pin Configuration

| Component       | Pin                 | LPC1768 GPIO Pin   |
|----------------|---------------------|--------------------|
| **LCD Display** | RS                  | P0.27              |
|                | E (Enable)          | P0.28              |
|                | Data Lines (D4-D7)  | P0.23 – P0.26      |
| **Ultrasonic**  | Trigger             | P0.15              |
|                | Echo                | P0.16              |
| **Stepper Motor** | IN1 – IN4 (via ULN2003) | P2.0 – P2.3   |
| **Power**       | 3.3V / 5V / 12V     | Varies per module  |
| **Ground**      | All components      | GND                |

---

## 🧱 System Architecture

```text
+------------------------+
|  Ultrasonic Sensor     |
|     (HCSR04)           |
+------------------------+
            |
            v
+----------------------------+
|   LPC1768 Microcontroller  |
| - Controls stepper motor   |
| - Reads sensor input       |
| - Drives LCD output        |
+----------------------------+
      |              |
      v              v
+-----------+   +------------+
| Stepper   |   |   LCD      |
| Motor     |   |   Display  |
+-----------+   +------------+


🔁 Methodology
System Init: LCD shows "System Ready". Components are initialized.

Detection: Ultrasonic sensor continuously scans. If object ≤ 30 cm:

Action:

LCD displays "Lid Opening..."

Stepper motor rotates (anticlockwise) to open lid.

After 3–5 seconds, LCD shows "Lid Closing..."

Motor rotates (clockwise) to close lid.

🖥️ Software Environment
Programming Language: C

IDE: Keil uVision

Microcontroller Driver: LPC17xx CMSIS, Timer-based delays

Motor Control: 4-step full sequence via ULN2003

🧪 Results & Relevance
✅ Accurate and real-time proximity sensing.

✅ Smooth lid control via stepper motor.

✅ Non-contact operation ideal for hospitals, offices, homes.

✅ Clean UI with status feedback via 16x2 LCD.

✅ Promotes hygiene and automation using affordable components.

🖼️ Photographs
(Insert photographs showing the dustbin in idle, active, and reset states)

👨‍💻 Team
Vedant Mathur – 230911328

Rukmender Reddy – 230911326

Sumit Sagar – 230911334

Department of I&CT, MIT Manipal
April 2025 – Embedded Systems Lab (ICT 2223)

📄 References
Eran Bamani et al., "Ultra-Range Gesture Recognition", 2023. (ScienceDirect)

Abdullah Mujahid et al., "Real-Time Gesture Recognition", 2023. (MDPI)

Ch. Lakshmi Narayana et al., "Gesture Recognition Using CNN", 2023. (RJPN)

📜 License
This academic project is open-source and licensed under the MIT License.
