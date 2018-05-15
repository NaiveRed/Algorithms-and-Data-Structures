/*
線段樹(segment tree, interval tree)
或是在演算法筆記中所述之 "Fake" segment tree
來解決 區間最小值查詢(RMQ, range minimum query)

http://www.csie.ntnu.edu.tw/~u91029/Sequence2.html#3
*/
#include <cstdio>
#define N (1 << 5)
#define MIN(a, b) ((a) < (b) ? (a) : (b))
//以陣列模擬樹，go left/right child
#define LC(i) ((i) << 1)
#define RC(i) (((i) << 1) + 1)

int arr[N];
struct node
{
    int min;      //區間最小值
} tree[(N << 1)]; //root 為 [1]
//int tree[N*4]; //非滿 2 元樹時

void build(int L, int R, int idx)
{
    /*
    [L, R]
    L, R: 目前所在的數列區間(遞迴中)
    idx: 樹的 index
    */
    if (L == R)
    {
        tree[idx].min = arr[L];
        return;
    }

    int M = (L + R) >> 1;
    int left_idx = LC(idx);     //index of left child
    int right_idx = RC(idx);    //index of right child
    build(L, M, left_idx);      //go left
    build(M + 1, R, right_idx); //go right

    tree[idx].min = MIN(tree[left_idx].min, tree[right_idx].min);
}

//單點修改
void modify(int n, int x, int L, int R, int idx)
{
    /*
    n: 欲修改的數字
    x: 欲修改的位置
    L, R: 目前所在的數列區間(遞迴中)
    idx: 樹的 index
    */

    if (L == R)
    {
        tree[idx].min = n;
        return;
    }

    int M = (L + R) >> 1;
    int left_idx = LC(idx);  //index of left child
    int right_idx = RC(idx); //index of right child
    if (x <= M)
        modify(n, x, L, M, left_idx); //go left
    else
        modify(n, x, M + 1, R, right_idx); //go right

    tree[idx].min = MIN(tree[left_idx].min, tree[right_idx].min);
}

//區間查詢
int query(int x1, int x2, int L, int R, int idx)
{
    /*
    [x1, x2]: 所查詢之區間
    L, R: 目前所在的數列區間(遞迴中)
    idx: 樹的 index
    */

    if (x1 == L && x2 == R)
        return tree[idx].min;

    int M = (L + R) >> 1;
    int left_idx = LC(idx);  //index of left child
    int right_idx = RC(idx); //index of right child

    if (x2 <= M) //查詢的區間在左邊
        return query(x1, x2, L, M, left_idx);
    else if (x1 > M) //查詢的區間在右邊
        return query(x1, x2, M + 1, R, right_idx);
    else //查詢的區間橫跨兩邊
        return MIN(query(x1, M, L, M, left_idx), query(M + 1, x2, M + 1, R, right_idx));
}
int main()
{
    for (int i = 0; i < N; ++i)
        arr[i] = i;

    build(0, N - 1, 1);
    int x1 = 5, x2 = 16;
    printf("%d\n", query(x1, x2, 0, N - 1, 1));

    int n = -100, x = 12;
    modify(n, x, 0, N - 1, 1);
    printf("%d\n", query(x1, x2, 0, N - 1, 1));

    return 0;
}