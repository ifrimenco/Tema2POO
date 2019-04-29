#ifndef WEAPON_H
#define WEAPON_H

#include <utility>
#include <string>

// clasa abstracta Weapon
class Weapon {
protected:
    std::pair <unsigned, unsigned> Damage;
    unsigned AttackRange;
    std::string Type;

public:
    Weapon(std::pair <unsigned, unsigned>, unsigned, std::string);
    Weapon();
    virtual ~Weapon();
    virtual int GetDamage(int) = 0; // functie virtuala pura
    virtual void AddArrows() = 0;
    std::string GetType() const;
    int GetAttackRange() const;
};

#endif // WEAPON_H
