#include "BWT.h"
#include <iostream>


void BWT::encriptBWT(string& str, int& count) {		// O(H*logH)
	int N = str.length();
	const int alphCount = 256;

	vector<int> p(N), cnt(max(N, alphCount)), c(N);
	fill(cnt.begin(), cnt.begin() + alphCount, 0);
	for (int i = 0; i < N; ++i) {
		++cnt[str[i]];
	}

	for (int i = 1; i < alphCount; ++i) {
		cnt[i] += cnt[i - 1];
	}

	for (int i = 0; i < N; ++i) {
		p[--cnt[str[i]]] = i;
	}

	c[p[0]] = 0;
	int classes = 1;
	for (int i = 1; i < N; ++i) {
		if (str[p[i]] != str[p[i - 1]])  ++classes;
		c[p[i]] = classes - 1;
	}

	int mid1, mid2;
	vector<int> pn(N), cn(N);
	for (int h = 0; (1 << h) < N; ++h) {
		for (int i = 0; i < N; ++i) {
			pn[i] = p[i] - (1 << h);
			if (pn[i] < 0)  pn[i] += N;
		}

		fill(cnt.begin(), cnt.begin() + classes, 0);
		for (int i = 0; i < N; ++i) {
			++cnt[c[pn[i]]];
		}

		for (int i = 1; i < classes; ++i) {
			cnt[i] += cnt[i - 1];
		}

		for (int i = N - 1; i >= 0; --i) {
			p[--cnt[c[pn[i]]]] = pn[i];
		}

		cn[p[0]] = 0;
		classes = 1;
		for (int i = 1; i < N; ++i) {
			mid1 = (p[i] + (1 << h)) % N;
			mid2 = (p[i - 1] + (1 << h)) % N;
			if (c[p[i]] != c[p[i - 1]] || c[mid1] != c[mid2])
				++classes;
			cn[p[i]] = classes - 1;
		}

		c = cn;
	}

	string result;
	result.resize(N);

	if (!str.empty()) {
		result[c[0]] = str[str.size() - 1];
		count = c[0];
	}
	for (int i = 1; i < N; ++i) {
		result[c[i]] = str[i - 1];
	}

	str = result;
}

void BWT::decriptBWT(string& str, int& count) {
	vector<int> alph(256, -1);
	vector<int> l(str.length());

	for (size_t i = 0; i < str.length(); ++i) {
		l[i] = (++alph[str[i]]);
	}

	size_t sum = 0, lsum = 0;
	for (size_t i = 0; i < alph.size(); ++i) {
		if (alph[i] != -1) {
			lsum += (alph[i] + 1);
			alph[i] = sum;
			sum = lsum;
		}
	}

	int lCount = count;

	string result;
	result.resize(str.length());
	for (int i = result.length() - 1; i >= 0; --i) {
		result[i] = str[lCount];
		lCount = l[lCount] + alph[str[lCount]];
	}

	str = result;
}

//	jfjdsnfsnfnnkjnfsjfkaaa