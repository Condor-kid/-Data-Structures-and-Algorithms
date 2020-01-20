#include<iostream>
#include<queue>
#include<vector>
using namespace std;
//实现了树的前序、中序、后序、层序遍历，查找，求高度，利用层序遍历原理构建树
struct Tree{
    int data;
    struct Tree *left;
    struct Tree *right;
    Tree(int val):data(val),left(NULL),right(NULL){};
};
void Midtree(Tree *t)//中序遍历
{
    if(t)
    {
        Midtree(t->left);
        cout<<t->data<<" ";
        Midtree(t->right);
    }
};
void fronttree(Tree *t)//前序遍历
{
    if(t)
    {
        cout<<t->data<<" ";
        fronttree(t->left);
        fronttree(t->right);
    }
};
void lasttree(Tree *t)//后序遍历
{
    if(t)
    {
        lasttree(t->left);
        lasttree(t->right);
        cout<<t->data<<" ";
    }
};
Tree* findpoint(Tree *t,int val)//查找元素x所在的节点，找不到则返回NULL
{
    Tree *p=NULL;
    if(t)
    {
        if(t->data==val)
        return t;
        if(t->left)
        {
            p=findpoint(t->left,val);
            if(p)
            return p;
        }
        if(t->right)
        {
            p=findpoint(t->right,val);
            if(p)
            return p;
        }
    }
    return p;
};
void level_traversal(Tree *t)//层序遍历
{
    queue<Tree *> q;
    q.push(t);
    while(!q.empty())
    {
        t=q.front();
        q.pop();
        if(t)
        {
            cout<<t->data<<" ";
            q.push(t->left);
            q.push(t->right);
        }
    }
};
int depth(Tree *t)//求二叉树的高度
{
    int dep1,dep2;
    if(t==NULL)
    return 0;
    else
    {
        dep1=depth(t->left);//左子树高度
        dep2=depth(t->right);//右子树高度
        if(dep1<dep2)//加上根
        {
            return dep2+1;
        }else
        {
            return dep1+1;
        }
    }
};
Tree* create(vector<int> arr)//通过vector来层序传入点构建树
{
    int len=arr.size();//二叉树的节点数
    queue<Tree *> q;
    int esc=0;
    Tree *t=new Tree(arr[0]);
    q.push(t);
    for(int i=1;i<len;)//每次构建一个点就判断是否已经构建完毕
    {
        while(!q.empty())
        {
            Tree *temp=q.front();
            q.pop();
            if(i<len)
            {
                temp->left=new Tree(arr[i++]);
            }
            else
            {
                esc=1;
                break;
            }
            if(i<len)
            {
                temp->right=new Tree(arr[i++]);
            }
            else
            {
                esc=1;
                break;
            }
            q.push(temp->left);
            q.push(temp->right);
        }
        if(esc==1)
        break;
    }
    return t;
};
int main()
{
    vector<int> ans(5);
    for(int i=0;i<5;i++)
    ans[i]=i;
    Tree *t=create(ans);
    level_traversal(t);
    cout<<endl;
    lasttree(t);
    cout<<endl;
    fronttree(t);
    cout<<endl;
    Midtree(t);
    cout<<endl;
    Tree *p=findpoint(t,4);
    cout<<p->data<<endl;
    int d=depth(t);
    cout<<d<<endl;
    system("pause");
    return 0;
}