#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h> 
#include <sys/stat.h> 
#include <unistd.h>
#include <sys/mman.h> 
#include <fcntl.h>

bool recursion(int n, int i)
{
    if (fork() == 0) {
        if (n < i)
            return false;
        else if (n == i)
            return true;
        else if (n % i == 0 && n != i)
            return false;
        else if (i < n / 2) {
            return recursion(n, i + 1);
        } else
           return true;
    } else {
        exit(0);
    }
    
    
 
}
int main()
{
    int fdin;
    void *src;
    struct stat statbuf; 
    fdin = open("file1.txt", O_RDONLY);
    fstat(fdin, &statbuf);
    src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0);
    char *chr = (char*) src;
    int n = atoi(chr);
    if (recursion(n, 2))
        printf("простое число\n");
    else printf("составное число\n");
    return 0;
}