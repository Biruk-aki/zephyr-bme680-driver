#ifndef BME680_DRIVER_H
#define BME680_DRIVER_H

#include <zephyr/device.h>
#include <zephyr/drivers/sensor.h>  // <--- This is vital!

struct bme680_app_device {
    const struct device *dev;
    struct sensor_value temp;
    struct sensor_value press;
    struct sensor_value hum;
};

int app_bme680_init(struct bme680_app_device *app_dev);
int app_bme680_fetch_data(struct bme680_app_device *app_dev);

#endif