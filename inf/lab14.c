#include <stdio.h>

int main(void)
{
    int k, n;
    scanf("%d%d", &k, &n);
    int n_lok;
    int m[n][n];
    for (int number = 0; number < k; number++) {
        scanf("%d", &n_lok);
        for (int i = 0; i < n_lok; i++) {
            for (int j = 0; j < n_lok; j++) {
                scanf("%d", &m[i][j]);
            }
        }
        int row = -1;
        int col = n_lok - 1;
        for (int idx = 0; idx < 2 * n_lok - 1; idx++) {
            int len = n_lok - (idx + 1) / 2;
            for (int el = 0; el < len; el++) {
                int ways[4] = {1, 0 , -1, 0};
                row += ways[idx % 4];
                col += ways[(idx + 1) % 4];
                printf("%d ", m[row][col]);
            }
        }
        printf("\n");
    }
    return 0;
}
