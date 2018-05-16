#include <cstdio>
#include <cstdlib>
#include <algorithm>
#define N 10

int arr[N] = {5, 4, 1, 9, 6, 7, 3, 2, 4, 8};
//int arr[N] = {1, 2, 3, 3, 3, 3, 3, 3, 5, 5};
inline bool lt(const int &a, const int &b)
{
    return a < b;
}
inline bool gt(const int &a, const int &b)
{
    return a > b;
}

int upper_bound(int L, int R, int val, bool (*comp)(const int &, const int &))
{
    /*
    comp 為 lt 的話: 傳回第一個 大於 val 的位置
    comp 為 gt 的話: 傳回第一個 小於 val 的位置
    如沒有找到符合條件的數字就傳回 last(N)
    
    尋找區間: [L, R)
    */
    while (L < R)
    {
        int M = (L + R) >> 1;
        if (comp(val, arr[M])) //lt: val < arr[M]
            R = M;
        else //lt: val >= arr[M]
            L = M + 1;
    }
    return L;
}
int lower_bound(int L, int R, int val, bool (*comp)(const int &, const int &))
{
    /*
    comp 為 lt 的話: 傳回第一個 大於等於 val 的位置
    comp 為 gt 的話: 傳回第一個 小於等於 val 的位置
    如沒有找到符合條件的數字就傳回 last(N)
    
    尋找區間: [L, R)
    */
    while (L < R)
    {
        int M = (L + R) >> 1;
        if (comp(arr[M], val)) //lt: arr[M] < val
            L = M + 1;
        else //lt: arr[M] >= val
            R = M;
    }
    return L;
}
int binary_search(int L, int R, int val, bool (*comp)(const int &, const int &))
{
    /*
    利用 lower_bound 的結果即可
    如在 [L, R) 找到等於 val 的就傳回第一個該位置，否則傳回 -1
    */
    int idx = lower_bound(L, R, val, comp);
    return (idx == R || arr[idx] != val) ? -1 : idx;
}
int main()
{
    for (int i = 0; i < N; ++i)
    {
        //arr[i] = rand() % 10;
        //arr[i] = i;
    }

    //Increasing
    std::sort(arr, arr + N);
    printf("arr: ");
    for (int i : arr)
        printf("%d ", i);
    puts("");

    int v = 4;
    //find the first number > v
    int up = upper_bound(0, N, v, &lt);
    //find the first number >= v
    int low = lower_bound(0, N, v, &lt);
    //find the first number == v
    int eq = binary_search(0, N, v, &lt);

    if (up != N)
        printf("arr[%d] = %d > %d\n", up, arr[up], v);
    else
        printf("Can't find any number greater than %d in arr\n", v);

    if (low != N)
        printf("arr[%d] = %d >= %d\n", low, arr[low], v);
    else
        printf("Can't find any number gt or equal to %d in arr\n", v);

    if (eq != -1)
        printf("arr[%d] = %d == %d\n", eq, arr[eq], v);
    else
        printf("Can't find any number equal to %d in arr\n", v);

    //#############################################

    //Decreasing
    std::sort(arr, arr + N, gt);
    printf("\narr: ");
    for (int i : arr)
        printf("%d ", i);
    puts("");

    //find the first number < v
    up = upper_bound(0, N, v, &gt);
    //find the first number <= v
    low = lower_bound(0, N, v, &gt);
    //find the first number == v
    eq = binary_search(0, N, v, &gt);

    if (up != N)
        printf("arr[%d] = %d < %d\n", up, arr[up], v);
    else
        printf("Can't find any number less than %d in arr\n", v);

    if (low != N)
        printf("arr[%d] = %d <= %d\n", low, arr[low], v);
    else
        printf("Can't find any number lt or equal to %d in arr\n", v);

    if (eq != -1)
        printf("arr[%d] = %d == %d\n", eq, arr[eq], v);
    else
        printf("Can't find any number equal to %d in arr\n", v);

    return 0;
}