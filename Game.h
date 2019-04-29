#ifndef GAME_H
#define GAME_H


#include "Map.h"
#include "Agent.h"
#include "XorShift.h"
#include "Scout.h"
#include "Weapon.h"
#include "Armor.h"
#include "Bow.h"
#include "BattleAxe.h"
#include "Sword.h"
#include "LightArmor.h"
#include "MediumArmor.h"
#include "HeavyArmor.h"

#include <vector>
#include <fstream>
#include <set>

class Game {
    Map *A;
    Agent** Players;
    unsigned PlayerCount, InitialCount;
    Agent* CurrPlayer;
    set <int>** VizMap;
    XorShift* Rand;
public:
    Map* GetMap() const;
    inline void SetPlayerCount(unsigned);
    unsigned GetPlayerCount();
    void CreateAgent(Agent*);
    Game(pair <unsigned, unsigned>, unsigned, int);
    friend ostream& operator<<(ostream&, const Game&);
    ~Game();
    void ClearScreen() const;
    void GenerateObjects();
    void RemoveVisitedBlocks(Agent*);
    void EliminateAgent(Agent*);
    void DoBestMove(Agent*);
    void Play(int, int);
    void PrintCurrRound();
};

#endif // GAME_H
