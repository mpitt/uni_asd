#include <fstream>
#include <iostream>
using namespace std;
int main() {
    int mx, n, inv=0;
    int r0, c0, r, c;
    ifstream in("input.txt");
    in>>r0>>c0;//acquire dimensions of the matrix
    //check if number of colons exceeds the number of rows
    //in this case is convenient to transpose the matrix
    if(c0<r0) inv=1;
    c = max(c0,r0);
    r = min(c0,r0);
    int** a = new int*[r];
    for (int i=0; i<r; i++) a[i] = new int[c];
    //acquire the matrix transposing it if convenient
    for(int i=0;i<r0;i++) {
        for(int j=0; j<c0;j++) {
            if(inv==1) in>>a[j][i];
            else in>>a[i][j];
        }
    }
    mx = 0;
    int* parz = new int[c];
    for(int i=0; i<r; i++) {
        for(int k=0; k<c; k++) parz[k]=0;
        for(int j=i; j<r; j++) {
            int temp = 0;
            for(int k=0; k<c; k++) {
                parz[k] += a[j][k];
                temp = max(temp+parz[k],0);
                mx = max(mx,temp);
            }
        }
    }
    ofstream out("output.txt");
    out<<mx<<'\n';
    return 0;
}
