# Segement tree

線段樹(segment tree, interval tree)  
或是在演算法筆記中所述之 "Fake" segment tree

## Segement tree with RMQ

利用線段樹來解決區間最小值查詢 (RMQ, range minimum query)。

要特別注意以陣列模擬樹時，長度為 `n` 的數列，其需要的大小為 `2*2^{ceil(log_2^n)}-1`。  
如果 `n` 是 2 的整數次方的話，需開大小為 `2*n`，否則是 `4*n`，因為是非滿二元樹。  
可以在一開始就進行填補使其成為滿二元樹。

Iterative 的版本則要注意留兩個空間，來從閉區間轉換成開區間，或使用其他實作方法。

**Code:**  
1. [Recursive version 1](segment_tree_with_RMQ_1.cpp)  
2. [Recursive version 2](segment_tree_with_RMQ_2.cpp)
3. [Iterative version](segment_tree_with_RMQ_3.cpp)

**Test:**  
* UVa 12299
* UVa 11235

**Ref:**  
* <http://www.csie.ntnu.edu.tw/~u91029/Sequence2.html#3>  
* <https://www.youtube.com/watch?v=GLuT4zKzdjc>  
* <https://www.slideshare.net/DanielChou/ss-7792670>  
* <http://codeforces.com/blog/entry/18051>  
* <https://www.geeksforgeeks.org/segment-tree-set-1-range-minimum-query/>