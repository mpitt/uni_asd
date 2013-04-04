#include <fstream>
#include <vector>
#include <stack>

using namespace std;

struct node {
    vector <int> adj;
    int index;
    int lowLink;
    bool inStack;
};

void tarjan(node graph[], int v, int *index, stack <int> *S,  int *dim);
int min(int a, int b);

int main() {
    fstream file;
    int n, m, dim=0, index=1;
    stack <int> S;
//Read the graph
    file.open("input.txt", ios::in);
    file >> n >> m;
    node* graph = new node[n];
    int x, y;
    for (int i=0; i<m; i++) {
        file >> x >> y;
        graph[x].adj.push_back(y);
    }
    file.close();
//Initialize the graph
    for (int i=0; i<n; i++) {
        graph[i].index=0;
        graph[i].lowLink=0;
        graph[i].inStack=false;
    }
//Compute the dimension of the largest strongly connected component of the graph
//Use tarjan algorithm
    for (int i=0; i<n; i++) {
        if (graph[i].index==0) {
            tarjan(graph, i, &index, &S, &dim);
        }
    }
//Write the result
    file.open("output.txt", ios::out);
    file << dim  << endl;
    file.close();
    return 0;
}

void tarjan(node graph[], int v, int *index, stack <int> *S,  int *dim) {
    graph[v].index = *index;
    graph[v].lowLink = *index;
    (*index)++;
    (*S).push(v);
    graph[v].inStack = true;

    for (int i=0; i<graph[v].adj.size(); i++) {
        int w=graph[v].adj[i];
        if(graph[w].index==0) {
            tarjan(graph, w, index, S, dim);
            graph[v].lowLink = min(graph[v].lowLink, graph[w].lowLink);
        }
        else if (graph[w].inStack) {
            graph[v].lowLink = min(graph[v].lowLink, graph[w].index);
        }
    }
    if (graph[v].index == graph[v].lowLink) {
        for (int count=1, x=-1; x!=v; count++) {
            x=(*S).top();
            (*S).pop();
            graph[x].inStack=false;
            (*dim)=-min(-(*dim),-count); //equivalent to (*dim)=max((*dim),count)
        }
    }
}

int min(int a, int b) {
    if (a<b) {
        return a;
    }
    return b;
}
