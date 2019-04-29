#include "Scout.h"
#include <iostream>

Scout::Scout(pair <unsigned, unsigned> Pos, string Str) :
    Agent("Scout", Pos, Str, 130, 7, 7, 3) {

}

void Scout::UniqueAbility(int Seed) {
/// De Implementat
}

void Attack(Agent *A) {
    // CurrWeapon->Attack(*this, Agent *A);
}


int Scout::GetDamage(int Seed) {
    int Crit = 1 + (1 == (Seed % 10));
    return Crit * (CurrWeapon->GetDamage(Seed) + BaseDmg);
}

void Scout::SetCurrArmor(Armor* A) {
    if (A->GetType() == "HeavyArmor") return;
    else CurrArmor = A;
}

void Scout::SetCurrWeapon(Weapon* A) {
    if (A->GetType() == "BattleAxe") return;
    else CurrWeapon = A;
}
