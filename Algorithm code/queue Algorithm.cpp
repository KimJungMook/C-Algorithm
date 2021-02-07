/* BOJ 19538번 알고리즘 
너비 알고리즘 + 큐 알고리즘 + vector 
이해 다시 하기. */
#include<stdio.h>
#include<vector>
#include<queue>
#include<algorithm>
#define N 2000002
using namespace std;
vector<int> v[N];
int check[N];
int time[N];
queue<int> Q;
queue<int> SQ;
int main()
{
	for(int i=0;i<N;i++)
	{
		check[i]=-1;
	}
	int first_num;
	int num;
	int number;
	scanf("%d",&first_num);
	for(int i=1;i<=first_num;i++)
	{
		while(1)
		{
			num=0;
			scanf("%d",&num);
			if(num==0)	break;
			v[i].push_back(num);
		}
	}
	scanf("%d",&number);
	for(int i=0;i<number;i++)
	{
		int start=0;
		scanf("%d",&start);
		check[start]=0;
		Q.push(start);
	}
/* 큐 알고리즘 이거 잘 기억 해두기 */
	while(!Q.empty())
	{
		int cur=Q.front();
		Q.pop();
		for(int i=0;i<v[cur].size();i++)
		{
			int nx=v[cur][i];
			if(check[nx]!=-1) continue;
			int cnt=0;
			for(int j=0;j<v[nx].size();j++)
			{
				if(check[v[nx][j]]!=-1) cnt++;
			}
			if(v[nx].size()>cnt*2) continue;
			SQ.push(nx);
		}
		if(Q.empty())
		{
			while(!SQ.empty())
			{
				int node=SQ.front();
				SQ.pop();
				check[node]=check[cur]+1;
				Q.push(node);
			}
		}
	}
	for(int i=1;i<=first_num;i++)
	{
		printf("%d ",check[i]);
	}
}