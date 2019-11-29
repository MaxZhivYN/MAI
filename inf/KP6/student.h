#ifndef _STUDENT_H_ 
#define _STUDENT_H_ 

#define STR_SIZE 24 

typedef struct { 
char surname[STR_SIZE]; 
char initials[3]; 
char gender[2]; 
int school; 
char medal[1]; 
int math;
int rus;
int physics;
char soch[1]; 
} Student; 


#endif 

