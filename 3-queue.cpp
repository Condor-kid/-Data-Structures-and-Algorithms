#include<iostream>
using namespace std;
//队列的基本操作
//初始化、判断队列是否为空、入队、出队、得到队列头、清空队列、得到队列长度
struct Node{
    int data;
    struct Node *next;
    Node(int val):data(val),next(NULL){};
};
class queue{
    public:
    queue()//初始化
    {
        head=NULL;
        size=0;
    };
    bool empty()//判断队列是否为空
    {
        return size==0;
    }
    void push(int data)//入队
    {
        Node *p=new Node(data);
        p->next=head;
        head=p;
        size++;
    };
    void pop()//出队
    {
        Node *p=head;
        while(p->next->next!=NULL)
        {
            p=p->next;
        }
        p->next=NULL;
        size--;
    };
    int front()//取得队列头部
    {
        Node *p=head;
        while(p->next!=NULL)
        {
            p=p->next;
        }
        return p->data;
    };
    void clear()//清空队列
    {
        head=NULL;
        size=0;
    };
    int getsize()//得到队列长度
    {
        return size;
    };
    int size;
    Node *head;
};
int main()
{
    queue a;
    a.push(1);
    a.push(2);
    a.push(3);
    a.pop();
    cout<<a.getsize()<<endl;
    cout<<a.empty()<<endl;
    cout<<a.front()<<endl;
    system("pause");
    return 0;
}