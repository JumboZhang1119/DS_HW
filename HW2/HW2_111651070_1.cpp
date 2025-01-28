#include <bits/stdc++.h>
using namespace std;

class List;

class ListNode {
    friend class List;
    int coef, exp;
    ListNode *link;
public:
    ListNode(int x = 0, int y = 0);
};

class List {
    ListNode *first;
public:
    void Create();
    void Insert(ListNode *x);
    void Delete(ListNode *x);
    void Print();
};

ListNode::ListNode(int x, int y):coef(x), exp(y), link(nullptr){}

void List::Create() {
    first = new ListNode(INT_MAX, INT_MAX);
    first->link = first;
}

void List::Insert(ListNode *x) {
    if (x->coef == 0) return;
    ListNode *t = first;
    if (first->link == first) {
        x->link = first->link;
        first->link = x;
        return;
    }
    while (t->link != first && x->exp < t->link->exp) {
        t = t->link;
    }
    if (x->exp == t->link->exp) {
        if (x->coef + t->link->coef == 0) {
            Delete(t->link);
        }
        else {
            t->link->coef = t->link->coef + x->coef;
        }
    }
    else {
        x->link = t->link;
        t->link = x;
    }
}

void List::Delete(ListNode *x) {
    ListNode *t = first;
    while (x != t->link) {
        t = t->link;
    }
    t->link = t->link->link;
    delete x;
}

void List::Print() {
    ListNode *t = first->link;
    if (t == first) {
        cout << '0' << endl;;
        return;
    }
    if (t->exp == 0) cout << t->coef;
    else if (t->exp == 1) {
        if (t->coef == 1) cout << "x";
        else if (t->coef == -1) cout << "-x";
        else cout << t->coef << "x";
    }
    else {
        if (t->coef == 1) cout << "x^" << t->exp;
        else if (t->coef == -1) cout << "-x^" << t->exp;
        else cout << t->coef << "x^" << t->exp;
    }
    t = t->link;
    while (t != first) {
        if (t->coef > 0) cout << "+";
        if (t->exp == 0) {
            cout << t->coef;
        }
        else if (t->exp == 1) {
            if (t->coef == 1) cout << "x";
            else if (t->coef == -1) cout << "-x";
            else cout << t->coef << "x";
        }
        else {
            if (t->coef == 1) cout << "x^" << t->exp;
            else if (t->coef == -1) cout << "-x^" << t->exp;
            else cout << t->coef << "x^" << t->exp;
        }
        t = t->link;
    }
    cout << endl;
}

int main() {
    List A;
    A.Create();
    string s, B;
    char op;
    cin >> s >> B >> op;
    if (B[0] != '-') B = "+" + B;
    if (op == '-') {
        int i = 0;
        while (i < B.size()) {
            if (B[i] == '+') s = s + "-";
            else if (B[i] == '-') s = s + "+";
            else s = s + B[i];
            i++;
        }
    }
    else s = s + B;
    B.clear();
    B.shrink_to_fit();
    int coef = -1, exp = -1;
    string sub;
    int i;
    if (s[0] == '-') {
        sub = "-";
        i = 1;
    }
    else {
        sub = "+";
        i = 0;
    }
    while (i < s.size()) {
        while (i < s.size() && isdigit(s[i])) {
            sub = sub + s[i];
            i++;
        }
        if (sub.size() == 1) sub += "1";
        if (sub[0] == '+') {
            sub = sub.substr(1);
            coef = stoi(sub);
        }
        else if (sub[0] == '-') {
            sub = sub.substr(1);
            coef = -stoi(sub);
        }
        sub = "";
        if (i >= s.size()) exp = 0;
        else if (s[i] == 'x') {
            if (i+1 < s.size()) {
                i++;
                if (s[i] == '^') {
                    sub = sub + s[++i];
                    i++;
                    while (i < s.size() && isdigit(s[i])) {
                        sub = sub + s[i++];
                    }
                    exp = stoi(sub);
                    sub = "";
                    if (i < s.size()) sub = sub + s[i++];
                }
                else {
                    exp = 1;
                    sub = sub + s[i++];
                }
            }
            else {exp = 1;i++;}
        }
        else if (s[i] == '+' || s[i] == '-') {
            exp = 0;
            sub = sub + s[i++];
        }
        ListNode *n = new ListNode(coef, exp);
        A.Insert(n);
    }
    A.Print();
    return 0;
}