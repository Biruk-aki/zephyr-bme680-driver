#include "bme680_driver.h"          // <--- This lets the .c see the struct definition
#include <zephyr/drivers/sensor.h>  // <--- This lets the .c see sensor_sample_fetch
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(bme680_driver, LOG_LEVEL_INF);

int app_bme680_init(struct bme680_app_device *app_dev)
{
    if (!device_is_ready(app_dev->dev)) {
        return -1;
    }
    return 0;
}

int app_bme680_fetch_data(struct bme680_app_device *app_dev)
{
    int ret = sensor_sample_fetch(app_dev->dev);
    if (ret < 0) return ret;

    sensor_channel_get(app_dev->dev, SENSOR_CHAN_AMBIENT_TEMP, &app_dev->temp);
    sensor_channel_get(app_dev->dev, SENSOR_CHAN_PRESS, &app_dev->press);
    sensor_channel_get(app_dev->dev, SENSOR_CHAN_HUMIDITY, &app_dev->hum);

    return 0;
}