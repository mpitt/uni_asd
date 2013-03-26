#include <fstream>
#include <vector>

using namespace std;

struct node {
    vector <int> adj;
}

int main() {
    fstream file;
    int n, m, s;
    file.open("input.txt", ios::in);
    file >> n >> m >> s;
    node* graph = new node[n];
    int x, y;
    for (int i=0; i<m; i++) {
        file >> x >> y;
        graph[x].adj.push_back(y);
    }
    file.close();

    int d=0;

    file.open("output.txt", ios::out);
    file << d << endl;
    file.close();
    return 0;
}
