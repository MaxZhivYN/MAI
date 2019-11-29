#include <stdio.h>

int labs1(long long x)
{
    return (x >= 0) ? x : x * (-1);
}

int a(long long x)
{
    return (x % 10);
}

int b(long long x)
{
    return ((x / 10) % 10);
}

int main(void)
{
    long long number;
    while (scanf("%lld", &number) == 1) {
        long long znak = 1, copacity = 1, ans = 0;
        if (number < 0) {
            znak = -1;
            number *= -1;
        }
        while (number >= 10) {
            ans += (labs1(a(number) - b(number)) * 100 + b(number) * 10 + a(number)) * copacity;
            copacity *= 1000;
            number /= 100;
        }
        printf("%lld\n", (ans + number * copacity) * znak);
    }
    return 0;
}
