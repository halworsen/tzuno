#include <Wire.h>
#include <ZumoShield.h>

#define LED 13

// this might need to be tuned for different lighting conditions, surfaces, etc.
#define QTR_THRESHOLD  90 // microseconds
//WARNING!!! Det her e den aller viktigste verdien
//med verdi 90 kjøre den på bordet og alt mørkere og stoppe på hvitt ark
//grå underlag(som baksiden av skrivebøker) kan man ha verdi 100, kanskje 110
// jo større verdi man kan ha, jo mer sensitiv for kanten blir den :))

// these might need to be tuned for different motor types
#define REVERSE_SPEED     100 // 0 is stopped, 400 is full speed
#define TURN_SPEED        100
#define FORWARD_SPEED     100
#define REVERSE_DURATION  700 // ms
#define TURN_DURATION     200 // ms

ZumoBuzzer buzzer;
ZumoMotors motors;
Pushbutton button(ZUMO_BUTTON); // pushbutton on pin 12

#define NUM_SENSORS 6
unsigned int sensor_values[NUM_SENSORS];

ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);

void waitForButtonAndCountDown()
{
  digitalWrite(LED, HIGH);
  button.waitForButton();
  delay(1000);
}

void setup()
{
  // uncomment if necessary to correct motor directions
  //motors.flipLeftMotor(true);
  //motors.flipRightMotor(true);

  pinMode(LED, HIGH);
  Serial.begin(9600);
  waitForButtonAndCountDown();
  
}

void loop()
{
  if (button.isPressed())
  {
    // if button is pressed, stop and wait for another press to go again
    motors.setSpeeds(0, 0);
    button.waitForRelease();
    waitForButtonAndCountDown();
  }


  sensors.read(sensor_values);

  if (sensor_values[0] < QTR_THRESHOLD)
  {
    // if leftmost sensor detects line, reverse and turn to the right
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(TURN_SPEED, -TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  else if (sensor_values[5] < QTR_THRESHOLD)
  {
    // if rightmost sensor detects line, reverse and turn to the left
    motors.setSpeeds(-REVERSE_SPEED, -REVERSE_SPEED);
    delay(REVERSE_DURATION);
    motors.setSpeeds(-TURN_SPEED, TURN_SPEED);
    delay(TURN_DURATION);
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  else
  {
    // otherwise, go straight
    motors.setSpeeds(FORWARD_SPEED, FORWARD_SPEED);
  }
  Serial.print(sensor_values[0]);
  Serial.print("    ");
  Serial.print(sensor_values[5]);
  Serial.println();
  
}
