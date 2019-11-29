#pragma once

#include "Huffman.h"
#include "BWT.h"
#include "MTF.h"
#include "RLE.h"
#include "MyFStream.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

#define bufferSize 1000000

using namespace std;

class ZhivArchiver {
public:
	void zZip(ifstream& in, ofstream& out);
	void zUnZip(ifstream& in, ofstream& out);
private:
	BWT bwt;
	MTF mtf;
	RLE rle;
	Huffman huffman;
	MyFStream myFStream;
};

