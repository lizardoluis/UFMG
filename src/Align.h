#include "ScoringMatrix.h"
#include <algorithm>
#include <string>
#include <vector>

#define LINE_BREAK 80

using namespace std;

class Align {
private:
	//Sequences to be aligned	
	string seqA;
	string seqB;

	//Scoring matrix
	ScoringMatrix *scoringMatrix;

	//Similarity matrix
	vector<vector<int> > matrix;

	//Alignment score
	int score;

	//Aligned sequences
	string alignedSeqA;
	string alignedSeqB;

	//Aligns two sequences
	void globalAlignment();

	//Parses the similarity matrix from back to front to design the path.
	void backtrack();

public:

	/*
	 * Constructor;
	 */
	Align(string sequenceA, string sequenceB, ScoringMatrix * sM);

	/*
	 * Prints the score and alignments;
	 */
	void printAlignment(string seqAName, string seqBName);


	/*
	 * Prints the similarity matrix.
	 */
	void printMatrix();

	/*
	 * Returns the score of the alignment.
	 */
	int getScore();

	/*
	 * Returns the aligned sequence A.
	 */
	string getAlignedSeqA();

	/*
	 * Returns the aligned sequence B.
	 */
	string getAlignedSeqB();

	/*
	 * Returns a string that is the difference between the aligned sequences.
	 */
	string getDiffSeq();
};
