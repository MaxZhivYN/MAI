#include "ZhivArchiver.h"

#include <fstream>
#include <iostream>

using namespace std;


int main(int argc, char const *argv[]) {
	if (argc != 4) {
		cout << "write: ./zzip key fileIN fileOUT" << endl;
		cout << "keys:" << endl; 
		cout << "-z (zip fileIN to fileOUT)" << endl;
		cout << "-u (unzip fileIN to fileOUT)" << endl;

		return 0;
	}

	ZhivArchiver zhivArchiver;
	ofstream out;
	ifstream in;

	string command = argv[1];
	if (command == "-z") {
		in.open(argv[2], ifstream::in);
		out.open(argv[3], ifstream::binary | ifstream::out);

		zhivArchiver.zZip(in, out);
	} else if (command == "-u") {
		in.open(argv[2], ifstream::binary | ifstream::in);
		out.open(argv[3], ifstream::out);
		
		zhivArchiver.zUnZip(in, out);
	} else {
		cout << "Wrong key." << endl;
	}

	return 0;
}
