# BaseStation
This is an ESP2866 board that controls three [Teensy-based capacitive controllers](../controller/)



## Wiring Diagram
Wiring the SPI bus requires 4 connections between the ESP and Teensy. 

```
  Teensy 3.1                            ESP2866-12E   
+--------------+                      +---------------+
|              |                      |               |
|           10 <------< CS <----------< ANY           |
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

