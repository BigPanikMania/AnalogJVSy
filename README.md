# AnalogJVSy
Open source JVS to PC interface using a Teensy 

## Description
AnalogJVSy lets you connect your JVS analog controls (USB HID joystick with 4 analog axes + 32 buttons) to your PC and use them as controls, for MAME or other purposes. 
AnalogJVSy also include a serial command line interface allow you to control the first six JVS outputs (usefull to control Lamps, solenoids, etc.).

AnalogJVSy is base on JVSy project from **K4roshi**. Use Arduino IDE 1.8.5.

Sucessfully tested on SEGA I/O Board Type 1 (837-13551) and Type 2 (837-13844)

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

### PCB

I include a Gerber file to build a 2 layers PCB.

![JVSyPSB](https://github.com/BigPanikMania/AnalogJVSy/blob/main/PCB/PCB-AnalogJVSy-2.jpg "JVSyPCB")

![JVSyPSB](https://github.com/BigPanikMania/AnalogJVSy/blob/main/PCB/PCB-AnalogJVSy-1.jpg "JVSyPCB")


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
|    Button 29   |  Test Button   | 
|    Button 30 AND Keyboard key 5  |  Coin 1  | 
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

NB: Only the first six outputs are managed with AnalogJVSy (TODO: outputs \#7 to \#22)
    
## Thanks

This project is based on:
@k4roshi for JVSy digital sketch (https://github.com/k4roshi/JVSy). Thanks for the the wonderful work done.

@roysmeding for the reverse engineering done (https://github.com/TheOnlyJoey/openjvs).

SEGA JVS manual (http://superusr.free.fr/arcade/JVS/JVST_VER3.pdf)

Others similars projects use the same hardware:
   
- @k4roshi's initial JVSy work (https://github.com/k4roshi/JVSy)
- Adapted version of JVSy by gtranche (https://github.com/gtranche/JVSy)
- Advanced version by FredBedo (https://github.com/Fredobedo/JVS2X)
   

Many thanks for sharing all these precious sources of information

## License

The license is GPLv3 for all non commercial purposes.
Contact me directly if you want to use it commercially.
