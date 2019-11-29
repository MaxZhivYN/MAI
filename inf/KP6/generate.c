#include <stdio.h> 
#include <stdlib.h> 

#include "student.h" 
#include "io.h" 

int main(int argc, char *argv[]) 
{ 
	if (argc != 3) { 
		printf("Usage:\n\t./generate FILE_FROM FILE_TO\n"); 
		exit(0); 
	} 

	FILE *in = fopen(argv[1], "r"); 
	FILE *out = fopen(argv[2], "w"); 

	if (!in || !out) { 
		printf("I/O Error: can't open file.\n"); 
	exit(1); 
	} 

	Student s; 

	while (student_read_txt(&s, in)) { 
		student_write_bin(&s, out); 
	} 

	fclose(in); 
	fclose(out); 

	return 0; 
}
