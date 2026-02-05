cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV {ZEPHYR_BASE})
project (BME680_driver)

# Add your source files here
target_sources(app PRIVATE src/main.c src/bme680_driver.c)