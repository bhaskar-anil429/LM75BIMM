// Distributed with a free-will license.
// Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
// LM75BIMM
// This code is designed to work with the LM75BIMM_I2CS I2C Mini Module available from ControlEverything.com.
// https://www.controleverything.com/content/Temperature?sku=LM75BIMM_I2CS#tabs-0-product_tabset-2

import com.pi4j.io.i2c.I2CBus;
import com.pi4j.io.i2c.I2CDevice;
import com.pi4j.io.i2c.I2CFactory;
import java.io.IOException;

public class LM75BIMM
{
	public static void main(String args[]) throws Exception
	{
		// Create I2C bus
		I2CBus Bus = I2CFactory.getInstance(I2CBus.BUS_1);
		// Get I2C device, LM75BIMM I2C address is 0x49(73)
		I2CDevice device = Bus.getDevice(0x49);

		// Select configuration register
		// Continuous conversion mode, normal operation
		device.write(0x01, (byte)0x00);
		Thread.sleep(500);

		// Read 2 bytes of data from address 0x00(0)
		// temp msb, temp lsb
		byte[] data = new byte[2];
		device.read(0x00, data, 0, 2);

		// Convert the data to 9-bits
		int temp = ((data[0] & 0xFF) * 256 + (data[1] & 0x80)) / 128;
		if(temp > 255)
		{
			temp -= 512;
		}
		double cTemp = temp * 0.5;
		double fTemp = cTemp * 1.8 + 32;

		// Output data to screen
		System.out.printf("Temperature in Celsisus : %.2f C %n", cTemp);
		System.out.printf("Temperature in Fahrenheit : %.2f F %n", fTemp);
	}
}
