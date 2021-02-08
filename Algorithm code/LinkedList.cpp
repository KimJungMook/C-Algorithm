/* 링크드 리스트로 알고리즘 나타내기 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
    int no;
    char name[20];
}Member;
#define MEMBER_NO 1
#define MEMBER_NAME 2
/* ----- 노드 ----- */
typedef struct __node{
    Member data;
    struct __node *next;
}Node;

/* ---연결 리스트 ---*/
typedef struct{
    Node *head; /* 머리 노드에 대한 포인터 */
    Node *crnt; /* 선택한 노드에 대한 포인터 */
}List;

typedef enum{
    TERMINATE,INS_FRONT,INS_REAR,RMV_FRONT,RMV_REAR,PRINT_CRNT,
    RMV_CRNT,SRCH_NO,SRCH_NAME,PRINT_ALL,CLEAR
}Menu;
char mstring[100][100]={
    "머리에 노드를 삽입", "꼬리에 노드를 삽입", "머리 노드를 삭제",
    "꼬리 노드를 삭제", "선택한 노드를 출력",   "선택한 노드를 삭제",
    "번호로 검색"  ,      "이름으로 검색" ,       "모든 노드를 출력",
    "모든 노드를 삭제",
    };

void Initialize(List *list); // 연결 리스트를 초기화
Node *search(List *list,const Member *x,int compare(const Member *x,const Member *y));
/* 함수 compare로 x와 같은 노드를 검색 */
void InsertFront(List *list,const Member *x); // 머리에 노드를 삽입
void InSertRear(List *list,const Member *x); //꼬리에 노드를 삽입
void RemoveFront(List *list); // 머리 노드를 삭제
void RemoveRear(List *list); // 꼬리 노드를 삭제 
void RemoveCurrent(List *list); // 선택한 노드를 삭제
void Clear(List *list); // 모든 노드를 삭제 
void PrintCurrent(const List *list); // 선택한 노드의 데이터를 출력 
void PrintlnCurrent(const List *list); // 선택한 노드의 데이터를 출력(줄 바꿈 문자 포함)
void Print(const List *list); // 모든 노드의 데이터를 리스트 순서대로 출력 
void Terminate(List *list); // 연결 리스트 종료  

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

int MemberNoCmp(const Member *x,const Member *y)
{
    return x->no < y->no ? -1 : x->no > y->no ? 1:0;
}
void PrintlnMember(const Member *x)
{
    printf("%d %s\n",x->no,x->name);
}
static Node *AllocNode() // 노드를 동적으로 생성
{
    return (Node*)calloc(1,sizeof(Node));
}
/* n이 가르키는 노드의 각 멤버에 값을 설정 */
static void SetNode(Node *n,const Member *x,Node *next)
{
    n->data= *x; /* 데이터 */
    n->next= next; /* 위쪽 포인터 */
}

void Initialize(List *list)
{
    list->head=NULL; // 머리 노드
    list->crnt=NULL; // 선택한 노드
}
/* compare 함수를 사용해 x를 검색합니다. */
Node* search(List *list,const Member *x,int compare(const Member *x,const Member *y))
{
    Node *ptr=list->head;
    while(ptr!=NULL)
    {
        if(compare(&ptr->data,x)==0) // 키 값이 같은 경우
        {
            list -> crnt = ptr;
            return ptr; // 검색 성공
        }
        ptr=ptr->next; //다음 노드를 선택
    }
    return NULL;
}

void InsertFront(List* list,const Member *x) // 머리에 노드를 삽입하는 함수
{
    Node *ptr=list->head;
    list->head=list->crnt=AllocNode();
    SetNode(list->head,x,ptr);
}

void InsertRear(List *list,const Member *x) // 꼬리에 노드를 삽입하는 함수
{
    if(list->head==NULL) /* 비어 있는 경우 */
        InsertFront(list,x); /* 머리에 삽입 */
    else
    {
        Node* ptr=list->head;
        while(ptr->next!=NULL)
            ptr=ptr->next;
        ptr->next=list->crnt=AllocNode();
        SetNode(ptr->next,x,NULL);
    }
}
void RemoveFront(List* list) // 머리 노드를 삭제하는 함수
{
    if(list->head!=NULL)
    {
        Node *ptr=list->head->next; /* 두 번째 노드에 대한 포인터 */
        free(list->head); /* 머리 노드를 메모리 해제 */
        list->head=list->crnt=ptr;  /* 새로운 머리 노드 */
    }
}


void RemoveRear(List *list)
{
    if(list->head!=NULL)
    {
        if((list->head)->next==NULL) /* 노드가 1개만 있는 경우라면 */
            RemoveFront(list);/* 머리 노드= 꼬리 노드 머리노드 삭제 */
        else
        {
            Node *ptr=list->head;
            Node *pre;
            while(ptr->next != NULL)
            {
                pre=ptr;
                ptr=ptr->next;
            }
            pre->next=NULL; /* pre는 꼬리노드로부터 두 번째 노드  */
            free(ptr); // ptr은 꼬리 노드이므로 메모리 해제를 통해 삭제
            list->crnt=pre;
        }
    }
}
/* 선택한 노드를 삭제하는 함수 */
void RemoveCurrent(List* list)
{
    if(list->head!=NULL)
    {
        if(list->crnt==list->head) // 머리 노드를 선택한 상태라면
            RemoveFront(list); // 머리 노드를 삭제
        else
        {
            Node* ptr=list->head;
            while(ptr->next!=list->crnt)
                ptr=ptr->next;
            ptr->next = list->crnt->next;
            free(list->crnt);
            list->crnt=ptr;
        }
    }
}
/* 모든 노드를 삭제 */
void Clear(List* list)
{
    while(list->head != NULL) // 텅빌 때 까지
        RemoveFront(list); // 머리 노드를 삭제
    list->crnt=NULL;
}
/* 선택한 노드의 데이터를 출력 */
void PrintCurrent(const List* list)
{
    if(list->crnt==NULL)
        printf("선택한 노드가 없습니다.");
    else   
        PrintMember(&list->crnt->data);
}
/* 선택한 노드의 데이터를 출력(줄 바꿈 문자 포함) */
void PrintlnCurrent(const List *list)
{
    PrintCurrent(list);
    putchar('\n');
}
/* 모든 노드의 데이터를 리스트 순으로 출력하는 함수 */
void Print(const List* list)
{
    if(list->head==NULL)
        puts("노드가 없습니다.");
    else
    {
        Node* ptr=list->head;
        puts("[ 모두 보기 ] ");
        while(ptr!=NULL)
        {
            PrintlnMember(&ptr->data);
            ptr=ptr->next;
        }
    }
}
/* 연결 리스트를 종료하는 함수 */
void Terminate(List* list)
{
    Clear(list); // 모든 노드를 삭제
}
/* 메뉴 선택 */
Menu SelectMenu(void)
{
    int i,ch;
    char mstring[][100]={
    "머리에 노드를 삽입", "꼬리에 노드를 삽입", "머리 노드를 삭제",
    "꼬리 노드를 삭제", "선택한 노드를 출력",   "선택한 노드를 삭제",
    "번호로 검색"  ,      "이름으로 검색" ,       "모든 노드를 출력",
    "모든 노드를 삭제",
    };
    do
    {
        for(i=TERMINATE;i<CLEAR;i++)
        {
            printf("(%2d) %s ",i+1,mstring[i]);
            if((i%3)==2)
                putchar('\n');
        }
        printf("(0) 종료: ");
        scanf("%d",&ch);
    } while(ch<TERMINATE || ch>CLEAR);

    return (Menu)ch;
}

int main()
{
    Menu menu;
    List list;
    Initialize(&list);
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
            break;
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
        case SRCH_NO: /* 번호로 검색 */
            x=ScanMember("검색",MEMBER_NO);
            if(search(&list,&x,MemberNoCmp)!=NULL)
                PrintlnCurrent(&list);
            else 
                puts("그 번호의 데이터가 없습니다.");
            break;
        case SRCH_NAME: /* 이름으로 검색 */
            x=ScanMember("검색",MEMBER_NAME);
            if(search(&list,&x,MemberNameCmp)!=NULL)
                PrintlnCurrent(&list);
            else 
                puts("그 이름의 데이터가 없습니다.");
            break;
        case PRINT_ALL: /* 모든 노드의 데이터를 출력 */
            Print(&list);
            break;
        case CLEAR: /* 모든 노드를 삭제 */
            Clear(&list);
            break;
        }
    } while (menu != TERMINATE);
    Terminate(&list);

    return 0;
    
}
