//iterative
#include <cstdio>
#define N ((1 << 5) - 2)
#define M (1 << 6)
#define MIN(a, b) ((a) < (b) ? (a) : (b))
//以陣列模擬樹，go left/right child
#define LC(i) ((i) << 1)
#define RC(i) (((i) << 1) | 1)
#define PADDING 1e9

int arr[N];
/*
struct node
{
    int data;     //區間最小值
} tree[(N << 1)]; //root 為 [1]
*/
int tree[M];
int T; //葉節點的起始 index

void build(int n)
{
    //n: n 為數列長度

    //算出葉節點的 index，要來存原始數據
    for (T = 1; T < n; T <<= 1)
        ;

    //printf("%d\n", T * 2); //所需要的 tree 大小 (M)

    int i;

    //將數列放進葉節點
    for (i = 0; i < n; ++i)
        tree[T + i] = arr[i];

    //進行填補，使其成為滿二元數
    for (; i < T; ++i)
        tree[T + i] = PADDING;

    //bottom-up 建構樹
    for (i = T - 1; i; --i)
        tree[i] = MIN(tree[LC(i)], tree[RC(i)]);
}

//單點修改
void modify(int n, int x)
{
    /*
    n: 欲修改的數字
    x: 欲修改的位置
    */

    int i = T + x;
    tree[i] = n;
    /*
    i^1: 看是否到達根結點了
    bottom-up 由葉節點一層一層往上修正
    */
    for (; i ^ 1; i >>= 1)
        tree[i >> 1] = MIN(tree[i], tree[i ^ 1]); //父節點 = MIN((左/右),(右/左)) 兩子節點
}

//區間查詢
int query(int L, int R)
{
    /*
    [L, R]: 所查詢之區間
    */

    int res = 1e9;

    /*
    將 L, R 變為開區間，並歸位到對應葉節點，一層一層往上比較。
    L^R^1: L 和 R 是否為同層相鄰的節點，由於是開區間，此時中間已無任何點要比較。
    L, R 只相差 1 時: (L^R)^1 = (0101^0100)^(0001) = (0001)^(0001) = 0
    否則 (L^R) 不會等於 (0001): (L^R)^1 = (xxxx)^(0001) != 0
    
    e.g.
    (二進位)
    L = 0010
    R = 0011
    (L^R)^1 = 0001^0001 = 0
    */

    //--L, ++R; //變為開區間 (L, R)

    for (L += T - 1, R += T + 1; L ^ R ^ 1; L >>= 1, R >>= 1)
    {
        //注意現在是 (L, R) 開區間
        if (~L & 1) //如果 L 是在左子樹，比較右邊的節點
            res = MIN(tree[L ^ 1], res);
        if (R & 1) //如果 R 是在右子樹，比較左邊的節點
            res = MIN(tree[R ^ 1], res);
    }

    return res;
}
int main()
{
    /*
    頭尾一定會有填補用的數字，為了在 query 時能進行開區間的轉換。
    所以資料應存在 [1]~[N]
    查詢時只能在區間 [1, N] 內
    */
    arr[0] = arr[N + 1] = PADDING;
    for (int i = 1; i <= N; ++i)
        arr[i] = i;

    build(N + 2);
    int x1 = 10, x2 = 16;
    printf("%d\n", query(x1, x2));

    int n = -100, x = 16;
    modify(n, x);
    printf("%d\n", query(x1, x2));

    modify(-113, 10);
    printf("%d\n", query(x1, x2));
    return 0;
}