#include <fstream>
#include <vector>
using namespace std;

vector<int> sort(vector<int> A);
vector<int> combine(vector<int> A, int x, vector<int> B);

vector<int> A;
int n;

int main() {
    fstream fin, fout;
    fin.open("input.txt", ios::in);
    fin >> n;
    A.reserve(n);
    for (int i = 0; i < n; i++) {
        int x;
        fin >> x;
        A.push_back(x);
    }
    fin.close();

    A = sort(A);

    fout.open("output.txt", ios::out);
    for (int i = 0; i < n; i++) {
        fout << A[i] << ' ';
    }
    fout << endl;
    fout.close();

    return 0;
}

vector<int> sort(vector<int> A) {
    if (A.size() <= 1)
        return A;
    int pivot = A[0];
    vector<int> less, greater;
    for (int i = 1; i < A.size(); i++) {
        int x = A[i];
        if (x < pivot)
            less.push_back(x);
        else
            greater.push_back(x);
    }
    return combine(sort(less), pivot, sort(greater));
}

vector<int> combine(vector<int> A, int x, vector<int> B) {
    A.reserve(A.size() + B.size() + 1);
    A.push_back(x);
    for(int i = 0; i < B.size(); i++) {
        A.push_back(B[i]);
    }
    return A;
}
