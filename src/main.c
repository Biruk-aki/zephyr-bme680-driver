#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include "bme680_driver.h"

int main(void)
{
    /* 1. Initialize our wrapper struct using the devicetree label */
    struct bme680_app_device my_sensor = {
        .dev = DEVICE_DT_GET(DT_NODELABEL(bme680))
    };

    /* 2. Initialize the sensor using our API wrapper function */
    if (app_bme680_init(&my_sensor) != 0) {
        printk("Failed to initialize BME680 via Sensor API\n");
        return 0;
    }

    printk("BME680 API Driver Started Successfully!\n");

    while (1) {
        /* 3. Fetch all data (Temp, Press, Hum) in one command */
        if (app_bme680_fetch_data(&my_sensor) == 0) {
            
            /* Print the human-readable values */
            /* val1 is the integer part, val2 is the micro-decimal part */
            printk("Temp: %d.%06d C | Press: %d.%06d kPa | Hum: %d.%06d %%\n",
                   my_sensor.temp.val1, my_sensor.temp.val2,
                   my_sensor.press.val1, my_sensor.press.val2,
                   my_sensor.hum.val1, my_sensor.hum.val2);
        } else {
            printk("Error: Failed to fetch sensor data\n");
        }

        /* Wait 3 seconds before the next reading */
        k_msleep(3000);
    }
    return 0;
}