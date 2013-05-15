#include <fstream>
#include <iostream>
#define N 0
#define J 1
#define H 2


using namespace std;

int fapunti (int ist, int rim, char tr, int*** P, int serate, int istanti, char** chi);
int g(int i, char t, char** chi, int istanti);

int main() {
  //variabili
  fstream fin, fout;
  int serate, istanti, travestimenti;
  char temp;
    
  //apro lo stream in entrata
  fin.open("input.txt", ios::in);
  
  //leggo i dati
  fin >> serate >> istanti >> travestimenti;
  //valore massimo
  int bottom = serate*istanti+1;
  
  //istanzio la matrice dinamica
  char** chi = new char*[serate];
  for(int i = 0; i < serate; i++) {
    chi[i] = new char[istanti];
  }
  
  //leggo le serate
  for(int i = 0; i < serate; i++) {
    for(int j = 0; j < istanti; j++) {
      char temp;
      fin >> temp;
      if (temp == 'J') {
        chi[i][j] = J;
      } else {
        chi[i][j] = H;
    }
    }
  }
  //chiudo lo stream
  fin.close();

  //inizializzo la tabella dei punti
  int ***P = new int**[serate*istanti];
  
  for (int i = 0; i < serate*istanti; i++) {
    P[i] = new int*[travestimenti + 1];
    for (int j = 0; j < travestimenti + 1; j++) {
      P[i][j] = new int[3];
      P[i][j][0] = bottom;
      P[i][j][1] = bottom;
      P[i][j][2] = bottom;
    }
  }
  
  /* FORMATO OUTPUT
   * un numero che rappresenta il massimo numero di istanti in cui
   * Sherlock può avere il travestimento adatto
   */
  fout.open("output.txt", ios::out);
  fout << fapunti(0, travestimenti, 0, P, serate, istanti, chi) << endl;
  fout.close();

  return 0;
}

//magica funzione risolvi i nostri problemi, amen
int fapunti (int ist, int rim, char tr, int*** P, int serate, int istanti, char** chi) {
  cout << "ist: " << ist << ", rim: " << rim << ", tr: " << (int) tr << endl;
  int bottom = serate*istanti+1;
    
    if(rim < 0) {
    cout << "ret: " << -bottom << endl;
       return -bottom;
     }
     if(ist >= bottom - 1){
         cout << "ret: " << 0 << endl;
       return 0;
     }
    if(P[ist][rim][tr] == bottom) {
        if(ist % istanti == 0 ) {
        cout << "contr inizio\n";
          int m = fapunti(ist+1, rim, N, P, serate, istanti, chi);
           m = max(m, fapunti(ist+1, rim-1, J, P, serate, istanti, chi) + g(ist, J, chi, istanti));
           m = max(m, fapunti(ist+1, rim-1, H, P, serate, istanti, chi) + g(ist, H, chi, istanti));
           P[ist][rim][tr] = m;
        } else {
        cout << "contr avanti\n";
          char x = ((tr == J) ? H : J);
          P[ist][rim][tr] = max(fapunti(ist+1, rim, tr, P, serate, istanti, chi) + g(ist, tr, chi, istanti),
                                fapunti(ist+1, rim - 1, x, P, serate, istanti, chi) + g(ist, x, chi, istanti));    
        }
     }
      
    cout << "ret: " << P[ist][rim][tr] << endl;
      return P[ist][rim][tr];
}

int g(int i, char t, char** chi, int istanti) {
  return (chi[i / istanti][i % istanti] == t);
}