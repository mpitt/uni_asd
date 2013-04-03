#include <fstream>
#include <vector>

using namespace std;

struct node {
    vector <int> adj;
    int start;
    int end;
};

void dfs(node graph[], node v, int &time);

int main() {
    fstream file;
    int n, m, dim=0;
    queue <int> Q;
    file.open("input.txt", ios::in);
    file >> n >> m;
    node* graph = new node[n];
    node* graphT = new node[n];
    int x, y;
    for (int i=0; i<m; i++) {
        file >> x >> y;
        graph[x].adj.push_back(y);
        graphT[y].adj.push_back(x);
    }
    file.close();
    
    for (int i=0; i<n; i++) {
        graph[i].start=0;
        graph[i].end=0;
        graphT[i].start=0;
        graphT[i].end=0;
    }



    file.open("output.txt", ios::out);
    file << dim  << endl;
    file.close();
    return 0;
}

void dfs(node graph[], int v, int &time) {
    time++;
    graph[v].start=++time;
    for (int i=0; i<graph[v].adj.size(); i++) {
        int w=graph[v].adj[i];
        if(graph[w].start==0) {
            dfs(graph, w, &time);
        }
        time++;
        graph[v].end=time;
    }
}
