#include "BattleAxe.h"

BattleAxe::BattleAxe() :
    Weapon(std::make_pair(30, 45), 2, "BattleAxe") {} // ctor

BattleAxe::~BattleAxe() {} // dtor


int BattleAxe::GetDamage(int Seed) {
    return Damage.first + Seed % (Damage.second - Damage.first + 1);
}
