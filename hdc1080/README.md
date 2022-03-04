**Small micropython library for esp82266 (should work on ESP32 as well) to work with HDC1080 humidity and temperature sensor.**

It consists of one class with three methods.

Constructor:<br />
**HDC1080.\_\_init\_\_(self, i2c, address=0x40, heater=False)**<br />
You have to pass I2C object and sensor address (if not default). Heater option enables internal heater which is usefull in high humidity environment to prevent condensation on sensor. Heater only works during measurements so you have to take them frequently to have desired effect. If device with given address is not found exception is raised and all found device adresses are printed.

To measure temperature (Celsius degrees) and relative humidity you have to use **object.read_temperature()** and **object.read_humidity()** respectively. Those are synchronous calls and both take slightly more than 7ms. <br />
It's possible to retrieve last measured parameters with object.temperature and object.humidity.
