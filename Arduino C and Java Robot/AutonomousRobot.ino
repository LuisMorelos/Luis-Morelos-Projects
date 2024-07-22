/*
  SparkFun Inventor’s Kit
  Circuit 5C - Autonomous Robot

  This robot will drive around on its own and react to obstacles by backing up and turning to a new direction.
  This sketch was adapted from one of the activities in the SparkFun Guide to Arduino.
  Check out the rest of the book at
  https://www.sparkfun.com/products/14326

  This sketch was written by SparkFun Electronics, with lots of help from the Arduino community.
  This code is completely free for any use.

  View circuit diagram and instructions at: https://learn.sparkfun.com/tutorials/sparkfun-inventors-kit-experiment-guide---v41
  Download drawings and code at: https://github.com/sparkfun/SIK-Guide-Code
*/

enum State {
  readMagic,
  readKey,
  readDirection,
  readMovement,
  movement
};
State currentState = readMagic;

//the right motor will be controlled by the motor A pins on the motor driver
const int AIN1 = 13;  //control pin 1 on the motor driver for the right motor
const int AIN2 = 12;  //control pin 2 on the motor driver for the right motor
const int PWMA = 11;  //speed control pin on the motor driver for the right motor

//the left motor will be controlled by the motor B pins on the motor driver
const int PWMB = 10;  //speed control pin on the motor driver for the left motor
const int BIN2 = 9;   //control pin 2 on the motor driver for the left motor
const int BIN1 = 8;   //control pin 1 on the motor driver for the left motor

//LED and button pins, as well as button debouncing variables
const int ledPin = 3;
const int buttonPin = 4;
int ledState = HIGH;                 // the current state of the output pin
int buttonState;                     // the current reading from the input pin
int lastButtonState = LOW;           // the previous reading from the input pin
unsigned long lastDebounceTime = 0;  // the last time the output pin was toggled
unsigned long debounceDelay = 50;    // the debounce time; increase if the output flickers

//distance and key variables
const int trigPin = 6;
const int echoPin = 5;
const byte magicNum = 0x21;
const byte dataKey = 0x35;

//delta timing variables
unsigned long readingDelta = 50;
unsigned long readingInterval = 0;
unsigned long sendingDelta = 1000;
unsigned long sendingInterval = 0;

bool isRemote = true;  //mode of robot

int switchPin = 7;  //switch to turn the robot on and off

float distance = 0;  //variable to store the distance measured by the distance sensor

int currentDirection = 0;  //which way we are going

int index = 0;
long value = 0;

//robot behaviour variables
int backupTime = 300;  //amount of time that the robot will back up when it senses an object
int turnTime = 200;    //amount that the robot will turn once it has backed up

const int driveTimePerCm = 20;  //this is the number of milliseconds that it takes the robot to drive 1 inch
                                //it is set so that if you tell the robot to drive forward 25 units, the robot drives about 25 inches

const int turnTimePerCm = 8;      //this is the number of milliseconds that it takes to turn the robot 1 degree
                                  //it is set so that if you tell the robot to turn right 90 units, the robot turns about 90 degrees
unsigned long movementInterval = 0;         //how long will we move?
unsigned long movementStart = 0;  //when did we start moving?

//Note: these numbers will vary a little bit based on how you mount your motors, the friction of the
//surface that your driving on, and fluctuations in the power to the motors.
//You can change the driveTime and turnTime to make them more accurate

/********************************************************************************/
void setup() {
  pinMode(trigPin, OUTPUT);  //this pin will send ultrasonic pulses out from the distance sensor
  pinMode(echoPin, INPUT);   //this pin will sense when the pulses reflect back to the distance sensor

  pinMode(switchPin, INPUT_PULLUP);  //set this as a pullup to sense whether the switch is flipped

  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(ledPin, ledState);

  //set the motor control pins as outputs
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(PWMA, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  Serial.begin(9600);                       //begin serial communication with the computer
  Serial.print("To infinity and beyond!");  //test the serial connection
}

/********************************************************************************/
void loop() {
  buttonDebouncer();
  moving();
  if (Serial.available() > 0) {  //read values to see if we move
    char c = Serial.read();
    switch (currentState) {
      case readMagic:
        if (c == magicNum && digitalRead(switchPin) == LOW) {
          currentState = readKey;
        }
        break;

      case readKey:
        if (c == dataKey) {
          currentState = readDirection;
        }
        break;

      case readDirection:
        switch (c) {
          case 'f':
            currentDirection = 1;
            break;
          case 'b':
            currentDirection = 2;
            break;
          case 'l':
            currentDirection = 3;
            break;
          case 'r':
            currentDirection = 4;
            break;
          default:
            currentDirection = 0;
        }
        index = 0;
        value = 0;
        currentState = readMovement;
        break;

      case readMovement:
        movementStart = millis();
        if (currentDirection <= 2) {
          movementInterval = driveTimePerCm * (int)c;
        } else {
          movementInterval = turnTimePerCm * (int)c;
        }
        currentState = movement;
        break;
    }
  }

  if (millis() >= readingInterval) {  //runs every 50 ms
    //DETECT THE DISTANCE READ BY THE DISTANCE SENSOR
    distance = getDistance();
    if (millis() >= sendingInterval) {  //send raw data once every second
      sendData((distance * 2) / 0.0343);
      sendingInterval = millis() + sendingDelta;
    }

    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");  // print the units

    autonomousMode();

    readingInterval = millis() + readingDelta;
  }
}

/********************************************************************************/
void rightMotor(int motorSpeed)  //function for driving the right motor
{
  if (motorSpeed > 0)  //if the motor should drive forward (positive speed)
  {
    digitalWrite(AIN1, HIGH);  //set pin 1 to high
    digitalWrite(AIN2, LOW);   //set pin 2 to low
  } else if (motorSpeed < 0)   //if the motor should drive backward (negative speed)
  {
    digitalWrite(AIN1, LOW);   //set pin 1 to low
    digitalWrite(AIN2, HIGH);  //set pin 2 to high
  } else                       //if the motor should stop
  {
    digitalWrite(AIN1, LOW);  //set pin 1 to low
    digitalWrite(AIN2, LOW);  //set pin 2 to low
  }
  analogWrite(PWMA, abs(motorSpeed));  //now that the motor direction is set, drive it at the entered speed
}

/********************************************************************************/
void leftMotor(int motorSpeed)  //function for driving the left motor
{
  if (motorSpeed > 0)  //if the motor should drive forward (positive speed)
  {
    digitalWrite(BIN1, HIGH);  //set pin 1 to high
    digitalWrite(BIN2, LOW);   //set pin 2 to low
  } else if (motorSpeed < 0)   //if the motor should drive backward (negative speed)
  {
    digitalWrite(BIN1, LOW);   //set pin 1 to low
    digitalWrite(BIN2, HIGH);  //set pin 2 to high
  } else                       //if the motor should stop
  {
    digitalWrite(BIN1, LOW);  //set pin 1 to low
    digitalWrite(BIN2, LOW);  //set pin 2 to low
  }
  analogWrite(PWMB, abs(motorSpeed));  //now that the motor direction is set, drive it at the entered speed
}

/********************************************************************************/
//RETURNS THE DISTANCE MEASURED BY THE HC-SR04 DISTANCE SENSOR
float getDistance() {
  unsigned long echoTime;    //variable to store the time it takes for a ping to bounce off an object
  float calculatedDistance;  //variable to store the distance calculated from the echo time

  //send out an ultrasonic pulse that's 10ms long
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  echoTime = pulseIn(echoPin, HIGH);  //use the pulsein command to see how long it takes for the
                                      //pulse to bounce back to the sensor

  calculatedDistance = (echoTime * 0.0343) / 2;  //calculate the distance of the object that reflected the pulse (half the bounce time multiplied by the speed of sound)

  return calculatedDistance;  //send back the distance that was calculated
}

void buttonDebouncer() {
  int reading = digitalRead(buttonPin);  //read button input

  if (reading != lastButtonState) {
    lastDebounceTime = millis();  // reset the debouncing timer
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    // whatever the reading is at, it's been there for longer than the debounce
    // delay, so take it as the actual current state:
    // if the button state has changed:
    if (reading != buttonState) {
      buttonState = reading;
      // only toggle the LED if the new button state is HIGH
      if (buttonState == HIGH) {
        ledState = !ledState;
        isRemote = !isRemote;
      }
    }
  }

  digitalWrite(ledPin, ledState);
  lastButtonState = reading;
}

void autonomousMode() {
  if (digitalRead(switchPin) == LOW && isRemote == false) {  //if the on switch is flipped and it is on the automation mode

    if (distance < 10) {  //if an object is detected
      //back up and turn
      Serial.print(" ");
      Serial.print("BACK!");

      //stop for a moment
      rightMotor(0);
      leftMotor(0);
      delay(200);

      //back up
      rightMotor(-255);
      leftMotor(-255);
      delay(backupTime);

      //turn away from obstacle
      rightMotor(255);
      leftMotor(-255);
      delay(turnTime);

    } else {  //if no obstacle is detected drive forward
      Serial.print(" ");
      Serial.print("Moving...");


      rightMotor(255);
      leftMotor(255);
    }
  } else {  //if the switch is off then stop

    //stop the motors
    rightMotor(0);
    leftMotor(0);
  }
}

void sendData(unsigned int value) {
  Serial.write(magicNum);
  Serial.write(0x34);
  Serial.write(value >> 24);
  Serial.write(value >> 16);
  Serial.write(value >> 8);
  Serial.write(value);
}

void sendInfo(unsigned int value) {
  Serial.write(magicNum);
  Serial.write(0x32);
  Serial.write(value >> 24);
  Serial.write(value >> 16);
  Serial.write(value >> 8);
  Serial.write(value);
}

void moving() {
  if (currentState == movement) {
    if (currentDirection == 1) {
      rightMotor(255);
      leftMotor(255);
    } else if (currentDirection == 2) {
      rightMotor(-255);
      leftMotor(-255);
    } else if (currentDirection == 3) {
      rightMotor(255);
      leftMotor(-255);
    } else if (currentDirection == 4) {
      rightMotor(-255);
      leftMotor(255);
    }
    if (millis() - movementStart >= movementInterval) {
      currentState = readMagic;
    }
  }
}