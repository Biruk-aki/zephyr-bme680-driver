#include <zephyr/kernel.h>
#include <zephyr/drivers/i2c.h>
#include "bme680_driver.h"



static const struct i2c_dt_spec dev_i2c = {
    .bus = DEVICE_DT_GET(DT_NODELABEL(i2c0)),
    .addr = BME680_I2C_ADDR,
};

int main(void)
{


    
    printk("Starting BME680 Driver...\n");
    if (!device_is_ready(dev_i2c.bus)) return 0;

    /* 1. Initialization Check */
    if (bme680_read_chip_id(&dev_i2c) != 0) {
        return 0; // Stop if sensor not found
    }

    struct bme680_raw_data raw;

    while (1) {
        /* Step A: Trigger Measurement */
        bme680_start_measurement(&dev_i2c);

        /* Step B: Wait for it to finish (approx 100ms is safe) */
        k_msleep(100);

        /* Step C: Read Data */
        if (bme680_read_raw_data(&dev_i2c, &raw) == 0) {
            /* Print raw bytes just to prove it's alive! */
            /* We will turn these into real degrees Celsius later */
            printk("Raw Data: %02X %02X %02X %02X \n", 
                   raw.buf[0], raw.buf[1], raw.buf[2], raw.buf[3]);
        }

        k_msleep(3000); // Repeat every 3 seconds
    }
    return 0;
}