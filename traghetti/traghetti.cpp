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
    vector <int> leftv;
    vector <int> rightv;
    int length = 0;

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
    graph[u].seen = true;
    for(int i = 0; i<2; i++) {
        while(graph[u].adj.size()>1){
            //se vero va sul primo, se falso va sul secondo
            u = graph[graph[u].adj[0]].seen ? graph[u].adj[1] : graph[u].adj[0];
            graph[u].seen = true;
            //aggiunge l'elemento all'inizio o alla fine a seconda che sia il primo o secondo ramo
            switch(i) {
                case 0:
                    leftv.push_back(u);
                    break;
                case 1:
                    rightv.push_back(u);
                    break;
                default:
                    //non dovremmo arrivare qui
                    cerr << "How did I ever get here?!?" << endl;
                    return -1;
            }
            //visto che scorro il grafo mi segno anche la lunghezza
            length++;
        }
        
        if(leftv.empty() && i==0) {
            u = graph[0].adj[0];
            rightv.push_back(u);
            graph[u].seen = true;
            length++;
        }
        else {
            u = 0;
        }
    }
    for (int i=0; i<leftv.size(); i++) {
        cout << leftv[i] << ' ';
    }
    cout << endl;
    for (int i=0; i<rightv.size(); i++) {
        cout << rightv[i] << ' ';
    }
    cout << endl;

    int index[4];
    index[0] = length/2 - leftv.size();
    index[1] = length/2 + 1 - leftv.size();
    index[2] = length/4 - leftv.size();
    index[3] = length - length/4 - leftv.size();
    cout<<"Length: "<<length<<endl;
    for (int i=0; i<4; i++) {
        cout << index[i] << endl;
    }
    
    fout.open("output.txt", ios::out);
    
    for (int i=0; i<4; i++) {
        if (index[i]>0) {
            fout << rightv[index[i] - 1] << ' ';
        }
        else if (index[i] == 0) {
            fout << 0 << ' ';
        }
        else {
            fout << leftv[-index[i] - 1] << ' ';
        }
        if (i%2 == 1) fout << endl;
    }
    /* FORMATO OUTPUT
     * nella prima riga le prime due isole che scolleghi
     * nella seconda riga le due isole che colleghi
     */

    fout.close();

    return 0;
}
