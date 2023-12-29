//Nama : Agusmia Intan Sari
//NIM : 23343027
//Program : Program ini memungkinkan pemain bermain melawan komputer dalam permainan Tic-Tac-Toe.

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int UKURAN_PAPAN = 3;

enum Sel {
    KOSONG,
    X,
    O
};

struct Gerakan {
    int baris;
    int kolom;
};

void tampilkanPapan(const vector<vector<Sel> >& papan) {
    for (int i = 0; i < UKURAN_PAPAN; ++i) {
        for (int j = 0; j < UKURAN_PAPAN; ++j) {
            switch (papan[i][j]) {
                case KOSONG:
                    cout << "   ";
                    break;
                case X:
                    cout << " X ";
                    break;
                case O:
                    cout << " O ";
                    break;
            }

            if (j < UKURAN_PAPAN - 1) {
                cout << "|";
            }
        }

        cout << endl;

        if (i < UKURAN_PAPAN - 1) {
            cout << "-----------\n";
        }
    }
}

bool apakahGerakanValid(const vector<vector<Sel> >& papan, int baris, int kolom) {
    return (baris >= 0 && baris < UKURAN_PAPAN && kolom >= 0 && kolom < UKURAN_PAPAN && papan[baris][kolom] == KOSONG);
}

bool apakahPapanPenuh(const vector<vector<Sel> >& papan) {
    for (int i = 0; i < UKURAN_PAPAN; ++i) {
        for (int j = 0; j < UKURAN_PAPAN; ++j) {
            if (papan[i][j] == KOSONG) {
                return false;
            }
        }
    }
    return true;
}

bool cekMenang(const vector<vector<Sel> >& papan, Sel pemain) {
    for (int i = 0; i < UKURAN_PAPAN; ++i) {
        // Periksa baris dan kolom
        if ((papan[i][0] == pemain && papan[i][1] == pemain && papan[i][2] == pemain) ||
            (papan[0][i] == pemain && papan[1][i] == pemain && papan[2][i] == pemain)) {
            return true;
        }
    }

    // Periksa diagonal
    if ((papan[0][0] == pemain && papan[1][1] == pemain && papan[2][2] == pemain) ||
        (papan[0][2] == pemain && papan[1][1] == pemain && papan[2][0] == pemain)) {
        return true;
    }

    return false;
}

Gerakan dapatkanGerakanPemain() {
    Gerakan gerakan;
    cout << "Masukkan gerakan Anda (baris dan kolom, contohnya 1 2): ";
    cin >> gerakan.baris >> gerakan.kolom;
    return gerakan;
}

Gerakan dapatkanGerakanKomputer(const vector<vector<Sel> >& papan) {
    Gerakan gerakan;

    do {
        gerakan.baris = rand() % UKURAN_PAPAN;
        gerakan.kolom = rand() % UKURAN_PAPAN;
    } while (!apakahGerakanValid(papan, gerakan.baris, gerakan.kolom));

    return gerakan;
}

int main() {
    srand(static_cast<unsigned>(time(0)));

    vector<vector<Sel> > papan(UKURAN_PAPAN, vector<Sel>(UKURAN_PAPAN, KOSONG));
    bool giliranPemain = true; // true untuk pemain, false untuk komputer

    cout << "Selamat datang di permainan Tic-Tac-Toe!\n";
    tampilkanPapan(papan);

    while (true) {
        Gerakan gerakan;

        if (giliranPemain) {
            gerakan = dapatkanGerakanPemain();
        } else {
            cout << "Giliran komputer...\n";
            gerakan = dapatkanGerakanKomputer(papan);
        }

        if (!apakahGerakanValid(papan, gerakan.baris, gerakan.kolom)) {
            cout << "Gerakan tidak valid. Coba lagi.\n";
            continue;
        }

        papan[gerakan.baris][gerakan.kolom] = giliranPemain ? X : O;
        tampilkanPapan(papan);

        if (cekMenang(papan, giliranPemain ? X : O)) {
            cout << (giliranPemain ? "Anda menang!" : "Komputer menang!") << endl;
            break;
        }

        if (apakahPapanPenuh(papan)) {
            cout << "Ini seri!" << endl;
            break;
        }

        giliranPemain = !giliranPemain; // Ganti giliran
    }

    return 0;
}

