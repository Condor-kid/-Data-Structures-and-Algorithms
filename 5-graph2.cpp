#include<iostream>
#include<algorithm>
#include<climits>
using namespace std;
//弗洛依德算法
struct Edge{
    int first;
    int second;
    int val;
};
int main()
{
    int n,m;//n个点，m条边
    cin>>n>>m;
    Edge kk[m];
    int matrix[n+1][n+1];
    for(int i=1;i<n+1;i++)
    for(int j=1;j<n+1;j++)
    if(i==j)
    {
        matrix[i][j]=0;
    }
    else
    {
        matrix[i][j]=1000;
    }
    
    for(int i=0;i<m;i++)
    {
        cin>>kk[i].first>>kk[i].second>>kk[i].val;
        matrix[kk[i].first][kk[i].second]=kk[i].val;
    }
    for(int k=1;k<n+1;k++)
    {
        for(int i=1;i<n+1;i++)
        {
            for(int j=1;j<n+1;j++)
            {
                if(matrix[i][j]>matrix[i][k]+matrix[k][j])
                {
                    matrix[i][j]=matrix[i][k]+matrix[k][j];
                }
            }
        }
    }
    for(int i=1;i<n+1;i++)
    {
        for(int j=1;j<n+1;j++)
        {
            cout<<matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    //Floyd算法
    system("pause");
    return 0;
}