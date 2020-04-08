/*    Linda Ryan (020080205)
       4 Apr 2020
       Lab 12
       Title: 321Maker Experiment #012 - Motor Control
*/

#include <Servo.h>  // include servo library

int button1Pin = 2;    //The SW1 button is connected to pin 2 of the Arduino.
int button2Pin = 3;    //The SW2 button is connected to pin 3 of the Arduino.
int rgbLED[3] = {9, 10, 11};  // The rgb led is connected to pins 9, 10 & 11
int servoPin = 7;  // the servo is connected to pin 7
Servo servoObj;  // create servo object
int counter = 0;  // SW1 button state

void setup() { //The Setup function runs once.
  pinMode(button1Pin, INPUT);  //Setup button1 pin as an input pin.
  pinMode(button2Pin, INPUT);  //Setup button2 pin as an input pin.
  servoObj.attach(servoPin);  // attach the servo to the pin used
  for (int i = 0; i < 3; i++) {
    pinMode(rgbLED[i], OUTPUT); // set up rgbLED as output pin
  }
}

void loop() { //The loop function runs forever.
  if (digitalRead(button1Pin) == LOW) { //Check to see if button1Pin is pressed.
    counter++; // increment button state counter
    delay(150);
  }
  if (digitalRead(button2Pin) == LOW) { //Check to see if button2 is pressed.
    counter--; // decrement button state counter
    delay(150);
  }
  
  // each time button1 is pressed the motor moves forward by 25% (45 degrees) and colour changes based on servo pos. when motor reaches 100% and button 1 is pressed the motor returns to 0% (going through leds in reverse order)
  if (counter < 0) {
    while (counter < 4) { 
      counter++; //when button1 is pressed the counter is incremented if <4
      changePosition(); // change servo position
      changeColour();  // change rgbLED colour
    }
  }
  // each time button2 is pressed the motor moves backward by 25% (45 degrees) and colour changes based on servo pos. when motor reaches 0% and button 2 is pressed it goes to 100% and goes through all the lights in reverse order
  if (counter > 4) {
    while (counter > 0) {
      counter--; //when button2 is pressed the counter is decrememted if >4
      changePosition(); // change servo position
      changeColour();  // change rgbLED colour
    }
  }
  changePosition(); // change servo position
  changeColour();  // change rgbLED colour
}

void changeColour() {
  switch (counter) {
    case 1:
      digitalWrite(rgbLED[0], HIGH); // turn on red led
      digitalWrite(rgbLED[1], LOW); // turn off green led
      digitalWrite(rgbLED[2], LOW); // turn off blue led
      break;
    case 2:
      digitalWrite(rgbLED[0], HIGH); // turn on red led
      digitalWrite(rgbLED[1], LOW); // turn off green led
      digitalWrite(rgbLED[2], HIGH); // turn on blue led
      break;
    case 3:
      digitalWrite(rgbLED[0], LOW); // turn off red led
      digitalWrite(rgbLED[1], HIGH); // turn on green led
      digitalWrite(rgbLED[2], LOW); // turn off blue led
      break;
    case 4:
      digitalWrite(rgbLED[0], LOW); // turn off red led
      digitalWrite(rgbLED[1], LOW); // turn off green led
      digitalWrite(rgbLED[2], HIGH); // turn on blue led
      break;
    default:
      digitalWrite(rgbLED[0], LOW); // turn off red led
      digitalWrite(rgbLED[1], LOW); // turn off green led
      digitalWrite(rgbLED[2], LOW); // turn off blue led
      break;
  }
}

//change servo position based on button state (counter): when you press button 1(d2) the motor moves forward by 25% (45 degrees)
void changePosition() {  
  switch (counter) {
    case 1:
      servoObj.write(45);
      delay(150);
      break;
    case 2:
      servoObj.write(90);
      delay(150);
      break;
    case 3:
      servoObj.write(135);
      delay(150);
      break;
    case 4:
      servoObj.write(180);
      delay(150);
      break;
    default:
      servoObj.write(0);
      delay(150);
      break;
  }
}
