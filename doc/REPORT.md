# HW1 阿克曼函數

## 1.解題說明

使用遞迴實作阿克曼函數，已知阿克曼函數定義為:

A(m,n) = { n+1 , if m=0 ; A(m-1,1) , if n=0 ; A(m-1,A(m,n-1) , otherwise ; }

實作`HW101.cpp`,遞迴函式:

```cpp
int funA(int m,int n){
    if(m==0){
        return n+1;
    }
    else if(n==0){
        return funA(m-1,1);
    }
    else{
        return funA(m-1,funA(m,n-1));
    }
}
```

## 2.演算法設計與實作

```cpp
int main(){
    int m,n;
    while(cin>>m>>n){ //輸入變數
        int ans=funA(m,n); //呼叫函式，並將函式結果回傳存入ans
        cout<<ans<<"\n"; //輸出結果
    }
    return 0;
}
```

## 3.效能分析

### Worst Case

時間複雜度T(m,n)=O(A(m,n))

空間複雜度S(m,n)=O(A(m,n))

### Best Case

時間複雜度T(m,n)=O(1)

空間複雜度S(m,n)=O(1)

### Average Case

近似於Worst Case

## 4.測試

### Input

```
3 4
1 3
3 3
```
### Output

```
125
5
61
```
