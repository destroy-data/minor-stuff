from time import sleep_ms

class HDC1080:
    def __init__(self, i2c, address=0x40, heater=False):
        devices = i2c.scan()
        assert address in devices, "Didn't find sensor with %d address. Found %s instead." % (address, devices)
        self.i2c = i2c
        self.address = address
        sleep_ms(15)
        #Setting measurements to be separate, turning on heater
        buff = bytearray(2)
        if heater:
			buff[0] = 1 << 6
        i2c.writeto_mem(address, 0x02, buff)

    def read_temperature(self):
        self.i2c.writeto(self.address, bytearray(2))
        sleep_ms(7)
        self.temperature = self.i2c.readfrom(self.address, 2)
        self.temperature = int.from_bytes(self.temperature, "big") / 2**16 * 165 - 40
        return self.temperature

    def read_humidity(self):
        self.i2c.writeto_mem(self.address, 0x01, bytearray(1))
        sleep_ms(7)
        self.humidity = self.i2c.readfrom(self.address, 2)
        self.humidity = int.from_bytes(self.humidity, "big") / 2**16 * 100
        return self.humidity
