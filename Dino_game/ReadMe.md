## About 
This is my Microprocessor and Microcontroller(MPMC) Project (CSE 306). It's a simple dino game which is controlled using Joystick module.

## Hardware
- Arduino Mega
- 3.5inch TFT display
- Joystick Module
- Buzzer

## Pin Diagram
### TFT display with Arduino Mega2560:
- 5V  connects to Arduino 5V pin
- GND connects to Arduino Ground
- 3V3 do not need to connect(NC)
- LCD_RD   connects to Analog pin A0
- LCD_WR   connects to Analog pin A1
- LCD_RS   connects to Analog pin A2
- LCD_CS   connects to Analog pin A3
- LCD_RST  connects to Analog pin A4
- LCD_D0   connects to digital pin 8
- LCD_D1   connects to digital pin 9
- LCD_D2   connects to digital pin 2
- LCD_D3   connects to digital pin 3
- LCD_D4   connects to digital pin 4
- LCD_D5   connects to digital pin 5
- LCD_D6   connects to digital pin 6
- LCD_D7   connects to digital pin 7

### Joystick with Mega2560
- 5V  connects to Arduino 5V pin
- GND connects to Arduino Ground
- VRx connects to Analog pin A6
- VRy connects to Analog pin A7
- SW  connects to digital pin 31

### Buzzer with Mega2560
- 5V connects to digital pin 33
- GND connects to Arduino Ground

## Library Used
- MCUFRIEND_kbv [Source](https://github.com/prenticedavid/MCUFRIEND_kbv)
- Adafruit_GFX  [Source](https://github.com/adafruit/Adafruit-GFX-Library)

**_To Know more about TFT display_** [click here.](https://create.arduino.cc/projecthub/electropeak/ultimate-beginner-s-guide-to-run-tft-lcd-displays-by-arduino-081006)
