#include<iostream>
using namespace std;
//链表存储
//实现功能：创建、查找、删除、添加、获取长度、输出、简单排序、反序
struct Node{
    int data;//数据
    struct Node *next;//指针
    Node(int val):data(val),next(NULL){};//初始化
};
class List{
    public:
     List();//创建
     int search(int data);//按照值查找,返回位置
     int pos_search(int pos);//按照位置查找，返回值
     void del(int data);//按照值删除
     void pos_del(int pos);//按照位置删除
     void add(int pos,Node *p);//按照位置添加(在后面插入)
     void addafter(int data);//在最末尾添加一个数据为data的点
     int getsize();//获取长度
     void ouput();//输出
     void mysort();//排序
     void myreverse();//反序
    
     int size;//长度
     Node *head;//链表的头节点
};
List::List()//初始化
{
    size=0;
    head=NULL;
};
int List::search(int data)//按照值查找,返回位置
{
    int position=1;
    Node *temp=head;
    while(temp->data!=data)
    {
        position++;
        temp=temp->next;
    }
    return position;
};
int List::pos_search(int pos)//按照位置查找，返回值
{
    Node *temp=head;
    while(--pos)
    {
        temp=temp->next;
    }
    return temp->data;
};
void List::del(int data)//按照值删除
{
    if(head->data==data)
    {
        head=head->next;
        size--;
        return;
    }
    Node *temp=head;
    Node *pre;
    while(temp->data!=data)
    {
        pre=temp;
        temp=temp->next;
    }
    pre->next=temp->next;
    size--;
};
void List::pos_del(int pos)//按照位置删除
{
    if(pos==1)
    {
        head=head->next;
        size--;
        return;
    }
    Node *temp=head;
    Node *pre;
    while(--pos)
    {
        pre=temp;
        temp=temp->next;
    }
    pre->next=temp->next;
    size--;
};
void List::add(int pos,Node *p)//按照位置添加(在后面插入)
{
    if(pos==0)
    {
        p->next=head;
        head=p;
        size++;
        return;
    }
    Node *temp=head;
    while(--pos)
    {
        temp=temp->next;
    }
    p->next=temp->next;
    temp->next=p;
    size++;
};
int List::getsize()//获取长度
{
    return size;
};
void List::ouput()//输出
{
    Node *temp=head;
    while(temp!=NULL)
    {
        cout<<temp->data<<" ";
        temp=temp->next;
    }
    cout<<endl;
};
void List::addafter(int data)//在最末尾添加一个数据为data的点
{
    if(head==NULL)
    {
        head=new Node(data);
        size++;
        return;
    }
    Node *temp=head;
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    Node *p=new Node(data);
    temp->next=p;
    size++;
};
void List::mysort()//采用冒泡排序,升序
{
    Node *p,*q;
    for(p=head;p!=NULL;p=p->next)
    {
        for(q=p->next;q!=NULL;q=q->next)
        {
            if(p->data>q->data)
            {
                int temp=p->data;
                p->data=q->data;
                q->data=temp;
            }
        }
    }
};
void List::myreverse()//将链表反序
{
    Node *p,*q,*temp;
    p=head;
    q=head->next;
    head->next=NULL;
    while(q)
    {
        temp=q->next;
        q->next=p;
        p=q;
        q=temp;
    }
    head=p;
};
int main()
{
    List a;
    a.addafter(100);
    a.addafter(2);//测试在末尾添加
    a.addafter(3);
    a.myreverse();
    a.ouput();
    a.mysort();
    a.ouput();
    a.myreverse();
    a.ouput();
    cout<<a.getsize()<<endl;
    system("pause");
    return 0;
}