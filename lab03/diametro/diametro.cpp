#include <fstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>

using namespace std;

struct node {
    vector <int> adj;
};

int maxpath(node graph[], int u, int dist[]) {
    queue <int> S;
    int cont = 0;
    S.push(u);
    while (!S.empty()) {
        int v = S.front();
        S.pop();
        int numero_adiacenti = graph[v].adj.size();
        for (int i=0; i < numero_adiacenti; i++){
            int x = graph[v].adj[i];
            if(dist[x]==-1) {
                S.push(x);
                dist[x]=dist[v]+1;
                cont= max(cont, dist[x]);
            }
        }
    }

    return cont;
}

int main() {
    fstream file;
    int n, m, d=0;
    file.open("input.txt", ios::in);
    file >> n >> m;
    node* graph = new node[n];
    int x, y;
    for (int i=0; i<m; i++) {
        file >> x >> y;
        graph[x].adj.push_back(y);
        graph[y].adj.push_back(x);
    }
    file.close();
    int *dist = new int[n];
    
    for (int i=0; i<n; i++) {
        for (int j=0; j<n; j++) {
            dist[j]=-1;
        }
        dist[i]=0;
        d=max(d,maxpath(graph,i,dist));
    }

    file.open("output.txt", ios::out);
    file << d << endl;
    file.close();
    return 0;
}
