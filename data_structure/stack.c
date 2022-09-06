#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MaxSize 5

typedef struct SNode *Stack;
struct SNode{
    int Data[MaxSize];
    int Top;
};

void Push(Stack Ptrs, int i){
    if(Ptrs->Top == MaxSize - 1){
        printf("fulled");
        return;
    }
    else{
        Ptrs->Data[++(Ptrs->Top)] = i;
        return;
    }
}


int Pop(Stack Ptrs){
    if(Ptrs->Top == -1){
        printf("empty");
        return -1;
    }
    else{
        return (Ptrs->Data[(Ptrs->Top)--]);
    }
}


void main(){
    struct SNode s;
    s.Top = -1;

    Stack s1 = &s;
    
    for(int i = 0; i < MaxSize; i++){
        Push(s1,2*i);
    }
    for(int i = 0; i < s1->Top+1; i++){
        printf("%d  ",s1->Data[i]);
    }
    printf("\n");
    for(int j = 0; s1->Top > -1; j++){
        printf("%d\n",s1->Data[s1->Top]);
        Pop(s1);
    }

    
}
