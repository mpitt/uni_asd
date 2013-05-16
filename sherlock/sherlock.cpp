#include <fstream>
#include <iostream>

using namespace std;

int fapunti (int ist, int rim, bool tr, int*** P, int serate, int istanti, bool** chi);
int g(int i, bool t, bool** chi, int istanti);

int main() {
  //variabili
  fstream fin, fout;
  int serate, istanti, travestimenti;

  //apro lo stream in entrata
  fin.open("input.txt", ios::in);

  //leggo i dati
  fin >> serate >> istanti >> travestimenti;
  //valore massimo
  int bottom = serate * istanti + 1;

  //istanzio la matrice dinamica
  bool** chi = new bool*[serate];
  for(int i = 0; i < serate; i++) {
    chi[i] = new bool[istanti];
  }

  //leggo le serate
  for(int i = 0; i < serate; i++) {
    for(int j = 0; j < istanti; j++) {
      char temp;
      fin >> temp;
      chi[i][j] = (temp == 'J');
    }
  }
  //chiudo lo stream
  fin.close();

  //inizializzo la tabella dei punti
  int ***P = new int**[serate * istanti];

  for (int i = 0; i < serate*istanti; i++) {
    P[i] = new int*[travestimenti + 1];
    for (int j = 0; j < travestimenti + 1; j++) {
      P[i][j] = new int[2];
      P[i][j][0] = bottom;
      P[i][j][1] = bottom;
    }
  }

  /* FORMATO OUTPUT
   * un numero che rappresenta il massimo numero di istanti in cui
   * Sherlock può avere il travestimento adatto
   */
  fout.open("output.txt", ios::out);
  fout << fapunti(0, travestimenti, true, P, serate, istanti, chi) << endl;
  fout.close();

  return 0;
}

//magica funzione risolvi i nostri problemi, amen
int fapunti (int ist, int rim, bool tr, int*** P, int serate, int istanti, bool** chi) {
  int bottom = serate * istanti + 1;

  if(rim < 0) {
    return -bottom;
  }
  if(ist >= serate * istanti){
    return 0;
  }
  if(P[ist][rim][tr] == bottom) {
    if(ist % istanti == 0 ) {
      int m = fapunti(ist + istanti, rim, tr, P, serate, istanti, chi);
      m = max(m, fapunti(ist + 1, rim - 1, true, P, serate, istanti, chi) + g(ist, true, chi, istanti));
      m = max(m, fapunti(ist + 1, rim - 1, false, P, serate, istanti, chi) + g(ist, false, chi, istanti));
      P[ist][rim][tr] = m;
    } else {
      P[ist][rim][tr] = max(fapunti(ist + 1, rim, tr, P, serate, istanti, chi) + g(ist, tr, chi, istanti),
          fapunti(ist + 1, rim - 1, !tr, P, serate, istanti, chi) + g(ist, !tr, chi, istanti));
    }
  }

  return P[ist][rim][tr];
}

int g(int i, bool t, bool** chi, int istanti) {
  return (chi[i / istanti][i % istanti] == t);
}
