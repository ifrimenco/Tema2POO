#ifndef SWORD_H
#define SWORD_H


#include "Weapon.h"


class Sword : public Weapon {

public:
    Sword();
    ~Sword();
    int GetDamage(int);
    void AddArrows() {}
};

#endif // SWORD_H
