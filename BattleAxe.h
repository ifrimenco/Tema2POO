#ifndef BATTLEAXE_H
#define BATTLEAXE_H

#include <Weapon.h>


class BattleAxe : public Weapon
{

public:
    BattleAxe();
    ~BattleAxe();
    int GetDamage(int);
    void AddArrows() {}
};

#endif // BATTLEAXE_H
