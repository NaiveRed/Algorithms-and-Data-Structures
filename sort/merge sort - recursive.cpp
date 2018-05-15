//recursive version
#include <cstdio>
#define N 20

int arr[N] = {33, 10, 45, 0, 8, 22, 84, 77, 6, 16, 62, 18, 3, 12, 20, 21, 17, 55, 1, 43};

void merge(int L, int M, int R)
{
    static int sort_arr[N];

    int idx = L;
    int s1 = L, s2 = M + 1; //left/right
    while (s1 <= M && s2 <= R)
    {
        sort_arr[idx++] = arr[(arr[s1] < arr[s2]) ? (s1++) : (s2++)];
        /*
        if (arr[s1] < arr[s2])
            sort_arr[idx++] = arr[s1++];
        else
            sort_arr[idx++] = arr[s2++];
        */
    }

    //[L, M] 剩餘未排進去的
    while (s1 <= M)
        sort_arr[idx++] = arr[s1++];

    //[M+1, R] 剩餘未排進去的
    while (s2 <= R)
        sort_arr[idx++] = arr[s2++];

    for (int i = L; i <= R; ++i)
        arr[i] = sort_arr[i];
}
void merge_sort(int L, int R)
{
    if (R - L + 1 < 2)
        return;

    int M = (R + L) >> 1;
    merge_sort(L, M);
    merge_sort(M + 1, R);
    merge(L, M, R);
}
int main()
{
    merge_sort(0, N - 1);
    for (int i = 0; i < N; ++i)
        printf("%d ", arr[i]);

    return 0;
}