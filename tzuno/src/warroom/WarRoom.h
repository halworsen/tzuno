#ifndef _warroom_h
#define _warroom_h

#include <Arduino.h>
#include <SoftwareSerial.h>

class WarRoom {

private:
	int rxPin;
	int txPin;

	SoftwareSerial* bt;
	String bufferedMsg;

	void msgReceived(String msg);

public:
	WarRoom(int rxPin, int txPin);
	~WarRoom();

	void setup();
	void loop();
	void sendMsg(String msg);

	String getBufferedMsg();

};

#endif