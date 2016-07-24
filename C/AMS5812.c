// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// AMS5812
// This code is designed to work with the AMS5812_I2CS_0150-D-B I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Pressure?sku=AMS5812_I2CS_0150-D-B#tabs-0-product_tabset-2

#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <fcntl.h>

void main()
{
	// Create I2C bus
	int file;
	char *bus = "/dev/i2c-1";
	if((file = open(bus, O_RDWR)) < 0)
	{
		printf("Failed to open the bus. \n");
		exit(1);
	}
	// Get I2C device, AMS5812 I2C address is 0x78(120)
	ioctl(file, I2C_SLAVE, 0x78);

	// Read 4 bytes of data
	// pressure msb, pressure lsb, temp msb, temp lsb
	char data[4] = {0};
	if(read(file, data, 4) != 4)
	{
		printf("Erorr : Input/output Erorr \n");
	}
	else 
	{
		// Convert the data
		float pressure = (data[0] * 256 + data[1]);
		float temp = (data[2] * 256 + data[3]);

		pressure = ((pressure - 3277.0) / ((26214.0) / 30.0)) - 15.0;
		float cTemp = ((temp - 3277.0) / ((26214.0) / 110.0)) - 25.0;
		float fTemp = (cTemp * 1.8 ) + 32;

		// Output data to screen
		printf("Pressure is : %.2f PSI\n", pressure);
		printf("Temperature in Celsius : %.2f C\n", cTemp);
		printf("Temperature in Fahrenheit : %.2f F\n", fTemp);
	}
}
