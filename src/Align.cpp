#include "Align.h"

void Align::globalAlignment() {
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

void Align::backtrack() {
	int i = seqA.length();
	int j = seqB.length();
	int gap = scoringMatrix->getGapOpenPenalty();

	string sA("");
	string sB("");

	while (i > 0 && j > 0) {
		if (matrix[i][j]
				== matrix[i - 1][j - 1]
						+ scoringMatrix->getScore(seqA[i - 1], seqB[j - 1])) {
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

Align::Align(string sequenceA, string sequenceB, ScoringMatrix * sM) {
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

void Align::printAlignment(string seqAName, string seqBName) {

	string diff = getDiffSeq();

	for (int i = 0; i < alignedSeqA.length(); i += LINE_BREAK) {
		printf("%s:\t %s %ld\n", seqAName.c_str(), alignedSeqA.substr(i, LINE_BREAK).c_str(),
				i + alignedSeqA.substr(i, LINE_BREAK).length());
		printf("\t %s\n", diff.substr(i, LINE_BREAK).c_str());
		printf("%s:\t %s %ld\n", seqBName.c_str(), alignedSeqB.substr(i, LINE_BREAK).c_str(),
				i + alignedSeqA.substr(i, LINE_BREAK).length());
		printf("\n");
	}
}

void Align::printMatrix() {
	printf("D =\n");
	for (int i = 0; i < seqA.length() + 1; i++) {
		for (int j = 0; j < seqB.length() + 1; j++) {
			printf("%4d ", matrix[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int Align::getScore() {
	return score;
}

string Align::getAlignedSeqA() {
	return alignedSeqA;
}

string Align::getAlignedSeqB() {
	return alignedSeqA;
}

string Align::getDiffSeq() {
	string diff;

	for (int i = 0; i < alignedSeqA.length(); i++) {
		if (alignedSeqA[i] == alignedSeqB[i])
			diff.push_back(alignedSeqA[i]);
		else
			diff.push_back(' ');
	}

	return diff;
}
