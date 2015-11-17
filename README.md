# Wireless-Speedometer
Arduino based speedometer that uses a infrared sensor to measure wheel rotations and returns live data over Bluetooth

## Specifications
Uses a [QTI sensor](http://learn.parallax.com/KickStart/555-27401) which is a simple infrared sensor and an [Arduino Uno](http://arduino.cc/en/Main/arduinoBoardUno) to measure wheel roations and calculate a speed. Uses a [bluetooth module](http://www.mikrokopter.de/ucwiki/en/HC-06) to relay that information back to a computer in real time. Currently set to return data every 10 rotations of the wheel.
