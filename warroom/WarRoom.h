#ifndef _warroom_h
#define _warroom_h

#include <Arduino.h>
#include <SoftwareSerial.h>

class WarRoom {

private:
	int rxPin;
	int txPin;

	SoftwareSerial bt;
	String bufferedMsg;

	void*(String msg) callback;
	bool hasCallback();

public:
	WarRoom(int rxPin, int txPin);
	~WarRoom();

	void setCallback(void*(String msg) func);

	void setup();
	void loop();
	void sendMsg(String msg);

	String getBufferedMessage();

}

#endif