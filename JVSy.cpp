#include "JVSy.h"
#include "JVS.h"

HardwareSerial Uart = HardwareSerial();
JVS j = JVS(Uart);
unsigned long lastTime = 0;
unsigned char oldoutputdata=0;

void setup()
{
	Serial.begin(115200);
	Uart.begin(115200, DE_PIN);
	Joystick.useManualSend(true);
	delay(START_DELAY);
	Serial.println("Start");
	while (!j.initialized){
		j.reset();
		int i = 1;
		while (analogRead(SENSE_PIN) > 20){
			j.init(i++);
		}
		// USE THIS TO REBOOT, IF NEEDED
	// _restart_Teensyduino_();
	}
    lastTime = millis();
}

void loop()
{
    
    unsigned long time = millis();
if(Serial.available()>0){
    int outputport = Serial.parseInt();
    unsigned int outputdata=Serial.parseInt();
    if (Serial.read()=='x'){
      if (outputport==0)oldoutputdata=outputdata;
      if (outputport>0 && outputport<7){
        outputport=7-outputport;
        if(outputdata==0)oldoutputdata &=~(1<<outputport+1);
        if(outputdata==1)oldoutputdata|=1<<outputport+1;
      }
      j.outputs(1,oldoutputdata);
     
    }
 }
   
          
    if(time - lastTime >= 20)
    {
        lastTime = time;
        j.switches(1);

        
    }
}


