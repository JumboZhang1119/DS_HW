#include <bits/stdc++.h>
using namespace std;

vector<int> Postor;

class Tree;

class Node {
    friend class Tree;
    int data;
    Node* linkR;
    Node* linkL;
public:
    Node(int r);
};

class Tree {
    Node* root;
public:
    void Init(int r);
    void Create(vector<int> &preor, vector<int> &inor, Node *x);
    Node* getRoot();
    void printPostTree(Node* x);
};

Node::Node(int r):data(r), linkR(nullptr), linkL(nullptr){}

void Tree::Init(int r) {
    root = new Node(r);
}

void Tree::Create(vector<int>& preor, vector<int>& inor, Node* x) {
    vector<int> pre, in;
    int i = 0;
    while(x->data != inor[i]) {
        in.push_back(inor[i]);
        i++;
    }
    for (int j = 1; j <= i; j++) {
        pre.push_back(preor[j]);
    }
    if (in.size()) {
        x->linkL = new Node(pre[0]);
        Create(pre, in, x->linkL);
    }
    pre.clear();
    in.clear();
    for (int j = i + 1; j < preor.size(); j++) {
        in.push_back(inor[j]);
        pre.push_back(preor[j]);
    }
    if (in.size()) {
        x->linkR = new Node(pre[0]);
        Create(pre, in, x->linkR);
    }
    return;
}

Node* Tree::getRoot() {
    return root;
}

void Tree::printPostTree(Node* x) {
    if (x->linkL) {
        printPostTree(x->linkL);
    }
    if (x->linkR) {
        printPostTree(x->linkR);
    }
    Postor.push_back(x->data);
}


int main() {
    int n;
    cin >> n;
    vector<int> Preor(n), Inor(n);
    for (int i = 0; i < n; i++) {
        cin >> Preor[i];
    }
    bool flag = 1;
    if (n) cin >> Inor[0];
    for (int i = 1; i < n; i++) {
        cin >> Inor[i];
        if (Inor[i-1] > Inor[i]) flag = 0;
    }
    Tree T;
    T.Init(Preor[0]);
    T.Create(Preor, Inor, T.getRoot());
    T.printPostTree(T.getRoot());
    if (Postor[0]) cout << Postor[0];
    for (int i = 1; i < Postor.size(); i++) {
        cout << " " << Postor[i];
    }
    cout << endl;
    if (flag) cout << "Yes" << endl;
    else cout << "No" << endl;
}