#ifndef _warroom_h
#define _warroom_h

#include <Arduino.h>
#include <SoftwareSerial.h>

class WarRoom {

	// En funksjon med returtype void og en String-parameter
	typedef void (*CallbackFunction)(String);

private:
	int rxPin;
	int txPin;

	CallbackFunction callback;

	SoftwareSerial* bt;
	String bufferedMsg;

	void msgReceived(String msg);

public:
	WarRoom(int rxPin, int txPin);
	~WarRoom();

	void setup();
	void loop();
	void sendMsg(String msg);

	void setCallback(CallbackFunction func);
	bool hasCallback();

	String getBufferedMsg();

};

#endif