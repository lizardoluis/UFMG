#include "ScoringMatrix.h"

int ScoringMatrix::getIndex(char c) {
	switch (toupper(c)) {
	case 'A':
		return 0;
	case 'R':
		return 1;
	case 'N':
		return 2;
	case 'D':
		return 3;
	case 'C':
		return 4;
	case 'Q':
		return 5;
	case 'E':
		return 6;
	case 'G':
		return 7;
	case 'H':
		return 8;
	case 'I':
		return 9;
	case 'L':
		return 10;
	case 'K':
		return 11;
	case 'M':
		return 12;
	case 'F':
		return 13;
	case 'P':
		return 14;
	case 'S':
		return 15;
	case 'T':
		return 16;
	case 'W':
		return 17;
	case 'Y':
		return 18;
	case 'V':
		return 19;
	default:
		return -1;
	}
}

ScoringMatrix::ScoringMatrix(char *filepath) {
	importScoringMatrix(filepath);
}

int ScoringMatrix::getScore(char u, char v) {
	return (matrix[getIndex(u)][getIndex(v)]);
}

int ScoringMatrix::getGapOpenPenalty() {
	return gapOpenPenalty;
}

int ScoringMatrix::getExtendPenalty() {
	return gapExtendPenalty;
}

void ScoringMatrix::importScoringMatrix(char *filepath) {
	char u, v;
	int score;

	FILE *file = fopen(filepath, "r");

	if (file != NULL) {

		fscanf(file, "%d;%d%*c", &gapOpenPenalty, &gapExtendPenalty);

		while (fscanf(file, "%c;%c;%d%*c", &u, &v, &score) != EOF) {
			matrix[getIndex(u)][getIndex(v)] = score;
			matrix[getIndex(v)][getIndex(u)] = score;
		}

		fclose(file);
	} else {
		printf("file not opened");
	}
}

