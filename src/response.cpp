/*
 * response.cpp
 *
 *  Created on: Nov 15, 2014
 *      Author: lizardo
 */

#include "response.h"

#include <iostream>

using namespace std;

void printResponse(Response r) {
	switch (r) {
	case TRUE:
		cout << "true\n";
		break;
	case FALSE:
		cout << "false\n";
		break;
	case BOTH:
		cout << "both\n";
		break;
	}
}
