# Distributed with a free-will license.
# Use it any way you want, profit or free, provided it fits in the licenses of its associated works.
# LM75BIMM
# This code is designed to work with the LM75BIMM_I2CS I2C Mini Module available from ControlEverything.com.
# https://www.controleverything.com/content/Temperature?sku=LM75BIMM_I2CS#tabs-0-product_tabset-2

import smbus
import time

# Get I2C bus
bus = smbus.SMBus(1)

# LM75BIMM address, 0x49(73)
# Select configuration register, 0x01(01)
#		0x00(00)	Continous conversion, Normal operation
bus.write_byte_data(0x49, 0x01, 0x00)

time.sleep(0.5)

# LM75BIMM address, 0x49(73)
# Read data back from 0x00(0), 2 bytes
# Temp MSB, Temp LSB
data = bus.read_i2c_block_data(0x49, 0x00, 2)

# Convert the data to 9-bits
cTemp = (data[0] * 256 + (data[1] & 0x80)) / 128
if cTemp > 255 :
	cTemp -= 512
cTemp = cTemp * 0.5
fTemp = cTemp * 1.8 + 32

# Output data to screen
print "Temperature in Celsius is : %.2f C" %cTemp
print "Temperature in Fahrenheit is : %.2f F" %fTemp
