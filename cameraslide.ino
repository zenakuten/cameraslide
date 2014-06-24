//------------------------------------------------------------------------------
// 2 Axis CNC Demo v1 - only supports motor shield v1
// dan@marginallycelver.com 2013-08-30
// zenakuten@yahoo.com 2014-06-11 - altered/branched for custom single axis system
//------------------------------------------------------------------------------
// Copyright at end of file.
// please see http://www.github.com/MarginallyClever/GcodeCNCDemo for more information.
//#define F_CPU 7900000 // clock frequency, set according to clock used!
#define F_CPU 16000000 // clock frequency, set according to clock used!

#include <inttypes.h>
#include <stdlib.h>
#include <avr/io.h>
#include <avr/sleep.h>
#include <util/delay.h>
#include <avr/interrupt.h>
//------------------------------------------------------------------------------
// CONSTANTS
//------------------------------------------------------------------------------
#define VERSION (1) // firmware version
#define BAUD (115200) // How fast is the Arduino talking?
#define MAX_BUF (64) // What is the longest message Arduino can store?
#define STEPS_PER_TURN (200) // depends on your stepper motor. most are 200.
#define STEPS_PER_MM (STEPS_PER_TURN/1.27) //steps per mm
#define MIN_STEP_DELAY (50.0)
#define MAX_FEEDRATE (1000000.0/MIN_STEP_DELAY)
#define MIN_FEEDRATE (0.01)


#define PIN_STEP (4)
#define PIN_DIR  (5)
#define PIN_ENDSTOP_X (8)
#define PIN_PHOTOGRAPH (6)

#define XOFF 19
#define XON  17


//------------------------------------------------------------------------------
// GLOBALS
//------------------------------------------------------------------------------
char buffer[MAX_BUF]; // where we store the message until we get a ';'
int sofar; // how much is in the buffer

float px=0.0, py=0.0; // location

// speeds
float fr=0; // human version
long step_delay; // machine version

// settings
char mode_abs=1; // absolute mode?


//------------------------------------------------------------------------------
// METHODS
//------------------------------------------------------------------------------


/**
* delay for the appropriate number of microseconds
* @input ms how many milliseconds to wait
*/
void pause(long ms) {
  delay(ms/1000);
  delayMicroseconds(ms%1000); // delayMicroseconds doesn't work for values > ~16k.
}


/**
* Set the feedrate (speed motors will move)
* @input nfr the new speed in steps/second
*/
void feedrate(float nfr) {
  if(fr==nfr) return; // same as last time? quit now.

  if(nfr>MAX_FEEDRATE || nfr<MIN_FEEDRATE) { // don't allow crazy feed rates
    Serial.print(F("New feedrate must be greater than "));
    Serial.print(MIN_FEEDRATE);
    Serial.print(F("steps/s and less than "));
    Serial.print(MAX_FEEDRATE);
    Serial.println(F("steps/s."));
    return;
  }
  step_delay = 1000000.0/nfr;
  fr=nfr;
}


/**
* Set the logical position
* @input npx new position x
* @input npy new position y
*/
void position(float npx,float npy) {
  // here is a good place to add sanity tests
  px=npx;
  py=npy;
}


/**
* Uses bresenham's line algorithm to move both motors
* @input newx the destination x position
* @input newy the destination y position
**/
void line(float newx,float newy) {
  long dx=newx-px;
  long dy=newy-py;
  int dirx=dx>0?1:-1;
  int diry=dy>0?-1:1; // because the motors are mounted in opposite directions
  dx=abs(dx);
  dy=abs(dy);

  long i;
  long over=0;

  if(dx>dy) {
    for(i=0;i<dx;++i) {      
      //m1.onestep(dirx);
      onestepx(dirx);
      over+=dy;
      if(over>=dx) {
        over-=dx;
        //m2.onestep(diry);
      }
      pause(step_delay);
    }
  } else {
    for(i=0;i<dy;++i) {
      //m2.onestep(diry);
      over+=dx;
      if(over>=dy) {
        over-=dy;
        //m1.onestep(dirx);
        onestepx(dirx);
      }
      pause(step_delay);
    }
  }

  px=newx;
  py=newy;
}

//step via drv8825
void onestepx(int dir)
{
    if(digitalRead(PIN_ENDSTOP_X) == LOW && dir <= 0) {
      Serial.println("Endstop X triggered");
      return;
    }
    digitalWrite(PIN_DIR, dir > 0 ? 1 : 0);
    delay(1);
    digitalWrite(PIN_STEP, 1);
    delay(1);
    digitalWrite(PIN_STEP, 0); 
    delay(1);
}

void home() 
{  
   while(digitalRead(PIN_ENDSTOP_X) != LOW) {
     onestepx(-1);
     pause(10);
   }  
   position(0,0);
}


void takepicture()
{
	const uint8_t count=12;
	for(int i=0; i < count; i++) {
		digitalWrite(PIN_PHOTOGRAPH, HIGH);
		delayMicroseconds(10);
		digitalWrite(PIN_PHOTOGRAPH, LOW);
		delayMicroseconds(10);
	}
	delayMicroseconds(7330);
	for(int i=0; i < count; i++) {
		digitalWrite(PIN_PHOTOGRAPH, HIGH);
		delayMicroseconds(10);
		digitalWrite(PIN_PHOTOGRAPH, LOW);
		delayMicroseconds(10);
	}
}

/**
* Look for character /code/ in the buffer and read the float that immediately follows it.
* @return the value found. If nothing is found, /val/ is returned.
* @input code the character to look for.
* @input val the return value if /code/ is not found.
**/
float parsenumber(char code,float val) {
  char *ptr=buffer;
  while(ptr && *ptr && ptr<buffer+sofar) {
    if(toupper(*ptr)==code) {
      return atof(ptr+1);
    }
    ptr=strchr(ptr,' ')+1;
  }
  return val;
}


/**
* write a string followed by a float to the serial line. Convenient for debugging.
* @input code the string.
* @input val the float.
*/
void output(char *code,float val) {
  Serial.print(code);
  Serial.println(val);
}


/**
* print the current position, feedrate, and absolute mode.
*/
void where() {
  output("X",px);
  output("Y",py);
  output("F",fr);
  Serial.println(mode_abs?"ABS":"REL");
}


/**
* display helpful information
*/
void help() {
  Serial.print(F("GcodeCNCDemo2AxisV1 "));
  Serial.println(VERSION);
  Serial.println(F("Commands:"));
  Serial.println(F("G00 [X(steps)] [Y(steps)] [F(feedrate)]; - linear move"));
  Serial.println(F("G01 [X(steps)] [Y(steps)] [F(feedrate)]; - linear move"));
  Serial.println(F("G04 P[seconds]; - delay"));
  Serial.println(F("G28; - home"));
  Serial.println(F("G90; - absolute mode"));
  Serial.println(F("G91; - relative mode"));
  Serial.println(F("G92 [X(steps)] [Y(steps)]; - change logical position"));
  Serial.println(F("M18; - disable motors"));
  Serial.println(F("M100; - this help message"));
  Serial.println(F("M114; - report position and feedrate"));
  Serial.println(F("M240; - Cannon DSLR remote picture"));
}


/**
* Read the input buffer and find any recognized commands. One G or M command per line.
*/
void processCommand() {
  int cmd = parsenumber('G',-1);
  switch(cmd) {
  case 0: // move linear
  case 1: // move linear
    feedrate(parsenumber('F',fr));
    line( (parsenumber('X',(mode_abs?px:0)) + (mode_abs?0:px))*STEPS_PER_MM,
          (parsenumber('Y',(mode_abs?py:0)) + (mode_abs?0:py))*STEPS_PER_MM );
    break;
  case 4: 
      delay(parsenumber('P', 0)*1000.0);
      break; // dwell
  case 28: home(); break;
  case 90: mode_abs=1; break; // absolute mode
  case 91: mode_abs=0; break; // relative mode
  case 92: // set logical position
    position( parsenumber('X',0),
              parsenumber('Y',0) );
    break;
  default: break;
  }

  cmd = parsenumber('M',-1);
  switch(cmd) {
    case 18: // disable motors
  //    m1.release();
  //    m2.release();
      break;
    case 100: help(); break;
    case 114: where(); break;
    case 240: takepicture(); break;
    case 241: 
              digitalWrite(PIN_PHOTOGRAPH, HIGH);  //led test
              delay(3000);
              digitalWrite(PIN_PHOTOGRAPH, LOW);
         break;
    default: break;
  }
}


/**
* prepares the input buffer to receive a new message and tells the serial connected device it is ready for more.
*/
void ready() {
  sofar=0; // clear input buffer
  Serial.print(F(">")); // signal ready to receive input
}


/**
* First thing this machine does on startup. Runs only once.
*/
void setup() {
  pinMode(PIN_DIR, OUTPUT);
  pinMode(PIN_STEP, OUTPUT);
  pinMode(PIN_PHOTOGRAPH, OUTPUT);
  pinMode(PIN_ENDSTOP_X, INPUT_PULLUP);
  
  Serial.begin(BAUD); // open coms
  help(); // say hello
  position(0,0); // set staring position
  feedrate((MAX_FEEDRATE + MIN_FEEDRATE)/2); // set default speed
  ready();
}


/**
* After setup() this machine will repeat loop() forever.
*/
void loop() {
  // listen for serial commands
  while(Serial.available() > 0) { // if something is available
    char c=Serial.read(); // get it
    Serial.print(c); // repeat it back so I know you got the message
    if(sofar<MAX_BUF) buffer[sofar++]=c; // store it
    if(buffer[sofar-1]==';' || buffer[sofar-1] == '\n' || buffer[sofar-1] == '\r') break; // entire message received
  }

  if(sofar>0 && (buffer[sofar-1]==';' || buffer[sofar-1]=='\n' || buffer[sofar-1] =='\r')) {
    // we got a message and it ends with a semicolon
    buffer[sofar]=0; // end the buffer so string functions work right
    Serial.print(F("\r\n")); // echo a return character for humans
    Serial.write(XOFF);
    processCommand(); // do something with the command
    ready();
    Serial.write(XON);
  }
}

/**
* This file is part of GcodeCNCDemo.
*
* GcodeCNCDemo is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* GcodeCNCDemo is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with Foobar. If not, see <http://www.gnu.org/licenses/>.
*/
