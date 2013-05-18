#include <fstream>
#include <iostream>
#include <list>

using namespace std;

int fapunti(int*** P, int serate, int istanti, int total, int travestimenti, list<int>* chi, int* finali, int* lunghezze);
int g(int iter, bool trav, int* finali, int serata, bool pari);

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
  int ***P = new int**[total + 1];

  for (int i = 0; i < total + 1; i++) {
    P[i] = new int*[travestimenti + 2];
    for (int j = 0; j < travestimenti + 2; j++) {
      P[i][j] = new int[2];
      P[i][j][0] = P[i][j][1] = 0; 
    }
  }
  /* FORMATO OUTPUT
   * un numero che rappresenta il massimo numero di istanti in cui
   * Sherlock può avere il travestimento adatto
   */
fout.open("output.txt", ios::out);
fout << fapunti(P, serate, istanti, total, travestimenti, chi, finali, lunghezze) << endl;
fout.close();

return 0;
}

//magica funzione risolvi i nostri problemi, amen
int fapunti(int*** P, int serate, int istanti, int total, int travestimenti, list<int>* chi, int* finali, int* lunghezze) {
  int inf = -(serate * istanti + 1);
  int serata = serate - 1;
  bool pari = false;
  list<int>::reverse_iterator iter = chi[serata].rbegin(), next;

  bool cambiasera = false;
  P[total][0][false] = inf;
  P[total][0][true] = inf;
  for (int ist = total - 1; ist >= 0; ist--) {
    P[ist][0][false] = inf;
    P[ist][0][true] = inf;

    for (int rim = 1; rim <= travestimenti + 1; rim++) {
      next = iter;
      next++;
      if (next == chi[serata].rend()) {
        int m = P[ist + lunghezze[serata]][rim][0];
        m = max(m, P[ist + 1][rim - 1][true] + g(*iter, true, finali, serata, pari));
        m = max(m, P[ist + 1][rim - 1][false] + g(*iter, false, finali, serata, pari));
        P[ist][rim][false] = m;
        P[ist][rim][true] = m;
        cambiasera = (serata > 0);
      } else {
        P[ist][rim][true] = max(P[ist + 1][rim][true] + g(*iter, true, finali, serata, pari),
            P[ist + 1][rim - 1][false] + g(*iter, false, finali, serata, pari));
        P[ist][rim][false] = max(P[ist + 1][rim][false] + g(*iter, false, finali, serata, pari),
            P[ist + 1][rim - 1][true] + g(*iter, true, finali, serata, pari));
      } 
    }
    if (cambiasera) {
      serata--;
      iter = chi[serata].rbegin();
      pari = cambiasera = false;
    } else {
      ++iter;
      pari = !pari;
    }
  }
  return P[0][travestimenti + 1][false];
}

int g(int points, bool trav, int* finali, int serata, bool pari) {
  if ((pari != finali[serata]) == trav) {
    return points;
  } else {
    return 0;
  }
}
