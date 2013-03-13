#include <fstream>
#include <algorithm>

using namespace std;

int A[100000];
int B[100000];

int main() {
    fstream fin, fout;
    fin.open("input.txt", ios::in);
    int n;
    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> A[i] >> B[i];
    }
    fin.close();

    sort(A, A+n);
    sort(B, B+n);

    int closing = 0, opening = 0;
    int thisClosing, thisOpening;
    int level = 1, i = 0, j = 0;
    while (i < n && j < n) {
        if (i < n-1 && B[j] < A[i+1]) {
            level--;
            j++;
        } else {
            i++;
            level++;
        }
        if (level == 0) {
            thisClosing = B[j-1];
            thisOpening = A[i+1];
        }
        if ((thisOpening-thisClosing) > (opening-closing)) {
            closing = thisClosing;
            opening = thisOpening;
        }
    }

    fout.open("output.txt", ios::out);
    fout << closing << " " << opening << endl;
    fout.close();

    return 0;
}
