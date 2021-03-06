// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// AMS5812
// This code is designed to work with the AMS5812_I2CS_0150-D-B I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Pressure?sku=AMS5812_I2CS_0150-D-B#tabs-0-product_tabset-2

#include <Wire.h>

// AMS5812 I2C address is 0x78(120)
#define Addr 0x78

void setup()
{
  // Initialise I2C communication as MASTER
  Wire.begin();
  // Initialise serial communication, set baud rate = 9600
  Serial.begin(9600);
  delay(300);
}

void loop()
{
  unsigned int data[4];
  delay(500);

  // Request 4 bytes of data
  Wire.requestFrom(Addr, 4);

  // Read 4 bytes of data
  // pressure msb, pressure lsb, temp msb, temp lsb
  if (Wire.available() == 4)
  {
    data[0] = Wire.read();
    data[1] = Wire.read();
    data[2] = Wire.read();
    data[3] = Wire.read();
  }

  // Convert the data
  float pressure = ((data[0] & 0xFF) * 256 + (data[1] & 0xFF));
  float temp = ((data[2] & 0xFF) * 256 + (data[3] & 0xFF));

  pressure = ((pressure - 3277.0) / ((26214.0) / 30.0)) - 15.0;
  float cTemp = ((temp - 3277.0) / ((26214.0) / 110.0)) - 25.0;
  float fTemp = (cTemp * 1.8 ) + 32;

  // Output data to serial monitor
  Serial.print("Pressure : ");
  Serial.print(pressure);
  Serial.println(" PSI");
  Serial.print("Temperature in Celsius : ");
  Serial.print(cTemp);
  Serial.println(" C");
  Serial.print("Temperature in Fahrenheit : ");
  Serial.print(fTemp);
  Serial.println(" F");
  delay(500);
}

