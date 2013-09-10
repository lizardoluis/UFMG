//#include "ScoringMatrix.h"
#include "Align.h"
#include <iostream>

using namespace std;

int main(){

	char filepath[] = "data/ScoringMatrix.txt";
	ScoringMatrix sm(filepath);

	char seqA[] = "ACGTC";
	char seqB[] = "AGTC";

	Align align(seqB, seqA, &sm);

	align.printMatrix();
	align.printScoreAndAlignments();

	return 0;
}
