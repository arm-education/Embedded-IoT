# Reading Sensor Data

In this example, we will read the sensor data using the sensors embedded in the ST board.

We will use I2C for the serial communication and USART to print out the sensor data.

**Configure I2C2 and USART1 as follows:**

### I2C2
![module3-I2C-config](images/module3-I2C-config.png)

### USART1
![module3-USART-config](images/module3-USART-config.png)

**The peripherals should look like this:**

![module3-peripherals](images/module3-peripherals.png)

In the code we initialize all the sensors and read the sensor data. Calibration was required to get more accurate measurements.
