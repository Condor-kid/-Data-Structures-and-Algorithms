//给定一组节点值，请构建一颗二叉平衡树
//并按照层次遍历的顺序将其打印出来。
//不含有重复的数字
#include<iostream>
#include<cstdio>
#include<queue>
#include<cstdlib>
#include<vector>
using namespace std;
struct Tree{
    int val;//值
    int height;//高度
    struct Tree *left;
    struct Tree *right;
    Tree(int vals):val(vals),height(1),left(NULL),right(NULL){};
};
//需要实现的函数有：
//层序遍历、逐个插入节点以构建树、左旋转、右旋转
//先左后右旋转、先右后左旋转
int MAX(int a,int b)
{
    return (a>b)?a:b;
};
int height(Tree *t)
{
    if(t==NULL)
    return 0;
    else
    return t->height;
};
Tree *LL(Tree *t)
{
    Tree *temp=t->left;
    t->left=temp->right;
    temp->right=t;
    t->height=MAX(height(t->left),height(t->right))+1;
    temp->height=MAX(height(temp->left),height(temp->right))+1;
    return temp;
};
Tree *RR(Tree *t)
{
    Tree *temp=t->right;
    t->right=temp->left;
    temp->left=t;
    t->height=MAX(height(t->left),height(t->right))+1;
    temp->height=MAX(height(temp->left),height(temp->right))+1;
    return temp;
};
int getBalance(Tree *t)
{
    if(t==NULL)
    return 0;
    else
    {
        return height(t->left)-height(t->right);
    }
};
Tree *insert(Tree *t,int val)
{
    if(t==NULL)//如果t为空，就构建新节点
    {
        t=new Tree(val);
        return t;
    }
    if(val<t->val)//比根小时，插入左子树，直到叶子节点的子树为空新建节点
    {
        t->left=insert(t->left,val);
    }
    else if(val>t->val)//比根大时，插入右子树，直到叶子节点的子树为空新建节点
    {
        t->right=insert(t->right,val);
    }
    else//如果输入的数字有重复的，直接返回整个树的根节点，以忽略重复数字的影响
    {
        return t;
    }
    t->height=1+MAX(height(t->left),height(t->right));//更新树的高度
    int balance=getBalance(t);
    if(balance>1&&val<t->left->val)
    {
        return LL(t);
    }
    if(balance<-1&&val>t->right->val)
    {
        return RR(t);
    }
    if(balance>1&&val>t->left->val)
    {
        t->left=RR(t->left);
        return LL(t);
    }
    if(balance<-1&&val<t->right->val)
    {
        t->right=LL(t->right);
        return RR(t);
    }
    return t;
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
            cout<<t->val<<" ";
            q.push(t->left);
            q.push(t->right);
        }
    }
};
int main()
{
    //假定一个长度为10，升序排列1到10的数组依次插入以构建AVL树
    vector<int> arr(10);
    Tree *t=NULL;//根节点
    int len=arr.size();
    for(int i=0;i<len;i++)
    {
        arr[i]=i+1;
        t=insert(t,arr[i]);
    }
    level_traversal(t);
    system("pause");
    return 0;
}