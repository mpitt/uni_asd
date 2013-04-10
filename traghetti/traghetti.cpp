#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct node {
    vector <int> adj;
    int seen;
};


int main() {
    //variabili
    fstream fin, fout;
    int n, m;
    int remove[2];
    int add[2];

    //apro lo stream in entrata
    fin.open("input.txt", ios::in);
    fin >> n >> m;

    node* graph = new node[n];

    //popolo il grafo
    for(int i=0; i<m; i++) {
        int x, y;
        fin >> x >> y;
        graph[x].adj.push_back(y);
        graph[y].adj.push_back(x);
    }
    fin.close();

    //tunonhaivistoniente
    for(int i=0; i<n; i++) {
        graph[i].seen = 0;
    }



    /* FORMATO OUTPUT
     * nella prima riga le prime due isole che scolleghi
     * nella seconda riga le due isole che colleghi
     */
    fout.open("output.txt", ios::out);

    fout.close();

    return 0;
}
