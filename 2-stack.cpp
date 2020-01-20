#include<iostream>
using namespace std;
//完成栈的基本操作：
//置空栈、判断栈是否为空、入栈、出栈、得到栈顶元素、打印栈
struct Node{
    int data;
    struct Node *next;
    Node(int val):data(val),next(NULL){};
};
class stack{
    public:
    stack()//初始化
    {
        size=0;
        head=NULL;
    };
    int gettop()//获得栈顶元素
    {
        return head->data;
    };
    void push(int data)//压栈
    {
        Node *p=new Node(data);
        p->next=head;
        head=p;
        size++;
    };
    void pop()//出栈
    {
        size--;
        head=head->next;
    };
    bool empty()
    {
        return size==0;
    };
    void delete_stack()
    {
        head=NULL;
        size=0;
    };
    void ouput()//从栈顶到栈底输出
    {
        Node *temp=head;
        while(temp!=NULL)
        {
            cout<<temp->data<<" ";
            temp=temp->next;
        }
        cout<<endl;
    }
    Node *head;
    int size;
};
int main()
{
    stack a;
    a.push(1);
    a.push(2);
    a.push(3);
    cout<<a.gettop()<<endl;
    cout<<a.empty()<<endl;
    a.ouput();
    a.pop();
    a.ouput();
    a.delete_stack();
    cout<<a.empty()<<endl;
    system("pause");
    return 0;
}