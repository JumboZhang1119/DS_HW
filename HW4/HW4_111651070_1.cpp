#include <bits/stdc++.h>
using namespace std;

class Tree;

class Node {
    friend class Tree;
    int data;
    Node* parent;
    vector<Node *> child;

public:
    Node(int r);
};

class Tree {
    Node* root;
public:
    void Init_and_find(vector<vector<int>>& v, int source);
};

Node::Node(int r):data(r), parent(nullptr){}

void Tree::Init_and_find(vector<vector<int>>& v, int source) {
    root = new Node(source);
    queue<Node *> q;
    q.push(root);
    while(!q.empty()) {
        Node *p = q.front();
        q.pop();
        for (int i = 0; i < v[p->data].size(); i++) {
            if (v[v[p->data][i]][0] == -1) {
                string s = "";
                Node *c = p;
                while (c->data != source) {
                    s = to_string(c->data) + " " + s;
                    c = c->parent;
                }
                cout << source << " " << s << v[p->data][i] << endl;
            }
            else {
                Node *c = new Node(v[p->data][i]);
                c->parent = p;
                q.push(c);
                p->child.push_back(c);
            }
        }
    }
}
bool checkV(vector<vector<int>>& v, int n) {
    for (int i = 0; i < n; i++) {
        if (v[i].size() == 0) return 1;
    }
    return 0;
}

int main() {
    int n, start, end;
    int source = 0;
    cin >> n;
    vector<vector<int>> v(n);
    vector<bool> V(n, 0);
    while (checkV(v, n)) {
        cin >> start >> end;
        if (end != -1) V[end] = 1;
        v[start].push_back(end);
    }
    for (int i = 0; i < n; i++) {
        if (V[i] == 0) {
            source = i;
        }
    }
    for (int i = 0; i < n; i++) {
        sort(v[i].begin(), v[i].end());
    }
    Tree T;
    T.Init_and_find(v, source);
    return 0;
}