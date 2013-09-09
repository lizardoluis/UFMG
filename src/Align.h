#include "ScoringMatrix.h"
#include <algorithm>
#include <string>

//https://code.google.com/p/himmele/source/browse/trunk/Bioinformatics/NeedlemanWunsch/src/NeedlemanWunsch.java

using namespace std;

class Align {
private:
	//Sequences to be aligned	
	string seqA;
	string seqB;

	//Scoring matrix
	ScoringMatrix scoringMatrix;

	//Similarity matrix
	int **matrix;

	//Alignment score
	int score;

	//Aligned sequences
	string alignedSeqA;
	string alignedSeqB;
	
public:

	Align(char* sequenceA, char* sequenceB, ScoringMatrix sM) {
		seqA = sequenceA;
		seqB = sequenceB;
		scoringMatrix = sM;

		globalAlignment();
		backtrack();
	}

	void globalAlignment() {
		int m = seqA.length();
                int n = seqB.length();
		int gap = scoringMatrix.getGapOpenPenalty();

		for (int i = 0; i < m; i++) {
			matrix[i][0] = i;
		}
		for (int j = 0; j < n; j++) {
			matrix[0][j] = j;
		}
		for (int i = 0; i < m; i++) {
			for (int j = 0; j < n; j++) {

				int Insert = matrix[i][j - 1] + gap;
				int Delete = matrix[i - 1][j] + gap;
				int Match = matrix[i - 1][j - 1]
						+ scoringMatrix.getScore(seqA[i - 1], 
								seqB[j - 1]);

				matrix[i][j] = max(max(Insert, Delete), Match);
			}
		}

		score = matrix[m-1][n-1];
	}

	void backtrack() {
		int i = seqA.length();
                int j = seqB.length();

		string sA ("");
		string sB ("");
          
                while (i > 0 && j > 0) {                        
                        if (matrix[i][j] == matrix[i-1][j-1] + scoringMatrix.getScore(seqA[i], seqB[j])) {                          
                                sA += seqA[i-1];
                                sB += seqB[j-1];
                                i--;
                                j--;                            
                                continue;
                        } else if (matrix[i][j] == matrix[i][j-1] - 1) {
                                sA += "-";
                                sB += seqB[j-1];
                                j--;
                                continue;
                        } else {
                                sA += seqA[i-1];
                                sB += "-";
                                i--;
                                continue;
                        }
                }

                alignedSeqA = string (sA.rbegin(), sA.rend());
                alignedSeqB = string (sB.rbegin(), sB.rend());
	}

	void printScoreAndAlignments() {
                printf("Score: %d\n", score);
                printf("Sequence A: %s\n", alignedSeqA.c_str());
                printf("Sequence B: %s\n", alignedSeqB.c_str());
        }
};
