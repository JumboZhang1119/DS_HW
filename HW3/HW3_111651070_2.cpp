#include <bits/stdc++.h>
using namespace std;

class Tree;

class Node {
    friend class Tree;
    int data;
    Node* parent;
    Node* linkR;
    Node* linkL;
    Node* sibR;
public:
    Node(int r);
};

class Tree {
    Node* root;
public:
    void Init(int r);
    bool AddNewLayer(int i);
    void Find_and_swap(int a, int b);
    void FindMaxDepth();
    void Swap(Node *a, Node *b);
    void printInorderTree(Node* x);
    Node* getRoot();
};

Node::Node(int r):data(r), linkR(nullptr), linkL(nullptr), parent(nullptr), sibR(nullptr){}

void Tree::Init(int r) {
    root = new Node(r);
}

bool Tree::AddNewLayer(int i) {
    Node* t = root;
    for (int j = 1; j < i; j++) {
        t = t->linkL;
    }
    Node* tt = t;
    while(t) {
        int n;
        cin >> n;
        if (n == -1) {
            while(t) {
                Node *N = new Node(0);
                t->linkL = N;
                t->linkL->parent = t;
                N = new Node(0);
                t->linkR = N;
                t->linkR->parent = t;
                t = t->sibR;
            }
            return 0;
        }
        Node* N = new Node(n);
        t->linkL = N;
        t->linkL->parent = t;
        // Only the first time skip
        if (tt != t) {
            tt->linkR->sibR = t->linkL;
        }
        cin >> n;
        N = new Node(n);
        t->linkR = N;
        t->linkR->parent = t;
        t->linkL->sibR = t->linkR;
        tt = t;
        t = t->sibR;
    }
    return 1;
}

void Tree::Find_and_swap(int a, int b) {
    queue<Node*> q;
    Node* A, *B;
    q.push(root);
    bool flag = 0;
    while (!q.empty()) {
        Node* t = q.front();
        q.pop();
        if (t->data == a) {
            A = t;
            if (flag == 1) {
                Swap(B, A);
                return;
            }
            flag = 1;
        }
        else if (t->data == b) {
            B = t;
            if (flag == 1) {
                Swap(A, B);
                return;
            }
            flag = 1;
        }
        if (t->linkL && t->linkL->data) q.push(t->linkL);
        if (t->linkR && t->linkR->data) q.push(t->linkR);
    }
    return;
}

void Tree::FindMaxDepth() {
    Node *t = root;
    queue<Node *> q;
    q.push(root);
    while(!q.empty()) {
        t = q.front();
        q.pop();
        if (t->linkL && t->linkL->data) q.push(t->linkL);
        if (t->linkR && t->linkR->data) q.push(t->linkR);
    }
    int n = 0;
    while (t) {
        n++;
        t = t->parent;
    }
    cout << n << endl;
    return;
}

void Tree::Swap(Node* a, Node* b){
    Node *t = b;
    while(t != root) {
        t = t->parent;
        if (t->data == a->data) {
            swap(b->data, a->data);
            return;
        }
    }
    a->linkL->parent = b;
    a->linkR->parent = b;
    b->linkL->parent = a;
    b->linkR->parent = a;
    t = a->linkR;
    a->linkR = b->linkR;
    b->linkR = t;
    t = a->linkL;
    a->linkL = b->linkL;
    b->linkL = t;
    swap(a->data, b->data);
    return;
}
bool NotPrint = 1;
void Tree::printInorderTree(Node* x){
    Node* t = x;
    if (t->linkL && t->linkL->data) {
        printInorderTree(t->linkL);
    }
    if (NotPrint && t->data) {
        NotPrint = 0;
        cout << t->data;
    }
    else if (t->data) cout << " " << t->data;
    if (t->linkR && t->linkR->data) {
        printInorderTree(t->linkR);
    }
    return;
}

Node* Tree::getRoot() {
    return root;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    Tree T;
    int n, a, b;
    cin >> n;
    if (n != -1) T.Init(n);
    int i = 1;
    while (T.AddNewLayer(i)) i++;
    cin >> n;
    pair<Node*, Node*> p;
    for (int j = 0; j < n; j++) {
        cin >> a >> b;
        if (a == b) continue;
        T.Find_and_swap(a, b);
    }
    T.printInorderTree(T.getRoot());
    cout << endl;
    T.FindMaxDepth();
    return 0;
}