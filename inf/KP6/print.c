#include <stdio.h> 
#include <stdlib.h> 

#include "student.h" 
#include "io.h" 

int main(int argc, char *argv[]) 
{ 
	FILE *in = fopen(argv[1], "r"); 

	if (argc != 2) { 
		printf("Usage:\n\t./print DB_FILE\n"); 
		exit(0); 
	} 

	if (!in) { 
		printf("I/O Error: can't open file.\n"); 
		exit(1); 
	} 

	Student s; 

	while (student_read_txt(&s, in)) { 
		student_print(&s);
	} 

	fclose(in); 

	return 0; 
}
