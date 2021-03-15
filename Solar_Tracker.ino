#include <Servo.h>

#define DBG_VERBOSE 1

// motors 
Servo xServo;
const unsigned int xServoPin = 2, xControllerPin = A0;
unsigned int xCurrentAngle = 90;

Servo yServo;
const unsigned int yServoPin = 3, yControllerPin = A0;
unsigned int yCurrentAngle = 90;

// power collection and analysis variables
const unsigned int photoresistorPin = A1;
const unsigned int solarPanelPin = A2;

// .text

void setup()
{
	Serial.begin(9600);

	// setup the motors
	xServo.attach(xServoPin);
	xServo.write(xCurrentAngle);

	yServo.attach(yServoPin);
	yServo.write(yCurrentAngle);
}

void updateMotor(const unsigned int controllerPin, Servo& servo, unsigned int& currentAngle)
{

	// read the adc code from the potentiometer
	// converting it to an angle from 0 -> 180
	float newAngle = analogRead(controllerPin);	// get the voltage, on 5v 0 - 1023 scale
	newAngle /= 1023;				// convert that voltage into a ratio
	newAngle *= 180;				// convert that ratio into an angle

#if DBG_VERBOSE
	Serial.print("New Angle: ");
	Serial.print(newAngle);
	Serial.print("\t");
#endif

	// update the servo, if required
	if(newAngle != currentAngle)
	{
		servo.write(newAngle);
		currentAngle = newAngle;
		delay(200);
	}
}

void loop() 
{
#if DBG_VERBOSE
	// photoresistor readings
	Serial.print("Photoresistor: ");
	Serial.print(analogRead(photoresistorPin));
	Serial.print("\t");

	// Solar Panel ADC reading
	Serial.print("Solar Panel: ");
	Serial.print(analogRead(solarPanelPin));
	Serial.print("\t");

	// Motor Positioning
	Serial.print("Motors x  y: ");
	Serial.print(xCurrentAngle);
	Serial.print(" - ");
	Serial.print(yCurrentAngle);
	Serial.print("\t");
#endif

	updateMotor(xControllerPin, xServo, xCurrentAngle);
	updateMotor(yControllerPin, yServo, yCurrentAngle);

#if DBG_VERBOSE
	Serial.print("\n");
#endif
}
