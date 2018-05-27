# Binary search

**Code:**  
1. [Binary Search](binary_search.cpp)

**Test:**  
* UVa 10611

## Upper bound

回傳第一個 **大於**(依數列順序) 條件的 **位置**。  
否則傳回 last(n)。

畫出來可以比較好想。  
\* : including(包含該點)  
o : excluding(不包含該點)

i.e. arr[M] > val
```
L     M     R  
------o      : val < arr[M], then R = M
      *------: val >= arr[M], then L = M + 1
```

## Lower bound

回傳第一個 **大於等於**(依數列順序) 條件的 **位置**。  
否則傳回 last(n)。

i.e. arr[M] >= val
```
L     M     R  
------*      : val <= arr[M], then R = M
      o------: val > arr[M], then L = M + 1
```

## Equal

直接使用 lower bound 的結果再進行判斷即可。