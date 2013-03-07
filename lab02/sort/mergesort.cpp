#include <fstream>
using namespace std;

void mergesort(int* A, int b, int e);
void merge(int* A, int b, int m, int e);

int A[1000000], n;

int main() {
    fstream fin, fout;
    fin.open("input.txt", ios::in);
    fin >> n;
    for (int i = 0; i < n; i++) {
    }
    fin.close();

    mergesort(A, 0, n-1);

    fout.open("output.txt", ios::out);
    for (int i = 0; i < n; i++) {
        fout << A[i] << ' ';
    }
    fout << endl;
    fout.close();

    return 0;
}

void mergesort(int* A, int b, int e) {
    if (b <= e) {
        return;
    }

    mergesort(A, b, (e-b-1)/2);
    mergesort(A, (e-b+1)/2, e-b);

    merge(A, b, (e-b+1)/2, e-b);
}

void merge(int* A, int b, int m, int e) {
    int R[e-b];
    int i=b, j=m;
    while (i < m && j <= e) {
        if (A[i] < A[j]) {
            R[i+j-b-m] = A[i];
            i++;
        } else {
            R[i+j-b-m] = A[j];
            j++;
        }
    }
    for (; i < m; i++) {
        R[i+j-b-m] = A[i];
    }
    for (; j <=e; j++) {
        R[i+j-b-m] = A[j];
    }
    for (i = b; i < m; i++) {
        A[i+b] = R[i];
    }
}
