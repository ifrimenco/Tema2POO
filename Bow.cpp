#include "Bow.h"

#include <iostream>

Bow::Bow() :
    Weapon(std::make_pair(10, 25), 7, "Bow"),
    ArrowCount(5) {}

Bow::~Bow() {
    //dtor
}

int Bow::GetDamage(int Seed) {
    if (ArrowCount == 0) return -100; // ma asigur ca un agent fara sageti nu va da Damage
    ArrowCount--;
    return Damage.first + Seed % (Damage.second - Damage.first + 1);
}

void Bow::AddArrows() {
    ArrowCount += 5;
}





