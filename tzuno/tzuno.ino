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
//=========================================================


//=========================================================
// Defines
//---------------------------------------------------------
// IR
#define LED 13
#define QTR_THRESHOLD  1900 // microseconds
#define NUM_SENSORS    6    
// Sonar
#define ECHOPIN       2 
#define TRIGGERPIN    1
#define MAX_DISTANCE  100
// Servo
#define SERVOPIN      6
//=========================================================


//=========================================================
// Deklarasjoner
//---------------------------------------------------------
Strategy* strat;

PLab_ZumoMotors motors;

Pushbutton button(ZUMO_BUTTON);

NewPing sonar(TRIGGERPIN, ECHOPIN, MAX_DISTANCE);

unsigned int sensor_values[NUM_SENSORS];
ZumoReflectanceSensorArray sensors(QTR_NO_EMITTER_PIN);

NewServo servo;
//=========================================================


void setup() {
	//init servo
	servo.attach(SERVOPIN);
	
	//strats
    strat = new SearchAndDestroy(&motors);
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
        unsigned int t = sonar.ping();
        float dist = sonar.convert_cm(t);
        strat->setSonarDistance(dist);
        Serial.println(dist);
    }

    // Strategiens loop
    strat->run();
    Serial.println(strat->getState());
}
