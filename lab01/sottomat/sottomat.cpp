#include <fstream>
#include <iostream>
using namespace std;
int r,c;
//Array dichiarato con la dimensione massima
int a[4000000];
int main(){
    int max, parz, temp, inv, n;
    ifstream in("input.txt");
    in>>r>>c;
    n = inv=(r<c) ? r : c;
    for(int i=0;i<r;i++){
        for(int j=0; j<c;j++){
            in>> (inv ? a[j*n+i] : a[i*n+j]);
        }
    }
    r = inv ? c : r;
    c=n;
    max = 0;
    for(int i=0; i<c; i++){
        for(int j=1; j<=c;j++){
            parz = temp = 0;
            for(int k=0; k<r;k++){
                for(int l=i; l<j; l++) parz += a[k*n+l];
                    parz = temp = parz > 0 ? parz : 0;
                    max = (temp > max) ? temp : max;
            }
        }
    }
    ofstream out("output.txt");
    out<<max<<'\n';
    return 0;
}
