#include <fstream>
#include <vector>

using namespace std;

struct node {
    vector<int> adj;
    bool saw;
};

int visit(node * graph, int s);

int main() {
    fstream file;
    int n, m, s;
    file.open("input.txt", ios::in);
    file >> n >> m >> s;
    node * graph = new node[n];
    int x, y;
    for (int i = 0; i < n; i++) {
        graph[i].saw = false;
    }
    for (int i = 0; i < m; i++) {
        file >> x >> y;
        graph[x].adj.push_back(y);
    }
    file.close();

    int r = visit(graph, s);
    
    file.open("output.txt", ios::out);
    file << r << endl;
    file.close();
    return 0;
}

int visit(node * graph, int s) {
    int r = 1;
    int num_adj = graph[s].adj.size();
    int v;
    graph[s].saw = true;
    for (int i = 0; i < num_adj; i++) {
        v = graph[s].adj[i];
        if (graph[v].saw == false) {
            r += visit(graph, v);
        }
    }
    return r;
}
