// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// AMS5812
// This code is designed to work with the AMS5812_I2CS_0150-D-B I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Pressure?sku=AMS5812_I2CS_0150-D-B#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class AMS5812
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus Bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, AMS5812 I2C address is 0x78(120)
		I2CDevice device = Bus.getDevice(0x78);
		
		// Read 4 bytes of data
		// pressure msb, pressure lsb, temp msb, temp lsb
		byte[] data = new byte[4];
		device.read(data, 0, 4);
        
        	// Convert the data
		double pressure = ((data[0] & 0xFF)* 256 + (data[1] & 0xFF));
		double temp = ((data[2] & 0xFF)* 256 + (data[3] & 0xFF));
        
        	pressure = ((pressure - 3277.0) / ((26214.0) / 30.0)) - 15.0;
        	double cTemp = ((temp - 3277.0) / ((26214.0) / 110.0)) - 25.0;
        	double fTemp = (cTemp * 1.8 ) + 32;
        
        	// Output data to screen
		System.out.printf("Pressure is : %.2f PSI%n", pressure);
		System.out.printf("Temperature in Celsius : %.2f C%n", cTemp);
		System.out.printf("Temperature in Fahrenheit : %.2f F%n", fTemp);
	}
}

