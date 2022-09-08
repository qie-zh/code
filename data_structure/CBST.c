//完全二叉搜索树的实现
//要求输入十个数字，创建完全搜索树，然后层序输出

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MaxNum 10

int A[MaxNum], T[MaxNum];

int GetLeftLength( int n){
    int H,X;

    H = log2((double)(n+1));
    X = n - pow(2,H) +1;

    X = (X > (pow(2,H-1))) ? pow(2,H-1) : X;


    return pow(2,H-1)-1+X;
}




void CreatCBST(int ALeft, int ARight, int TRoot){
    int n, L, LeftRoot, RightRoot;

    n = ARight - ALeft +1;
    if(n == 0) return;

    L = GetLeftLength(n);

    T[TRoot] = A[ALeft + L];
    LeftRoot = TRoot * 2 + 1;
    RightRoot = LeftRoot + 1;
    CreatCBST(ALeft, ALeft+L-1, LeftRoot);
    CreatCBST(ALeft+L+1, ARight, RightRoot);

}

int compare(const void* a, const void* b){

    return *(int*)a - *(int*)b;
}

void print_num(int a[],int n){
    for(int i = 0; i < n; i++){
        printf("%d ",a[i]);
    }
}

void main(){
    int a[]={4,3,6,7,2,0,1,5,9,8};

    for(int i = 0; i < 10; i++){
        A[i] = a[i];
    }
    qsort(A,10,sizeof(int),compare);
    
    CreatCBST(0,9,0);

    print_num(T,10);

    
}
