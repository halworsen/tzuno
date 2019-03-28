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
#include "src/triplesonar/TripleSonar.h"
//=========================================================

//=========================================================
// Bluetooth
//---------------------------------------------------------
#include "src/warroom/WarRoom.h"
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

// Bluetooth serial
#define RX_PIN A4
#define TX_PIN A5

#define MAX_DISTANCE  35
// Servo
//#define SERVOPIN      6//Kan ikke brukes med 3 sonarer
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


//NewServo servo;

WarRoom warroom(RX_PIN, TX_PIN);
boolean standbyMode = true;

//=================HJELPEFUNKSJONER========================
float sonarDistance(NewPing* sonar) {
  // Gjør ett ping, og beregn avstanden
  unsigned int time = sonar->ping();
  float distance = sonar->convert_cm(time);
  Serial.println(distance);
  return distance;
}

//=========================================================

//===============BLUETOOTH MELDINGSHÅNDTERING==============

void handleMsg(String msg) {
  if(msg == "stratsad") {
    strat = new SearchAndDestroy(&motors);
    warroom.sendMsg("Strategi valgt: Search and Destroy");
  } else if(msg == "stratinward") {
    //strat = new InwardsRadar(&motors, &servo);
    warroom.sendMsg("Strategi valgt: Inwards Radar");
  } else if(msg == "stratrmc") {
    strat = new InwardsRadar(&motors);
    warroom.sendMsg("Strategi valgt: Random Motion Contact");
  }
}

//=========================================================

void setup() {
  // Bluetooth
  warroom.setup();
  warroom.setCallback(&handleMsg);
  
	//init servo
	//servo.attach(SERVOPIN);
  //servo.write(90);
	
	//strats
    strat = new TripleSonar(&motors);
    //strat = new SearchAndDestroy(&motors);
    //strat = new InwardsRadar(&motors, &servo);
    Serial.begin(9600);
    randomSeed(analogRead(0));

    
    //button.waitForButton();
    Serial.println("Setup ferdig");
    warroom.sendMsg("Tzuno er klar!");
}

void loop() {
    // Start når knappen trykkes inn
    // Bluetooth kan bare brukes i standbymodus
    if(button.isPressed())
    {
      button.waitForRelease();
      standbyMode = !standbyMode;
    }
  
    // Les eventuelle bluetooth-meldinger. Det er viktig at denne kjøres hver loop!
    // Ellers kan vi miste bytes fra innkommende meldinger
    // Timing er generelt sett kritisk for bluetooth-funksjonalitet
    // Dette er også av grunnen til at vi bare tillater bruk av bluetooth før knappen trykkes inn. Resten av koden roter til timingen
    if(standbyMode)
    {
      warroom.loop();

      // Ikke kjør strategi-relatert kode før knappen trykkes inn
      return;
    }
  
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
    //Serial.println(strat->getState());
}
