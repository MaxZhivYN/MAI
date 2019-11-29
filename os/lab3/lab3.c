#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <inttypes.h>
#include <limits.h>
#include <string.h>

#define NUMBER_SIZE 32
#define DEC_SIZE 40

typedef struct _mytype {
    char *word;
    __int128 word_int_128;
} Mytype;


int magic(char *s)
{
    if(*s == 'A')
        return 10;
    if(*s == 'B')
        return 11;
    if(*s == 'C')
        return 12;
    if(*s == 'D')
        return 13;
    if(*s == 'E')
        return 14;
    if(*s == 'F')
        return 15;
    return 0;
}

int is_num(char *s)
{
    return (*s >= '0' && *s <= '9');
}

void* threadFunc(void *mytype_in)
{
    Mytype *mytype = (Mytype*) mytype_in;
    while (*(mytype->word)) {
        if(is_num(mytype->word))
            mytype->word_int_128 = mytype->word_int_128 * 16 + (*mytype->word - '0');
        else {
            int kek = magic(mytype->word);
            mytype->word_int_128 = mytype->word_int_128 * 16 + kek;
        }
        ++mytype->word;
    }
    
    pthread_exit(0);
}

void print_int128(__int128 u128)
{
    char buf[DEC_SIZE + 1];
    int i;
    for (i = 0; i < DEC_SIZE; ++i) {
        buf[i] = '0';
    }
    buf[DEC_SIZE] = '\0';
    for (i = DEC_SIZE - 1; u128 > 0; --i) {
        buf[i] = (int) (u128 % 10) + '0';
        u128 /= 10;
    }
    if (i == DEC_SIZE - 1) {
        printf("%d\n", 0);
    } else {
        printf("%s\n", &buf[i + 1]);
    }
}

int main (int argc, char *argv[]) 
{
    unsigned long int memory = 0;
    FILE *file= fopen("file.txt", "r");
    Mytype *mytype = (Mytype*)malloc(sizeof(Mytype));
    int n = 0;
    if (argc == 2) {
        memory = atoi(argv[1]);
    }
    else {
        printf("Enter the amount of memory\n");
        return 1;
    }
    
    unsigned long int memory_expended = sizeof(unsigned long int) * 2 + sizeof(file) + sizeof(int) * 2 + sizeof(__int128);

    while (feof(file) == 0) {
        memory_expended += sizeof(Mytype) + sizeof(char) * (NUMBER_SIZE + 1) + sizeof(pthread_t);
        if (memory < memory_expended) {
            printf("Your memory is over!\n");
            return 1;
        }
        mytype = (Mytype*)realloc(mytype, sizeof(Mytype) * (n + 1)); 
        mytype[n].word = (char*)malloc((NUMBER_SIZE + 1) * sizeof(char));
        mytype[n].word_int_128 = 0;
        fscanf(file, "%s", mytype[n].word);
        ++n;
    }
    
    
    fclose(file);
    pthread_t *thread_id = (pthread_t*) malloc(sizeof(pthread_t) * (n + 1));
    for (int i = 0; i < n; ++i) {
        pthread_create(&thread_id[i], NULL, threadFunc, (void *) &mytype[i]);
    }
    __int128 sum = 0;
    for (int i = 0; i < n; i++) {
        pthread_join(thread_id[i], NULL);
        sum += mytype[i].word_int_128;
    }
    sum /= n;
    print_int128(sum);

    free(mytype);
    free(thread_id);
    
    return 0;
}