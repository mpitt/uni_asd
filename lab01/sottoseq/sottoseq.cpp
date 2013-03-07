#include <fstream>
using namespace std;

int A[1000000];
int N, here, mx;

int max(int a, int b);

int main() {
    fstream fin, fout;
    
    fin.open("input.txt", ios::in);
    fin >> N;
    for (int i = 0; i < N; i++) {
        fin >> A[i];
    }
    fin.close();

    for (int i = 0; i < N; i++) {
        here = max(here + A[i], 0);
        mx = max(here, mx);
    }
    
    fout.open("output.txt", ios::out);
    fout << mx << endl;
    fout.close();

    return 0;
}
    
int max(int a, int b) {
    if (a < b)
        return b;
    return a;
}
