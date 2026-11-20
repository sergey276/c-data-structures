#include <limits.h>
#include "matrix.h"

int chainMatrixMultiplication(int *r, int n)
{
    int m[n+1][n+1];

    for (int i = 1; i <= n; i++)
        m[i][i] = 0;

    for (int L = 2; L <= n; L++) {
        for (int i = 1; i <= n - L + 1; i++) {
            int j = i + L - 1;
            m[i][j] = INT_MAX;
            for (int k = i; k < j; k++) {
                int q = m[i][k] + m[k+1][j] + r[i-1]*r[k]*r[j];
                if (q < m[i][j]) m[i][j] = q;
            }
        }
    }

    return m[1][n];
}