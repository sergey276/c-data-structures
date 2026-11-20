#include "maxmin.h"

#ifndef MAX
#define MAX(a,b) ((a)>(b)?a:b)
#endif
#ifndef MIN
#define MIN(a,b) ((a)<(b)?a:b)
#endif

pair MaxMin(int A[], int L, int H)
{
    pair ret, left, right;

    // one element
    if (L == H) {
        ret.min = A[L];
        ret.max = A[L];
        return ret;
    }

    // two elements
    if (H == L + 1) {
        if (A[L] > A[H]) {
            ret.max = A[L];
            ret.min = A[H];
        } else {
            ret.max = A[H];
            ret.min = A[L];
        }
        return ret;
    }

    int mid = (L + H) / 2;

    left = MaxMin(A, L, mid);
    right = MaxMin(A, mid + 1, H);

    ret.max = MAX(left.max, right.max);
    ret.min = MIN(left.min, right.min);

    return ret;
}