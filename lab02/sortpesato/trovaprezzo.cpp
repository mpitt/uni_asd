#include <fstream>
#include <iostream>

using namespace std;

int A[100];

int main(int argc, char ** argv) {
    if (argc != 2) {
        cout << "Usage: trovaprezzo <input_file>" << endl;
        return 1;
    }

    fstream fin;
    fin.open(argv[1]);

    if (fin.fail()) {
        cout << "[ERROR] Cannot open " << argv[1] << endl;
        return 1;
    }

    return 0;
}

