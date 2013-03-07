#include <fstream>

using namespace std;

int main() {
    fstream fin, fout;
    int n, m;
    
    fin.open("input.txt", ios::in);
    fin >> n >> m;
    fin.close();
    fout.open("output.txt", ios::out);
    fout << n+m << endl;
    fout.close();

    return 0;
}
