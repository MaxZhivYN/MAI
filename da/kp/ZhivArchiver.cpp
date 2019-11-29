#include "ZhivArchiver.h"

#include <bitset>

void ZhivArchiver::zZip(ifstream& in, ofstream& out) {
	string str, alph;
	char symbol;
	int bwtCount = 0;

	while (true) {
		if (!str.empty()) str.clear();

		int lbufferSeize = -1;
		while (++lbufferSeize < bufferSize && (symbol = in.get()) != EOF) {
			str.push_back(symbol);
		}
//bhbh

		if (str.empty()) return;

		bwt.encriptBWT(str, bwtCount);		//	O(H*logH)
		//cout << str << endl;
		mtf.encriptMTF(str, alph);		//	O(H*HAlph)
		//cout << alph << " " << str << endl;
		rle.encriptRLE(str);		//	O(H)	//	H -> R
		//cout << str << endl;
		huffman.encoding(str);		//	O(N)	//	N -> H	//	H >= N
		//cout << str << endl;

		out.write((char*)&bwtCount, sizeof(bwtCount));
		myFStream.writeStr(alph, out);
		myFStream.writeHStr(str, out);
		huffman.printHTree(out);	//	O(NAlph)

		if (symbol == EOF) return;
	}
}

void ZhivArchiver::zUnZip(ifstream& in, ofstream& out) {
	string str, alph;
	int bwtCount;

	while (true) {
		if (!in.read((char*)&bwtCount, sizeof(bwtCount))) break;
		myFStream.readStr(alph, in);
		myFStream.readHStr(str, in);
		huffman.scanHTree(in);	//	O(NAlph)


		huffman.decoding(str);	//	O(H)
		//cout << str << endl;
		rle.decriptRLE(str);	//	O(H)
		//cout << str << endl;
		mtf.decriptMTF(str, alph);		//	O(H*HAlph)
		//cout << alph << " " << str << endl;
		bwt.decriptBWT(str, bwtCount);	//	O(H)
		//cout << str << endl;

		out << str;
	}
}
/*

-z
xogmsn coolitgoh  a
 acghilmnostx 1210591111686011111294127012
11#21#11#01#51#91#14#61#81#61#01#15#21#91#41#11#21#71#01#11#21#
0011101101100111000011101010111001001101010011100111011100110101110011101110000110101011110110111001001110100011001110110111001100011100001100111011011

-u
0011101101100111000011101010111001001101010011100111011100110101110011101110000110101011110110111001001110100011001110110111001100011100001100111011011
11#21#11#01#51#91#14#61#81#61#01#15#21#91#41#11#21#71#01#11#21#
1210591111686011111294127012
 acghilmnostx acaaioioiohm  m m mhnonhcchn
hhhhhhhhhhhhhhhhhhhhhhhhhhhh

*/