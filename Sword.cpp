#include "Sword.h"

Sword::Sword() :
    Weapon(std::make_pair(20, 30), 1, "Sword") {}

Sword::~Sword() {}

int Sword :: GetDamage(int Seed) {
    return Damage.first + Seed % (Damage.second - Damage.first + 1);
}
