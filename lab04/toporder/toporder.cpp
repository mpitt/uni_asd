#include <fstream>
#include <vector>
#include <stack>

using namespace std;

struct node {
    vector<int> adj;
    bool seen;
};

void visit(node * graph, int s, stack<int> &toporder);

int main() {
    fstream file;
    int n, m;
    file.open("input.txt", ios::in);
    file >> n >> m;
    node * graph = new node[n];
    int x, y;
    for (int i = 0; i < n; i++) {
        graph[i].seen = false;
    }
    for (int i = 0; i < m; i++) {
        file >> x >> y;
        graph[x].adj.push_back(y);
    }
    file.close();

    stack<int> toporder;
    for(int i=0; i<n; i++) {
        if (!graph[i].seen) visit(graph, i, toporder);
    }
    
    file.open("output.txt", ios::out);
    while (!toporder.empty()) {
        int x = toporder.top();
        toporder.pop();
        file << x << ' ';
    }
    file << endl;
    file.close();
    return 0;
}

void visit(node * graph, int s, stack<int> &toporder) {
    graph[s].seen = true;
    int num_adj = graph[s].adj.size();
    for (int i = 0; i < num_adj; i++) {
        int v = graph[s].adj[i];
        if (!graph[v].seen) {
            visit(graph, v, toporder);
        }
    }
    toporder.push(s);
}
