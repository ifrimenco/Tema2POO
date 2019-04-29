#ifndef MAP_H
#define MAP_H

#include "Agent.h"
#include "Weapon.h"
#include "Armor.h"
#include "XorShift.h"

using namespace std;

struct Point {
    Agent* CurrAgent;
    Weapon* CurrWeapon;
    Armor* CurrArmor;
};

class Map {
private:
    unsigned int Length, Width;
    Point **Matrix;
public:
    Map(pair <unsigned, unsigned>);
    ~Map();
    friend class Scout;
    void SetAgent(int, int, Agent*);
    void SetArmor(int, int, Armor*);
    void SetWeapon(int, int, Weapon*);
    void DelAgent(int, int);
    int GetLength() const;
    int GetWidth() const;
    Armor* GetArmor(int, int) const;
    Weapon* GetWeapon(int, int) const;
    Agent* GetAgent(int, int) const;
    void Print();
    friend ostream& operator<< (ostream&, const Map&);
    void Move(Agent*, pair <unsigned, unsigned>);

};

#endif // MAP_H
