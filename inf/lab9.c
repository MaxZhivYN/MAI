#include <stdio.h>
#include <math.h>


int abs(int x)
{
    return (x >= 0) ? x : x * (-1);
}

int min(int x, int y)
{
    return (x >= y) ? y : x;
}


int max(int x, int y)
{
    return (y >= x) ? y : x;
}

int mod(int x, int y)
{
    int c;
    c = x % y;
    if (c < 0) {
        c = c + abs(y);
    }
    return c;
}

int sign(int x)
{
    if (x > 0) {
        return 1;
    }
    if (x < 0) {
        return (-1);
    }
    return 0;
}

int main(void)
{
    int i, j, l, k, ln, in, ln;
    scanf("%d %d %d", &i, &j, &l);
    for (k = 0; k < 50; k++) {
        if (j >= -10 - i && j <= -20 - i) {
            printf("Yes\n");
            printf("%d %d %d %d\n", in, jn, ln, k);
            break;
        }
        in = mod(abs(i - j) * l - abs(j - l) * i + abs(i - l) * j, 20) - k;
        jn = min(i, j) * max(j, l) * mod(min(i, l), 25) + 5 * sign(i) + k;
        ln = abs(l) * sign(i - j) - abs(i) * sign(j - l) + abs(j) * sign(i - l);
        i = in;
        j = jn;
        l = ln;
    }    
    if (k == 50) {
        printf("No\n");
        printf("%d %d %d %d\n", in, jn, ln, k);
    }
    return 0;
}