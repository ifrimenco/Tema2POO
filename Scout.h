#ifndef SCOUT_H
#define SCOUT_H

#include <Agent.h>

/// Clasa derivata Scout
// Pros: Vizibilitate si agilitate mai mare
//       sansa 10% la lovitura Critica
// Cons: Squishy
//       Nu poate purta Heavy Armor si nici BattleAxe
//       Dependent de arc



class Scout : public Agent {

public:
    Scout(pair <unsigned, unsigned>, string);
    void UniqueAbility(int);
    void SetCurrWeapon(Weapon*);
    void SetCurrArmor(Armor*);
    int GetDamage(int);
};

#endif // SCOUT_H
