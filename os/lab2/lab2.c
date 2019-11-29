#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h> 
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
    int n;
    scanf("%d", &n);
    if (recursion(n, 2))
        printf("простое число\n");
    else printf("составное число\n");
    return 0;
}