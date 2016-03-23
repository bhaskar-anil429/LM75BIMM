// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LM75BIMM
// This code is designed to work with the LM75BIMM_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Temperature?sku=LM75BIMM_I2CS#tabs-0-product_tabset-2

#include <application.h>
#include <spark_wiring_i2c.h>

// LM75BIMM I2C address is 0x49(73)
#define Addr 0x49

float cTemp = 0, fTemp = 0;
void setup() 
{
    // Set variable
    Particle.variable("i2cdevice", "LM75BIMM");
    Particle.variable("cTemp", cTemp);
    
    // Initialise I2C communication as MASTER
    Wire.begin();
    // Initialise Serial communication, set baud rate = 9600
    Serial.begin(9600);
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Select configuration register
    Wire.write(0x01);
    // Continuous operation, normal operation
    Wire.write(0x00);
    // Stop I2C Transmission
    Wire.endTransmission();
    delay(300);
}

void loop()
{ 
    unsigned int data[2];
    
    // Start I2C Transmission
    Wire.beginTransmission(Addr);
    // Select temperature data register
    Wire.write(0x00);
    // Stop I2C Transmission
    Wire.endTransmission();
    
    // Request 2 bytes of data
    Wire.requestFrom(Addr,2);
    
    // Read 2 bytes of data
    // temp msb, temp lsb
    if(Wire.available()==2)
    {
        data[0] = Wire.read();
        data[1] = Wire.read();
    } 
    
    // Convert the data to 9-bits
    int temp = (data[0] * 256 + (data[1] & 0x80)) / 128;
    if (temp > 255)
    {
        temp -= 512;
    }
    float cTemp = temp * 0.5;
    float fTemp = cTemp * 1.8 + 32;
    
    // Output data to dashboard
    Particle.publish("Temperature in Celsius:  ", String(cTemp));
    Particle.publish("Temperature in Farhenheit:  ", String(fTemp));
    delay(1000);
}

