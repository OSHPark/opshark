
# Capacitive controller
This is a small Teensy 3.1 based board, which works as a 4 way direction pad with 2 buttons. The board provides a SPI interface, and the button presses can be picked up using a standard SPI Library.

## Code requirements
Compiling the provided code requires a special [Teensy 3.1 SPI Slave library](https://github.com/soerup/Teensy-3.0-SPI-Master---Slave), as this functionality isn't provided by standard Arduino SPI libraries.



