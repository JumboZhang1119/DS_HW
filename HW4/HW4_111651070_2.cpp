#include <bits/stdc++.h>
using namespace std;

class Tree;

class Node {
    friend class Tree;
    int data;
    string gate;
    string wire;
    Node* parent1;
    Node *parent2;
    vector<Node *> child;
public:
    Node(int d, string g, string w);
};

class Tree {
    vector<Node *> input_nodes;
    vector<Node *> all_nodes;
public:
    void Init(vector<string>& v, vector<int>& value);
    Node *find_gate(string w);
    void add_gate(string g, string win, string wout);
    void add_gate(string g, string win1, string win2, string wout);
    Node* trace_back(Node* n);
    void calculate(vector<string>& w);
};

Node::Node(int d, string g, string w):data(d), gate(g), wire(w), parent1(nullptr), parent2(nullptr){}

void Tree::Init(vector<string>& v, vector<int>& value) {
    for (int i = 0; i < v.size(); i++) {
        Node *n = new Node(value[i], "" ,v[i]);
        input_nodes.push_back(n);
        all_nodes.push_back(n);
    }
}

Node* Tree::find_gate(string w) {
    for (int i = 0; i < all_nodes.size(); i++) {
        if (all_nodes[i]->wire == w) {
            return all_nodes[i];
        }
    }
    return nullptr;
}

void Tree::add_gate(string g, string win, string wout) {
    Node *in = find_gate(win);
    Node *out = find_gate(wout);
    if (in != nullptr) {
        if (out == nullptr) {
            out = new Node(2, g, wout);
            all_nodes.push_back(out);
        }
        if (in->data != 2) {
            out->data = !in->data;
        }
    }
    else {
        in = new Node(2, "", win);
        all_nodes.push_back(in);
        if (out == nullptr) {
            out = new Node(2, g, wout);
            all_nodes.push_back(out);
        }
    }
    out->gate = g;
    in->child.push_back(out);
    out->parent1 = in;
}

void Tree::add_gate(string g, string win1, string win2, string wout) {
    Node *in1 = find_gate(win1);
    Node *in2 = find_gate(win2);
    Node *out = find_gate(wout);
    if (in1 == nullptr) {
        in1 = new Node(2, "", win1);
        all_nodes.push_back(in1);
    }
    if (in2 == nullptr) {
        in2 = new Node(2, "", win2);
        all_nodes.push_back(in2);
    }
    if (out == nullptr) {
        out = new Node(2, g, wout);
        all_nodes.push_back(out);
    }
    else out->gate = g;
    if (in1->data != 2 && in2->data != 2) {
        if (g == "NOR") {
            out->data = !(in1->data || in2->data);
        }
        else {
            out->data = !(in1->data && in2->data);
        }
    }
    in1->child.push_back(out);
    in2->child.push_back(out);
    out->parent1 = in1;
    out->parent2 = in2;
}

Node* Tree::trace_back(Node* n) {
    if (n == nullptr) return nullptr;
    if (n->data != 2) return n;
    if (n->gate == "INV") {
        Node *t = trace_back(n->parent1);
        n->data = !t->data;
    }
    else if (n->gate == "NOR") {
        Node *t1 = trace_back(n->parent1);
        Node *t2 = trace_back(n->parent2);
        n->data = !(t1->data || t2->data);
    }
    else{
        Node *t1 = trace_back(n->parent1);
        Node *t2 = trace_back(n->parent2);
        n->data = !(t1->data && t2->data);
    }
    return n;
}

void Tree::calculate(vector<string>& w) {
    for (int i = 0; i < w.size(); i++) {
        Node *n = find_gate(w[i]);
        if (n != nullptr) {
            trace_back(n);
            cout << n->wire << " " << n->data << endl;
        }
    }
}

int main() {
    string s;
    vector<string> v;
    vector<string> e;
    Tree T;
    int in, out = 0;
    getline(cin, s);
    stringstream ss(s);
    while(ss >> s) {
        v.push_back(s);
    }
    in = v.size();
    vector<int> value(in);
    for (int i = 0; i < in; i++) {
        cin >> value[i];
    }
    T.Init(v, value);
    cin.ignore();
    ss.str("");
    ss.clear();
    getline(cin, s);
    ss << s;
    while(ss >> s) {
        e.push_back(s);
    }
    while(getline(cin, s)) {
        ss.str("");
        ss.clear();
        ss << s;
        string a, c1, c2, c3, c4;
        ss >> a;
        if (a == "INV") {
            ss >> c1 >> c2 >> c3;
            T.add_gate(a, c2, c3);
        }
        else {
            ss >> c1 >> c2 >> c3 >> c4;
            T.add_gate(a, c2, c3, c4);
        }
    }
    T.calculate(e);
    return 0;
}