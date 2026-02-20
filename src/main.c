#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include "bme680_driver.h"

int main(void)
{

/* Get the buzzer configuration from the devicetree alias */
static const struct gpio_dt_spec buzzer = GPIO_DT_SPEC_GET(DT_ALIAS(buzzer), gpios);

/* Define your threshold */
#define TEMP_THRESHOLD_CELSIUS 23

    /* 1. Initialize our wrapper struct using the devicetree label */
    struct bme680_app_device my_sensor = {
        .dev = DEVICE_DT_GET(DT_NODELABEL(bme680))
    };

    // prepare the Buzzer Hardware
if(!device_is_ready(buzzer.port)){
printk("Error: Buzzer device is not ready\n");
return 0;

}
gpio_pin_configure_dt(&buzzer, GPIO_OUTPUT_INACTIVE);

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

                   // print the reistance in ohms,high gas resistance means good air quality, low gas resistance means bad air quality

                   printk("gas resistance:%d ohms\n",my_sensor.gas.val1);
               
//BUZZER logic: if temp is above threshold, turn on buzzer, else turn off buzzer
if(my_sensor.temp.val1>= TEMP_THRESHOLD_CELSIUS){
    printk("!!warning: HIGH TEMPERATURE!!\n");

    for (int i=0;i<250;i++){
gpio_pin_set_dt(&buzzer, 1); // turn on buzzer
k_usleep(1000);
gpio_pin_set_dt(&buzzer, 0); // turn off buzzer
k_usleep(1000);

}

}else{
    gpio_pin_set_dt(&buzzer, 0); // turn off buzzer
}

        printk("--------------------------------------------------\n");
        } 

        /* Wait 3 seconds before the next reading */
        k_msleep(500);
    }
    
}