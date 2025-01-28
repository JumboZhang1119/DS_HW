#include <bits/stdc++.h>

using namespace std;

int main() {
    vector<int> pushed;
    vector<int> popped;
    stack<int> pu;
    string s;
    getline(cin, s);
    stringstream ss;
	string a;
	ss << s;
	while (getline(ss, a, ',')) {
		pushed.push_back(stoi(a));
	}
    ss.clear();
    ss.str("");
    s.clear();
    a.clear();
    getline(cin, s);
    ss << s;
	while (getline(ss, a, ',')) {
		popped.push_back(stoi(a));
	}
    int current_push_pos = 0;
    for (int i = 0; i < popped.size(); i++) {
        if (!pu.empty() && pu.top() == popped[i]) {
            pu.pop();
        }
        else if (pushed[current_push_pos] == popped[i]) {
            current_push_pos++;
        }
        else {
            if (current_push_pos >= pushed.size()) {
                cout << "false" << endl;
                return 0;
            }
            pu.push(pushed[current_push_pos]);
            current_push_pos++;
            while (current_push_pos != pushed.size() && pushed[current_push_pos] != popped[i]) {
                pu.push(pushed[current_push_pos]);
                current_push_pos++;
            }
            if (current_push_pos != pushed.size()) {
                current_push_pos++;
            }
        }
    }
    cout << "true" << endl;
    return 0;
}