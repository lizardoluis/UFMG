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

    map<int, map<string, int> > statistic;

	Align align(YPIA, dTIM, &sm);
    map<int, int> diff = align.getDiff();
	//align.printAlignment("2ypia", "dTIM");
    //align.printDiff();

    string aminA, aminB;

	//cout << "----" << endl << "----" << endl << endl;
    cout << familyIds.size() << endl << endl;

	for (set<string>::iterator it = familyIds.begin(); it != familyIds.end(); ++it) {
		Align align2(families[*it], dTIM, &sm);
        map<int, int> diff2 = align2.getDiff();
		//align2.printAlignment("2YPIA", *it);
		//cout << "----" << endl << endl;

        for (map<int, int>::iterator it = diff.begin(); it != diff.end(); it++) {
            if (diff2[it->first] == DEL || diff2[it->first] == ADD || diff2[it->first] == MUT) {
                aminA = align2.getAlignedSeqA()[it->first];
                aminB = align2.getAlignedSeqB()[it->first];
                statistic[it->first][aminA + aminB] += 1;
            }
        }
	}

    for (map<int, map<string, int> >::iterator it = statistic.begin(); it != statistic.end(); it++) {
        cout << it->first << ": ";
        for (map<string, int>::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            cout << it2->first << "(" << it2->second << ") ";
        }
        cout << endl;
    }

	return 0;
}
