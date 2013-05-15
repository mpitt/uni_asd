#include <fstream>
#include <iostream>
using namespace std;

int main() {
  //variabili
  fstream fin, fout;
  int n, m;

  //apro lo stream in entrata
  fin.open("input.txt", ios::in);
  // ... leggere i dati ...
  fin.close();

  /* FORMATO OUTPUT
   * un numero che rappresenta il massimo numero di istanti in cui
   * Sherlock può avere il travestimento adatto
   */

  fout.open("output.txt", ios::out);
  // ... scrivere il risultato ...
  fout.close();

  return 0;
}
