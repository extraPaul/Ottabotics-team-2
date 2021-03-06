// Motor A pins (enableA = enable motor, pinA1 = forward, pinA2 = backward)
int enableA = 2;
int pinA1 = 3;
int pinA2 = 4;

//Motor B pins (enabledB = enable motor, pinB2 = forward, pinB2 = backward)
int enableB = 5;
int pinB1 = 6;
int pinB2 = 7;

int trigPin = 8;
int echoPin = 9;
int trigPin2 = 11;
int echoPin2 = 12;
int led = 10;
int led2 = 13;

//This lets you run the loop a single time for testing
boolean run = true;
boolean looking = true;

void setup() {
Serial.begin (9600);
pinMode(trigPin, OUTPUT);
pinMode(echoPin2, INPUT);
pinMode(trigPin2, OUTPUT);
pinMode(echoPin, INPUT);
pinMode(led, OUTPUT);

pinMode(enableA, OUTPUT);
pinMode(pinA1, OUTPUT);
pinMode(pinA2, OUTPUT);

pinMode(enableB, OUTPUT);
pinMode(pinB1, OUTPUT);
pinMode(pinB2, OUTPUT);

enableMotors(153);
}

void loop() {
  if(run){
    enableMotors(153);
  
      long  duration, distance, duration2, distance2;
      digitalWrite(trigPin, LOW);  // Added this line
      digitalWrite(trigPin2, LOW);  // Added this line
      delayMicroseconds(2); // Added this line
      digitalWrite(trigPin, HIGH);
      digitalWrite(trigPin2, HIGH);
      delayMicroseconds(10);
      digitalWrite(trigPin, LOW);
      digitalWrite(trigPin2, LOW);
      duration = pulseIn(echoPin, HIGH);
      duration2 = pulseIn(echoPin2, HIGH);
      distance = (duration/2) / 29.1;
      distance2 = (duration2/2) / 29.1;
  
      if (distance < 30) {  // This is where the LED On/Off happens
        //An object was detected, therefore stop turning
        digitalWrite(led,HIGH); // When the Red condition is met, the Green LED should turn off
        looking = false;
      } else {
        digitalWrite(led,LOW);
      }
      
      if (distance2 > 5) {  // This is where the LED On/Off happens
        digitalWrite(led2, HIGH);
        backward(1000);
      } else {
        digitalWrite(led2, LOW);
      }
    
    if(looking){
      //Turn right, unless an object was detected
      turnRight(200);
    } else {
      //Go forward, to push the object
      forward(400);
      looking = true;
    }
  }
}

//Define high-level H-bridge commands

void enableMotors(int power)
{
motorAOn(power);
motorBOn(power);
}

void disableMotors()
{
motorAOff();
motorBOff();
}

void forward(int time)
{
motorAForward();
motorBForward();
delay(time);
}

void backward(int time)
{
motorABackward();
motorBBackward();
delay(time);
}

void turnLeft(int time)
{
motorABackward();
motorBForward();
delay(time);
}

void turnRight(int time)
{
motorAForward();
motorBBackward();
delay(time);
}

void coast(int time)
{
motorACoast();
motorBCoast();
delay(time);
}

void brake(int time)
{
motorABrake();
motorBBrake();
delay(time);
}
//Define low-level H-bridge commands

//enable motors
void motorAOn(int power)
{
digitalWrite(enableA, power);
}

void motorBOn(int power)
{
digitalWrite(enableB, power);
}

//disable motors
void motorAOff()
{
digitalWrite(enableB, LOW);
}

void motorBOff()
{
digitalWrite(enableA, LOW);
}

//motor A controls
void motorAForward()
{
digitalWrite(pinA1, HIGH);
digitalWrite(pinA2, LOW);
}

void motorABackward()
{
digitalWrite(pinA1, LOW);
digitalWrite(pinA2, HIGH);
}

//motor B controls
void motorBForward()
{
digitalWrite(pinB1, HIGH);
digitalWrite(pinB2, LOW);
}

void motorBBackward()
{
digitalWrite(pinB1, LOW);
digitalWrite(pinB2, HIGH);
}

//coasting and braking
void motorACoast()
{
digitalWrite(pinA1, LOW);
digitalWrite(pinA2, LOW);
}

void motorABrake()
{
digitalWrite(pinA1, HIGH);
digitalWrite(pinA2, HIGH);
}

void motorBCoast()
{
digitalWrite(pinB1, LOW);
digitalWrite(pinB2, LOW);
}

void motorBBrake()
{
digitalWrite(pinB1, HIGH);
digitalWrite(pinB2, HIGH);
}
