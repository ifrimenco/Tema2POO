#ifndef BOW_H
#define BOW_H

#include <Weapon.h>
#include "Arrow.h"

/// Clasa derivata Bow - Mosteneste clasa Weapon



class Bow : public Weapon {
int ArrowCount;
public:
    Bow();
    ~Bow();
    int GetDamage(int);
    void AddArrows();
};

#endif // BOW_H
