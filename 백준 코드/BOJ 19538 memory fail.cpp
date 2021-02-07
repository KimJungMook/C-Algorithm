#include<stdio.h>
#include<stdlib.h>
/* BOJ 195338 메모리 초과 난 코드 */

int* arr; // 몇분인지 체크하는 배열
int* first; // 루머를 퍼트린 사람을 넣는 배열   
vector <int> check[2000002]
int* arr2;
int main()
{
	int minute=0;
	int minus=0;
	int num;
	int k;  // 최초 루머의 수 
	int l=0; // 루머 최초 퍼트린 사람 수
	int thing;
	int fin=0; // break를 위해서 
	int sum=0;
	int i,j;
	scanf("%d",&num);
	arr=(int*)malloc(sizeof(int)*num); //N
	first=(int*)malloc(sizeof(int)*num); //N
	arr2=(int*)malloc(sizeof(int)*num); //N
	int point;
	for(i=0;i<num;i++)
	{
		while(1)
		{	
			point=0;
			scanf("%d",&point);
			if(point==0)
				break;
			for(j=0;j<num;j++)
			{
				if(j+1==point)
				{
					check[i].insert(j,-1);
				}	
				check[i].insert(j,0);
			}
		}
		check[i].insert(i,1);
	}		// 여기 까지 입력을 다 받음. 1은 자기 자신 행,열 -1은 1로 바뀔거
	
	scanf("%d",&k);

	while(1)
	{
		scanf("%d",&first[l]);	// 맨처음 소문 믿는 사람 들어가는 곳
		l++; // 그게 몇명인지 카운트 
		if(l==k) // 맞으면 탈출 
			break;
	}

	for(i=0;i<num;i++)
	{
		minus=0;
		for(j=0;j<num;j++)
		{
			if(check[i][j]==0)
				minus++;
			if(minus==num-1)  // 아예 안되는 사람 체크
			{
				arr2[i]=1;
				arr[i]=-1;
			}
		}
	}
	for(i=0;i<k;i++)
	{
		arr[first[i]-1]=0; // 맨처음 소문 믿은 사람은 0분
		arr2[first[i]-1]=1; // 맨처음 사람 체크 0분으로 체크 하기 위해 하는 작업   
	}
while(1)
{
	thing=0;
	minute++;
	for(i=0;i<num;i++)
	{
		for(j=0;j<k;j++)
		{
			if(check[i][first[j]-1]==-1)
				check[i][first[j]-1]=1;
		}
	}	

	for(i=0;i<num;i++)
	{
		sum=0;
		for(j=0;j<num;j++)
		{
			sum+=check[i][j];
		}
		if(sum>0)
		{
			if(arr2[i]==0)
			{
				arr[i]=minute; // 시간 측정
				first[thing++]=i+1; // 다음 소문 믿은 사람 교체
				arr2[i]=1; // 체크하는 거 on으로 바꾸기.
				if(thing>=num)
					thing=thing-1;
			}
		}
	}
	k=thing;
	if(k==0)
		break;
}

for(i=0;i<num;i++)
{
	printf("%d ",arr[i]);
}

free(arr2);
free(first);
free(arr);
for(int i=0;i<num;i++)
{
	free(check[i]);
}
free(check);
}



	