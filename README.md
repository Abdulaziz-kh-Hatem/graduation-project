# EOG-Based Assistive HCI Platform

![Status](https://img.shields.io/badge/Project-Completed-success) 
![Evaluation](https://img.shields.io/badge/Grade-Distinction-blue)

> **Notice:** Source code (MATLAB and Arduino) is temporarily withheld pending academic publication.

**Senior Capstone Project | Biomedical Engineering | UST Aden**

Developed an assistive Human-Computer Interface (HCI) allowing patients with severe neuromuscular disorders (e.g., ALS, LIS) to control a motorized wheelchair and an Arabic virtual keyboard via Electrooculography (EOG) signals.

---

## Technical Specifications

### Hardware (Analog Front-End)
* **Pre-Amplification:** AD620 instrumentation amplifier (gain ~6×).
* **Filtering:** Active TL072/LM741 filters.
    * High-pass cutoff: 0.8 Hz (baseline wander removal).
    * Low-pass cutoff: 30 Hz (EMG artifact attenuation).
    * Notch filter: 50 Hz Twin-T (powerline interference rejection).
* **Final Gain Stage:** TL072 non-inverting amplifier (gain up to 100×–1000×), providing total system gain of 600×–6000× to condition microvolt EOG potentials for 0–5V ADC acquisition.

![Circuit Schematic](results/eog_circuit_schematic.png)
*Figure 1: Analog Front-End (AFE) circuit diagram.*

### Signal Processing (Software)
* **Acquisition:** Arduino ATmega328P 10-bit ADC, serial USB transmission.
* **DSP Pipeline:** MATLAB (DSP System Toolbox) implementing real-time moving-average filters and threshold-based directional/blink classification.
* **Actuation:** Bluetooth telemetry (HC-05) to a secondary Arduino actuating L298N motor drivers on a 3D-printed wheelchair prototype.
* **Safety Mechanism:** HC-SR04 ultrasonic sensors enforcing a 40 cm obstacle override distance.

---

## System Evaluation

Subject trials ($N = 5$ healthy participants) yielded the following metrics:
* **Directional Control Accuracy:** 94.0% across 100 continuous trials.
* **System Latency:** 143 ms processing latency; 213 ms total actuation latency.
* **Typing Speed:** 16.0 characters/min using a custom hierarchical Arabic virtual keyboard.

### Video Demonstrations
* **Typing Demo:** [HCI Virtual Keyboard (YouTube)](https://youtu.be/_7P_xF_lJTU?si=B2MbOErdmBXGmws5)
* **Wheelchair Demo:** [Hardware Actuation (YouTube)](https://youtu.be/ZO9QT6c9rzA?si=DyfI3WWjkoZByfXB)

![Virtual Keyboard](results/virtual_keyboard_main_interface.png)
*Figure 2: Arabic virtual keyboard UI.*

![Wheelchair Prototype](results/3d_printed_wheelchair_prototype.jpeg)
*Figure 3: 3D-printed wheelchair prototype.*
