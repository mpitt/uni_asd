#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

struct node {
    vector <int> adj;
    int dist;
    int npath;
};

int main() {
    fstream file;
    int n, m, src, dst;
    queue <int> Q;
    file.open("input.txt", ios::in);
    file >> n >> m >> src >> dst;
    node* graph = new node[n];
    int x, y;
    for (int i=0; i<m; i++) {
        file >> x >> y;
        graph[x].adj.push_back(y);
    }
    file.close();
    
    for (int i=0; i<n; i++) {
        graph[i].dist=-1;
        graph[i].npath=0;
    }

    graph[src].dist=0;
    graph[src].npath=1;
    
    Q.push(src);

    while (!Q.empty()) {
        int v=Q.front();
        Q.pop();

        for (int i=0; i<graph[v].adj.size(); i++) {
            int w = graph[v].adj[i];
            if (graph[w].dist==-1) {
                Q.push(w);
                graph[w].dist = graph[v].dist+1;
            }
            if (graph[w].dist == graph[v].dist+1) {
                graph[w].npath += graph[v].npath;
            }
        }
    }

    file.open("output.txt", ios::out);
    file << graph[dst].dist << ' '
         << graph[dst].npath << endl;
    file.close();
    return 0;
}
