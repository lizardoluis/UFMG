#include "Import.h"

string importSequence(char *filepath) {

	char line[LINE_SIZE];
	string str = "";
	FILE *file = fopen(filepath, "r");

	if (file != NULL) {
		fscanf(file, "%*s\n");
		while (fscanf(file, "%s\n", line) != EOF) {
			str += line;
		}
	} else {
		printf("file not opened");
	}

	fclose(file);
	return str;
}

map<string, string> importFamilies(char *filepath) {

	char line[LINE_SIZE];

	map < string, string > mymap;
	FILE *file = fopen(filepath, "r");

	if (file != NULL) {

		string sequence = "";
		string name = "";
		int lineRead = 0;

		while (fscanf(file, "%s\n", line) != EOF) {

			string data(line);

			if (data[0] == '>') {
				if (lineRead > 0) {
					mymap[name] = sequence;
					name = "";
					sequence = "";
				}
				name = data.substr(1, 4) + data[6];

			} else {
				sequence += data;
			}

			lineRead++;
		}

		mymap[name] = sequence;

	} else {
		printf("file not opened");
	}

	fclose(file);
	return mymap;
}

set<string> importFamilyIds(char *filepath) {

	char line[256];
	set < string > familyIds;

	FILE *file = fopen(filepath, "r");

	if (file != NULL) {
		while (fscanf(file, "%s\n", line) != EOF) {
			familyIds.insert(line);
		}
	} else {
		printf("file not opened");
	}

	fclose(file);

	return familyIds;
}

