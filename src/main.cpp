//============================================================================
// Name        : paa-tp3.cpp
// Author      : Luis Lizardo
// Version     :
// Copyright   : 
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
using namespace std;

#define MIN0 3
#define MIN1 5

#define CHAR0 '0'
#define CHAR1 '1'
#define CHAR_ '-'

#define FALSE 0
#define TRUE 1
#define BOTH 2

int processMsgBf(string msg, int index, int count, char last) {

	for (unsigned i = index; i < msg.length(); i++) {

		if ((last == CHAR0 && count == MIN0)
				|| (last == CHAR1 && count == MIN1)) {
			return TRUE;
		}

		if (msg[i] == CHAR_) {

			int a, b;

			if (last == CHAR0) {
				a = processMsgBf(msg, i + 1, count + 1, CHAR0);
				b = processMsgBf(msg, i + 1, 1, CHAR1);

			} else {
				a = processMsgBf(msg, i + 1, count + 1, CHAR1);
				b = processMsgBf(msg, i + 1, 1, CHAR0);
			}

			if (a == TRUE && b == FALSE)
				return BOTH;
			else if (a == TRUE && b == TRUE)
				return TRUE;
			else
				return FALSE;

		} else if (msg[i] == last) {
			count++;
		} else {
			count = 1;
			last = msg[i];
		}
	}

	if ((last == CHAR0 && count == MIN0) || (last == CHAR1 && count == MIN1)) {
		return TRUE;
	}

	return FALSE;
}

int processMsgGa(string msg) {

	int count = 0;
	char last = ' ';

	for (unsigned i = 0; i < msg.length(); i++) {

		if (msg[i] == last) {
			count++;
		} else if (msg[i] == CHAR_) {
			// Verifies if is better to make the undefined like the last,
			// or to start counting again.
			if (i < msg.length() - 1 && count < 4 && msg[i + 1] != CHAR_
					&& msg[i + 1] != last) {
				last = last == CHAR0 ? CHAR1 : CHAR0;
				count = 1;
			} else {
				count++;
			}
		} else {
			last = msg[i];
			count = 1;
		}

		if ((last == CHAR0 && count == MIN0)
				|| (last == CHAR1 && count == MIN1)) {
			return TRUE;
		}
	}
	return FALSE;
}

int processMsgPd(string msg){

}

int main() {

	int numInstances;

	cin >> numInstances;

	for (int i = 0; i < numInstances; i++) {
		string msg;
		cin >> msg;

		cout << processMsgBf(msg, 0, 0, ' ') << " "
				<< processMsgBf(msg, 0, 0, ' ') << endl;
	}

	return 0;
}
