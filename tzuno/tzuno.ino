//=========================================================
//                     Sun Tzuno                           
//                    -----------                          
//                        av                               
//            Andreas                                      
//            Andreas                                      
//            Mats                                         
//            Markus                                       
//            Martin                                       
//                                                         
//                til Zumokonkurranse                      
//                  PLab, vår 2019                         
//=========================================================


//=========================================================
// Inkluderte biblioteker
//---------------------------------------------------------
//  #include <ZumoShield.h>
#include <PLab_ZumoMotors.h>
#include <QTRSensors.h>                   //--------------------------
#include <Pushbutton.h>                   //  Inneholdt i ZumoShield.h
#include <ZumoReflectanceSensorArray.h>   //--------------------------
#include <NewPing.h>
#include <Wire.h> //Er kanskje relevant for border detection
#include <NewServo.h>
//=========================================================


//=========================================================
// Strategier
//---------------------------------------------------------
#include "src/aggressiveradar/AggressiveRadar.h"
#include "src/alertpassive/AlertPassive.h"
#include "src/randommotioncontact/RandomMotionContact.h"
#include "src/searchanddestroy/SearchAndDestroy.h"
#include "src/inwardsradar/InwardsRadar.h"
//=========================================================


//=========================================================
// Defines
//---------------------------------------------------------
// IR
#define LED 13
#define QTR_THRESHOLD  1900 // microseconds
#define NUM_SENSORS    6    
// Sonar
const int R_ECHOPIN = 0;
const int R_TRIGGERPIN = 6;

const int B_ECHOPIN = 2;
const int B_TRIGGERPIN = 1;

const int L_ECHOPIN = 3;
const int L_TRIGGERPIN = 13;

#define MAX_DISTANCE  35
// Servo
#define SERVOPIN      6
//=========================================================


//=========================================================
// Deklarasjoner
//---------------------------------------------------------
Strategy* strat;

PLab_ZumoMotors motors;

Pushbutton button(ZUMO_BUTTON);

NewPing r_sonar(R_TRIGGERPIN, R_ECHOPIN, MAX_DISTANCE);
NewPing b_sonar(B_TRIGGERPIN, B_ECHOPIN, MAX_DISTANCE);
NewPing l_sonar(L_TRIGGERPIN, L_ECHOPIN, MAX_DISTANCE);

unsigned int sensor_values[NUM_SENSORS];
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);

NewServo servo;
//=================HJELPEFUNKSJONER========================
float sonarDistance(NewPing* sonar) {
  // Gjør ett ping, og beregn avstanden
  unsigned int time = sonar->ping();
  float distance = sonar->convert_cm(time);
  //Serial.println(distance);
  return distance;
}

//=========================================================


void setup() {
	//init servo
	servo.attach(SERVOPIN);
  servo.write(90);
	
	//strats
    strat = new SearchAndDestroy(&motors);
    //strat = new InwardsRadar(&motors, &servo);
    Serial.begin(9600);
    randomSeed(analogRead(0));
//
//    Serial.print(F(
//      "Angi strategi:\n" +
//      "0: Search and Destroy\n" +
//      "1: Random Motion Contact\n"
//      );
//
//    char c = Serial.read();
//
//    if (c = '0')
//    {
//      strat = new SearchAndDestroy(&motors);
//    }
//    else if (c = '1')
//    {
//      strat = new RandomMotionContact(&motors);
//    }
    
    button.waitForButton();
}


void loop() {
    // Infrarød sjekk på bane
    // Borderdetection
  	{
    		sensors.read(sensor_values);
    		bool r =sensor_values[5] < QTR_THRESHOLD;
    		bool l =sensor_values[0] < QTR_THRESHOLD;
    		strat->setBorderRight(r);
    		strat->setBorderLeft(l);
  	}
   
    // Sonarmåling
    {
		strat->setSonarDistanceLeft(sonarDistance(&l_sonar));
		strat->setSonarDistanceRight(sonarDistance(&r_sonar));
		strat->setSonarDistanceBack(sonarDistance(&b_sonar));
    }

    // Strategiens loop
    strat->run();
    Serial.println(strat->getState());
}
