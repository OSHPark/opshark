
# Capacitive controller
This is a small Teensy 3.1 based board, which works as a 4 way direction pad with 2 buttons. The board provides a SPI interface, and the button presses can be picked up using a standard SPI Library.

# Usage 
Currently, this code only works when wired the BaseStation board. However, the Teensy is capable of operating as a USB human interface device, and with some tweaks to the code, the board can easily be used to operate a computer with capacitive buttons.


## Code requirements
Compiling the provided code requires a special [Teensy 3.1 SPI Slave library](https://github.com/soerup/Teensy-3.0-SPI-Master---Slave), as this functionality isn't provided by standard Arduino SPI libraries.

# BOM

- 1x [Teensy 3.x](https://www.pjrc.com/teensy/index.html). We're partial to the [purple ones](http://store.oshpark.com/products/teensy-3-1).
- 2x 14-pin male 0.1" headers
- 2x 14-pin female 0.1" headers