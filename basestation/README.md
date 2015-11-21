# BaseStation
This is an ESP2866 board that reads data from three [Teensy-based capacitive controllers](../controller/), and then sends it over wifi to an MQTT server to control a [shark bot](../sharkbot/).

## Simplified Wiring Schematic
Wiring the SPI bus requires 4 connections between the ESP and Teensy. 

```
  Controller                             BaseStation
  (Teensy 3.x)                           (ESP2866-12E)   
+--------------+                      +---------------+
|              |                      |               |
|           10 <------< CS <----------< Any IO        |
|              |                      |               |
|              |                      |               |
|           13 <------< SCK <---------< 14            |
|              |                      |               |
|              |                      |               |
|           11 >------> MISO >--------> 12            |
|              |                      |               |
|              |                      |               |
|           12 <------< MOSI <--------< 13            |
|              |                      |               |
+--------------+                      +---------------+
```

Other connections are simply there as part of the bootloading process.

# Known issues
Doesn't contain programming header of any sort, which makes changing wifi connections very difficult. Uploading firmware will require soldering to the ESP pads. 

It should be possible to configure the Base Station as a Wifi access point and run the MQTT server locally, in addition to handling the button input. However, this was not due due to time constraints and libraries available. 

# BOM
Only requires a few passive pull up/pull down resistors and an [ESP12E](https://www.adafruit.com/products/2491)
