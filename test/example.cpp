#include<stdio.h>
#include<stdlib.h>

typedef struct 
{
    int max;
    int num;
    int *set;
}IntSet;

int initialize(IntSet *s,int max);
int IsMember(const IntSet *s,int n);
void add(IntSet *s,int n);
int Capacity(const IntSet *s);
int Size(const IntSet *s);
void Assign(IntSet *s1,const IntSet *s2);
int Equal(const IntSet *s1,const IntSet *s2);
IntSet* Union(IntSet *s1,const IntSet *s2,const IntSet *s3);
IntSet* Intersection(IntSet *s1,const IntSet *s2,const IntSet *s3);
IntSet* Difference(IntSet *s1,const IntSet *s2,const IntSet *s3);
void Print(const IntSet *s);
void Println(const IntSet *s);
void Terminate(IntSet *s);

int Initialize(IntSet *s,int max)
{
    s->num=0;
    if((s->set=(int*)calloc(max,sizeof(int)))==NULL)
    {
        s->max=0;
        return -1;
    }
    s->max=max;
    return 0;
}

int IsMember(const IntSet *s,int n)
{
    int i;
    for(i=0;i<s->num;i++)
    {
        if(s->set[i]==n)
            return i;
    }
    return -1;
}

void Add(IntSet *s,int n)
{
    if(s->num < s->max && IsMember(s,n)==-1)
        s->set[s->num++]=n;
}

void Remove(IntSet *s,int n)
{
    int idx;
    if((idx=IsMember(s,n))!=-1)
    {
        s->set[idx]=s->set[--s->num];
    }
}

int Capacity(const IntSet *s)
{
    return s->max;
}

int Size(const IntSet *s)
{
    return s->num;
}

void Assign(IntSet *s1,const IntSet *s2)
{
    int i;
    int n=(s1->max < s2->num) ? s1->max : s2->num; /* 복사하는 원소의 개수 */
    for(i=0;i<n;i++)
        s1->set[i]=s2->set[i];
    s1->num=n;
}

int Equal(const IntSet *s1,const IntSet *s2)
{
    int i,j;
    if(Size(s1)!=Size(s2))
        return 0;
    for(i=0;i<s1->num;i++)
    {
        for(j=0;j<s2->num;j++)
            if(s1->set[i]==s2->set[j])
                break;
         if(j==s2->num)
             return 0;          
    }
    return 1;
}

IntSet *Union(IntSet *s1,const IntSet *s2,const IntSet *s3)
{
    int i;
    Assign(s1,s2);
    for(i=0;i<s3->num;i++)
    {
        Add(s1,s3->set[i]);
    }
    return s1;
}

IntSet *Intersection(IntSet *s1,const IntSet *s2,const IntSet *s3)
{
    int i,j;
    s1->num=0;
    for(i=0;i<s2->num;i++)
        for(j=0;j<s3->num;j++)
            if(s2->set[i]==s3->set[j])
                Add(s1,s2->set[i]);
    return s1;
}

IntSet* Difference(IntSet *s1,const IntSet *s2,const IntSet *s3)
{
    int i,j;
    s1->num=0;
    for(i=0;i<s2->num;i++)
    {
        for(j=0;j<s3->num;j++) 
            if(s2->set[i]==s3->set[j])
                break;
          if(j==s3->num)
            Add(s1,s2->set[i]);
    }
    return s1;
}

void Print(const IntSet *s)
{
    int i;

    printf("{");
    for(i=0;i<s->num;i++)
        printf("%d ",s->set[i]);
    printf("}");
}

void Println(const IntSet *s)
{
    Print(s);
    putchar('\n');
}

void Terminate(IntSet *s)
{
    if(s->set != NULL)
    {
        free(s->set);
        s->max=s->num=0;
    }
}

int main()
{
    IntSet s1,s2,s3;
    Initialize(&s1,24);
    Initialize(&s2,24);
    Initialize(&s3,24);

    Add(&s1,10);
    Add(&s1,15);
    Add(&s1,20);
    Add(&s1,25);

    Assign(&s2,&s1);
    Add(&s2,12);
    Remove(&s2,20);
    Assign(&s3,&s2);
    printf("s1= "); Println(&s1);
    printf("s2= "); Println(&s2);
    printf("s3= "); Println(&s3);

    printf("집합 s1에 15가 들어있%s\n",IsMember(&s1,15) > 0 ? "습니다." : "지 않습니다.");
    printf("집합 s2에 25가 들어있%s\n",IsMember(&s2,25) > 0 ? "습니다." : "지 않습니다.");
    printf("집합 s1에 s2가 서로 같%s\n",Equal(&s1,&s2) > 0 ? "습니다." : "지 않습니다.");
    printf("집합 s2에 s3가 서로 같%s\n",Equal(&s2,&s3) > 0 ? "습니다." : "지 않습니다.");\


    Terminate(&s1);
    Terminate(&s2);
    Terminate(&s3);
    return 0;
}