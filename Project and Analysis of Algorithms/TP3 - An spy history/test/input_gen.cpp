/*
 * input_gen.cpp
 *
 *  Created on: Nov 17, 2014
 *      Author: lizardo
 */

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <set>

using namespace std;

string gera4(int size){
	string msg;

	for(int i=0;i<size;i++){
		double r = rand() % 2;

		if(r == 0){
			msg += '0';
		}
		else {
			msg += '1';
		}
	}

	return msg;
}

void gera(int size){
	string msg;

	for(int i=0;i<size;i++){
		double r = rand() % 3;

		if(r == 0){
			msg += '0';
		}else if(r == 1){
			msg += '1';
		}else{
			msg += '-';
		}
	}

	cout << msg << endl;
}

void gera2(int size, char c){
	string msg;

	for(int i=0;i<size;i++){
		msg += c;
	}

	cout << msg << endl;
}

void gera3(int size, int num){

	set<int> myset;

	string msg = gera4(size);
	set<int>::iterator it;

	for(int i=0; i<num; i++){

		int r;
		do{
			r = rand() % size;
			it=myset.find(r);
		}while(it != myset.end());

		myset.insert(r);
		msg[r] = '-';

	}


	cout << msg << endl;
}

int main() {

//	int msgSize = 10;
	int numMsg = 100;

//	for(int i=5; i<=100; i+=5){
//
//		string msg;
//
//		for(int j=0; j<numMsg; j++)
//			gera2(int size, ');
//	}

	for(int i=5; i<=50; i+=5)
		for(int j=0; j<numMsg; j++)
			gera3(100, i);

	return 0;
}

