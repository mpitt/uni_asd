#include <fstream>
#include <iostream>
#include <list>

using namespace std;

int fapunti(int** P, int serate, int travestimenti, int** G, int* lunghezze);
int g(int iter, bool trav, int* finali, int serata, bool pari);
void analizza_sera(int serata, int lun, int finale, int** G, list<int> chi, int inf);

int main() {
  //variabili
  fstream fin, fout;
  int serate, istanti, travestimenti, total = 0;

  //apro lo stream in entrata
  fin.open("input.txt", ios::in);

  //leggo i dati
  fin >> serate >> istanti >> travestimenti;
  //valore massimo
  int bottom = serate * istanti + 1;

  //istanzio la matrice dinamica
  list<int>* chi = new list<int>[serate];
  int* finali = new int[serate];
  int* lunghezze = new int[serate];

  //leggo le serate
  for(int i = 0; i < serate; i++) {
    char temp, curr;
    int count = 0;
    lunghezze[i] = 0;
    fin >> temp;
    curr = temp;
    for(int j = 1; j <= istanti; j++) {
      if (curr == temp) {
        count++;
      } else {
        chi[i].push_back(count);
        count = 1;
        total++;
        lunghezze[i]++;
        curr = temp;
      }
      if (j < istanti) {
        fin >> temp;
      }
      finali[i] = (temp == 'J');
    }
    chi[i].push_back(count);
    lunghezze[i]++;
    total++;
    count = 0;
  }
  //chiudo lo stream
  fin.close();

  //inizializzo la tabella dei punti
  int ***S = new int**[total + 1];
  for (int i = 0; i < total + 1; i++) {
    S[i] = new int*[travestimenti + 2];
    for (int j = 0; j < travestimenti + 2; j++) {
      S[i][j] = new int[2];
      S[i][j][0] = S[i][j][1] = 0; 
    }
  }
  int** G = new int*[serate];
  for (int i = 0; i < serate; i++) {
    G[i] = new int[travestimenti];
    for (int j = 0; j < travestimenti; j++) {
      G[i][j] = 0;
    }
  }
  for (int i = 0; i < serate; i++) {
    analizza_sera(i, lunghezze[i], finali[i], G, chi[i], -bottom);
  }
  int** P = new int*[serate + 1];
  for (int i = 0; i <= serate; i++) {
    P[i] = new int[travestimenti + 2];
    P[i][0] = -bottom;
  }
  for (int i = 1; i < travestimenti + 2; i++) {
    P[serate][i] = 0;
  }
  /* FORMATO OUTPUT
   * un numero che rappresenta il massimo numero di istanti in cui
   * Sherlock può avere il travestimento adatto
   */
fout.open("output.txt", ios::out);
fout << fapunti(P, serate, travestimenti, G, lunghezze) << endl;
fout.close();

return 0;
}

//magica funzione risolvi i nostri problemi, amen
int fapunti(int** P, int serate, int travestimenti, int** G, int* lunghezze) {
  for (int s = serate - 1; s >= 0; s--) {
    for (int rim = 1; rim <= travestimenti + 1; rim++) {
      int m = P[s +1][rim];
      for (int k = 1; k < rim && k <=  lunghezze[s]; k++) {
        m = max(m, P[s + 1][rim - k] + G[s][k - 1]);
      }
      P[s][rim] = m;
    }
  }
  return P[0][travestimenti + 1];
}

int g(int points, bool trav, int finale, bool pari) {
  if ((pari != finale) == trav) {              // NB: != corrisponde a XOR
    return points;
  } else {
    return 0;
  }
}

void analizza_sera(int serata, int lun, int finale, int** G, list<int> chi, int inf) {
  int*** S = new int**[lun + 1];
  for (int i = 0; i <= lun; i++) {
    S[i] = new int*[lun + 2];
    for (int j = 0; j < lun + 2; j++) {
      S[i][j] = new int[2];
      S[i][j][0] = S[i][j][1] = 0; 
    }
    S[i][0][0] = S[i][0][1] = inf;
  }
  bool pari = false;
  list<int>::reverse_iterator iter = chi.rbegin();
  for (int ist = lun - 1; ist > 0; ist--) {
    for (int rim = 1; rim <= lun + 1; rim++) {
      S[ist][rim][true] = max(S[ist + 1][rim][true] + g(*iter, true, finale, pari),
          S[ist + 1][rim - 1][false] + g(*iter, false, finale, pari));
      S[ist][rim][false] = max(S[ist + 1][rim][false] + g(*iter, false, finale, pari),
          S[ist + 1][rim - 1][true] + g(*iter, true, finale, pari));
    } 
    iter++;
    pari = !pari;
  } 
  for (int rim = 1; rim <= lun; rim++) {
    int m = 0;
    m = max(m, S[1][rim][true] + g(*iter, true, finale, pari));
    m = max(m, S[1][rim][false] + g(*iter, false, finale, pari));
    G[serata][rim - 1] = m;
  }
}
