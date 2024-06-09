#include <math.h>

// Connection pins:
int a=2;
int b=3;
int c=4;
int d=5;
int e=6;
int f=7;
int g=8;
int in1 = 9;  //L293D-IN1
int in2 = 10;  //L293D-IN2
int leftButtonPin = 11;
int rightButtonPin = 12;

int leftButtonState = 0;     // current state of the left button
int rightButtonState = 0;    // current state of the right button
int lastLButtonState = 0;     // previous state of the button
int lastRButtonState = 0;     // previous state of the button

int dec[11] = {0b1111110, 0b0110000, 0b1101101, 0b1111001,
               0b0110011, 0b1011011, 0b1011111, 0b1110000,
               0b1111111, 0b1111011, 0b1110111};

int stepNumber = 4;
int maxStep = stepNumber;
int speedPercent = 100 / stepNumber;
int maxSpeed = 255;

void setup()
{
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(leftButtonPin, INPUT);
  pinMode(rightButtonPin, INPUT);
  
  stepNumber = 0;
}

void loop()
{
  leftButtonState = digitalRead(leftButtonPin);
  rightButtonState = digitalRead(rightButtonPin);

  // compare the buttonState to its previous state
  if (leftButtonState == HIGH && lastLButtonState == LOW) {
    if(stepNumber > -maxStep)
      stepNumber--;
  }
  lastLButtonState = leftButtonState;
  
  // compare the buttonState to its previous state
  if (rightButtonState == HIGH && lastRButtonState == LOW) {
    if(stepNumber < maxStep)
      stepNumber++;
  }
  lastRButtonState = rightButtonState;
  
  int motorSpeed = maxSpeed*speedPercent*stepNumber/100;
  
  if(stepNumber >= 0){ // CLOCKWISE
    analogWrite(in1, motorSpeed);  // set speed of motor (0-255)
    digitalWrite(in2, 0); // yön
  }
  else{ // COUNTER CLOCKWISE
    analogWrite(in1, 255+motorSpeed);  // set speed of motor (0-255)
    digitalWrite(in2, 1); // yön
  }
 
  // update 7 segment display
  for(int pin = a; pin <= g; pin++)
     digitalWrite(pin, bitRead(dec[abs(stepNumber)], g-a-pin+2));
}
