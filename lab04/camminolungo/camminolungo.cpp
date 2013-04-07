#include <fstream>
#include <vector>
#include <stack>

using namespace std;

struct node {
    vector<int> adj;
    int maxin;
};

void visit(node * graph, int s, stack<int> &toporder);

int main() {
    fstream file;
    int n, m, mp = 0;
    file.open("input.txt", ios::in);
    file >> n >> m;
    node * graph = new node[n];
    int x, y;
    for (int i = 0; i < n; i++) {
        graph[i].maxin = -1;
    }
    for (int i = 0; i < m; i++) {
        file >> x >> y;
        graph[x].adj.push_back(y);
    }
    file.close();

    stack<int> toporder;
    for(int i=0; i<n; i++) {
        if (graph[i].maxin) visit(graph, i, toporder);
    }
    
    while (!toporder.empty()) {
        int x = toporder.top();
        toporder.pop();
        for (int i = 0; i < graph[x].adj.size(); i++) {
            int v = graph[x].adj[i];
            graph[v].maxin = max(graph[v].maxin, graph[x].maxin+1);
            mp = max(mp, graph[v].maxin);
    }


    }
    file.open("output.txt", ios::out);
    file << mp << endl;
    file.close();
    return 0;
}

void visit(node * graph, int s, stack<int> &toporder) {
    graph[s].maxin = 0;
    int num_adj = graph[s].adj.size();
    for (int i = 0; i < num_adj; i++) {
        int v = graph[s].adj[i];
        if (graph[v].maxin) {
            visit(graph, v, toporder);
        }
    }
    toporder.push(s);
}
