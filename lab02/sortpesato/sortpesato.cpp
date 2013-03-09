#include <fstream>

using namespace std;

int A[100000], n;

int main() {
    fstream fin, fout;
    fin.open("input.txt", ios::in);
    fin >> n;
    for (int i = 0; i < n; i++) {
        fin >> A[i];
    }
    fin.close();

    int start, now, ciclePos;
    int progress = 0, swaps = 0, price = 0;
    int cicleLength = 0, cicleSum = 0, cicleMin = 0;
    while (progress < n) {
        start = now = A[progress];
        ciclePos = progress;
        while (now != (ciclePos + 1) && now > -1) {
            cicleLength++;
            cicleSum += now;
            if (now < cicleMin || cicleMin == 0) {
                cicleMin = now;
            }
            A[ciclePos] = -1;
            ciclePos = now - 1;
            now = A[ciclePos];
        }
        if (cicleLength > 1) {
            swaps += cicleLength - 1;
        }
        price += cicleSum + (cicleLength - 2) * cicleMin;
        cicleLength = 0;
        cicleSum = 0;
        cicleMin = 0;
        progress++;
    }

    fout.open("output.txt", ios::out);
    fout << swaps << " " << price << endl;
    fout.close();

    return 0;
}
