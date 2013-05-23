#include <fstream>

using namespace std;

int fapunti(int** P, int serate, int travestimenti, int** G, int* lunghezze, int available);
int g(int iter, bool trav, int* finali, int serata, bool pari);
void analizza_sera(int serata, int len, int finale, int** G, int* chi, int inf, int available);

int main() {
  //variabili
  fstream fin, fout;
  int serate, istanti, travestimenti, maxlen = 0, total = 0;

  //apro lo stream in entrata
  fin.open("input.txt", ios::in);

  //leggo i dati
  fin >> serate >> istanti >> travestimenti;
  //valore massimo
  int inf = -(serate * istanti + 1);

  //istanzio la matrice dinamica
  int** chi = new int*[serate];
  for (int i = 0; i < serate; i++) {
    chi[i] = new int[istanti];
  }
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
        chi[i][lunghezze[i]] = count;
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
    chi[i][lunghezze[i]] = count;
    lunghezze[i]++;
    total++;
    count = 0;
    maxlen = max(maxlen, lunghezze[i]);
  }
  int available = max(travestimenti - serate + 1, 1);
  //chiudo lo stream
  fin.close();

  //inizializzo la tabella dei punti
  int** G = new int*[serate];
  for (int i = 0; i < serate; i++) {
    G[i] = new int[maxlen];
    for (int j = 0; j < maxlen; j++) {
      G[i][j] = 0;
    }
  }
  for (int i = 0; i < serate; i++) {
    analizza_sera(i, lunghezze[i], finali[i], G, chi[i], inf, available);
  }
  int** P = new int*[serate + 1];
  for (int i = 0; i <= serate; i++) {
    P[i] = new int[travestimenti + 2];
    P[i][0] = inf;
  }
  for (int i = 1; i < travestimenti + 2; i++) {
    P[serate][i] = 0;
  }
  /* FORMATO OUTPUT
   * un numero che rappresenta il massimo numero di istanti in cui
   * Sherlock può avere il travestimento adatto
   */
fout.open("output.txt", ios::out);
fout << fapunti(P, serate, travestimenti, G, lunghezze, available) << endl;
fout.close();

return 0;
}

//magica funzione risolvi i nostri problemi, amen
int fapunti(int** P, int serate, int travestimenti, int** G, int* lunghezze, int available) {
  available += serate - 1;
  for (int s = serate - 1; s >= 0; s--) {
    int trav = min(available, lunghezze[s]);
    for (int rim = 1; rim <= travestimenti + 1; rim++) {
      int m = P[s +1][rim];
      for (int k = 1; k < rim && k <= trav; k++) {
        m = max(m, P[s + 1][rim - k] + G[s][k - 1]);
      }
      P[s][rim] = m;
    }
    available--;
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

void analizza_sera(int serata, int len, int finale, int** G, int* chi, int inf, int available) {
  int*** S = new int**[len + 1];
  for (int i = 0; i <= len; i++) {
    S[i] = new int*[len + 2];
    for (int j = 0; j < len + 2; j++) {
      S[i][j] = new int[2];
      S[i][j][0] = S[i][j][1] = 0; 
    }
    S[i][0][0] = S[i][0][1] = inf;
  }
  bool pari = false;
  available = min(available, len);
  for (int ist = len - 1; ist > 0; ist--) {
    for (int rim = 1; rim <= available + 1; rim++) {
      S[ist][rim][true] = max(S[ist + 1][rim][true] + g(chi[ist], true, finale, pari),
          S[ist + 1][rim - 1][false] + g(chi[ist], false, finale, pari));
      S[ist][rim][false] = max(S[ist + 1][rim][false] + g(chi[ist], false, finale, pari),
          S[ist + 1][rim - 1][true] + g(chi[ist], true, finale, pari));
    } 
    pari = !pari;
  } 
  for (int rim = 1; rim <= available; rim++) {
    int m = 0;
    m = max(m, S[1][rim][true] + g(chi[0], true, finale, pari));
    m = max(m, S[1][rim][false] + g(chi[0], false, finale, pari));
    G[serata][rim - 1] = m;
  }
  delete S;
}
