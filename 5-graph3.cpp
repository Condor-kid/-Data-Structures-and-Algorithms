#include<iostream>
#include<algorithm>
using namespace std;
#define MAX 101
//dijkstra算法
struct Graph{
    int vex[MAX];
    int vexnum;
    int edgenum;
    int matrix[MAX][MAX];
};
struct Edge{
    int first;
    int second;
    int val;
};
//vs：起始顶点
//dist：长度数组，dist[i]是顶点vs到顶点i的最短路径长度
void dijkstra(Graph g,int vs,int *dist)
{
    int flag[MAX];//flag[i]=1表示最短路径已经获取成功
    for(int i=0;i<g.vexnum;i++)
    {
        flag[i]=0;//所有点的最短路径尚未获取
        dist[i]=g.matrix[vs][i];//点vs到点i的边权值
    }
    flag[vs]=1;
    dist[vs]=0;
    int min;//遍历一次的最小值
    int pos;//prev的地址
    int temp;//临时值
    //遍历点数-1次，每次找出一个顶点的最短路径
    for(int i=1;i<g.vexnum;i++)
    {
        //寻找在未获取最短路径的顶点中，找到离vs最近的顶点pos
        min=INT_MAX;
        for(int j=0;j<g.vexnum;j++)
        {
            if(flag[j]==0&&dist[j]<min)
            {
                min=dist[j];
                pos=j;
            }
        }
        flag[pos]=1;//标记顶点pos为已经获取到最短路径
        for(int j=0;j<g.vexnum;j++)
        {
            //修正当前最短路径
            temp=(g.matrix[pos][j]==INT_MAX)?INT_MAX:(min+g.matrix[pos][j]);
            if(flag[j]==0&&(temp<dist[j]))
            {
                dist[j]=temp;
            }
        }
    }
}
int main()
{
    Graph g;
    cout<<"输入点和边的数量"<<endl;
    cin>>g.vexnum>>g.edgenum;
    for(int i=0;i<g.vexnum;i++)
    {
        for(int j=0;j<g.vexnum;j++)
        {
            g.matrix[i][j]=INT_MAX;
        }
    }
    cout<<"输入点-点-边权值"<<endl;
    for(int i=0;i<g.edgenum;i++)
    {
        int a,b,c;
        cin>>a>>b>>c;
        g.matrix[a][b]=c;
        g.matrix[b][a]=c;//无向图
        //如果是有向图则删去上面一行即可
    }
    cout<<"输入起始点："<<endl;
    int start;
    cin>>start;
    int dist[g.vexnum]={0};
    dijkstra(g,start,dist);
    for(int i=0;i<g.vexnum;i++)
    {
        cout<<start<<"到"<<i<<"的最短路径为"<<dist[i]<<endl;
    }
    system("pause");
    return 0;
}
