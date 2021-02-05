/* 비트 벡터 집합 */
#include<stdio.h>
typedef unsigned long BitSet;
#define BitSetNull (BitSet) 0
#define BitSetBits 32
#define Setof(no) ((BitSet)1 << (no))
enum {ADD,RMV,SCH};

int IsMember(BitSet s,int n);
void Add(BitSet *s,int n);
void Remove(BitSet *s,int n);
int Size(BitSet s);
void Print(BitSet s);
void Println(BitSet s);

int IsMember(BitSet s,int n)
{
    return s & Setof(n);
}

void Add(BitSet *s,int n)
{
    *s |= Setof(n);
}

void Remove(BitSet *s,int n)
{
    *s &= ~Setof(n);
}

int Size(BitSet s)
{
    int n=0;
    for(;s!=BitSetNull;n++)
        s &=s-1;
    return n;
}

void Print(BitSet s)
{
    int i;
    printf("{");
    for(i=0;i<BitSetBits;i++)
        if(IsMember(s,i))
            printf("%d ",i);
    printf("}");
}

void Println(BitSet s)
{
    Print(s);
    putchar('\n');
}

int scan_data(int sw)
{
    int data;
    switch (sw)
    {
    case ADD:
        printf("추가할 데이터");
        break;
    case RMV:
        printf("삭제할 데이터");
        break;
    case SCH:
        printf("검색할 데이터");
        break;
    }
    scanf("%d",&data);
    return data;
}

int main()
{
    BitSet s1=BitSetNull;
    BitSet s2=BitSetNull;
    while(1)
    {
        int m,x,idx;
        printf("s1= "); Println(s1);
        printf("s2= "); Println(s2);
        printf("(1)s1에 추가 (2)s1에서 삭제 (3)s1에서 검색 (4)s1<-s2 (5)여러연산\n"
        "(6)s2에 추가 (7)s2에서 삭제 (8)s2에서 검색 (9)s2<-s1 (0) 종료: ");
        scanf("%d",&m);
        if(m==0) break;
        switch (m)
        {
        case 1: 
            x=scan_data(ADD); Add(&s1,x);
            break;
        case 2:
            x=scan_data(RMV); Remove(&s1,x);
            break;
        case 3:
            x=scan_data(SCH); idx=IsMember(s1,x);
            printf("s1에 들어있%s.\n",idx>=0? "습니다" : "지 않습니다");
            break;
        case 4:
            s1=s2; 
            break;
        case 5:
            printf("s1==s2 %s\n",s1==s2? "true": "false");
            printf("s1&s2= "); Println(s1&s2);
            printf("s1 || s2= "); Println(s1|s2);
            printf("s1-s2= "); Println(s1&~s2);
            break;
        case 6: 
            x=scan_data(ADD); Add(&s2,x); break;
            break;
        case 7:
            x=scan_data(RMV); Remove(&s1,x);
           break;
        case 8:
            x=scan_data(SCH); idx=IsMember(s1,x);
            printf("s1에 들어있%s.\n",idx>=0? "습니다" : "지 않습니다");
            break;
        case 9:
            s2=s1;
            break;
        }
    }

}
    
