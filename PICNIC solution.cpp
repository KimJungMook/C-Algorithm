#include<stdio.h>
#include<string.h>
int n,m;
bool areFriends[10][10];
int count[10]; 

int countPairings(bool taken[10])
{
    int firstFree=-1;
    for(int i=0;i<(n);i++)
    {
        if(!taken[i])
        {
            firstFree=i;
            break;
        }
    }
    if(firstFree==-1) return 1;
    int ret=0;
    for(int pairWith=(firstFree+1);pairWith<(n);pairWith++)
    {
        if(!taken[pairWith]&&areFriends[firstFree][pairWith])
        {
            taken[firstFree]=taken[pairWith]=true;
            ret+=countPairings(taken);
            taken[firstFree]=taken[pairWith]=false;
        }
    }
    return ret;
}

int main()
{
    int Test_case;
    int l=0;
    scanf("%d",&Test_case);
    while(Test_case--)
    {
        memset(areFriends,0,sizeof(areFriends));
        scanf("%d %d",&n,&m);
 
        for(int i=0;i<m;i++)
        {
            int a,b;
            scanf("%d %d",&a,&b);
            areFriends[a][b]=areFriends[b][a]=true;
        }
        bool taken[10];
        memset(taken,0,sizeof(taken));
        count[l++]=countPairings(taken);
    }
    for(int i=0;i<l;i++)
    {
        printf("%d\n",count[i]);
    }
}
