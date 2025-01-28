#include <bits/stdc++.h>
using namespace std;

class List;

class Node {
    friend class List;
    string s;
    Node* linkR;
    Node* linkL;
public:
    Node(string a);
};

class List {
    Node* first;
public:
    void Create();
    void Add(Node* x);
    void Delete(string a);
    void TCF();
    void TCL();
    void Reverse();
    void Print();
};

Node::Node(string a):s(a), linkR(nullptr), linkL(nullptr){}

void List::Create() {
    first = new Node("N");
    first->linkR = first;
    first->linkL = first;
}

void List::Add(Node* x) {
    Node* t = first;
    t->linkR->linkL = x;
    x->linkR = t->linkR;
    t->linkR = x;
    x->linkL = t;
}

void List::Delete(string a) {
    Node* t = first->linkR;
    while (t->s != a) {
        t = t->linkR;
        if (t == first) return;
    }
    t->linkL->linkR = t->linkR;
    t->linkR->linkL = t->linkL;
}

void List::TCF() {
    if (first == first->linkR) return;
    Node* t = first->linkR;
    t->linkL->linkR = t->linkR;
    t->linkR->linkL = t->linkL;
}

void List::TCL() {
    if (first == first->linkL) return;
    Node* t = first->linkL;
    t->linkL->linkR = t->linkR;
    t->linkR->linkL = t->linkL;
}

void List::Reverse() {
    if (first == first->linkR) return;
    Node* t1 = first->linkR;
    Node* t2 = first;
    do {
        t1->linkL = t1->linkR;
        t1->linkR = t2;
        t2 = t1;
        t1 = t1->linkL;
    } while(t2 != first);
    return;
}

void List::Print() {
    Node* t = first->linkR;
    if (t != first) {
        cout << t->s;
        t = t->linkR;
    }
    while (t != first) {
        cout << " " << t->s;
        t = t->linkR;
    }
    cout << endl;
    return;
}

int main() {
    int n;
    string com, s;
    List L;
    L.Create();
    cin >> n;
    while(n--) {
        cin >> com;
        if (com == "add") {
            cin >> s;
            Node* x = new Node(s);
            L.Add(x);
        }
        else if (com == "delete") {
            cin >> s;
            L.Delete(s);
        }
        else if (com == "truncateFirst") {
            L.TCF();
        }
        else if (com == "truncateLast") {
            L.TCL();
        }
        else if (com == "reverse") {
            L.Reverse();
        }
    }
    L.Print();

    return 0;
}