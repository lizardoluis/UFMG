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
	int getIndex(char c);

public:

	/*
	 * Constructor.
	 */
	ScoringMatrix(char *filepath);

	/*
	 * Returns the corresponding score of the AminoAcids u and v.
	 */
	int getScore(char u, char v);

	/*
	 * Returns the gap open penalty.
	 */
	int getGapOpenPenalty();

	/*
	 * Returns the gap extend penalty.
	 */
	int getExtendPenalty();

	/*
	 * Imports a scoring matrix from a text file.
	 * Format:
	 * <gap_open_penalty>;<gap_extend_penalty>
	 * <AminoAcid>;<AminoAcid>;score
	 */
	void importScoringMatrix(char *filepath);
};
