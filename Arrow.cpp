#include "Arrow.h"

Arrow::Arrow() :
    Weapon(std::make_pair(0, 0), 0, "Arrow") {}

Arrow::~Arrow() {}


int Arrow::GetDamage(int Seed) {
    return 0;
}
