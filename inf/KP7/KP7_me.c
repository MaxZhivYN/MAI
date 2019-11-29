#include <stdio.h>
#include <complex.h>
#include <math.h>
#include <stdlib.h>

struct elements
{
	int column;
	int complex value;
	int idx;
};


int main() {
	int a = 0, b = 0, m = 0, n = 0;

	printf("Number of rows and columns in the matrix: ");
	scanf("%d%d", &m, &n);

	int complex beginer;
	unsigned int M[m];
	struct  elements A[300];

	printf("Input matrix\n");

	int index = 0, indicator_1 = 0, indicator_2 = 0, c = 0;
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			scanf("%d%d", &a, &b);
			beginer = a + b * I;
			if (beginer != 0.0 + 0.0 * I) {
				if (indicator_2 == 0) {
					M[c] = j + 1;
					++c;
					++indicator_2;
				}
				A[index].column = j + 1;
				A[index].value = beginer;
				if (indicator_1 == 0) {
					if (index != 0) {
						A[index - 1].idx = j + 1;
					}
				} else {
					A[index - 1].idx = 0;
					indicator_1 = 0;
				}
				++index;
			}
		}
		++indicator_1;
		if (indicator_2 == 0) {
			M[c] = 0;
			c++;
		} else {
			indicator_2 = 0;
		}
	}
	A[index].idx = 0;

	printf("Array A:\n");
	for (int i = 0; i < index; ++i) {
		printf("| %d | %f%+fi | %d |", A[i].column, creal(A[i].value), cimag(A[i].value), A[i].idx);		
	}
	printf("\n");

	printf("Array M:\n");
	for (int i = 0; i < m; ++i) {
		printf("%d ", M[i]);
	}
	printf("\n");

	int mass_vector[m];
	int complex mass_vector_result[m];

	printf("Input Vector\n");
	for (int i = 0; i < n; ++i) {
		scanf("%d", &mass_vector[i]);
	}

	int index_2 = 0, k = 0;
	int complex sum = 0;
	for (int i = 0; i < m; ++i) {
		if (M[i] != 0) {
			while (1 == 1) {
				sum += A[index_2].value * mass_vector[A[index_2].column - 1];
				if (A[index_2].idx == 0) {
					++index_2;
					break;
				}
				++index_2;
			}
			mass_vector_result[i] = sum;
			if (mass_vector_result[i] == 0.0 + 0.0 * I) {
				++k;
			}
			sum = 0;
		} else {
			mass_vector_result[i] = 0;
			++k;
		}
	}
	printf("Result vector:\n");
	for (int i = 0; i < m; ++i) {
		printf("%f%+fi ", creal(mass_vector_result[i]), cimag(mass_vector_result[i]));		
	}
	printf("\nNumber of non-zero elements in the vector:\n%d\n", k);
	return 0;
}