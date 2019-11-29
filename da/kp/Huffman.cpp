#include "Huffman.h"

void Huffman::encoding(string& str) {	//	O(N)
	vector<int> lalph(256, -1);
	
	char maxSymbol = 0;
	for (size_t i = 0; i < str.length(); ++i) {		//	O(N)
		++lalph[str[i]];
		maxSymbol = max(maxSymbol, str[i]);
	}

	string alph;
	for (size_t i = 0; i < lalph.size(); ++i) {
		if (lalph[i] != -1) {
			alph.push_back(i);
		}
	}

	createHTree(alph, lalph);		// O(A)

	vector<string> encoding(maxSymbol + 1);
	createEncodingVec(root, string(""), encoding);	//	O(A)

	string result = "";
	for (size_t i = 0; i < str.size(); ++i) {		//	O(N)
		result += encoding[str[i]];
	}
	
	str = result;
}

void Huffman::createHTree(string& alph, vector<int>& lalph) {
	struct CompareAge {
		bool operator()(HNode* p1, HNode* p2) {
			return p2->priority < p1->priority;
		}
	};

	priority_queue<HNode*, vector<HNode*>, CompareAge> HPrioQueue;

	for (string::iterator i = alph.begin(); i != alph.end(); ++i) {		//	O(A)
		HPrioQueue.push(new HNode{ false, *i, lalph[*i], nullptr, nullptr });
	}

	HNode* left;
	HNode* right;
	while (HPrioQueue.size() > 1) {		//	O(A)
		left = HPrioQueue.top();
		HPrioQueue.pop();

		right = HPrioQueue.top();
		HPrioQueue.pop();

		HPrioQueue.push(new HNode{ true, '\0', left->priority + right->priority, left, right });
	}

	root = HPrioQueue.top();
}

void Huffman::createEncodingVec(HNode* node, string code, vector<string>& encoding) {
	if (!node) return;
	++nodeCount;

	if (!(node->empty || node->left || node->right)) {
		encoding[node->symbol] = code;
	}

	createEncodingVec(node->left, code + "0", encoding);
	createEncodingVec(node->right, code + "1", encoding);
}

void Huffman::printHTree(ofstream& out) {
	string pPath, pAlph;

	printHTeeRec(root, pPath, pAlph);
	
	myFStream.writeHStr(pPath, out);
	myFStream.writeStr(pAlph, out);
}

void Huffman::printHTeeRec(HNode* node, string& pPath, string& pAlph) {
	if (!node) return;

	if (node->empty) {
		pPath.push_back('0');
	}
	else {
		pPath.push_back('1');
		pAlph.push_back(node->symbol);
	}

	printHTeeRec(node->left, pPath, pAlph);
	printHTeeRec(node->right, pPath, pAlph);
}

void Huffman::decoding(string& str) {
	string result;
	HNode* node = root;
	for (size_t i = 0; i < str.length(); ++i) {
		if (str[i] == '0') {
			node = node->left;
		}
		else {
			node = node->right;
		}

		if (!node->empty) {
			result.push_back(node->symbol);
			node = root;
		}
	}

	str = result;
}


void Huffman::scanHTree(ifstream& in) {
	string pPath, pAlph;
	
	myFStream.readHStr(pPath, in);
	myFStream.readStr(pAlph, in);
	
	root = new HNode{ true, '\0', 0, nullptr, nullptr };

	size_t* pPathCount = new size_t;
	*pPathCount = 0;

	size_t* pAlphCount = new size_t;
	*pAlphCount = 0;
	
	scanHTeeRec(root, pPath, pAlph, pPathCount, pAlphCount);

	delete pPathCount;
	delete pAlphCount;
}

void Huffman::scanHTeeRec(HNode* node, string& pPath, string& pAlph, size_t* pPathCount, size_t* pAlphCount) {
	if (pPath[(*pPathCount)++] == '0') {
		node->left = new HNode{ true, '\0', 0, nullptr, nullptr };
		node->right = new HNode{ true, '\0', 0, nullptr, nullptr };
	}
	else {
		node->empty = false;
		node->symbol = pAlph[(*pAlphCount)++];
		return;
	}

	scanHTeeRec(node->left, pPath, pAlph, pPathCount, pAlphCount);
	scanHTeeRec(node->right, pPath, pAlph, pPathCount, pAlphCount);
}

Huffman::~Huffman() {
	if(root) deleteHTree(root);
}

void Huffman::deleteHTree(HNode* node) {
	if (node->left) deleteHTree(node->left);
	if (node->right) deleteHTree(node->right);

	delete node;
}
