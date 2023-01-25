#include<stdio.h>

int main()
{
    char c;
    int count=0;
    int d,i=0;
    char s[10];

     FILE *voroodi;
    voroodi= fopen("in.txt","r");

    while (1)
    {

    fclose(voroodi);
    for(int i=0;i<count;i++)
    {
        d=getchar();
        s[i]=d;

    }
    }

}