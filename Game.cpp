#include "Game.h"

#include <iostream>
#include <queue>

Game::Game(pair <unsigned, unsigned> Dim, unsigned Count, int Seed) :
    PlayerCount(Count),
    InitialCount(Count) {
        A = new Map(Dim);
        Rand = new XorShift(Seed);
        Players = new Agent*[Count];
        VizMap = new set <int> *[Dim.first];
        for (int i = 0; i < Dim.first; ++i)
            VizMap[i] = new set <int>[Dim.second];
}



void Game::ClearScreen() const { // functie care 'curata' ecranul
    for (unsigned i = 0; i < 25; ++i)
        std::cout << "\n";
}
/* inline void Game::SetPlayerCount(unsigned Count) {
    PlayerCount = Count;
    cout << Count << "AA";
    Players = new Agent*[PlayerCount];
}*/

unsigned Game::GetPlayerCount() { // Returneaza nr. Agenti
    return PlayerCount;
}

void Game::CreateAgent(Agent* Smith) { // Adauga agentul pe lista de agenti ai jocului
    Players[Smith->GetIndex()] = Smith;
    A->SetAgent(Smith->GetPosition().first, Smith->GetPosition().second, Smith);
}

void Game::GenerateObjects() { // Genereaza obiectele hartii - maxim 8 de fiecare, pe pozitii random



    for (int i = 0, j = 0; i < 8 && j < A->GetWidth() * A->GetLength(); ++i, ++j) { // generez sabiile
    int Seed = Rand->GetRandomNumber(0, A->GetLength() * A->GetWidth() - 1);
    if (A->GetWeapon(Seed / A->GetWidth(), Seed % A->GetWidth()) == NULL) {
        Weapon* W = new Sword();
        A->SetWeapon(Seed / A->GetWidth(), Seed % A->GetWidth(), W);
        }
    else j--;
    }

    for (int i = 0, j = 0; i < 8 && j < A->GetWidth() * A->GetLength(); ++i, ++j) { // generez sagetile
    int Seed = Rand->GetRandomNumber(0, A->GetLength() * A->GetWidth() - 1);
    if (A->GetWeapon(Seed / A->GetWidth(), Seed % A->GetWidth()) == NULL) {
        Weapon* W = new Arrow();
        A->SetWeapon(Seed / A->GetWidth(), Seed % A->GetWidth(), W);
        }
    else j--;
    }

    for (int i = 0, j = 0; i < 8 && j < A->GetWidth() * A->GetLength(); ++i, ++j) { // generez arcurile
    int Seed = Rand->GetRandomNumber(0, A->GetLength() * A->GetWidth() - 1);
    if (A->GetWeapon(Seed / A->GetWidth(), Seed % A->GetWidth()) == NULL) {
        Weapon* W = new Bow();
        A->SetWeapon(Seed / A->GetWidth(), Seed % A->GetWidth(), W);
        }
    else j--;
    }

    for (int i = 0, j = 0; i < 8 && j < A->GetWidth() * A->GetLength(); ++i, ++j) { // generez topoarele
    int Seed = Rand->GetRandomNumber(0, A->GetLength() * A->GetWidth() - 1);
    if (A->GetWeapon(Seed / A->GetWidth(), Seed % A->GetWidth()) == NULL) {
        Weapon* W = new BattleAxe();
        A->SetWeapon(Seed / A->GetWidth(), Seed % A->GetWidth(), W);
        }
    else j--;
    }


    for (int i = 0, j = 0; i < 8 && j < A->GetWidth() * A->GetLength(); ++i, ++j) { // generez Light Armor
    int Seed = Rand->GetRandomNumber(0, A->GetLength() * A->GetWidth() - 1);
    if (A->GetArmor(Seed / A->GetWidth(), Seed % A->GetWidth()) == NULL) {
        Armor* W = new LightArmor();
        A->SetArmor(Seed / A->GetWidth(), Seed % A->GetWidth(), W);
        }
    else j--;
    }

    for (int i = 0, j = 0; i < 8 && j < A->GetWidth() * A->GetLength(); ++i, ++j) { // generez Medium Armor
    int Seed = Rand->GetRandomNumber(0, A->GetLength() * A->GetWidth() - 1);
    if (A->GetArmor(Seed / A->GetWidth(), Seed % A->GetWidth()) == NULL) {
        Armor* W = new MediumArmor();
        A->SetArmor(Seed / A->GetWidth(), Seed % A->GetWidth(), W);
        }
    else j--;
    }

    for (int i = 0, j = 0; i < 8 && j < A->GetWidth() * A->GetLength(); ++i, ++j) { // generez Heavy Armor
    int Seed = Rand->GetRandomNumber(0, A->GetLength() * A->GetWidth() - 1);
    if (A->GetArmor(Seed / A->GetWidth(), Seed % A->GetWidth()) == NULL) {
        Armor* W = new HeavyArmor();
        A->SetArmor(Seed / A->GetWidth(), Seed % A->GetWidth(), W);
        }
    else j--;
    }

}

ostream& operator<< (ostream& out, const Game& Joc) { // Supraincarcarea operatorului <<
    out << Joc.GetMap(); // Afisez harta
    return out;
}

Map* Game::GetMap() const { // returneaza harta aferenta jocului curent
    return A;
}

void Game::Play(int Type, int Round) {
    int Index = 0; int Rond = 0;
    CurrPlayer = Players[Index];
    while (PlayerCount > 1) {
        DoBestMove(CurrPlayer);
        Index++;
        Rond++;
        Index %= PlayerCount;
        CurrPlayer = Players[Index];
        if (Type == 1) PrintCurrRound();
        if (Type == 2 && Round == Rond) PrintCurrRound();
    }

    cout << "Castigatorul este " << Players[0]->GetName() << " cu " << Players[0]->GetKills() << " Kill-uri!\n";
}

void Game::DoBestMove(Agent* Smith) {
    // de imbunatatit 'AI'-ul
    int Row[4] = {-1, 0, 1, 0};
    int Col[4] = {0, -1, 0, 1};
    // Folosesc Algoritmul lui lee pentru a afla toate pozitiile posibile pana in range-ul agentului curent
    vector <pair < pair <int, int>, int> > Q; // membrul stang pair este pozitia, iar membrul drept
                                              // reprezinta nr. de pasi necesari pt a ajunge la pozitia respectiva
    int Mov = Smith->GetMovementSpeed();
    unsigned First = 0;

    Q.push_back(make_pair(Smith->GetPosition(), 0)); // bagam in coada pozitia agentului si 0
    bool Moved = false;
    int SmithX = Smith->GetPosition().first;
    int SmithY = Smith->GetPosition().second;
    while (First < Q.size()) {
        if (Moved == true) break; // agentii au voie sa faca doar o mutare pe runda
        int x = Q[First].first.first; // pozitia curenta
        int y = Q[First].first.second;
        int Steps = Q[First].second;

        if (Steps < Mov - 1) {
            for (int i = 0; i < 4; ++i) {
                if (x + Row[i] >= A->GetLength() || x + Row[i] < 0 || y + Col[i] < 0 || y + Col[i] >= A->GetWidth()) continue;
                if (VizMap[x + Row[i]][y + Col[i]].find(Smith->GetIndex()) == VizMap[x + Row[i]][y + Col[i]].end()) {// daca n-a mai fost adaugata in coada pozitia (x,y)
                    VizMap[x + Row[i]][y + Col[i]].insert(Smith->GetIndex());
                    Q.push_back(make_pair(make_pair(x + Row[i], y + Col[i]), Steps + 1));
                }
            }
        }

        if (Smith->GetCurrWeapon() != NULL && Moved == false && A->GetAgent(x, y) != NULL && A->GetAgent(x, y) != Smith) {
                if (Smith->GetCurrWeapon()->GetAttackRange() >= Steps) {
                Moved = true;
                int Seed = Rand->GetRandomNumber();
                Smith->Attack(Seed, A->GetAgent(x, y));
                if (A->GetAgent(x, y)->GetHealth() <= 0) {
                    EliminateAgent(A->GetAgent(x, y));
                }
            }
        }

        if (A->GetAgent(x, y) == NULL || A->GetAgent(x, y) == Smith) {
            // Daca a adunat vreun obiect Agentul nu mai poate ataca
            if (Smith->GetCurrWeapon() != NULL &&  A->GetWeapon(x, y) != NULL)
                if (Smith->GetCurrWeapon()->GetType() == "Bow" && A->GetWeapon(x, y)->GetType() == "Arrow") {
                    if (Moved == false) {
                        A->Move(Smith, make_pair(x, y));
                        Moved = true;
                        Smith->GetCurrWeapon()->AddArrows();
                        delete A->GetWeapon(x, y);
                        A->SetWeapon(x, y, NULL);
                    }
                }

            if (Smith->GetCurrWeapon() == NULL  && A->GetWeapon(x, y) != NULL && A->GetWeapon(x, y)->GetType() != "Arrow") {
                if (Smith->GetType() != "Scout" || A->GetWeapon(x, y)->GetType() != "BattleAxe") {  // ma asigur ca scoutul nu poate lua toporul
                    if (Moved == false) {
                        A->Move(Smith, make_pair(x, y));
                        Moved = true;
                        Smith->SetCurrWeapon(A->GetWeapon(x, y));
                        A->SetWeapon(x, y, NULL);
                    }
                }
            }

            if (Smith->GetCurrArmor() == NULL && A->GetArmor(x, y) != NULL) {
                if (Smith->GetType() != "Scout" || A->GetArmor(x, y)->GetType() != "HeavyArmor") { // ma asigur ca scoutul nu poate lua HeavyArmor
                    if (Moved == false) {
                        A->Move(Smith, make_pair(x, y));
                        Moved = true;
                        Smith->SetCurrArmor(A->GetArmor(x, y));
                        A->SetArmor(x, y, NULL);
                    }
                }
            }
        }
        First++;
    }
    // daca nu s-a mutat deloc agentul il voi muta intr-o pozitie aleatoare
    if (Moved == false) {

    // mi-a fost mai usor sa fac cu goto decat cu while
ReRoll:
        int Seed = Rand->GetRandomNumber(1, Q.size() - 1);
        if (A->GetAgent(Q[Seed].first.first, Q[Seed].first.second) == NULL) {
           // cout << Q[Seed].first.first << " " << Q[Seed].first.second;
            A->Move(Smith, Q[Seed].first);
            Moved = true;
        }
        else goto ReRoll;
    }
    RemoveVisitedBlocks(Smith);
}

void Game::EliminateAgent(Agent* Dead) {
    for (int i = 0; i < PlayerCount; ++i) {
        if (Players[i] == Dead) {
            A->SetAgent(Players[i]->GetPosition().first, Players[i]->GetPosition().second, NULL);
            delete Players[i];
            for (int j = i + 1; j < PlayerCount; ++j)
                Players[j - 1] = Players[j];
            break;
        }
    }
    PlayerCount--;
}

void Game::RemoveVisitedBlocks(Agent* S) {
    int i, j;
    for (i = 0; i < A->GetLength(); ++i)
        for (j = 0; j < A->GetWidth(); ++j)
            VizMap[i][j].erase(S->GetIndex());
}

void Game::PrintCurrRound() {
    cout << "Harta:\n";
    cout << *A << "\n";
    for (int i = 0; i < PlayerCount; ++i) {
        cout << Players[i]->GetName() << ": " << Players[i]->GetKills() << " Kill-uri\n";
    }
}

Game::~Game() { // destructor - dezaloc memoria alocata dinamic
    delete Rand;
    unsigned i;
    for (i = 0; i < PlayerCount; ++i) {
        delete Players[i];
    }
    delete[] Players;
    for (i = 0; i < A->GetLength(); ++i)
        delete[] VizMap[i];
    delete[] VizMap;
    delete A;
    cout << "GAME OVER!\n";
}



