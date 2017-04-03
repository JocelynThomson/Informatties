#include "nav.h"

long nLastXmitTimeStamp = nPgmTime;
long nDeltaTime         = 0;

const int kMaxSizeOfMessage = 30;
const int INBOX = 5;

void handle_message(string msg) {
//	writeDebugStreamLine("%s", msg);

	if (msg == "UP") {

	} else if (msg == "DOWN") {
		enqueue_direction(TURNABOUT);
	} else if (msg == "LEFT") {
		enqueue_direction(LEFT);
	} else if (msg == "RIGHT") {
		enqueue_direction(RIGHT);
	}
}

task app_task() {
  TFileIOResult nBTCmdRdErrorStatus;
  int nSizeOfMessage;
  ubyte nRcvBuffer[kMaxSizeOfMessage];

  while (true) {
    nSizeOfMessage = cCmdMessageGetSize(INBOX);

    if (nSizeOfMessage > kMaxSizeOfMessage) {
    	nSizeOfMessage = kMaxSizeOfMessage;
  	}

  	if (nSizeOfMessage > 0){
  		nBTCmdRdErrorStatus = cCmdMessageRead(nRcvBuffer, nSizeOfMessage, INBOX);
  		nRcvBuffer[nSizeOfMessage] = '\0';
  		string s = "";
  		stringFromChars(s, (char *) nRcvBuffer);
  		displayCenteredBigTextLine(4, s);
  		handle_message(s);
  	}

  	wait1Msec(100);
	}
}

void init_app() {
	startTask(app_task);
}
