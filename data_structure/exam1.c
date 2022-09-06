//??????????????????

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct PolyNode *Polynomial;
struct PolyNode{
    int coef;                 //???
    int expon;                //???
    Polynomial link;
};

void Attach( int c, int e, Polynomial *pRear){
    Polynomial P;

    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->coef = c;
    P->expon = e;
    P->link = NULL;
    (*pRear)->link = P;
    *pRear = P;

}


Polynomial ReadPoly(){
    Polynomial P,Rear,t;
    int c,e,N;

    scanf("%d",&N);

    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->link = NULL;
    Rear = P;

    while(N--){
        scanf("%d %d",&c,&e);
        Attach(c,e,&Rear);
    }

    t = P;
    P = P->link;
    free(t);

    return P;

}

int Length( Polynomial PtrL){    //????????
    Polynomial p = PtrL;
    int j = 0;
    while(p){
        p = p->link;
        j++;
    }
    return j;
}


Polynomial FindKth( int k, Polynomial PtrL){                 //???????? k??????
    Polynomial p = PtrL;
    int i = 1;
    while(p->link !=NULL && i < k){
        p = p->link;
        i++;
    }
    if(i == k){
        return p;
    }
    else return NULL;
}

void Print_Poly(Polynomial PP){
    Polynomial p;
    for(int i = 1; i <= Length(PP); i++){
        p = FindKth(i,PP);
        if(p->expon) printf("%dX%d+",p->coef,p->expon); 
        else printf("%d",p->coef);
    }
    printf("\n");
}

Polynomial Add(Polynomial P1, Polynomial P2){
    Polynomial t1,t2,P,Rear;

    t1 = P1; t2 = P2;

    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->link = NULL;
    Rear = P;

    while(t1 && t2){
        if(t1->expon == t2->expon){
            Attach(t1->coef + t2->coef , t1->expon, &Rear);
            t1 = t1->link;
            t2 = t2->link;
        }
        else if(t1->expon > t2->expon){
            Attach(t1->coef, t1->expon, &Rear);
            t1 = t1->link;
        }
        else{
            Attach(t2->coef, t2->expon, &Rear);
            t2 = t2->link;
        }
    }

    while(t1){
        Attach(t1->coef, t1->expon, &Rear);
        t1 = t1->link;
    }

    while (t2){
        Attach(t2->coef, t2->expon, &Rear);
        t2 = t2->link;
    }

    P = P->link;

    return P;

}

Polynomial Mult(Polynomial P1, Polynomial P2){
    Polynomial P,Rear,t1,t2,t;
    int c,e;

    if(!P1 || !P2) return NULL;

    t1 = P1; t2 = P2;

    P = (Polynomial)malloc(sizeof(struct PolyNode));
    P->link = NULL;
    Rear = P;

    while(t2){
        Attach(t1->coef*t2->coef,t1->expon+t2->expon, &Rear);
        t2 = t2->link;
    }

    t1 = t1->link;
    while(t1){
        t2 = P2;
        Rear = P;

        while(t2){
            e = t1->expon + t2->expon;
            c = t1->coef * t2->coef;
            while(Rear->link && Rear->link->expon > e){          //????????С
                Rear = Rear->link;
            }
            if(Rear->link && Rear->link->expon == e){
                if(Rear->link->coef + c){
                    Rear->link->coef += c;

                }
                else{
                    t = Rear->link;
                    Rear->link = t->link;
                    free(t);
                }

            }
            else{
                t = (Polynomial)malloc(sizeof(struct PolyNode));
                t->coef = c; t->expon = e;
                t->link = Rear->link;
                Rear->link = t;
                Rear = Rear->link;
            }
            t2 = t2->link;
        }
        t1 = t1->link;
    }
    t2 = P;
    P = P->link;
    free(t2);

    return P;
}

void main(){
    Polynomial P1,P2,PP,PS;

    P1 = ReadPoly();
    P2 = ReadPoly();

    PP = Mult(P1, P2);
    Print_Poly(PP);

    PS = Add(P1, P2);
    Print_Poly(PS); 
    
}
