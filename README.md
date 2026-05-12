# Digital DC-DC Buck Converter (ESP32)

**Author:** Rohit Kumar
**Focus:** Power Electronics & Microcontroller Interfaces

*This repository contains the firmware, schematic, and simulation files for a custom-built 12V to ~5V step-down converter, utilizing an IR2110 gate driver and an IRFZ44N MOSFET switching at 50kHz.*

## Hardware Demonstration
*(Click the image below to watch the hardware test and soft-start demonstration)*

[![Buck Converter Project Video](https://img.youtube.com/vi/z8G8Pr4DV4w/maxresdefault.jpg)](https://www.youtube.com/watch?v=z8G8Pr4DV4w)

## Project Overview
This project bridges low-voltage digital logic with high-current power switching. It uses an ESP32 to generate a high-frequency (50kHz) PWM signal. Because the high-side N-channel MOSFET (IRFZ44N) requires a gate voltage higher than the 12V source, an IR2110 gate driver is implemented alongside a custom bootstrap circuit to achieve full saturation.

### Key Engineering Features
1. **Bootstrap Topology:** Uses a 1N5822 Schottky diode and 100nF ceramic capacitor to drive the high-side switch.
2. **Software Soft-Start:** The firmware includes a ramp-up sequence, increasing the duty cycle gradually to prevent massive inrush currents from hitting the LC filter.
3. **Logic Isolation:** The 3.3V logic circuit is strictly isolated from the 12V power rail, sharing only a common power ground.

## Simulation vs. Hardware
The transient response of the LC filter was modeled in LTspice. 
* *Simulation:* Unmitigated startup causes a voltage spike up to ~7.6V before settling.
* *Hardware Implementation:* The physical build avoids this overshoot entirely by executing the ESP32 firmware soft-start logic.

## Bill of Materials
| Component | Part Number / Value | Purpose |
| :--- | :--- | :--- |
| Microcontroller | ESP32 | Generates 50kHz, 10-bit PWM logic |
| Gate Driver | IR2110 (PDIP-14) | Shifts 3.3V logic to high-voltage gate drive |
| MOSFET | IRFZ44N (N-Channel) | High-side power switch |
| Freewheeling Diode | SR5100 | 100V, 5A Schottky for continuous conduction |
| Inductor | 330µH | Primary energy storage |
| Output Capacitor | 470µF | Voltage ripple smoothing |
