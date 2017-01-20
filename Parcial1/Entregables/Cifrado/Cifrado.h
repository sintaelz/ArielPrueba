#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class Cifrado
{
public:
	Cifrado() {}
	~Cifrado() {}
	int decrypt(string word);
};

int Cifrado::decrypt(string word) {
	int offset = 0;
	string tempWord = word;
	string line;
	ifstream dictionary ("diccionario.txt");
	if (dictionary.is_open()) {
		// Offset the input word with offset
		while (offset < 26) {
			// offset word
			for (int i = 0; i < word.length(); i++) {
				tempWord[i] = (((word[i]+offset)-97)%26)+97;
			}
			cout << "word: " << word << " offset: " << offset << " offseted: " << tempWord << endl;
			// check if offseted
			while (getline(dictionary, line)) {
				if (!tempWord.compare(line)) {
					dictionary.close();
					return offset;
				}
			}
			// increase offset
			offset++;
			// return the dictionary iterator back to beginning of file
			dictionary.clear();
			dictionary.seekg(0, ios::beg);
		}
		dictionary.close();
		return -1;
	} else {
		// there was a problem openning file
		cout << "Could not open dictionary" << endl;
		return -1;
	}
}
