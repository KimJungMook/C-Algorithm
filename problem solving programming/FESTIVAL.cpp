#include<stdio.h>
int input_pay[1001];
double finish[1001];
void minimum_pay(int input_pay[],int Test_case,int Test_day,int num);
int main()
{
    int first_num;
    int k=first_num;
    int Test_case,Test_day;
    int num=0;
    scanf("%d",&first_num);
    while(first_num--)
    {
        Test_case=0,Test_day=0;
        scanf("%d %d",&Test_case,&Test_day);
        for(int i=0;i<Test_case;i++)
        {
            scanf("%d",&input_pay[i]);
        }
        minimum_pay(input_pay,Test_case,Test_day,num);
        num++;
    }
    for(int i=0;i<Test_day;i++)
    {
        printf("%.10f\n",finish[i]);
    }
    return 0;
}

void minimum_pay(int input_pay[],int Test_case,int Test_day,int num)
{
    int k=Test_day;
    double minimum;
    double sum=0;
    while(Test_case!=Test_day)
    {
        for(int i=0;i<(Test_case-Test_day+1);i++)
        {
            sum=0;
            for(int j=0;j<Test_day;j++)
            {
                sum+=input_pay[i+j];
            }
            if(i==0 && k==Test_day)
            {
                minimum=sum/Test_day;
            }
            if(minimum>(sum/Test_day))
            {
                minimum=(sum/Test_day);
            }
        }
        Test_day++;
    }
    finish[num]=minimum;
}