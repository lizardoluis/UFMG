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

int bruteForce(string &msg, unsigned i, int c0, int c1) {

	while(true){

		// stop conditions
		if (c0 == 3 || c1 == 5)
			return TRUE;
		if (i == msg.length())
			return FALSE;

		if (msg[i] == '0') {
			//bruteForce(msg, i + 1, c0 + 1, 0);
			c0++;
			i++;
			c1 = 0;
		}
		else if (msg[i] == '1') {
			//bruteForce(msg, i + 1, 0, c1 + 1);
			c1++;
			i++;
			c0 = 0;
		}
		else {
			int r0 = bruteForce(msg, i + 1, c0 + 1, 0);
			int r1 = bruteForce(msg, i + 1, 0, c1 + 1);

			if (r0 != r1)
				return BOTH;
			else
				return r0;
		}
	}
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

int processMsgPdTD(string msg) {

	int table[msg.length()][5][1];

	for (int i = 0; i < msg.length(); i++)
		for (int j = 0; j < 5; j++)
			for (int k = 0; k < 5; k++)
				table[i][j][k] = -1;

	// stop conditions
	if (c0 == 3 || c1 == 5)
		return TRUE;
	if (i == msg.length())
		return FALSE;

	if (msg[i] == '0') {
		processMsgPdTD(msg, i + 1, c0 + 1, 0);
	}
	else if (msg[i] == '1') {
		processMsgPdTD(msg, i + 1, 0, c1 + 1);
	}
	else {
		int r0 = processMsgPdTD(msg, i + 1, c0 + 1, 0);
		int r1 = processMsgPdTD(msg, i + 1, 0, c1 + 1);

		if (r0 != r1)
			return BOTH;
		else
			return r0;
	}
}

int main() {

	int numInstances;

	cin >> numInstances;

	for (int i = 0; i < numInstances; i++) {
		string msg;
		cin >> msg;

		cout << " "
				<< bruteForce(msg, 0, 0, 0) << endl;
	}

	return 0;
}
