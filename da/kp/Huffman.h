#pragma once

#include "MyFStream.h"

#include <fstream>
#include <string>
#include <map>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

class Huffman {
public:
	Huffman() {};
	~Huffman();

	void encoding(string& str);
	void decoding(string& str);

	void printHTree(ofstream& out);
	void scanHTree(ifstream& in);
private:
	struct HNode {
		bool empty;

		char symbol;
		int priority;

		HNode* left;
		HNode* right;
	};

	HNode* root{0};
	size_t nodeCount{0};
	
	MyFStream myFStream;

	void createHTree(string& alph, vector<int>& lalph);
	void createEncodingVec(HNode* root, string code, vector<string>& conding);

	void printHTeeRec(HNode* node, string& pPath, string& pAlph);
	void scanHTeeRec(HNode* node, string& pPath, string& pAlph, size_t* pPathCount, size_t* pAlphCount);

	void deleteHTree(HNode* node);
};
