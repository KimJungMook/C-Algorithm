#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
vector<pair<int,int>> v;
vector <int> count;
int main()
{
    int Test_case;
    int n,m;
    int a,b;
    scanf("%d",&Test_case);
    while(Test_case--)
    {
        v.clear();
        scanf("%d %d",&n,&m);
        for(int i=0;i<m;i++)
        {
            scanf("%d %d",a,b);
            v.push_back(make_pair(a,b));
        }
        sort(v.begin(),v.end());
    }

}

int meeting(vector<pair<int,int>>&v,int num,int m)
{
    for(int i=num;i<m;i++)
    {
        for(int j=num;j<m;j++)
        {
            if(v[i].first!=v[j].first && v[i].first!=v[j].second)
            {
                meeting(vector<pair<int,int>>&v,j,m);
            }
            
        }
    }
}