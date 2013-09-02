#include "ScoringMatrix.h"
#include "Sequence.h"

class Align {
private:

	int max(int Insert, int Delete, int Match) {

		if (Insert >= Delete && Insert >= Match) {
			return Insert;
		} else if (Delete > Match) {
			return Delete;
		} else {
			return Match;
		}
	}

public:

	int globalAlignment(Sequence query, Sequence subject,
			ScoringMatrix scoringMatrix) {
		int m = query.size();
		int n = subject.size();
		int matrix[m + 1][n + 1];
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
						+ scoringMatrix.getScore(query.getAminoAcid(i - 1),
								subject.getAminoAcid(j - 1));

				matrix[i][j] = max(Insert, Delete, Match);
			}
		}

		return matrix[m][n];
	}
};
