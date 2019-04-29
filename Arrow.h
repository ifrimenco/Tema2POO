#ifndef ARROW_H
#define ARROW_H

#include <Weapon.h>


class Arrow : public Weapon {

public:
    Arrow();
    ~Arrow();
    int GetDamage(int);
    void AddArrows() {}
};

#endif // ARROW_H
