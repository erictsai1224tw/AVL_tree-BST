# 函數指標
## 用途
可用來將函數傳到另一函數內進行運算(傳送函數位址進去)

## 範例
```C
#include <stdio.h>
#include <stdlib.h>

int func_add(int a, int b)
{
    return a + b;
}

int func_sub(int a, int b)
{
    return a - b;
}

int func_mul(int a, int b)
{
    return a * b;
}

int arith_func(int a, int b, int (*func_ptr)(int, int))
{
    int c;
    c = func_ptr(a, b);
    printf("%d\n", c);
    return c;
}

int main()
{
    arith_func(5, 5, func_add);
    arith_func(5, 5, func_sub);
    arith_func(5, 5, func_mul);
    return 0;
}
```

## output
```
10
0
25
```


