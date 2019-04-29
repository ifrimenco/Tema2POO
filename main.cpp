
/// Tema 2 POO - 'The Shootout' - Ifrimenco Alexandru - Daniel
/// Deadline - 25.04.2019

#include <iostream>
#include <cstdio>
#include <fstream>
#include "Game.h"

using namespace std;
unsigned int Agent::PlayersAlive = 0;
ifstream fin("seed.in");

int main()
{
    cout << "~~~~~~PROIECT POO - IFRIMENCO ALEXANDRU - DANIEL~~~~~~\n\n\n";
    cout << "             ~~~~\\\\\\\\The Shootout////~~~~       \n\n\n\n";
    int Seed;
    fin >> Seed;
    char c;
    do {
        try {
            int Length, Width;
            int Count;
            cout << "Introdu dimensiunile Hartii\n";
            cout << "Lungime: ";
            cin >> Length;
            cout << "\nLatime: ";
            cin >> Width;
            cout << "\n\n\n";
            if (Length <= 0 || Width <= 0)
                throw(make_pair(Length, Width));
            cout << "\nIntrodu nr. agenti: ";
            cin >> Count;
            if (Count <= 0 || Count > Length * Width) throw Count;
            // Aloc dinamic memorie pentru Jocul curent
            Game *CurrGame = new Game(make_pair(Length, Width), Count, Seed);

            for (int i = 0; i < Count; ++i) {
                cout << "Numele agentului " << i + 1 << ": ";
                int X, Y;
                string Name;
                cin >> Name;
                bool OK = true;
                while (OK == true) {
                    try {
                        cout << "Pozitia (X, Y): ";
                        cin >> X >> Y; // Ma asigur ca datele de intrare vor fi corecte
                        if (X < 0 || Y < 0 || X >= Length || Y >= Width) throw make_pair(X, Y);
                        OK = false;
                        Agent* CurrAgent = new Scout(make_pair(X, Y), Name);
                        CurrGame->CreateAgent(CurrAgent);
                    }
                    catch (pair <int, int>) {
                        cout << "Pozitia agentului trebuie sa fie pozitiva si sa se incadreze in harta\n";
                    }
                }
            }

            int Type, Round = 0;
            do {
                try {
                    cout << "0 - Afisare doar castigator\n1 - Afisare fiecare runda\n2 - Afisare runda data\n";
                    cin >> Type;
                    if (Type < 0 || Type > 2) throw (Type); // Daca type nu este 0, 1 sau 2
                    if (Type == 2) {
                        cout << "Runda: ";
                        cin >> Round; // Nu am implementat un try catch pentru runda deoarece daca numarul nu e corect runda nu va fi afisata
                    }
                    CurrGame->GenerateObjects();
                    CurrGame->Play(Type, Round);
                    delete CurrGame;
                }

                catch (int) {
                    cout << "Tipul de joc nu a fost introdus corect:\n";
                }
            }  while (Type < 0 || Type > 2); // Ma asigur de corectitudinea datelor de intrare

        }
        catch (pair <int, int>) {
            cout << "Dimensiunile hartii trebuie sa fie numere intregi strict pozitive!\n\n\n";
        }

        catch (int) {
            cout << "Nr playeri trebuie sa fie pozitv si mai mic sau egal decat aria hartii\n";
        }

        cout << "\n\n\nY -> reluare joc cu date noi\nOrice alt caracter -> terminarea programului\n";
        cin >> c;
    }  while (c == 'Y');
}
