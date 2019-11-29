#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

#include "student.h" 
#include "io.h" 

/* Student IO */ 
int student_read_txt(Student *s, FILE *in) 
{ 
fscanf(in, "%s", s->surname); 
fscanf(in, "%s", s->initials); 
fscanf(in, "%s", s->gender); 
fscanf(in, "%d", &(s->school)); 
fscanf(in, "%s", s->medal); 
fscanf(in, "%d", &(s->math));
fscanf(in, "%d", &(s->rus)); 
fscanf(in, "%d", &(s->physics));  
fscanf(in, "%s", s->soch); 

return !feof(in); 
} 

int student_read_bin(Student *s, FILE *in) 
{ 
fread(s->surname, sizeof(char), STR_SIZE, in); 
fread(s->initials, sizeof(char), 3, in); 
fread(s->gender, sizeof(char), 2, in); 
fread(&(s->school), sizeof(int), 1, in); 
fread(s->medal, sizeof(char), 1, in); 
fread(&(s->math), sizeof(int), 1, in);
fread(&(s->rus), sizeof(int), 1, in); 
fread(&(s->physics), sizeof(int), 1, in);  
fread(s->soch, sizeof(char), 1, in); 

return !feof(in); 
} 

void student_write_bin(Student *s, FILE *out) 
{ 
fwrite(s->surname, sizeof(char), STR_SIZE, out); 
fwrite(s->initials, sizeof(char), 3, out); 
fwrite(s->gender, sizeof(char), 2, out); 
fwrite(&(s->school), sizeof(int), 1, out); 
fwrite(s->medal, sizeof(char), 1, out); 
fwrite(&(s->math), sizeof(int), 1, out);
fwrite(&(s->rus), sizeof(int), 1, out);
fwrite(&(s->physics), sizeof(int), 1, out); 
fwrite(s->soch, sizeof(char), 1, out); 
} 

void student_print(Student *s) 
{ 
printf("Name: %s\n", s->surname); 
printf("Initials: %s\n", s->initials); 
printf("Gender: %s\n", s->gender); 
printf("School: %d\n", s->school); 
printf("Medal: %s\n", s->medal); 
printf("Mathematics: %d\n", s->math);
printf("Russian: %d\n", s->rus); 
printf("Physics: %d\n", s->physics);  
printf("Sochinenie: %s\n", s->soch); 

printf("\n"); 
}
