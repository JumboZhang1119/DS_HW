#include <bits/stdc++.h>
using namespace std;

struct node {
    int cur_x, cur_y;
};

struct vec_node {
    char flag;
    int pre_x, pre_y;
};

int main() {
    int x[4] = {0, 0, -1, 1};
    int y[4] = {-1, 1, 0, 0};
    node root;
    queue<node> q;
    int dest_x, dest_y, len;
    cin >> root.cur_y >> root.cur_x >> dest_x >> dest_y >> len;
    root.cur_x++;
    root.cur_y++;
    vector<vector<vec_node>> vec(len+2, vector<vec_node>(len+2));
    for (int i = 0; i < len+2; i++) {
        vec[0][i].flag = '#';
        vec[len + 1][i].flag = '#';
        vec[i][0].flag = '#';
        vec[i][len + 1].flag = '#';
    }
    for (int i = 1; i <= len; i++) {
        string s;
        cin >> s;
        for (int j = 1; j <= len; j++) {
            vec[i][j].flag = s[j-1];
        }
    }
    q.push(root);
    while (!q.empty()) {
        for (int i = 0; i < 4; i++) {
            if (vec[q.front().cur_y + y[i]][q.front().cur_x + x[i]].flag == '.') {
                node n;
                n.cur_y = q.front().cur_y + y[i];
                n.cur_x = q.front().cur_x + x[i];
                vec[n.cur_y][n.cur_x].flag = '#';
                vec[n.cur_y][n.cur_x].pre_x = q.front().cur_x;
                vec[n.cur_y][n.cur_x].pre_y = q.front().cur_y;
                q.push(n);
            }
            else if (vec[q.front().cur_y + y[i]][q.front().cur_x + x[i]].flag == 'E') {
                cout << "Shortest Path: Start -> ";
                int cur_x = q.front().cur_x;
                int cur_y = q.front().cur_y;
                string s = "(" + to_string(cur_y + y[i] - 1) + ", " + to_string(cur_x + x[i] - 1) + ") -> End";
                while (!(cur_x == root.cur_x && cur_y == root.cur_y)) {
                    s = "(" + to_string(cur_y - 1) + ", " + to_string(cur_x - 1) + ") -> " + s;
                    int temp = cur_x;
                    cur_x = vec[cur_y][cur_x].pre_x;
                    cur_y = vec[cur_y][temp].pre_y;
                }
                cout << "(" << root.cur_y-1 << ", " << root.cur_x-1 << ") -> " << s << endl;
                return 0;
            }
        }   
        q.pop();
    }
    cout << "No path found!" << endl;
    return 0;
}