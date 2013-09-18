#include "Align.h"
#include "Import.h"

#include <iostream>
#include <map>
#include <string>
#include <set>

using namespace std;

void initGroups(map<char, int> *groups) {
    #define PPE 1
    #define PNE 2
    #define PNL 3
    #define NPA 4
    #define NPR 5
    #define CRY 6

    groups->insert(pair<char, int>('H', PPE));
    groups->insert(pair<char, int>('K', PPE));
    groups->insert(pair<char, int>('R', PPE));
    groups->insert(pair<char, int>('D', PNE));
    groups->insert(pair<char, int>('E', PNE));
    groups->insert(pair<char, int>('N', PNL));
    groups->insert(pair<char, int>('Q', PNL));
    groups->insert(pair<char, int>('S', PNL));
    groups->insert(pair<char, int>('T', PNL));
    groups->insert(pair<char, int>('A', NPA));
    groups->insert(pair<char, int>('G', NPA));
    groups->insert(pair<char, int>('I', NPA));
    groups->insert(pair<char, int>('L', NPA));
    groups->insert(pair<char, int>('M', NPA));
    groups->insert(pair<char, int>('V', NPA));
    groups->insert(pair<char, int>('F', NPR));
    groups->insert(pair<char, int>('P', NPR));
    groups->insert(pair<char, int>('W', NPR));
    groups->insert(pair<char, int>('Y', NPR));
    groups->insert(pair<char, int>('C', CRY));
}

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
    map<char, int> aminoGroups;

    initGroups(&aminoGroups);

	Align align(YPIA, dTIM, &sm);
    map<int, int> diff = align.getDiff();
	//align.printAlignment("2ypia", "dTIM");
    //align.printDiff();

    string aminA, aminB, aminC, aminD;

	//cout << "----" << endl << "----" << endl << endl;
    //cout << familyIds.size() << endl << endl;

	for (set<string>::iterator it = familyIds.begin(); it != familyIds.end(); ++it) {
		Align align2(YPIA, families[*it], &sm);
        map<int, int> diff2 = align2.getDiff();
		//align2.printAlignment("2YPIA", *it);
        //align2.printDiff();
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

    cout << "----" << endl << endl;
    int total, count;

    for (map<int, int>::iterator it = diff.begin(); it != diff.end(); it++) {
        total = count = 0;
        aminA = align.getAlignedSeqA()[it->first];
        aminB = align.getAlignedSeqB()[it->first];

        for (map<string, int>::iterator it2 = statistic[it->first].begin(); it2 != statistic[it->first].end(); it2++) {
            total += it2->second;

            if (aminA + aminB == it2->first) {
                count = it2->second;
            }
        }

        cout << aminA + aminB << " " << count << "/";
        printf("%d = %.2f %%\n", total, (float)count*100/total);
    }

	return 0;
}
