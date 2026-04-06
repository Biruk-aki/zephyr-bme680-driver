BME680 Environmental Monitoring & Alert System

Developed for Raspberry Pi Pico 2 (RP2350) using Zephyr RTOS
📌 Project Overview
This project implements a real-time environmental monitoring system using the Bosch BME680 multi-gas sensor. The firmware is built on Zephyr RTOS, utilizing a modular driver architecture to measure Temperature, Pressure, Humidity, and Gas Resistance (IAQ).

A closed-loop logic is implemented to trigger a physical alarm (Passive Buzzer) when environmental thresholds are exceeded, demonstrating the integration of I2C digital sensors and GPIO actuators.

🛠 Technical Stack
Hardware: Raspberry Pi Pico 2 (RP2350 SoC), BME680 (I2C), Maker Pi Pico Baseboard.

RTOS: Zephyr v4.3.99.

Languages: C17.

Build System: West / CMake / Ninja.

Communication: I2C (400kHz), UART (115200 baud).

🚀 Key Features
Zephyr Sensor API Integration: Abstracted driver implementation using sensor_sample_fetch and sensor_channel_get for cross-platform portability.

Multi-Channel Sensing: Supports Temperature, Pressure, Humidity, and Gas Resistance (MOX heater management).

Threshold-Based Alert System: Real-time monitoring with a software-oscillated alarm (500Hz) for passive buzzers.

Devicetree Hardware Description: Hardware-to-Software mapping handled entirely through .overlay files, keeping the application code hardware-independent.

📂 Project Structure
app.overlay: Devicetree definition for I2C nodes and GPIO aliases.

prj.conf: Kconfig symbols for enabling I2C, GPIO, and Sensor subsystems.

src/bme680_driver.c/h: Driver wrapper for the Bosch BME680.

src/main.c: Application logic and alarm control.

📈 Results
The system successfully detects Volatile Organic Compounds (VOCs) and temperature spikes. When the temperature exceeds 21°C (or your preferred threshold), the system triggers an audible alert on GP18.
