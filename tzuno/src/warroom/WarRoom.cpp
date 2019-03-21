#include "WarRoom.h"
#include <SoftwareSerial.h>

WarRoom::WarRoom(int rxPin, int txPin) {
	this.rxPin = rxPin;
	this.txPin = txPin;
}

WarRoom::~WarRoom() {

}

bool WarRoom::hasCallback() {
	return (callback == null);
}

void WarRoom::setCallback(void*(String) func) {
	callback = func;
}

String WarRoom::getBufferedMsg() {
	return bufferedMsg;
}

void WarRoom::sendMsg(String msg) {
	bt.println("<" + msg + ">")
}

void WarRoom::setup() {
	bt = new SoftwareSerial(rxPin, txPin);
}

void WarRoom::loop() {
	if(bt.available()) {
		data = Bluetooth.read();

		// Message is starting/ending
		if(data == '<') {
		  bufferedMsg = "";
		} else if(data == '>') {
		  // Send an acknowledgement back
		  sendMsg("OK: " + dataStr);

		  if(hasCallback()) {
		  	&callback(bufferedMsg);
		  }
		} else{
		  dataStr += data;
		}
	}
}