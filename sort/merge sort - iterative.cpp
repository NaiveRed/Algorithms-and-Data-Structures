//iterative version
#include <cstdio>
#define N 20

//int arr[21] = {33, 10, 45, 0, 8, 22, 84, 77, 6, 16, 62, 18, 3, 12, 20, 21, 17, 55, 1, 43, 2};
int arr[N] = {33, 10, 45, 0, 8, 22, 84, 77, 6, 16, 62, 18, 3, 12, 20, 21, 17, 55, 1, 43};

int *p_sort_arr = new int[N]();
int *p_num = new int[N]();

int merge_sort(int len)
{
    int moves = 0;

    //bottom-up: seg = 1, 2, 4, 8, 16,...
    for (int seg = 1; seg < len; seg <<= 1)
    {
        int m = seg << 1;
        /*
        一段子序列可再分成左和右
        seg: 為子序列中一段左或右的長度
        m: 整段子序列的長度(左+右)
        [start, start+m-1] 為一段子序列，
        對每一段子序列的左和右做 merge。
        */
        for (int start = 0; start < len; start += m)
        {
            //左：[left, mid]
            //右：[mid+1, right]
            int left = start;
            int mid = (start + seg - 1 > len - 1) ? (len - 1) : (start + seg - 1);
            int right = (start + m - 1 > len - 1) ? (len - 1) : (start + m - 1);

            int s1 = left, end1 = mid;
            int s2 = mid + 1, end2 = right;

            int idx = left;
            while (s1 <= end1 && s2 <= end2)
            {
                p_sort_arr[idx++] = p_num[(p_num[s1] <= p_num[s2]) ? (s1++) : (s2++)];
                /*
                if (p_num[s1] <= p_num[s2])
                    p_sort_arr[idx++] = p_num[s1++];
                else
                    p_sort_arr[idx++] = p_num[s2++];
                */
            }
            while (s1 <= end1)
                p_sort_arr[idx++] = p_num[s1++];
            while (s2 <= end2)
                p_sort_arr[idx++] = p_num[s2++];
        }

        /*
        我們實際所需要的是 已部分排序好的子序列(p_sort_arr)，所以將它存到 p_num。
        而 p_num 原本的值就不重要了，它只是讓 p_sort_arr 繼續保有空間存下次 merge 的結果。
        
        原本遞迴中需要分段一個一個送回去的值，
        由於 iterative 的會一次做完整個序列的各子序列，可以直接對兩指標做交換。
        */
        int *temp = p_num;
        p_num = p_sort_arr; //將原本的 ptr 指向排序好的
        p_sort_arr = temp;
    }

    return moves;
}
int main()
{
    for (int i = 0; i < N; ++i)
        p_num[i] = arr[i];

    merge_sort(N);
    for (int i = 0; i < N; ++i)
        printf("%d ", p_num[i]);

    delete[] p_sort_arr;
    delete[] p_num;
    return 0;
}