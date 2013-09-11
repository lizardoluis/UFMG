#include <cstdio>
#include <string>

using namespace std;

class Sequence {
private:
        string sequence, name;

public:
        Sequence(char *filepath) {
            importSequence(filepath);
        }

        unsigned size(){
                return (unsigned) sequence.length();
        }

        void importSequence(char *filepath) {
            char line[30];

            FILE *file = fopen(filepath, "r");

            if (file != NULL) {
                fscanf(file, ">%s\n", line);

                if (strcmp(line, "2YPIA") == 0 || strcmp(line, "dTIM") == 0) {
                    printf("sequence\n");
                } else {
                    printf("family\n");
                }
            }
        }
};
