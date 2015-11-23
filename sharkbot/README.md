# Sharkbot
This set of boards forms the mechanics of the roving LAN'd shark. It can be controlled via an MQTT server such as [Data.SparkFun.com](data.sparkfun.com), with either computer driven code or the companion [Controller](../controller/) and [BaseStation](../basestation/) boards. 

## Brains
This top board is the primary electronics, including the ESP chip and supporting programming components, voltage regulator, and LIPO battery monitoring. Also contains an output for a strand of Adafruit Neopixels

This board is entirely usable as a standalone servo controller. 
 
## Chassis and Fins
These boards contain the mechanics for sharklike actuation. The Chassis contains a strip of Neopixels for maximum gleefullness. 

If you don't need the neopixels, these boards can be exported as DXF or SVG and imported into most laser cutters or CNC software


# Software
This code uses the [ESP8266 Arduino](https://github.com/esp8266/Arduino) platform for the codebase. It also uses the Adafruit Neopixel library, which is conveniently included with the ESP Arduino downloads.

# Hardware

A very helpful resource was this tutorial for [creating a shark in maya](http://cgi.tutsplus.com/tutorials/create-a-realistic-shark-in-maya-using-subdivision-surfaces-part-3--cg-31246), even though I only used the 2d outline. 

The images in [references](./references) are copied from the tutorial for practical inclusion with the source files, and no claims are made to ownership. 


## BOM
See [BOM.txt](./BOM.txt) for the full component list from Eagle. Here's the notable/major components: 

- [ESP12E](https://www.adafruit.com/products/2491)
- Brains PCB. 
- Either Fin and Chassis  PCBs, or laser-cut equivilents (will have no place to mount neopixels)
- [Pair of AA Sized Lipo battery](https://www.sparkfun.com/products/7949)
- [MCP73871 LIPO battery management IC](http://www.digikey.com/product-detail/en/MCP73871-2CCI%2FML/MCP73871-2CCI%2FML-ND/1680971)
- [MC1703T 3.0V SOT23 Voltage ](http://www.digikey.com/product-detail/en/MCP1703T-3002E%2FCB/MCP1703T-3002E%2FCBCT-ND/1776944)
- [5x Neopixel LEDs](https://www.adafruit.com/products/1655)
- [5x Micro servos](http://www.hobbyking.com/hobbyking/store/__662__HXT900_Micro_Servo_1_6kg_0_12sec_9g.html). Various sizes and suppliers
- Several 2mm mounting screws, 3-6mm in length 
- 2mm nuts
- 2mm bolts
- Various passives and headers
- [Small nylon hinges](http://www.amazon.com/Du-Bro-Small-Nylon-Hinge-15-Pack/dp/B0006O4FYC/ref=pd_sim_21_1?ie=UTF8&dpID=310lU0qV%2BrL&dpSrc=sims&preST=_AC_UL160_SR160%2C160_&refRID=1N4D6JPY20T97VXT0CP7)

All passives use a universal footprint optimized for 0603, but tolerant of 0402 and 0805 components. 

# Errata/issues
The mechanics are not 100% defined, and some glue/creativity may be required to get this design fully operating. Our demo models were assembled with hot glue and some coffee stir sticks from 711.

There is no "off" button, which makes battery access critical as it's the only way to de-power the servo. The code implements a "sleep" function when the bootloader button is pressed, but this does not power down the servo motors.
