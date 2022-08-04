#include <iostream>
using namespace std;

class noh
{
    friend class Pilha;

    private:
        int mdata;
        noh* mProximo;

    public:
        noh(int data);
};

noh::noh(int data){
    mdata = data;
    mProximo = NULL;
}

class Pilha
{
    private:
        int data;
        Pilha *link;
        Pilha *top;
    public:
        Pilha();
        
        void push( int data );
        int isEmpty();
        void peek();
        void pop();
        void display();
};

Pilha::Pilha()
{
    top = NULL;
}

void Pilha::push( int data )
{
    Pilha *temp = new Pilha();

    if (!temp)
    {
        cout << "\nStack Overflow";
    }

    temp->data = data;

    temp->link = top;

    top = temp;
}
  
int Pilha::isEmpty()
{
    return top == NULL;
}
  
void Pilha::peek()
{
    if ( !isEmpty() )
    {
        cout << "O Elemento do topo eh ";
        cout << top->data << endl;
    }
    else
        cout << "VAZIA" << endl;
}

void Pilha::pop()
{
    Pilha *temp;

    if (top == NULL)
    {
        cout << "VAZIA" << endl;
    }
    else
    {
        temp = top;
  
        top = top->link;

        cout << temp->data << ": REMOVED";
        cout << endl;
  
        free(temp);
    }
}

void Pilha::display()
{
    Pilha *temp;
  
    if (top == NULL)
    {
        cout << "VAZIA" << endl;
    }
    else
    {
        temp = top;
        while (temp != NULL)
        {
            cout << temp->data << " -> ";
  
            temp = temp->link;
        }
        cout << "NULL";
        cout << endl;
    }
}
  
int main()
{
    Pilha p1;
    int selector;
    int data;
    
    do {
        cout << "[1]PUSH ";
        cout << "[2]POP ";
        cout << "[3]PEEK ";
        cout << "[4]DISPLAY ";
        cout << "[5]EXIT ";
        cout << endl << "SELECTOR: ";
        
        cin >> selector;
        
        switch (selector)
        {
        case 1: 
            cin >> data;
            p1.push(data);
            break;      
        case 2:
            p1.pop();
            break;      
        case 3:
            p1.peek();
            break;
        case 4:
            p1.display();
            break;
        }
    } while (selector != 5);
          
    return 0;
}