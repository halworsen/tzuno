#include "WarRoom.h"
#include <SoftwareSerial.h>

WarRoom::WarRoom(int rxPin, int txPin) {
	this->rxPin = rxPin;
	this->txPin = txPin;
}

WarRoom::~WarRoom() {

}

void WarRoom::setup() {
	this->bt = new SoftwareSerial(rxPin, txPin);
}

void WarRoom::loop() {
	if(bt->available()) {
		char data = bt->read();

		// Message is starting/ending
		if(data == '<') {
		  bufferedMsg = "";
		} else if(data == '>') {
		  // Send an acknowledgement back
		  sendMsg("OK: " + bufferedMsg);

		  msgReceived(bufferedMsg);
		} else{
		  bufferedMsg += data;
		}
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
