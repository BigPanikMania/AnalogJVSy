# AnalogJVSy
Open source JVS to PC interface using a Teensy 

## Description
AnalogJVSy lets you connect your JVS analog controls (analog joystick and buttons plus 6 outputs) to your PC and use them as controls, for MAME or other purposes. 
AnalogJVSy is base on JVSy project from K4roshi

In its current state it's basically an open source JVS-PAC clone.

### Tech description
AnalogJVSy is an implementation of a JVS I/O host using a teensy 2.0 and an RS-485 to serial interface. The signals read from the other nodes are then converted to standard HID Joystick signals.


## Hardware
The hardware requires an USB female port, an RS-485 interface and a Teensy 2.0. It has been tested only with an SN75176B and a teensy 2.0, but should also work with a MAX 485. Teensy 2.0++ and Teensy 3.x can be supported in the future.

### Connections

SN65176B:
- Pin 1: Teensy D2
- Pin 2: Teensy F6
- Pin 3: Teensy F6
- Pin 4: Teensy D3
- Pin 5: Teensy GND
- Pin 6: USB Data+
- Pin 7: USB Data-
- Pin 8: Teensy VCC

USB:
- RED (5v): Teensy B4
- WHITE (Data -): SN65176B 7
- GREEN (Data +): SN65176B 6
- BLACK (GND): Teensy GND

### Scheme

![JVSy scheme](https://github.com/BigPanikMania/AnalogJVSy/blob/main/PCB/JVSy-Scheme.JPG "JVSy Scheme")

When built, connect the usb cable that comes from your sega i/o board to the usb port you just soldered, while you connect the teensy to your pc with the standard usb port. If flashed correctly it will be recognized as a joystick hid device.

## Device setup

### Inputs
Controls for both player one and two and report as a single HID device (Joystick+Keyboard+Mouse(not use)+serial).

Input switchs and potentiometers are mapped to the corresponding joystick buttons/axes:

|     Joystick     |     Inputs    | 
| :------------  | :------------- |
|Analog X axe    |Analog 1   |
|Analog Y axe    |Analog 2    |
|Analog Z axe   |Analog 3   |
|Analog Zr axe   |Analog 4   |
|Button 1   |Player 1 - Start  |
|Button 2   | Player 1 - Service   | 
|    Button 3   |  Player 1 - Up   | 
|    Button 4   |  Player 1 - Down   | 
|    Button 5   |  Player 1 - Left   | 
|    Button 6   |  Player 1 - Right   | 
|    Button 7   |  Player 1 - Button 1   | 
|    Button 8   |  Player 1 - Button 2   | 
|   Button 9   |  Player 1 - Button 3   | 
|    Button 10   |  Player 1 - Button 4   | 
|    Button 11   |  Player 1 - Button 5   | 
|    Button 12   |  Player 1 - Button 6   | 
|    Button 13   |  Player 1 - Button 7   | 
|   Button 14   |  Player 1 - Button 8   | 
|   Button 15   |  Player 2 - Start    | 
|    Button 16   |  Player 2 - Service   | 
|    Button 17   |  Player 2 - Up   | 
|    Button 18   |  Player 2 - Down   | 
|    Button 19   |  Player 2 - Left   | 
|    Button 20   |  Player 2 - Right   | 
|    Button 21   |  Player 2 - Button 1   | 
|    Button 22   |  Player 2 - Button 2   | 
|    Button 23   |  Player 2 - Button 3   | 
|    Button 24   |  Player 2 - Button 4   | 
|    Button 25   |  Player 2 - Button 5   | 
|    Button 26   |  Player 2 - Button 6   | 
|    Button 27   |  Player 2 - Button 7   | 
|    Button 28   |  Player 2 - Button 8   | 
|    Button 29   |  Not used   | 
|    Button 30   |  Test Button   | 
|    Button 31   |  Not used   | 
|    Button 32   |  Not used   | 
|    Hat Up    |  Not used   | 
|    Hat Down   |  Not used   | 
|    Hat Left   |  Not used   | 
|    Hat Right  |  Not used   | 
        
### Outputs

Outputs 1-6 could be controled with the serial line (115Kbps). Syntax is 
~~~
<OutputPort>;<value>x
~~~
with:
- **\<OutputPort\>**: 1 to 6 or use port 0 to address all ports
- **\<value\>**: 0 (OFF) or 1 (ON) or use the decimal value to set all ports one shot (ie 252 (11111100) will set the 6 outputs ON)
- Examples:
    - **1;1x**      = turn ON output 1.1 (pin51)
    - **5;0x**      = turn OFF output 2.2 (pin54)
    - **0;252x**    = turn ON outputs 1, 2, 3, 4, 5 and 6 

|     Bit 7     |     Bit 6    |    Bit 5   |  Bit 4     |    Bit 3     |      Bit 2     |  Bit 1   |     Bit 0    |
| :------------:  | :-------------: | :-------------: |:------------:  | :-------------: | :-------------: |:------------:  | :-------------: |
|    Output 1  |    Output 2     |     Output 3      |    Output 4   |   Output 5     |     Output 6      |   x  |  x     |  
|   Output 1.1  |  Output 1.2     |      Output 1.3     |   Output 2.1  |  Output 2.2     |      Output 2.3     |   x  |  x     |  
| pin 51   |   pin 53    |      pin 55 | pin 52   |   pin 54    |      pin 56 |  x    |   x    |

NB: For the moment, only the first six outputs are managed with AnalogJVSy (TODO: outputs \#7 to \#22)
    
## Thanks

@k4roshi for JVSy digital sketch 

@roysmeding for the wonderful reverse engineering done for Open JVS (https://github.com/TheOnlyJoey/openjvs) and the helpful attitude.

## License

The license is GPLv3 for all non commercial purposes.
Contact me directly if you want to use it commercially.
