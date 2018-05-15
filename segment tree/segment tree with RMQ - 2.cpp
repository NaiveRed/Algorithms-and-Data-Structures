//recursive
#include <cstdio>
#define N (100)
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int arr[N];
struct node
{
    int L, R;             //所對應數列中的 [L,R] 區間
    int min;              //區間最小值
    int l_child, r_child; //其 child 的 index
} tree[(N << 2)];         //root 為 [0]

int st_idx; //tree index
void build(int L, int R, int idx)
{
    /*
    [L, R]
    L, R: 目前所在的數列區間(遞迴中)
    idx: 樹的 index
    */
    tree[idx].L = L;
    tree[idx].R = R;
    if (L == R)
    {
        tree[idx].min = arr[L];
        return;
    }

    int M = (L + R) >> 1;
    int left_idx = tree[idx].l_child = ++st_idx;  //index of left child
    int right_idx = tree[idx].r_child = ++st_idx; //index of right child
    build(L, M, left_idx);                        //go left
    build(M + 1, R, right_idx);                   //go right

    tree[idx].min = MIN(tree[left_idx].min, tree[right_idx].min);
}

//單點修改
void modify(int n, int x, int idx)
{
    /*
    n: 欲修改的數字
    x: 欲修改的位置    
    idx: 樹的 index
    */

    if (tree[idx].L == tree[idx].R)
    {
        tree[idx].min = n;
        return;
    }

    int M = (tree[idx].L + tree[idx].R) >> 1;
    int left_idx = tree[idx].l_child;  //index of left child
    int right_idx = tree[idx].r_child; //index of right child
    if (x <= M)
        modify(n, x, left_idx); //go left
    else
        modify(n, x, right_idx); //go right

    tree[idx].min = MIN(tree[left_idx].min, tree[right_idx].min);
}

//區間查詢
int query(int L, int R, int idx)
{
    /*
    L, R: 欲查詢的區間 [L, R]
    idx: 樹的 index
    */

    if (tree[idx].L == L && tree[idx].R == R)
        return tree[idx].min;

    int M = (tree[idx].L + tree[idx].R) >> 1;
    int left_idx = tree[idx].l_child;  //index of left child
    int right_idx = tree[idx].r_child; //index of right child

    if (R <= M) //查詢的區間在左邊
        return query(L, R, left_idx);
    else if (L > M) //查詢的區間在右邊
        return query(L, R, right_idx);
    else //查詢的區間橫跨兩邊
        return MIN(query(L, M, left_idx), query(M + 1, R, right_idx));
}
int main()
{
    for (int i = 0; i < N; ++i)
        arr[i] = i;

    st_idx = 0; //root
    build(0, N - 1, 0);
    int x1 = 5, x2 = 16;
    printf("%d\n", query(x1, x2, 0));

    int n = -100, x = 12;
    modify(n, x, 0);
    printf("%d\n", query(x1, x2, 0));

    return 0;
}