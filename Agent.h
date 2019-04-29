#ifndef AGENT_H
#define AGENT_H

/// Clasa abstracta Agent

#include <utility>
#include <string>

#include "Weapon.h"
#include "Armor.h"
#include "XorShift.h"

using namespace std;

// de implementat - clasa Tank, Fighter
class Agent {
protected:
    string Type;
    string Name;
    pair <unsigned, unsigned> Position;
    int Health;
    static unsigned PlayersAlive;
    unsigned Index;
    unsigned Kills;
    int BaseDmg;
    int VisibilityRange;
    int MovementSpeed;
    Weapon* CurrWeapon;
    Armor* CurrArmor;

public:
    Agent(string, pair <unsigned, unsigned>, string, int, int, int, int);
    friend class Map;
    virtual void SetCurrWeapon(Weapon*) = 0; // functie virtuala pura pentru ca Scout nu poate purta BattleAxe
    virtual void SetCurrArmor(Armor*) = 0; // functie virtuala pura pentru ca Scout nu poate purta heavy armor;
    virtual void UniqueAbility(int) = 0; // Abilitatea unica a fiecarui agent - functie virtuala pura
    virtual int GetDamage(int) = 0;
    virtual ~Agent(); // Destructorul virtual
    Weapon* ChangeWeapon();
    Armor* ChangeArmor();
    Weapon* GetCurrWeapon() const;
    Armor* GetCurrArmor() const;
    unsigned GetMovementSpeed() const;
    unsigned GetIndex() const;
    int GetDmgReduction() const;
    int GetHealth() const;
    int GetKills() const;
    void Attack(int, Agent*);
    string GetType() const;
    void DecreaseHealth(int);
    string GetName() const;
    pair <unsigned, unsigned> GetPosition();
};

#endif // AGENT_H
