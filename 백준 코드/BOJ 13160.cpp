#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
vector <pair<int,int>> v;
vector <pair<int,int>> ary;
int u,maximum,position;
int main()
{
    int first_num;
    int first_input,second_input;
    scanf("%d",&first_num);
    for(int i=0;i<first_num;i++)
    {
        scanf("%d %d",&first_input,&second_input);
        v.push_back({first_input,-1});   //시작점에는 -1이라는 인덱스를 
        v.push_back({second_input,1});   // 끝점에는 1이라는 인덱스를 설정 해준다. 
        ary.push_back({first_input,second_input}); // 마지막 체크 할 때 필요한 벡터
    }
    sort(v.begin(),v.end()); // 정렬 해주기.
    for(int i=0;i<first_num*2;i++)
    {
        u+=v[i].second; 
        if(u<maximum)
        {
              maximum=u;
              position=v[i].first;    // -1을 계속 더한거에 마이너스를 붙인 값이 최대 클리크의 값.   
        }
    }
    printf("%d\n",(-maximum));
    for(int i=0;i<first_num;i++)
    {
        if(ary[i].first<=position && ary[i].second>=position)
            printf("%d ",i+1);      // 최대 클리크안에 들어 있는 거.
    }
}


/* 다시 한번더 보기 */