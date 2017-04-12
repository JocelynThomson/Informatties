/**
 * @file	app.h
 * @author	Julian van Doorn
 * @brief	Receives and handles input from the app.
 */

#include "sensors.h"
#include "nav.h"

bool changing_speed = false;
bool force_stopped = false;
float stop_speed_multiplier = 1.0;

const int kMaxSizeOfMessage = 30;
const int INBOX = 5;

enum MODE {
	MANHATTAN = 0,
	BRABANT = 1
};

MODE mode = MANHATTAN;

void cycle_mode() {
	mode++;
	mode = (MODE) (mode % 2);
}

void enable_mode() {
	if (mode == MANHATTAN) {
		power = 90;
		junction_derivative = 1;
	} else if (mode == BRABANT) {
		power = 90;
		junction_derivative = 2;
	}
}

void toggle_stop_robot() {
	if (!changing_speed) {
		force_stopped = !force_stopped;
	}
}

bool waiting_for_input_destination = false;
int begin = 0;
int dest = 0;

/**
 * @brief Takes a string as input and runs the appropriate function.
 * @param msg
 */
void handle_message(string msg) {
	if (msg == "UP") {
		if (!waiting_for_input_destination) {
			enqueue_direction(FORWARD);
		} else {
			//writeDebugStreamLine("%d", edges[dest->index][NORTH]);
			dest = edges[dest][NORTH];
		}
	} else if (msg == "DOWN") {
		if (!waiting_for_input_destination) {
			enqueue_direction(TURNABOUT);
		} else {
			dest = edges[dest][SOUTH];
		}
	} else if (msg == "LEFT") {
		if (!waiting_for_input_destination) {
			enqueue_direction(LEFT);
		} else {
			dest = edges[dest][WEST];
		}
	} else if (msg == "RIGHT") {
		if (!waiting_for_input_destination) {
			enqueue_direction(RIGHT);
		} else {
			dest = edges[dest][EAST];
		}
	} else if (msg == "FIRE") {
		toggle_stop_robot();
	} else if (msg == "A") {
		empty_queue(nav_queue);
	} else if (msg == "B") {
		waiting_for_input_destination = !waiting_for_input_destination;

		if (!waiting_for_input_destination) {
			clear_nodes(nodes);
			breadth_first_search(&nodes[begin], &nodes[dest]);
			begin = dest;
		}
	} else if (msg == "C") {
		cycle_mode();
		enable_mode();
	}
}

/**
 * @brief Specialized task which incrementally increases or decreases speed.
 */
task start_stop_task() {
	while (1) {
		waitUntil(force_stopped);
		changing_speed = true;
		while (force_stopped && stop_speed_multiplier > 0) {
			stop_speed_multiplier -= 0.02;
			wait1Msec(10);
		}
		changing_speed = false;
		nullify_derivative();

		stop_speed_multiplier = 0;

		waitUntil(!force_stopped);
		changing_speed = true;
		while (!force_stopped && stop_speed_multiplier < 1) {
			stop_speed_multiplier += 0.02;
			wait1Msec(10);
		}
		changing_speed = false;
		nullify_derivative();

		stop_speed_multiplier = 1;
	}
}

/**
 * @brief Task for receiving bluetooth input from the android app.
 */
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

/**
 * @brief Initializes app_task and start_stop_task
 */
void init_app() {
	startTask(app_task);
	startTask(start_stop_task);
}
