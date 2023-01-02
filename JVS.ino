/*
   JVS.cpp

    Created on: 14/apr/2014
        Author: k4roshi
    Add 2 ways Analog joystick 2020
        Author: BigPanik
    Add 6 Outputs 2022 september
        Author: BigPanik
*/

#include "Arduino.h"
#include "JVS.h"
#include "constants.h"

JVS::JVS(HardwareSerial& serial) :
  _Uart(serial) // Need to initialize references before body
{
  coins1 = 0;
  coins2 = 0;
  coin_pressed_at = 0;
  initialized = false;
  shift_mode = false;
  pressed_smth = false;
  old_key = 0;
}

void JVS::reset() {
  char str[] = { CMD_RESET, CMD_RESET_ARG };
  this->write_packet(BROADCAST, str, 2);
  delay(ASSIGN_DELAY);
  Serial.println("RESET");
}

void JVS::assign(int attempt) {
  char str[] = { CMD_ASSIGN_ADDR, attempt };
  this->cmd(BROADCAST, str, 2);
  Serial.println("ADDR");
}

void JVS::init(int board) {
  Serial.println("ADDR");
  char str[] = { CMD_ASSIGN_ADDR, board };
  this->cmd(BROADCAST, str, 2);
  Serial.println("REQ");
  char str1[] = { CMD_REQUEST_ID };
  this->cmd(board, str1, 1);
  Serial.println("CMD");
  char str2[] = { CMD_COMMAND_VERSION };
  this->cmd(board, str2, 1);
  Serial.println("JVS");
  char str3[] = { CMD_JVS_VERSION };
  this->cmd(board, str3, 1);
  Serial.println("CMS");
  char str4[] = { CMD_COMMS_VERSION };
  this->cmd(board, str4, 1);
  Serial.println("CAP");
  char str5[] = { CMD_CAPABILITIES };
  this->cmd(board, str5, 1);
  initialized = true;
}

void JVS::outputs(int board, unsigned char outbyte) {
  
  Serial.print("CMD_WRITE_DIGITAL_OUTPUT:");
  Serial.println(outbyte, BIN);
  char str1[] = { CMD_WRITE_DIGITAL, 0x01, 0x80}; //FC = 11111100 output  51 53 55 52 54 56 x x 
  str1[2]=outbyte;
  this->cmd(board, str1, sizeof str1);

}

void JVS::switches(int board) {
  char str[] = { CMD_READ_DIGITAL, 0x02, 0x02, CMD_READ_COINS, 0x02, CMD_READ_ANALOG, 0x04};
  //char str[ ] = { 0x20, 0x02, 0x02, 0x21, 0x02, 0x22, 0x08};
  this->write_packet(board, str, sizeof str);
  char incomingByte;
  while (!_Uart.available()) {
  }
  while (_Uart.read() != 0xE0) {
  } // wait for sync
  while (_Uart.read() != 0) {
  } // only if it's for me
  while (!_Uart.available()) {
  } // wait for length
  int length = _Uart.read();
  int counter = 0;
  int x = 512;
  int y = 512;
  int z = 512;
  int zA = 512;
  int coin1 = 0;
  int key = 0;
  bool old_shift = shift_mode;

  if	(DEBUG_MODE) {
    Serial.print("swthc: E0 0 ");
    Serial.print(length, HEX);
  }
  while (counter < length) {
    while (!_Uart.available()) {
    }
    incomingByte = _Uart.read();
    if (DEBUG_MODE) {
      Serial.print(" ");
      Serial.print(incomingByte, HEX);
    }
    switch (counter) {
      // first three bytes are sync 
      case 2:
          Joystick.button(29, bitRead(incomingByte, 7)); //TEST button
          break;
      case 3:
        // player 1 byte 1

          Joystick.button(8, bitRead(incomingByte, 0)); // push 2
          Joystick.button(7, bitRead(incomingByte, 1)); // push 1
          Joystick.button(6, bitRead(incomingByte, 2)); //Right
          Joystick.button(5, bitRead(incomingByte, 3)); //Left
          Joystick.button(4, bitRead(incomingByte, 4)); //Down
          Joystick.button(3, bitRead(incomingByte, 5)); // UP
          Joystick.button(2, bitRead(incomingByte, 6)); //Service
          Joystick.button(1, bitRead(incomingByte, 7)); //Start button
 
        break;
      case 4:
          Joystick.button(9, bitRead(incomingByte, 7));   //push 3
          Joystick.button(10, bitRead(incomingByte, 6));  //push 4
          Joystick.button(11, bitRead(incomingByte, 5));  //push 5
          Joystick.button(12, bitRead(incomingByte, 4));  //push 6
          Joystick.button(13, bitRead(incomingByte, 3));  //push 7
          Joystick.button(14, bitRead(incomingByte, 2));  //push 8
          
        break;
      case 5:
        // player 2 byte 1
          Joystick.button(22, bitRead(incomingByte, 1));
          Joystick.button(21, bitRead(incomingByte, 0));
          Joystick.button(20, bitRead(incomingByte, 2));
          Joystick.button(19, bitRead(incomingByte, 3));
          Joystick.button(18, bitRead(incomingByte, 4));
          Joystick.button(17, bitRead(incomingByte, 5));         
          Joystick.button(16, bitRead(incomingByte, 6));
          Joystick.button(15, bitRead(incomingByte, 7)); //Start button Player 2
        break;
      case 6:
        // player 2 byte 2
          Joystick.button(23, bitRead(incomingByte, 7));
          Joystick.button(24, bitRead(incomingByte, 6));
          Joystick.button(25, bitRead(incomingByte, 5));
          Joystick.button(26, bitRead(incomingByte, 4));
          Joystick.button(27, bitRead(incomingByte, 3));
          Joystick.button(28, bitRead(incomingByte, 2));
        
        break;
      case 8:
        // coins 1 status
        break;
      case 9:
        // Insert coin 1
        if (incomingByte > coins1) {
          // added coin
          coin1 = 1;
          coins1 = incomingByte;
        }
        if (coin1) {
          coin_pressed_at = millis();
          Keyboard.press(KEY_5);
          Joystick.button(30, 1);
        } else if (coin_pressed_at > 0) {
          if (millis() - coin_pressed_at > 50) {
            coin_pressed_at = 0;
            Keyboard.release(KEY_5);
            Joystick.button(30, 0);
          }
        }
        break;
      case 10:
        // coins2 status
        break;
      case 11:
        // coins2
        break;
      case 13:
        // Analog1
        x = (unsigned char)incomingByte * 4;
        Joystick.X(x);
        break;
      case 15:
        // Analog2
        y = (unsigned char)incomingByte * 4;
        Joystick.Y(y);
        break;
      case 17:
        // Analog3
        z = (unsigned char)incomingByte * 4;
        Joystick.Z(z);
        break;
      case 19:
        // Analog4
        zA = (unsigned char)incomingByte * 4;         
        Joystick.Zrotate(zA);
        break;
    }
    counter++;
    Joystick.send_now();
  }

  if (key) {
    if (key != old_key) {
      old_key = key;
      //	Serial.print("pressed key: ");
      //	Serial.println(key, HEX);
      Keyboard.set_key1(key);
    }
  } else {
    if (old_key) {
      //	Serial.print("old_key: ");
      //	Serial.println(old_key, HEX);
      Keyboard.set_key1(0);
      old_key = 0;
    }
  }
  Keyboard.send_now();
  delay(SWCH_DELAY);

  //	if (coins1 > 0){
  //		char str1[ ] = {CMD_DECREASE_COIN};
  //		this->cmd(board, str1, 1);
  //	}
  if (DEBUG_MODE)
    Serial.println();
}

int* JVS::cmd(char destination, char data[], int size) {
  this->write_packet(destination, data, size);
  char incomingByte;
  while (!_Uart.available()) {
  }
  while (_Uart.read() != 0xE0) {
  } // wait for sync
  while (_Uart.read() != 0) {
  } // only if it's for me
  while (!_Uart.available()) {
  } // wait for length
  int length = _Uart.read();
  Serial.print("Received: E0 0 ");
  Serial.print(length, HEX);
  int counter = 0;
  int * res = (int *) malloc(length * sizeof(int));
  while (counter < length) {
    while (!_Uart.available()) {
    }
    incomingByte = _Uart.read();
    res[counter] = incomingByte;
    // actually do something with incomingByte
    Serial.print(" ");
    Serial.print(res[counter], HEX);
    counter++;
  }
  Serial.println();
  delay(CMD_DELAY);
  return res;
}

void JVS::write_packet(char destination, char data[], int size) {
  _Uart.write(SYNC);
  _Uart.write(destination);
  _Uart.write(size + 1);
  char sum = destination + size + 1;
  for (int i = 0; i < size; i++) {
    if (data[i] == SYNC || data[i] == ESCAPE) {
      _Uart.write(ESCAPE);
      _Uart.write(data[i] - 1);
    } else {
      _Uart.write(data[i]);
    }
    sum = (sum + data[i]) % 256;
  }
  _Uart.write(sum);
  _Uart.flush();
}
//Button debugs
//Serial.print("1P1: ");
//for (int i = 0; i<=7; i++)
//	Serial.print(bitRead(incomingByte, i));
//Serial.println();
