#include <vector>

using namespace std;

class Sequence {
private:
	vector <char> sequence;

public:
	Sequence();

	char getAminoAcid(int p){
		return sequence[p];
	}

	unsigned size(){
		return (unsigned) sequence.size();
	}
};
