/* 커서로 만든 연결리스트 알고리즘 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Member.h"
#include "ArrLinkedList.h"
char mstring[100][100]={
        "머리에 노드를 삽입", "꼬리에 노드를 삽입","머리 노드를 삭제",
        "꼬리 노드를 삭제", "선택한 노드를 출력", "선택한 노드를 삭제",
        "번호로 검색", "이름으로 검색", "모든 노드를 출력",
        "모든 노드를 삭제"
    };
/* 삽입할 레코드의 인덱스를 구한 다음 반환 */
static Index GetIndex (List *list)
{
    if(list->deleted==Null) /* 삭제할 레코드가 없는 경우 */
        return ++(list->max); /* max값을 하나를 더한다. */
    else
    {
        Index rec=list->deleted;
        list->deleted=list->n[rec].Dnext;
        return rec;
    }
}
/* 지정된 레코드를 삭제 리스트에 등록 */
static void DeleteIndex(List *list,Index idx)
{
    if(list->deleted==Null) /* 삭제할 레코드가 없는 경우 */
    {
        list->deleted=idx;
        list->n[idx].Dnext=Null;
    }
    else
    {
        Index ptr= list->deleted;
        list->deleted=idx;
        list->n[idx].Dnext=ptr;
    }
}
/* n이 가르키는 노드의 각 멤버에 값을 설정 */
static void SetNode(Node *n,const Member *x,Index next)
{
    n->data=*x; /* 데이터 */
    n->next=next; /* 다음 노드에 대한 포인터 */
}
/* 연결 리스트를 초기화 */
void Initialize(List *list,int size)
{
    list->n=(Node*)calloc(size,sizeof(Node));
    list->head=Null; /* 머리 노드 */
    list->crnt=Null; /* 선택한 노드 */
    list->max=Null;
    list->deleted=Null;
}
/* compare 함수로 x와 일치하는 노드 검색 */
Index search(List* list,const Member *x,int compare(const Member *x,const Member *y))
{
    Index ptr= list->head;
    while(ptr!=Null)
    {
        if(compare(&list->n[ptr].data,x)==0)
        {
            list->crnt=ptr;
            return ptr; /* 검색 성공 */
        }
        ptr=list->n[ptr].next;
    }
    return Null; /* 검색 실패 */
}
/* 머리에 노드를 삽입 */
void InsertFront(List* list,const Member *x)
{
    Index ptr= list->head;
    list->head=list->crnt=GetIndex(list);
    SetNode(&list->n[list->head],x,ptr);
}
/* 꼬리에 노드를 삽입 */
void InsertRear(List *list,const Member *x)
{
    if(list->head==Null) /* 비어 있는 경우 */
        InsertFront(list,x); /* 머리에 삽입 */
    else
    {
        Index ptr=list->head;
        while(list->n[ptr].next != Null)
        ptr=list->n[ptr].next;
        list->n[ptr].next=list->crnt=GetIndex(list);
        SetNode(&list->n[list->n[ptr].next],x,Null);
    }
}
/* 머리 노드를 삭제 */
void RemoveFront(List* list)
{
    if(list->head != Null)
    {
        Index ptr=list->n[list->head].next;
        DeleteIndex(list,list->head);
        list->head=list->crnt=ptr;
    }
}
/*  꼬리 노드를 삭제 */
void RemoveRear(List *list)
{
    if(list->head != Null)
    {
        if(list->n[list->head].next==Null) /*  노드가 1개만 있으면 */
            RemoveFront(list); /* 머리 노드를 삭제 (머리노드 == 꼬리노드 ) */
        else
        {
            Index ptr= list->head;
            Index pre;
            while(list->n[ptr].next != Null)
            {
                pre=ptr;
                ptr=list->n[ptr].next;
            }
            list->n[pre].next=Null;
            DeleteIndex(list,ptr);
            list->crnt=pre;
        }
    }
}
/* 선택한 노드를 삭제 */
void RemoveCurrent(List* list)
{
    if(list->head!=Null)
    {
        if(list->crnt == list->head) /* 머리 노드가 선택되어 있다면 */
         RemoveFront(list); /* 머리 노드를 삭제 */
        else
        {
            Index ptr=list->head;
            while(list->n[ptr].next!=list->crnt)
                ptr=list->n[ptr].next;
            list->n[ptr].next=list->n[list->crnt].next;
            DeleteIndex(list,list->crnt);
            list->crnt=ptr;
        }
    }
}
/* 모든 노드를 삭제 */
void Clear(List* list)
{
    while(list->head!=Null) /* 텅 빌 때까지 */
        RemoveFront(list); /* 머리 노드를 삭제 */
    list->crnt=Null;
}
/* 선택한 노드의 데이터를 출력 */
void PrintCurrent(const List *list)
{
    if(list->crnt==Null)
        printf("선택한 노드가 없습니다.");
    else
        PrintMember(&list->n[list->crnt].data);
}
/* 선택한 노드의 데이터를 출력(줄 바꿈 문자 추가) */
void PrintlnCurrent(const List* list)
{
    PrintCurrent(list);
    putchar('\n');
}
/* 모든 노드의 데이터를 출력 */
void Print(const List* list)
{
    if(list->head==Null)
        puts("노드가 없습니다.");
    else
    {
        Index ptr=list->head;
        puts("[ 모두 보기]");
        while(ptr!=Null)
        {
            PrintLnMember(&list->n[ptr].data);
            ptr=list->n[ptr].next; /* 다음 노드 */
        }
    }
}
/* 연결 리스트 종료 */
void Terminate(List *list)
{
    Clear(list);
    free(list->n);
}

typedef enum{
    TERMINATE,INS_FRONT,INS_REAR,RMV_FRONT,RMV_REAR,PRINT_CRNT,
    RMV_CRNT,SRCH_NO,SRCH_NAME,PRINT_ALL,CLEAR
}Menu;

Menu SelectMenu(void)
{
    int i,ch;
    do
    {
        for(i=TERMINATE;i<CLEAR;i++)
        {
            printf("(%2d) %s",i+1,mstring[i]);
            if((i%3)==2)
                putchar('\n');
        }
        printf("(0)종료: ");
        scanf("%d",&ch);
    } while (ch<TERMINATE || ch>CLEAR);
    return (Menu)ch;
}

void PrintMember(const Member *x)
{
    printf("%d %s",x->no,x->name);
}
int MemberNameCmp(const Member *x,const Member *y)
{
    return strcmp(x->name,y->name);
}

Member ScanMember(const char *message,int sw)
{
    Member temp;
    printf("%s하는 데이터를 입력하세요\n",message);
    if(sw & MEMBER_NO) 
    {
        printf("번호: "); 
        scanf("%d",&temp.no);
    } 
    if(sw & MEMBER_NAME) 
    {
        printf("이름: "); 
        scanf("%s",temp.name);
    }
    return temp;
}
void PrintLnMember(const Member *x)
{
    printf("%d %s\n",x->no,x->name);
}

int MemberNoCmp(const Member *x,const Member *y)
{
    return x->no < y->no ? -1 : x->no > y->no ? 1:0;
}

int main()
{
    Menu menu;
    List list;
    Initialize(&list,30);
    do
    {
        Member x;
        switch (menu=SelectMenu())
        {
        case INS_FRONT: /* 머리에 노드를 삽입 */
            x=ScanMember("머리에 삽입",MEMBER_NO | MEMBER_NAME);
            InsertFront(&list,&x);
            break;
        case INS_REAR: /* 꼬리에 노드를 삽입 */
            x=ScanMember("꼬리에 삽입",MEMBER_NO | MEMBER_NAME);
            InsertRear(&list,&x); 
        case RMV_FRONT: /* 머리 노드를 삭제 */  
            RemoveFront(&list);
            break;
        case RMV_REAR: /* 꼬리 노드를 삭제 */
            RemoveRear(&list);
            break;
        case PRINT_CRNT: /* 선택한 노드의 데이터를 출력 */
            PrintlnCurrent(&list);
            break;
        case RMV_CRNT: /* 선택한 노드를 삭제 */
            RemoveCurrent(&list);
            break;
        case SRCH_NO:/* 번호로 검색 */
            x=ScanMember("검색",MEMBER_NO);
            if(search(&list,&x,MemberNoCmp)!=Null)
                PrintlnCurrent(&list);
            else
                puts("그 번호의 데이터가 없습니다.");
            break;
        case SRCH_NAME: /* 이름으로 검색 */
            x=ScanMember("검색",MEMBER_NAME);
                if(search(&list,&x,MemberNameCmp)!=Null)
                    PrintlnCurrent(&list);
                else
                    puts("그 이름의 데이터가 없습니다.");
                break;
        case PRINT_ALL: /* 모든 노드의 데이터를 출력 */
            Print(&list);
            break;
        case CLEAR:
            Clear(&list);
            break;
        }
    } while (menu!=TERMINATE);
    Terminate(&list);
    return 0;
}