# Embedded-Sensor-Library

This is a library specifically targeted at using the MPU-6050 accelerometer/gyroscope sensor with the TI MSP430. With this library, you 
should be able to read the accelerometer values at a resolution of your choice (+/- 2gs, 4gs, 8gs, 16gs), gyro values at a resolution 
of your choice (+/- ..,..,..,..), the temperature value, and configure the built in low-pass filter. There is also some code which
enables you to save these values to flash memory, in case you wanted to save the data and perform offline post-processing.
