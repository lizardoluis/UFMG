#include <cstdio>
#include <cctype>
#include <string>
#include <iostream>

using namespace std;

class ScoringMatrix {
private:

	int matrix[20][20];
	int gapOpenPenalty;
	int gapExtendPenalty;

	/*
	 * Converts from the AminoAcid letter to the corresponding integer representation in the matrix.
	 */
	int getIndex(char c) {
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

public:

	/*
	 * Constructor.
	 */
	ScoringMatrix(){}

	ScoringMatrix(char *filepath) {
		importScoringMatrix(filepath);
	}

	/*
	 * Returns the corresponding score of the AminoAcids u and v.
	 */
	int getScore(char u, char v) {
		return (matrix[getIndex(u)][getIndex(v)]);
	}

	/*
	 * Returns the gap open penalty.
	 */
	int getGapOpenPenalty() {
		return gapOpenPenalty;
	}

	/*
	 * Returns the gap extend penalty.
	 */
	int getExtendPenalty() {
		return gapExtendPenalty;
	}

	/*
	 * Imports a scoring matrix from a text file.
	 * Format:
	 * <gap_open_penalty>;<gap_extend_penalty>
	 * <AminoAcid>;<AminoAcid>;score
	 */
	void importScoringMatrix(char *filepath) {
		char u, v;
		int score;

		FILE *file = fopen(filepath, "r");

		if (file != NULL) {

			fscanf(file, "%d;%d%*c", &gapOpenPenalty, &gapExtendPenalty);

			while (fscanf(file, "%c;%c;%d%*c", &u, &v, &score) != EOF ) {
				matrix[getIndex(u)][getIndex(v)] = score;
				matrix[getIndex(v)][getIndex(u)] = score;
			}

			fclose(file);
		}
		else{
			printf("file not opened");
		}
	}
};
