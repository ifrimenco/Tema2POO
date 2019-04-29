#include "Weapon.h"

Weapon::Weapon(std::pair <unsigned, unsigned> Dmg, unsigned Rng, std::string Typ) :
    Damage(Dmg),
    AttackRange(Rng),
    Type(Typ) {}

Weapon::Weapon() {}

Weapon::~Weapon() {}

int Weapon::GetAttackRange() const {
    return AttackRange;
}

std::string Weapon::GetType() const {
    return Type;
}

