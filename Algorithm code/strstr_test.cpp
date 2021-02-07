/* strstr함수 사용 but, 시간 복잡도를 많이 잡아먹기에 주로 쓰진 않는다. */

#include<stdio.h>  
#include<string.h>

int main()
{
    char s1[256], s2[256];
    char *p;
    puts("strstr 함수");
    printf("텍스트 : ");
    scanf("%s",s1);
    printf("패턴: ");
    scanf("%s",s2);
    p=strstr(s1,s2); /* 문자열 s1에서 문자열 s2를 검색 */
    if(p==NULL)
        printf("텍스트에 패턴이 없습니다.\n");
    else
    {
        int ofs=p-s1;
        printf("\n%s\n",s1);
        printf("%*s| \n",ofs,"");
        printf("%*s%s\n",ofs,"",s2);
    }

    return 0;
}