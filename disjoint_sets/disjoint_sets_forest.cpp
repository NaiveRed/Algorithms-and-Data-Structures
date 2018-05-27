//Disjoint Sets: Forest
#include <cstdio>
#define N 100

//disjoint set
int p[N];    //the leader of each unit([x]: x 的老大)
int size[N]; //number of each group([x]: x 老大的成員有幾人)
inline void init(int n)
{
    for (int i = 0; i < n; ++i)
    {
        p[i] = i;
        size[i] = 1;
    }
}
inline int find(int x)
{
    //路徑壓縮
    return (x == p[x]) ? x : (p[x] = find(p[x]));
}
inline void do_union(int x, int y)
{
    x = find(x), y = find(y);
    if (x == y)
        return;

    //小的併入大的
    if (size[x] < size[y])
    {
        p[x] = y;
        size[y] += size[x];
        //size[x] = 0;
    }
    else
    {
        p[y] = x;
        size[x] += size[y];
        //size[y] = 0;
    }
}

int main()
{
    init(10);
    do_union(2, 5);
    printf("2:%d, 5:%d\n", find(2), find(5));
    do_union(3, 5);
    printf("2:%d, 5:%d, 3:%d\n", find(2), find(5), find(3));
    return 0;
}