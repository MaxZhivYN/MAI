#include <stdio.h>

int usl(char a)
{
    return (a >= '0' && a <= '7');
}

int main(void)
{
    int s, state = 1, q = 0;

    while ((s = getchar()) != EOF) {
        switch (state) {


            case 1:
                if (usl(s)) {
                    if (s == 1) {
                        state = 2;
                    } else {
                        state = 10;
                    }
                } else {
                    state = 999;
                }
                break;

            
            case 2:
                if (usl(s)) {
                    if (s == 0) {
                        state = 3;
                    } else {
                        state = 11;
                    }
                } else {
                    state = 999;
                }
                break;

            
            case 3:
                if ((s == ' ') || (s == '\n') || (s == '\r') || (s == '\t')) {
                    state = 1;
                    q++;
                } else {
                    if (usl(s)) {
                        if (s == 0) {
                            state = 4;
                        } else {
                            state = 12;
                        }
                    } else {
                        state = 999;
                    }
                }
                break;

            
            case 4:
                if (s == 0) {
                    state = 5;
                } else {
                    state = 999;
                }
                break;

            
            case 5:
                if ((s == ' ') || (s == '\n') || (s == '\r') || (s == '\t')) {
                    state = 1;
                    q++;
                } else {
                    state = 999;
                }
                break;

            
            case 10:
                if ((s == ' ') || (s == '\n') || (s == '\r') || (s == '\t')) {
                    state = 1;
                } else {
                    if (usl(s)) {
                        state = 11;
                    } else {
                        state = 999;
                    }
                }
                break;


            case 11:
                if ((s == ' ') || (s == '\n') || (s == '\r') || (s == '\t')) {
                    state = 1;
                    q++;
                } else {
                    if (usl(s)) {
                        state = 5;
                    } else {
                        state = 999;
                    }
                }
                break;


            case 999:
                if ((s == ' ') || (s == '\n') || (s == '\r') || (s == '\t')) {
                    state = 1;
                }
                break;
        }
    }
    printf("%d\n", q);
    return 0;
}
