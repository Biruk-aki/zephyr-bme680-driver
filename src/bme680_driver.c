#include "bme680_driver.h"
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(bme680_driver, LOG_LEVEL_INF);

/* 1. Check if sensor exists */
int bme680_read_chip_id(const struct i2c_dt_spec *dev_i2c)
{
    uint8_t reg_addr = BME680_REG_CHIP_ID;
    uint8_t chip_id = 0;
    int ret = i2c_write_read_dt(dev_i2c, &reg_addr, 1, &chip_id, 1);

    if (ret == 0 && chip_id == BME680_CHIP_ID_VAL) {
        LOG_INF("Success! Found BME680. ID: 0x%02X", chip_id);
        return 0;
    }
    LOG_ERR("Failed to find BME680 (ID: 0x%02X, Err: %d)", chip_id, ret);
    return -1;
}

/* 2. Wake up and measure (Forced Mode) */
int bme680_start_measurement(const struct i2c_dt_spec *dev_i2c)
{
    /* To start a measurement, we write 0x01 (Forced Mode)
     * AND we enable Temperature/Pressure oversampling.
     * Value 0xB5 means: Os_Temp=16x, Os_Press=16x, Mode=Forced.
     * (Don't worry about the math for now, just trust 0xB5 works!)
     */
    uint8_t cmd[2] = { BME680_REG_CTRL_MEAS, 0xB5 }; 
    
    int ret = i2c_write_dt(dev_i2c, cmd, 2);
    if (ret != 0) {
        LOG_ERR("Failed to start measurement");
    }
    return ret;
}

/* 3. Read the Raw Data Block */
int bme680_read_raw_data(const struct i2c_dt_spec *dev_i2c, struct bme680_raw_data *data)
{
    uint8_t reg_addr = BME680_REG_TEMP_MSB;
    
    /* Read 8 bytes starting from 0x22 */
    /* This grabs Pressure, Temperature, and Humidity in one go */
    return i2c_write_read_dt(dev_i2c, &reg_addr, 1, data->buf, 8);
}