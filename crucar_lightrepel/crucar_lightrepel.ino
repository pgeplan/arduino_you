#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN 9
#define NUM_PIXELS 3
Adafruit_NeoPixel npStrip(NUM_PIXELS, PIXEL_PIN);


const int motorEnablePinA = 11;
const int motorEnablePinB = 3;

const int motorPinA1 = 10;
const int motorPinA2 = 7;
const int motorPinB1 = 12;
const int motorPinB2 = 4;

const int echoPin = 5;
const int trigPin = 6;
const int photocellRpin = A6;
const int photocellLpin = A7;
const int photocellMpin = A5;


bool shouldTurnLeft = false;
bool objInWay = false;

long echo; 
long cm;
long standardSpeed = 127;

long attackCm = 15;

const int lightLimitRL = 700;
const int lightLimitMid = 600;


void setup() {

  // motors
  pinMode(motorEnablePinA, OUTPUT);
  pinMode(motorEnablePinB, OUTPUT);
  pinMode(motorPinA1, OUTPUT);
  pinMode(motorPinA2, OUTPUT);

  // sensors
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  digitalWrite(trigPin, LOW);

  /// neopixel
  npStrip.begin(); 

  Serial.begin(9600);
}

void loop() {  
  
  


  // sense light
  int leftPhotocell = analogRead(photocellLpin);
  int rightPhotocell = analogRead(photocellRpin);
  int midPhotocell = analogRead(photocellMpin);

  // if at midPhotoCell, get away from edge
  if (midPhotocell > lightLimitMid) {
    stopMoving(50);
    setMidSensorPixels();
    goBackwards(standardSpeed, 600);
    turnLeft(standardSpeed, 200);
  }

  // get distance 
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trigPin, LOW); 
  echo = pulseIn(echoPin, HIGH); 
  
  cm = echo / 58; 
  Serial.println(cm);

  // else attack okay
  if (cm < attackCm) {
    setAttackPixels();
    goForward(255, 50);
  }

  // otherwise check front sensors, if both off turn around
  else if ((leftPhotocell > lightLimitRL) && (rightPhotocell > lightLimitRL)) {
    stopMoving(100);
    setBothSensorsPixels();
    goBackwards(standardSpeed, 600);
    turnLeft(standardSpeed, 500);
  }

  else if (leftPhotocell > lightLimitRL) {
    stopMoving(100);
    setLeftSensorPixels();
    goBackwards(standardSpeed, 500);
    turnRight(standardSpeed, 200);
  }

  else if (rightPhotocell > lightLimitRL) {
    stopMoving(100);
    setRightSensorPixels();
    goBackwards(standardSpeed, 500);
    turnLeft(standardSpeed, 200);
  }

  else {
    setForwardPixels();
    goForward(80, 50);   
  }
}


void setForwardPixels() {
  //npStrip.clear();
  //npStrip.show();
  for (int i=0; i<NUM_PIXELS; i++) {
    npStrip.setPixelColor(i, random(0, 255), random(0, 255), random(0, 255));
    delay(100);
    npStrip.show();
  }
  for (int i=NUM_PIXELS-1; i>=0; i--) {
    npStrip.setPixelColor(i, random(0, 255), random(0, 255), random(0, 255));
    delay(100);
    npStrip.show();
  }
}

void setStopPixels() {
  npStrip.clear();
  for (int i=0; i<NUM_PIXELS; i++) {
    npStrip.setPixelColor(i, 0, 255, 0);
  }
  npStrip.show();
}

void setAttackPixels() {
  npStrip.clear();
  for (int i=0; i<NUM_PIXELS; i++) {
    npStrip.setPixelColor(i, 255, 0, 0);
  }
  npStrip.show();
}

void setBothSensorsPixels() {
  npStrip.clear();
  npStrip.setPixelColor(0, 0, 0, 255);
  npStrip.setPixelColor(1, 0, 0, 0);
  npStrip.setPixelColor(2, 0, 0, 255);
  npStrip.show();
}



void setLeftSensorPixels() {
  npStrip.clear();
  npStrip.setPixelColor(0, 0, 0, 255);
  npStrip.setPixelColor(1, 0, 0, 0);
  npStrip.setPixelColor(2, 0, 0, 0);
  npStrip.show();
}


void setRightSensorPixels() {
  npStrip.clear();
  npStrip.setPixelColor(0, 0, 0, 0);
  npStrip.setPixelColor(1, 0, 0, 0);
  npStrip.setPixelColor(2, 0, 0, 255);
  npStrip.show();
}

void setMidSensorPixels() {
  npStrip.clear();
  npStrip.setPixelColor(0, 0, 0, 0);
  npStrip.setPixelColor(1, 0, 0, 255);
  npStrip.setPixelColor(2, 0, 0, 0);
  npStrip.show();
}






void goForward(int vel, int delayTime) {
  analogWrite(motorEnablePinA, vel);
  analogWrite(motorEnablePinB, vel);
  digitalWrite(motorPinA1, HIGH);
  digitalWrite(motorPinA2, LOW);
  digitalWrite(motorPinB1, HIGH);
  digitalWrite(motorPinB2, LOW);
  delay(delayTime);
}

void turnLeft(int vel, int delayTime) {
  analogWrite(motorEnablePinA, vel);
  analogWrite(motorEnablePinB, vel);
  digitalWrite(motorPinA1, HIGH);
  digitalWrite(motorPinA2, LOW);
  digitalWrite(motorPinB1, LOW);
  digitalWrite(motorPinB2, LOW);
  delay(delayTime);
}

void turnRight(int vel, int delayTime) {
  analogWrite(motorEnablePinA, vel);
  analogWrite(motorEnablePinB, vel);
  digitalWrite(motorPinA1, LOW);
  digitalWrite(motorPinA2, LOW);
  digitalWrite(motorPinB1, HIGH);
  digitalWrite(motorPinB2, LOW);
  delay(delayTime);
}

void stopMoving(int delayTime) {
  digitalWrite(motorPinA1, LOW);
  digitalWrite(motorPinA2, LOW);
  digitalWrite(motorPinB1, LOW);
  digitalWrite(motorPinB2, LOW);
  delay(delayTime);
}

void goBackwards(int vel, int delayTime) {
  analogWrite(motorEnablePinB, vel);
  digitalWrite(motorPinA1, LOW);
  digitalWrite(motorPinA2, HIGH);
  digitalWrite(motorPinB1, LOW);
  digitalWrite(motorPinB2, HIGH);
  delay(delayTime);
}
