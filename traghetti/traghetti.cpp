#include <fstream>
#include <iostream>
#include <vector>
#include <list>
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
    list <int> line;
    int lenght = 0;

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
        graph[i].seen = false;
    }


    //scorre il grafo e lo mette dentro a una lista
    int u = 0;
    line.push_front(0);
    graph[u].seen = true;
    for(int i = 0; i<2; i++) {
        while(graph[u].adj.size()>1){
            //se vero va sul primo, se falso va sul secondo
            u = graph[graph[u].adj[0]].seen ? graph[u].adj[1] : graph[u].adj[0];
            graph[u].seen = true;
            //aggiunge l'elemento all'inizio o alla fine a seconda che sia il primo o secondo ramo
            switch(i) {
                case 0:
                    line.push_front(u);
                    break;
                case 1:
                    line.push_back(u);
                    break;
                default:
                    //non dovremmo arrivare qui
                    cerr << "How did I ever get here?!?" << endl;
                    return -1;
            }
            //visto che scorro il grafo mi segno anche la lunghezza
            lenght++;
        }
        u = 0;
    }


    /* FORMATO OUTPUT
     * nella prima riga le prime due isole che scolleghi
     * nella seconda riga le due isole che colleghi
     */
    fout.open("output.txt", ios::out);

    fout.close();

    return 0;
}
