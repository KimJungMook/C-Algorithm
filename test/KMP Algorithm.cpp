/* KMP법 알고리즘  */

int kep_match(const char a[],const char pat[])
{
    int pt=1; /* txt 커서 */
    int pp=0;  /* pat 커서 */
    int skip[1024]; /* 건너뛰기 표 */

    skip[pt]=0;
    while(pat[pt]!='\0') // 표 만들기 
   {
        if(pat[pt]==pat[pp])
            skip[++pt]=++pp;
        else if(pp==0)
            skip[++pt]=pp;
        else
            pp=skip[pp];
    } 
    pt=pp=0;
    while(txt[pt]!='\0' && pat[pp]!='\0') // 검색하기 
    {
        if(txt[pt]==pat[pp])
        {
            pt++;
            pp++;
        }
        else if(pp==0)
            pt++;
        else
            pp=skip[pp];
    }
    if(pat[pp]=='\0')
        return pt-pp;
    
    return -1;
}