#include "WarRoom.h"
#include <SoftwareSerial.h>

WarRoom::WarRoom(int rxPin, int txPin) {
	this->rxPin = rxPin;
	this->txPin = txPin;
}

WarRoom::~WarRoom() {

}

void WarRoom::setup() {
	bt = new SoftwareSerial(rxPin, txPin);
	bt->begin(9600);
}

void WarRoom::loop() {
	if(!bt->available()) {
		return;
	}

	char data = bt->read();

	// Messages start with < and end with >. Anything in between is the actual message
	if(data == '<') {
		bufferedMsg = "";
	} else if(data == '>') {
		// Send an acknowledgement back
		sendMsg("OK: " + bufferedMsg);

		msgReceived(bufferedMsg);
	} else {
		bufferedMsg += data;
	}
}

void WarRoom::sendMsg(String msg) {
	bt->println("<" + msg + ">");
}

void WarRoom::msgReceived(String msg) {
	Serial.println("MSG received: " + msg);
}

String WarRoom::getBufferedMsg() {
	return bufferedMsg;
}
