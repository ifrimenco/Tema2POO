#include "Map.h"

#include <iostream>

Map::Map (pair <unsigned, unsigned> Dim) : // Constructorul cu lista de initializare
    Length(Dim.first),
    Width(Dim.second) {
        cout << "S-a creat o harta de dimensiune " << Length << " x " << Width <<"\n";
        unsigned i, j;
        Matrix = new Point*[Length];
        for (i = 0; i < Length; ++i) { // Aloc spatiu in memorie pentru harta
            Matrix[i] = new Point[Width];
            for (j = 0; j < Width; ++j) {
                Matrix[i][j].CurrAgent = NULL;
                Matrix[i][j].CurrArmor = NULL;
                Matrix[i][j].CurrWeapon = NULL;
            }
        }
    }

Map::~Map() {
    for (unsigned i = 0; i < Length; ++i)
        for (unsigned j = 0; j < Width; ++j) {
            if (Matrix[i][j].CurrArmor != NULL)
                delete Matrix[i][j].CurrArmor;
            if (Matrix[i][j].CurrWeapon != NULL)
                delete Matrix[i][j].CurrWeapon;
        }
    for (unsigned i = 0; i < Length; ++i)
        delete[] Matrix[i];
    delete[] Matrix;
}

void Map::SetAgent(int Row, int Col, Agent* Player) {
    Matrix[Row][Col].CurrAgent = Player;
}

void Map::SetArmor(int Row, int Col, Armor* A) {
    Matrix[Row][Col].CurrArmor = A;
}

void Map::SetWeapon(int Row, int Col, Weapon* W) {
    Matrix[Row][Col].CurrWeapon = W;
}


ostream& operator<< (ostream& out, const Map& A) {
    unsigned i, j;
    out << " ";
    for (i = 0; i <= A.Width + 1; ++i)
        out << "___";
        out << "\n";

    for (i = 0; i < A.Length; ++i) {
        out << "||";
        for (j = 0; j < A.Width; ++j) {
            string buff;
            buff.resize(3);
            buff[0] = ' '; buff[1] = ' '; buff[2] = ' ';
            if (A.Matrix[i][j].CurrAgent != NULL)
                buff[0] = A.Matrix[i][j].CurrAgent->GetIndex() + 49;

            if (A.Matrix[i][j].CurrArmor != NULL) {
                Armor* X = A.Matrix[i][j].CurrArmor;
                if (X->GetType() == "HeavyArmor")
                    buff[1] = 'H';
                else if (X->GetType() == "MediumArmor")
                    buff[1] = 'M';
                else if (X->GetType() == "LightArmor")
                    buff[1] = 'L';
                }
            if (A.Matrix[i][j].CurrWeapon != NULL) {
                Weapon* X = A.Matrix[i][j].CurrWeapon;
                if (X->GetType() == "Bow")
                    buff[2] = 'B';
                else if (X->GetType() == "Arrow")
                    buff[2] = 'A';
                else if (X->GetType() == "Sword")
                    buff[2] = 'S';
                else if (X->GetType() == "BattleAxe")
                    buff[2] = 'T';
                }
            out << buff;
        }

        out << "||";
        out << "\n";
    }

    cout << " ";
    for (i = 0; i <= A.Width + 1; ++i)
        cout << "___";
    return out;
}

void Map::Move(Agent* A, pair <unsigned, unsigned> Pos) {
    SetAgent(A->Position.first, A->Position.second, NULL);
    A->Position = Pos;
    SetAgent(Pos.first, Pos.second, A);
}

int Map::GetLength() const {
    return Length;
}

int Map::GetWidth() const {
    return Width;
}

Armor* Map::GetArmor(int Row, int Column) const { // returneaza pointer catre armura din Matrix[Row][Column]
    return Matrix[Row][Column].CurrArmor; // returneaza pointer catre arma din Matrix[Row][Column]
}

Weapon* Map::GetWeapon(int Row, int Column) const {
    return Matrix[Row][Column].CurrWeapon;
}

Agent* Map::GetAgent(int Row, int Column) const {
    return Matrix[Row][Column].CurrAgent;
}




