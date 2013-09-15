#include <cstdio>
#include <map>
#include <set>
#include <string>

#define LINE_SIZE 256

using namespace std;

#ifndef IMPORTER_H_
#define IMPORTER_H_

/*
 * Imports a sequence.
 */
string importSequence(char *filepath);

/*
 * Imports the family of sequences.
 */
map<string, string> importFamilies(char *filepath);

/*
 * Import the family ids.
 */
set<string> importFamilyIds(char *filepath);


#endif /* IMPORTER_H_ */
