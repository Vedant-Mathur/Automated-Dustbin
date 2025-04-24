# ♻️ Distance-Based Automated Dustbin

An embedded system mini-project for ICT 2223, designed to promote hygiene and hands-free waste disposal using proximity detection and automated lid control.

---

## 📘 Overview

The **Distance-Based Automated Dustbin** leverages the LPC1768 ARM Cortex-M3 microcontroller to automate the process of opening and closing a dustbin lid based on user proximity. It enhances sanitation by eliminating the need for physical contact and provides real-time feedback using an LCD screen.

---

## 🎯 Objectives

- Automate waste disposal through distance sensing.
- Enhance public hygiene by promoting contactless interaction.
- Demonstrate real-world application of embedded systems in sanitation.

---

## 🧠 Key Features

- 🧍‍♂️ **Proximity Sensing**: Ultrasonic sensor detects users within 30 cm.
- ⚙️ **Stepper Motor Control**: Precise lid operation with a 4-step control sequence.
- 📺 **LCD Feedback**: Displays status messages like *"Lid Opening..."* and *"Dispose Your Waste"*
- 🔋 **Low Power Operation**: Designed for reliable performance with efficient energy use.

---

## 🛠️ Hardware Components

- **Microcontroller**: LPC1768 (ARM Cortex-M3)
- **Sensor**: HCSR04 Ultrasonic Distance Sensor
- **Actuator**: 28BYJ-48 Stepper Motor with ULN2003 Driver
- **Display**: 16x2 LCD (RS → P0.27, E → P0.28, D4-D7 → P0.23–P0.26)
- **Others**: FRC cables, Jumper Wires, Regulated Power Supply (3.3V/5V)

---

## 🧱 System Architecture

```mermaid
graph LR
A[Ultrasonic Sensor (HCSR04)] -->|Triggers| B[LPC1768 Microcontroller]
B -->|Controls| C[Stepper Motor]
B -->|Displays| D[LCD Screen]
B <-->|Power| E[Power Supply]
