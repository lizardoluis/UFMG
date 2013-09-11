#include "ScoringMatrix.h"
#include <algorithm>
#include <string>
#include <vector>

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
	void globalAlignment() {
		int m = seqA.length();
		int n = seqB.length();
		int gap = scoringMatrix->getGapOpenPenalty();

		for (int i = 0; i <= m; i++) {
			matrix[i][0] = gap * i;
		}
		for (int j = 0; j <= n; j++) {
			matrix[0][j] = gap * j;
		}
		for (int i = 1; i <= m; i++) {
			for (int j = 1; j <= n; j++) {

				int left = matrix[i][j - 1] + gap;
				int up = matrix[i - 1][j] + gap;
				int diag = matrix[i - 1][j - 1]
						+ scoringMatrix->getScore(seqA[i - 1], seqB[j - 1]);

//				cout << seqA[i - 1] << " " << seqB[j - 1] << endl;
//				cout << "[" << i << "," << j << "] left: " << left << " up: "
//						<< up << " diag: " << diag << endl;

				matrix[i][j] = max(max(left, up), diag);
			}
		}

		score = matrix[m][n];
	}

	//Parses the similarity matrix from back to front to design the path.
	void backtrack() {
		int i = seqA.length();
		int j = seqB.length();
		int gap = scoringMatrix->getGapOpenPenalty();

		string sA("");
		string sB("");

		while (i > 0 && j > 0) {
			if (matrix[i][j]
					== matrix[i - 1][j - 1]
							+ scoringMatrix->getScore(seqA[i - 1],
									seqB[j - 1])) {
				sA += seqA[i - 1];
				sB += seqB[j - 1];
				i--;
				j--;
				continue;
			} else if (matrix[i][j] == matrix[i][j - 1] + gap) {
				sA += "-";
				sB += seqB[j - 1];
				j--;
				continue;
			} else {
				sA += seqA[i - 1];
				sB += "-";
				i--;
				continue;
			}
		}

		alignedSeqA = string(sA.rbegin(), sA.rend());
		alignedSeqB = string(sB.rbegin(), sB.rend());
	}

public:

	Align(char* sequenceA, char* sequenceB, ScoringMatrix * sM) {
		seqA = sequenceA;
		seqB = sequenceB;
		scoringMatrix = sM;

		matrix.resize(seqA.length() + 1);
		for (int i = 0; i <= seqA.length(); ++i) {
			matrix[i].resize(seqB.length() + 1);
		}

		globalAlignment();
		backtrack();
	}

	void printScoreAndAlignments() {
		
		string diff;
		int len = 60;

		for(int i=0; i<alignedSeqA.length(); i++){
			if(alignedSeqA[i] == alignedSeqB[i])
				diff.push_back(alignedSeqA[i]);
			else
				diff.push_back(' ');
		}

		for(int i=0; i<alignedSeqA.length(); i+=len){
			printf("Sequence A:\t %s %d\n", alignedSeqA.substr(i, len).c_str(), i+alignedSeqA.substr(i, len).length());
			printf("\t\t %s\n", diff.substr(i, len).c_str());
			printf("Sequence B:\t %s %d\n", alignedSeqB.substr(i, len).c_str(), i+alignedSeqA.substr(i, len).length());
			printf("\n");
		}		



		//printf("Score: %d\n", score);
		//printf("Sequence A: %s\n", alignedSeqA.c_str());
		//printf("Sequence B: %s\n", alignedSeqB.c_str());
	}

	void printMatrix() {
		printf("D =\n");
		for (int i = 0; i < seqA.length() + 1; i++) {
			for (int j = 0; j < seqB.length() + 1; j++) {
				printf("%4d ", matrix[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}

	int getScore() {
		return score;
	}

	string getAlignedSeqA() {
		return alignedSeqA;
	}

	string getAlignedSeqB() {
		return alignedSeqA;
	}
};
