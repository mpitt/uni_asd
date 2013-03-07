#include <fstream>

using namespace std;

int A[2000][2000];
int r, c;
int h[2000][2000];
int m;

int main() {
    fstream fin, fout;

    fin.open("input.txt", ios::in);
    fin >> r >> c;
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            fin >> A[i][j];
        }
    }
    fin.close();

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            h[i][j] = max(h[i][j] + A[i][j], 0);
            my[j] = max(my[j], hy[j]);
        }
        h = max(h + my[j], 0);
        m = max(m, h);
    }

    fout.open("output.txt", ios::out);
    fout << m << endl;
    fout.close();

    return 0;
}

int max (int a, int b) {
    if (a < b)
        return b;
    return a;
}
