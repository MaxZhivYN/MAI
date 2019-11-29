#include <stdio.h>

int max(int x, int y)
{
    return (x >= y) ? x : y;
}

int min(int x, int y)
{
    return (x <= y) ? x : y;
}

int main(void)
{
    int k, n;
    scanf("%d %d", &k, &n);
    int n_lok[k];
    int m[k][n][n];
    
    //scan all
    for (int test = 0; test < k; test++) {
        scanf("%d", &n_lok[test]);
        for (int i = 0; i < n_lok[test]; i++) {
            for (int j = 0; j < n_lok[test]; j++) {
                scanf("%d", &m[test][i][j]);
            }
        }
    }
    printf("\n");
    
    //max && min of all i
    int d[k][n];
    int c[k][n];
    int max_c[k];
    int min_d[k];
    for (int test1 = 0; test1 < k; test1++) {
        for (int in = 0; in < n_lok[test1]; in++) {
            for (int jn = 0; jn < n_lok[test1]; jn++) {
                if (jn < 1) {
                    if (m[test1][in][0] < 0) {
                        c[test1][in] = m[test1][in][0];
                    } else {
                        c[test1][in] = 0;
                    }
                }
                c[test1][in] = max(m[test1][in][jn], c[test1][in]);
                if (jn < 1) {
                    if (m[test1][in][0] < 0) {
                        d[test1][in] = 0;
                    } else {
                        d[test1][in] = m[test1][in][0];
                    }
                }
                d[test1][in] = min(m[test1][in][jn], d[test1][in]);
            }
            if (in < 1) {
                if (c[test1][0] < 0) {  
                    max_c[test1] = c[test1][0];
                } else {
                    max_c[test1] = 0;
                }
            } 
            max_c[test1] = max(c[test1][in], max_c[test1]);
            if (in < 1) {
                if (c[test1][0] < 0) {  
                    min_d[test1] = 0;
                } else {
                    min_d[test1] = c[test1][0];
                }
            } 
            min_d[test1] = min(d[test1][in], min_d[test1]);
        }

        //поиск минимальной строчки
        int op = 0;
        int min_i[k];
        int max_i[k][n];
        for (int in1 = 0; in1 < n_lok[test1]; in1++) {
            for (int jn1 = 0; jn1 < n_lok[test1]; jn1++) {
                if (m[test1][in1][jn1] == min_d[test1]) {
                    min_i[test1] = in1;
                    op = 1;
                    break;
                }
            }
            if (op == 1) {
                op = 0;
                break;  
            }
        }
        int q = 0;
        for (int in2 = 0; in2 < n_lok[test1]; in2++) {
            for (int jn2 = 0; jn2 < n_lok[test1]; jn2++) {
                if (m[test1][in2][jn2] == max_c[test1]) {
                    op = 1;
                }
            }
            if (op == 1) {
                max_i[test1][q] = in2;
                //printf("%d\n", max_i[test1][q]);
                q++;
                op = 0;
            }
        }

        
        for (int i4 = 0; i4 < n_lok[test1]; i4++) {
            for (int j4 = 0; j4 < n_lok[test1]; j4++) {
                for (int u = 0; u < q - 1; u++) {
                    if (i4 == max_i[test1][u]) {
                        printf("%d ", m[test1][min_i[test1]][j4]);
                    } else {
                        printf("%d ", m[test1][i4][j4]);
                    }
                }
            }
            printf("\n");
        }
        // printf("\n");
        // printf("%d\n", min_i[test1]);
    }

    
    return 0;
}