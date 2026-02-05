#ifndef BME680_DRIVER_H
#define BME680_DRIVER_H

#include <zephyr/drivers/i2c.h>

/* Addresses & Registers */
#define BME680_I2C_ADDR       0x77
#define BME680_REG_CHIP_ID    0xD0
#define BME680_REG_CTRL_MEAS  0x74  // The Control Register
#define BME680_REG_TEMP_MSB   0x22  // Start of Data (Temp/Press/Hum)

/* Values */
#define BME680_CHIP_ID_VAL    0x61
#define BME680_MODE_FORCED    0x01  // Command to "Take 1 measurement"


/* Struct to hold raw data */
struct bme680_raw_data {
    uint8_t buf[8]; // Holds Pressure (3), Temp (3), Hum (2)
};

/* Function Prototypes */
int bme680_read_chip_id(const struct i2c_dt_spec *dev_i2c);
int bme680_start_measurement(const struct i2c_dt_spec *dev_i2c);
int bme680_read_raw_data(const struct i2c_dt_spec *dev_i2c, struct bme680_raw_data *data);

#endif




