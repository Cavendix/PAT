#include<iostream>
#include<stdio.h>
using namespace std;

int main(void)
{
    int n,e;
    scanf("%d%d",&n,&e);
    int a[n][n]={};
    for(int i=0;i<e;i++)
    {
        int x,y,z;
        scanf("%d%d%d",&x,&y,&z);
        a[x-1][y-1]=z;
        a[y-1][x-1]=z;
    }
    long long m[n][n]={},t[n][n]={};
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==j)
            {
                m[i][j]=0;
                t[i][j]=0;
            }
            else if(i!=j&&a[i][j]==0)
            {
                m[i][j]=100000;
                t[i][j]=0;
            }
            else
            {
                m[i][j]=a[i][j];
                t[i][j]=1;
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            for(int k=0;k<n;k++)
            {
                if(i!=j&&i!=k&&j!=k&&m[j][i]!=100000&&m[i][k]!=100000&&m[j][k]>(m[j][i]+m[i][k]))
                {
                    m[j][k]=m[i][j]+m[i][k];
                    t[j][k]=t[j][i]*t[i][k];
                }
                if(i!=j&&i!=k&&j!=k&&m[j][i]!=100000&&m[i][k]!=100000&&m[j][k]==(m[j][i]+m[i][k]))
                {
                    t[j][k]+=t[j][i]*t[i][k];
                }
            }
        }
    }
    for(int i=0;i<n;i++)
    {
        double s=0;
        for(int j=0;j<n;j++)
        {
            for(int k=0;k<n;k++)
            {
                if(i!=j&&i!=k&&j!=k)
                {
                    if(m[j][i]+m[i][k]==m[j][k]){
                    double  q=t[j][i]*t[i][k];
                    s+=m[j][k]*(q/t[j][k]);
                    }
                }
            }
        }
        printf("%.3lf\n",s);
    }
    return 0;
}