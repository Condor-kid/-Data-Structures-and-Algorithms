//用邻接表表示有向图,图的构造，图的打印，图的深度、广度优先搜索、普利姆算法、克鲁斯卡尔算法
#include<iostream>
#include<vector>
#include<queue>
#include<climits>
#include<algorithm>
using namespace std;
struct Kruskal_edge{
    int first;//一个点
    int second;//另一个点
    int val;//边权值
};
//邻接表表示法、邻接矩阵表示法
//边表结构
struct Edge{
    int val;//边的权值
    int adjvex;//这条边指向的哪个点
    Edge *next=NULL;//下一条边的指针
};
//顶点表结构
struct Vertex{
    int val;//顶点的权值
    Edge *firstedge=NULL;//第一条边
};
//图结构
struct Graph{
    Vertex graph[1000];//顶点的一维数组
    int numspot;//顶点数
    int numedge;//边数
};
void creategraph(Graph *g,int vex,int edge,vector<int> spot,int ans[][3])//传递点和边的数量,
{                                                                        //点构成的一维数组，点边关系的二维数组
    g->numedge=edge;
    g->numspot=vex;
    int len=spot.size();
    for(int i=0;i<len;i++)//初始化顶点
    {
        g->graph[i].val=spot[i];
    }
    //添加有向边
    for(int i=0;i<g->numedge;i++)//ans[i][0]、ans[i][1]、ans[i][2]
    {
        if(g->graph[ans[i][0]].firstedge==NULL)
        {
            g->graph[ans[i][0]].firstedge=new Edge;
            g->graph[ans[i][0]].firstedge->adjvex=ans[i][1];
            g->graph[ans[i][0]].firstedge->val=ans[i][2];
        }
        else//注意next代表的是下一个边的指针，所以当我们需要添加边的时候，是针对p->next进行添加
        {
            Edge *p=g->graph[ans[i][0]].firstedge;
            while(p->next!=NULL)//没有下一条边时，对下一条边进行添加
            {
                p=p->next;
            }
            p->next=new Edge;
            p->next->adjvex=ans[i][1];
            p->next->val=ans[i][2];
        }
    }
};
void printGraph(Graph *g)//打印表的结构
{
    int i=0;
    while(i<g->numspot)
    {
        if(g->graph[i].firstedge!=NULL)
        {
            cout<<g->graph[i].val<<endl;
            Edge *p=g->graph[i].firstedge;
            while(p!=NULL)
            {
                cout<<p->adjvex<<":"<<p->val<<" ";
                p=p->next;
            }
            cout<<endl;
        }
        i++;
    }
};
//深度优先搜索DFS
void DFS(Graph *g,int i,int *visited)
{
    cout<<g->graph[i].val<<endl;//从第i个顶点开始
    visited[i]=1;//标记
    Edge* p=g->graph[i].firstedge;
    while(p!=NULL)//如果第i个点有邻接点
    {
        int w=p->adjvex;
        if(visited[w]==0)//如果邻接点没有被访问
        {
            DFS(g,w,visited);//从第w个点找邻接点（深度）
        }
        if(p->next==NULL)//如果还有第二个邻接点，记录下来
        break;
        w=p->next->adjvex;
        p=p->next;
    }
};
void Graph_DFS(Graph *g)
{
    int visited[g->numspot];//辅助数组
    for(int i=0;i<g->numspot;i++)
    {
        visited[i]=0;
    }//初始化为0
    for(int i=0;i<g->numspot;i++)//从小到大遍历
    {
        if(visited[i]==0)
        {
            DFS(g,i,visited);
        }
    }
};
//广度优先搜索BFS
void BFS(Graph *g,int i,int *visited)
{
    cout<<g->graph[i].val<<endl;
    visited[i]=1;
    queue<int> q;
    q.push(i);//将i入队
    while(!q.empty())//队列为空就跳出
    {
        int w=q.front();//取队首
        q.pop();
        Edge *p=g->graph[w].firstedge;
        while(p!=NULL)//如果队首的位置的点有邻接点
        {
            int w=p->adjvex;//记录第一个邻接点
            if(visited[w]==0)
            {
                cout<<w<<endl;
                visited[w]=1;
                q.push(w);//将该邻接点入队
            }
            if(p->next==NULL)
            break;
            p=p->next;
            w=p->adjvex;//寻找i点的下一个邻接点，直到所有i的邻接点被找过（广度）
        }
        
    }
};
void Graph_BFS(Graph *g)
{
    int visited[g->numspot];//辅助数组
    for(int i=0;i<g->numspot;i++)
    {
        visited[i]=0;
    }//初始化为0
    for(int i=0;i<g->numspot;i++)//从小到大遍历
    {
        if(visited[i]==0)
        {
            BFS(g,i,visited);
        }
    }
};
int Find(int *parent,int final)
{
    while(parent[final]>=0)
    {
        final=parent[final];
    }
    return final;//返回终点
}
void Kruskal(Graph *g)//邻接表表示图传入，转成矩阵形式再用Kruskal算法
{
    Kruskal_edge kk[g->numedge];//克鲁斯卡尔算法的边集
    for(int i=0,j=0;i<g->numspot;i++)
    {
        Edge *p=g->graph[i].firstedge;
        while(p)
        {
            kk[j].first=i;
            kk[j].second=p->adjvex;
            kk[j].val=p->val;
            j++;
            p=p->next;
        }
    }//边集已经初始化完成
    for(int i=0;i<g->numedge;i++)
    {
        for(int j=i;j<g->numedge;j++)
        {
            if(kk[i].val>kk[j].val)
            {
                Kruskal_edge temp;
                temp=kk[i];
                kk[i]=kk[j];
                kk[j]=temp;
            }
        }
    }//按照边的权值从小到大排序
    int parent[g->numspot];//判断是否成环用的辅助数组
    for(int i=0;i<g->numspot;i++)
    {
        parent[i]=-1;
    }
    int m,n;
    for(int i=0;i<g->numedge;i++)//n个点，n-1条边足矣
    {
        m=Find(parent,kk[i].first);
        n=Find(parent,kk[i].second);
        if(m!=n)//如果没有到达同一终点，则没有成环
        {
            parent[m]=n;//加入边
            cout<<kk[i].first<<"-"<<kk[i].second<<"="<<kk[i].val<<endl;
        }
    }
}
//设置辅助数组closedge[]
//lowcost域:存放生成树顶点集合内顶点到生成树外各顶点的各边上的当前最小权值
//mst域：记录生成树顶点集合外各顶点距离集合内哪个顶点最近（即权值最小，对应生成树中的顶点）
//用邻接矩阵来整比较好理解
//需要写一个邻接表转邻接矩阵的算法,在主函数写算了
int main()
{
    Graph g;
    int vex,edge;//点和边的数量
    cin>>vex>>edge;
    vector<int> spot(vex);//记录点的权值
    for(int i=0;i<spot.size();i++)
    {
        cin>>spot[i];//第i个点的值
    }
    int ans[edge][3];//记录点之间的有向边以及权重
    for(int i=0;i<edge;i++)
    {
        cin>>ans[i][0]>>ans[i][1]>>ans[i][2];//依次输入顶点、指向点、边权重（也就是第n个点，指向第m个点，边的权值为k）
    }
    creategraph(&g,vex,edge,spot,ans);
    printGraph(&g);
    Kruskal(&g);
    system("pause");
    Graph_DFS(&g);
    Graph_BFS(&g);
    //转邻接矩阵表示，实现普利姆算法
    int len=g.numspot;//多少个点，矩阵多大

    int matrix[len][len];//邻接矩阵表示

    int MSTprim[len-1][3];//记录MST

    for(int i=0;i<len;i++)
    for(int j=0;j<len;j++)
    matrix[i][j]=INT_MAX;//初始化

    for(int i=0;i<g.numspot;i++)//将边一条一条赋给,按照点的顺序
    {
        Edge *p=g.graph[i].firstedge;
        while(p!=NULL)
        {
            matrix[i][p->adjvex]=p->val;
            matrix[p->adjvex][i]=p->val;
            p=p->next;
        }
    }

    int lowcost[len];//以i为终点的边的最小权值,INT_MAX表示无穷大,=0表示i点已经加入MST

    int mst[len];//lowcost[i]的起点，边<mst[i],i>是MST的一条边

    //首先要将一个点加入MST中，这就需要我们在矩阵中找出存在非INT_MAX的值的一行
    bool t=1;int temp;
    for(int i=0;i<len;i++)
    {
        for(int j=0;j<len;j++)
        {
            if(matrix[i][j]!=INT_MAX)//也就是第i行，点i
            {
                t=0;
                temp=i;
                break;
            }
        }
        if(t==0)
        break;
    }
    //从i点开始
    for(int i=0;i<len;i++)
    {
        lowcost[i]=matrix[temp][i];
        mst[i]=temp;
    }
    int min;//记录最小权值
    int minid;//最小权值的边的终点

    for(int i=1;i<len;i++)//一行一行来
    {
        min=INT_MAX;//刚开始的最小值是无穷
        minid=0;
        for(int j=1;j<len;j++)
        {
            if(lowcost[j]<min&&lowcost[j]!=0)
            {
                min=lowcost[j];//一轮遍历记录的边的最小权值
                minid=j;//记录终点
            }
        }
        lowcost[minid]=0;//记录该点已经加入MST
        //然后MST更新
        MSTprim[i-1][0]=mst[minid];
        MSTprim[i-1][1]=minid;
        MSTprim[i-1][2]=min;
        for(int j=1;j<len;j++)
        {
            if(matrix[minid][j]<lowcost[j])
            {
                mst[j]=minid;
                lowcost[j]=matrix[minid][j];
            }
        }
    }//MSTprim存放着边->边 权重的关系
    //尝试打印验证
    for(int i=0;i<len-1;i++)
    {
        cout<<MSTprim[i][0]<<" "<<MSTprim[i][1]<<" "<<MSTprim[i][2]<<endl;
    }
    system("pause");
    return 0;
}