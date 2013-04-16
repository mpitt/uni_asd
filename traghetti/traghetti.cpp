#include <fstream>
#include <iostream>
#include <vector>
#include <list>
#include <queue>
using namespace std;

int chuck_norris (int father[], int d, int start);

void reset (int father[], int dist[], int n);

int bfs (vector<int> adj[], int u, int father[], int dist[]);

int spezzatino (vector<int> adj[], int father[], int n, int dist[], int border[], int breaknode[], int join[]);

/*HERE IT STARTS DRAGONS*/
int main() {
    //variabili
    fstream fin, fout;
    int n, m;
	
    //apro lo stream in entrata
    fin.open("input.txt", ios::in);
    fin >> n >> m;
	
	//istanzio i vector e i padri
	vector<int> * adj = new vector<int> [n];
	int * father = new int [n];
	int * dist = new int [n];
	int border[2];
	int chuck [4];
	int join[2][2];
	int diameter, min = n, minChuck = 0;

    //popolo il grafo
    for(int i=0; i<m; i++) {
        int x, y;
        fin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    fin.close();

    //tunonhaivistoniente
    for(int i=0; i<n; i++) {
        father[i] = -1;
    }
	
	//CHIAMO UNA BFS IN UNA BFS, DAWG!
	reset(father, dist, n);
	border[0] = bfs(adj, 0, father, dist);
	reset(father, dist, n);
	border[1] = bfs(adj, border[0], father, dist);
	
	/*
	//stampa il diametro da estremo a estremo
	for(int i=border[1]; i!=-2; i=father[i]) {
		cout << i << "\t"
		     << dist[i] << endl;
	}
	cout << endl;
	*/

	chuck[0] = chuck_norris(father, dist[border[1]]/2-2, border[1]);	
	
	for(int i = 1; i < 4; i++) {	
		chuck[i] = father[chuck[i-1]];
    }
    
    for(int i = 0; i < 3; i++) {
    	diameter = spezzatino (adj, father, n, dist, border, chuck+i, join[0]);
    	if(diameter < min) {
    		min = diameter;
    		join[1][0] = join[0][0];
    		join[1][1] = join[0][1];
    		minChuck = i;
    	}
    	cout<<diameter<<" "<<chuck[i]<<" "<<chuck[i+1]<<" "<<join[0][0]<<" "<<join[0][1]<<endl;
    }
	
    /* FORMATO OUTPUT
     * nella prima riga le prime due isole che scolleghi
     * nella seconda riga le due isole che colleghi
     */

	fout.open("output.txt", ios::out);
	
	fout << chuck[minChuck] << " " << chuck[minChuck+1] << endl;
	fout << join[1][0] << " " << join[1][1] << endl;

    fout.close();

    return 0;
}

void reset (int father[], int dist[], int n) {
 	//tolgo il padre a tutti
    for(int i=0; i<n; i++) {
    	father[i] = -1;
    	dist[i] = 0;
    }
}

int bfs (vector<int> adj[], int u, int father[], int dist[]) {
    //istanzio coda
    queue<int> S;
    
    /* pusho nella coda la ROOT per trovare il piu' distante
     * (prendo un solo elemento visto che e' un albero) */
    S.push(u);
    //segnala la ROOT
    father[u] = -2;

    
    while (!S.empty()) {
        //salvo il primo elemento della coda
        u = S.front();
        //estraggo l'elemento dalla coda
        S.pop();
        //trovo il numero di adj
        int numero_adiacenti = adj[u].size();
        //scorro i figli del nodo
        for (int i=0; i < numero_adiacenti; i++){
            int x = adj[u][i];
            //se non e' ancora visitato
            if(father[x] == -1) {
                S.push(x);
        		//il padre di x e' v, da cui siamo arrivati
                father[x] = u;
                dist[x] = dist[u]+1;
            }
        }
    }
    
	return u; 
}

int spezzatino (vector<int> adj[], int father[], int n, int dist[], int border[], int breaknode[], int join[]) {
	int end;
	int diameter = 0;
	cout<<"ultime robe: "<<border[0]<<" "<<border[1]<<" "<<breaknode[0]<<" "<<breaknode[1]<<"\n";
	
	for (int i = 0; i<2; i++) {			
		reset(father, dist, n);
		father[breaknode[1-i]] = -2;
		end = bfs(adj, border[i], father, dist);
		join[i] = chuck_norris(father, dist[end]/2, end);
		diameter += dist[end] - dist[end]/2;
		cout<<"End: "<<end<<endl;
		cout<<"Spatzle "<<dist[end] - dist[end]/2<<endl;
	}
	
	return diameter+1;
}

int chuck_norris (int father[], int distance, int start) {
	int i = start;
	for(; distance>0; distance--) {
		i=father[i];
	}
	return i;
}