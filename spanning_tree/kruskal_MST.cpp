//Minimum Spanning Tree by Kruskal algorithm
#include <cstdio>
#include <algorithm>
#define N 100
#define M 10
struct edge
{
    int u, v, w;
    bool operator<(const edge &a) const
    {
        return w < a.w;
    }
} E[N];

//disjoint set
int p[M];
inline void init(int n)
{
    for (int i = 0; i < n; ++i)
        p[i] = i;
}
inline int find(int x)
{
    return (x == p[x]) ? x : (p[x] = find(p[x]));
}
inline void do_union(int x, int y)
{
    p[find(x)] = find(y);
}

int main()
{
    int n; //number of vertices
    int e; //number of edges

    scanf("%d%d", &n, &e);
    for (int i = 0; i < e; ++i)
    {
        //u<->v: w
        scanf("%d%d%d", &E[i].u, &E[i].v, &E[i].w);
    }

    //kruskal algorithm
    init(n);
    std::sort(E, E + e); //increasing

    for (int i = 0, k = 0; i < e && k < n - 1; ++i, ++k) //n 個點的生成樹共 n - 1 個邊
    {
        //找在不同樹上的
        while (find(E[i].u) == find(E[i].v))
            ++i;

        do_union(E[i].u, E[i].v);
        printf("%d <-> %d : %d\n", E[i].u, E[i].v, E[i].w);
    }

    return 0;
}
/*
4 5
1 2 5
1 3 4
1 4 5
2 3 6
3 4 2

graph:
1-2
|\|
4-3
*/