/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 https://www.arduino.cc/en/Tutorial/LibraryExamples/Sweep
*/

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position
int state = 0;
void setup() {
  Serial.begin(9600);
  myservo.attach(6);  // attaches the servo on pin 3 to the servo object
}

void loop() {
  if (Serial.available()) {
    state =  Serial.parseInt();
  }
  else {
    state = state;
  }
    myservo.write(state);                  // sets the servo position according to the scaled value
    delay(15); 
}
