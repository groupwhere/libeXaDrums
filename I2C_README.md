# Experimental I2C support

My goal here was to work with an Arduino Micro, which has some native USB serial capabilities and can do USB Midi.

I only wanted to be able to send note on and note off data from eXadrums to USB Midi, so this is one-way.

## Connections

The device is connected to my Raspberry Pi 3B as follows:

|Function|Pi|Arduino|
|---|---|---|
|+5V supp|2 |NC|
|SDA|3|2|
|SCL|5|3|
|GND|9|GND|

Note that the Pi is able to supply 5V to power the Arduino, but DO NOT do this if the Arduino is also connected via USB to your PC as intended.

This allows for direct I2C communication where the Pi is the master and Arduino is the slave.

Connect the Arduino to your desktop/laptop/etc.

Using a small test program and MidiView, I was able to see messages coming in via USB Midi on my desktop.

## Arduino Sketch

See DS1_2024.ino for the source code to upload to your Arduino Micro.

## I2C test

See i2ctest.cpp for a small test program.
This will send one note on and one note off to your Arduino so you can verify operation.

Compile with
```
g++ i2ctest.cpp -o i2ctest
```

You should also run the following to detect your Arduino:
```
pi@pi:~/libeXaDrums $ i2cdetect -y 1
     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f
00:                         08 -- -- -- -- -- -- --
10: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
20: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
30: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
40: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
50: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
60: -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
70: -- -- -- -- -- -- -- --

```

Note the addres 08, which is how the code is written for the Arduino.  We currently also hard code that into libeXadrums, but this will likely change.

## Status

I was able to map the pads in Superior Drummer although the velocity was extremely low.

Quick fix: Multiply velo (volume) by 100.

Concept is relatively proven now, just waiting on my trigger board :)

