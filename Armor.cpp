#include "Armor.h"

#include <iostream>

Armor::Armor(std::string Typ, int Red, int Mov) :
    Type(Typ),
    DmgReduction(Red),
    MovReduction(Mov) {}


std::string Armor::GetType() {
    return Type;
}

int Armor::GetMovReduction() const {
    return MovReduction;
}

int Armor::GetDmgReduction() const {
    return DmgReduction;
}
Armor::~Armor() {}
