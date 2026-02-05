# Custom BME680 Driver for Zephyr RTOS

**Status:** 🚧 Work In Progress (Phase 1: I2C Communication)

A custom, bare-metal I2C driver for the Bosch BME680 Environmental Sensor, written from scratch using the Zephyr OS API on a Raspberry Pi Pico.

## Completed Features
- [x] I2C Bus initialization
- [x] Chip ID Verification (`0xD0` -> `0x61`)
- [x] Forced Mode Triggering (Waking sensor from sleep)
- [x] Raw Data Block Read (Pressure, Temp, Humidity)

## To Do
- [ ] Implement Compensation Formulas (Math)
- [ ] Parse Gas Resistance (VOCs)
- [ ] Add Shell/CLI commands
