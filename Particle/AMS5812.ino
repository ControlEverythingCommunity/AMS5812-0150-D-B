// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// AMS5812
// This code is designed to work with the AMS5812_I2CS_0150-D-B I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Pressure?sku=AMS5812_I2CS_0150-D-B#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// AMS5812 I2C address is 0x78(120)
#define Addr 0x78

double pressure = 0.0, cTemp = 0.0, fTemp = 0.0;
unsigned long ptemp, temp;
void setup()
{
// Set variable
Particle.variable("i2cdevice","AMS5812");
Particle.variable("pressure",pressure);
Particle.variable("cTemp",cTemp);

// Initialise I2C communication
Wire.begin();
// Initialise Serial
Serial.begin(9600);
delay(300);
}

void loop()
{
byte data[4];

// Request 4 bytes of data from slave device
Wire.requestFrom(Addr,4);

// Read 4 bytes of data
// pressure msb, pressure lsb, temp msb, temp lsb
if(Wire.available() == 4)
{
data[0] = Wire.read();
data[1] = Wire.read();
data[2] = Wire.read();
data[3] = Wire.read();
}
delay(300);

// Convert the data
ptemp = ((data[0] & 0xFF) * 256 + (data[1] & 0xFF));
temp = ((data[2] & 0xFF) * 256 + (data[3] & 0xFF));

pressure = ((ptemp - 3277.0) / ((26214.0) / 30.0)) - 15.0;
cTemp = ((temp - 3277.0) / ((26214.0) / 110.0)) - 25.0;
fTemp = (cTemp * 1.8 ) + 32;

// Output data to dashboard
Particle.publish("Temperature in Celsius :", String(cTemp));
delay(1000);
Particle.publish("Temperature in Fahrenheit : ", String(fTemp));
delay(1000);
Particle.publish("Pressure in PSI: ", String(pressure));
delay(1000);
}
