#include <stdio.h> 
#include <stdlib.h> 

#include "student.h" 
#include "io.h" 

int main(int argc, char *argv[]) 
{ 
	if (argc != 2) { 
		printf("Usage:\n\t./execute DB_FILE\n"); 
		exit(0); 
	} 

	FILE *in = fopen(argv[1], "r"); 
	if (!in) { 
		printf("I/O Error: can't open file.\n"); 
		exit(1); 
	} 
	Student s; 
	while (student_read_txt(&s, in)){ 
		if (s.math != s.rus != s.physics && s.gender[0] == 'F'){ 
			student_print(&s); 
		} 
	} 
	fclose(in); 
	return 0; 
}
