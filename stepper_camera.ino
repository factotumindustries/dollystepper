#include <Stepper.h>

const int stepsPerRevolution = 64;  // change this to fit the number of steps per revolution
const float driveRadius = 10;
const float wheelRadius = 25;
const float outputStep = (2 * PI * driveRadius) / stepsPerRevolution * (driveRadius / wheelRadius);

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(stepsPerRevolution, 8, 9, 10, 11);

const int buttonPin = 7;

int stepCount = 0;  // number of steps the motor has taken
int travelLength = 2000;  // how far in mm
int travelTime = 600;

int totalSteps = int( travelLength  / outputStep);
int myDelay = (travelTime * 1000.0) / totalSteps;

int buttonState = 0; 

unsigned long previousMillis = 0;

String myDisplay = "Travel length = ";

void setup() {
	pinMode(buttonPin, INPUT_PULLUP);
	Serial.begin(9600);
	myDisplay = String (myDisplay + String(travelLength, DEC) + ", Travel time = " + String(travelTime, DEC));
	myDisplay = String (myDisplay + " Total steps = " + String(totalSteps, DEC) + " Total time = " + String(myDelay, 4));
	Serial.println(myDisplay);
	
}

void loop() {
	unsigned long currentMillis = millis();
	buttonState = digitalRead(buttonPin);
	if ((currentMillis - previousMillis >= myDelay) && (buttonState == LOW)) {
		previousMillis = currentMillis;
		Serial.print(".");
		myStepper.step(1);
	} //end if
}

