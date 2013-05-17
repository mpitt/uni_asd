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

  for (int ist = total; ist >= 0; ist--) {
    for (int rim = 0; rim <= travestimenti + 1; rim++) {

      if (rim == 0) {
        P[ist][rim][false] = inf;
        P[ist][rim][true] = inf;

      } else if (ist == total){
        P[ist][rim][false] = 0;
        P[ist][rim][true] = 0;

      } else {
        next = iter;
        next++;
        if (next == chi[serata].rend()) {
//          cout << "inizio sera\n";
          int m = P[ist + lunghezze[serata]][rim][0];
          m = max(m, P[ist + 1][rim - 1][true] + g(*iter, true, finali, serata, pari));
          m = max(m, P[ist + 1][rim - 1][false] + g(*iter, false, finali, serata, pari));
          P[ist][rim][false] = m;
          P[ist][rim][true] = m;
//          cout << "in ist: " << ist << ", rim: " << rim - 1 << ", scelgo te! -> " << m << endl;

          if (serata > 0) {
            serata--;
            iter = chi[serata].rbegin();
            pari = false;
          }
        } else {
//          cout <<"proseguio\n";
          P[ist][rim][true] = max(P[ist + 1][rim][true] + g(*iter, true, finali, serata, pari),
              P[ist + 1][rim - 1][false] + g(*iter, false, finali, serata, pari));
          P[ist][rim][false] = max(P[ist + 1][rim][false] + g(*iter, false, finali, serata, pari),
              P[ist + 1][rim - 1][true] + g(*iter, true, finali, serata, pari));
//          cout << "in ist: " << ist << ", rim: " << rim - 1 << ", 0  -> " << P[ist][rim][0] << endl;
//          cout << "in ist: " << ist << ", rim: " << rim - 1 << ", 1  -> " << P[ist][rim][1] << endl;
          ++iter;
          pari = !pari;
        } 
      }
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
