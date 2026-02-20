Custom BME680 Driver for Zephyr RTOS
Status: ✅ Phase 2: Sensor API Integration Complete

This project implements a driver for the Bosch BME680 Environmental Sensor on the Raspberry Pi Pico 2 (RP2350) using Zephyr RTOS. It has evolved from a bare-metal I2C register implementation to a high-level wrapper around the official Zephyr Sensor API.

Completed Features
[x] I2C Bus & Devicetree: Configured via app.overlay for the RP2350.

[x] Sensor API Wrapper: Abstracted hardware logic into a clean bme680_app_device struct.

[x] Automated Compensation: Utilizes Zephyr's internal Bosch math for Temperature, Pressure, and Humidity.

[x] Data Fetching: Implemented sensor_sample_fetch for synchronized data retrieval.

[x] Formatted Output: Real-time serial logging with floating-point support via PuTTY.

To Do
[ ] Gas Resistance: Enable the internal heater and parse IAQ (Indoor Air Quality) data.

[ ] Interrupt Triggers: Use Zephyr triggers to fetch data only on threshold changes.

[ ] Shell Integration: Add Zephyr Shell commands to query sensor status manually.

Project Structure
src/bme680_driver.c/h: High-level wrapper for the Zephyr Sensor API.

src/main.c: Application logic and data reporting loop.

app.overlay: Hardware definition for the I2C bus and sensor node. 