#include <fstream>
#include <utility>
#include <algorithm>

pair<int,int> A[100000];

int main() {
    fstream fin, fout;
    fin.open("input.txt", ios::in);
    int n;
    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> A[i].first >> A[i].second;
    }
    fin.close();

    sort(A, A+n);


}

