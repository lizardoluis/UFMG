#include "Align.h"
#include "Import.h"

#include <iostream>
#include <map>
#include <string>
#include <set>

using namespace std;

int main() {

	char smFilepath[] = "data/ScoringMatrix.txt";
	ScoringMatrix sm(smFilepath);

	char idsFilePath[] = "data/idsFamily.txt";
	set < string > familyIds = importFamilyIds(idsFilePath);

	char dtimFilePath[] = "data/dTIM.fasta";
	string dTIM = importSequence(dtimFilePath);

	char ypiaFilePath[] = "data/2YPIA.fasta";
	string YPIA = importSequence(ypiaFilePath);

	char fFilePath[] = "data/family.fasta";
	map < string, string > families = importFamilies(fFilePath);


	Align align(dTIM, YPIA, &sm);
	align.printAlignment("dTIM", "2ypia");

	cout << "----" << endl << "----" << endl << endl;

	for (set<string>::iterator it = familyIds.begin(); it != familyIds.end(); ++it) {
		Align align2(YPIA, families[*it], &sm);
		align.printAlignment("2YPIA", *it);
		cout << "----" << endl << endl;
	}

	return 0;
}
