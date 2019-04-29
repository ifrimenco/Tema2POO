#include "Agent.h"

#include <iostream>
Agent::Agent(string AgentType, pair <unsigned, unsigned> Pos, string Str, int Hp, int Dmg, int VisRange, int Steps) :
    Type(AgentType),
    Name(Str),
    Position(Pos),
    Health(Hp),
    Index(PlayersAlive++),
    Kills(0),
    BaseDmg(Dmg),
    VisibilityRange(VisRange),
    MovementSpeed(Steps),
    CurrWeapon(NULL),
    CurrArmor(NULL) {}

string Agent::GetName() const { // Returneaza numele dat de utilizator agentului
    return Name;
}

unsigned Agent::GetIndex() const { // returneaza indexul agentului (pentru indexarea in vectorul cu playeri din Game.h)
    return Index;
}

pair <unsigned, unsigned> Agent::GetPosition() { // returneaza pozitia agentului
    return Position;
}

void Agent::SetCurrWeapon(Weapon* W) { // seteaza arma curenta a agentului
    CurrWeapon = W;
}

unsigned Agent::GetMovementSpeed() const {
    if (CurrArmor == NULL) return MovementSpeed;
    else return MovementSpeed - CurrArmor->GetMovReduction();
}

Armor* Agent::ChangeArmor() {
    Armor *A = CurrArmor;
    CurrArmor = NULL;
    return A;
}

Weapon* Agent::ChangeWeapon() {
    Weapon* A = CurrWeapon;
    CurrWeapon = NULL;
    return A;
}

Agent::~Agent() {
    std::cout << "\nAgentul " << Name << " a murit!\n";
    PlayersAlive--;
    // dezaloc memoria pentru arma si armura
    // De implementat in viitor - DropWeapon si DropArmor cand moare;
    if (CurrWeapon != NULL) delete CurrWeapon;
    if (CurrArmor != NULL) delete CurrArmor;
}

Weapon* Agent::GetCurrWeapon() const {
    return CurrWeapon;
}

Armor* Agent::GetCurrArmor() const {
    return CurrArmor;
}


string Agent::GetType() const {
    return Type;
}

void Agent::DecreaseHealth(int Dmg) {
    Health -= Dmg;
}

int Agent::GetDmgReduction() const {
    if (CurrArmor == NULL) return 0;
    else return CurrArmor->GetDmgReduction();
}

void Agent::Attack(int Seed, Agent* Target) {

    Target->DecreaseHealth(GetDamage(Seed) - Target->GetDmgReduction());
    if (Target->Health <= 0) Kills++, PlayersAlive--;
}

int Agent::GetHealth() const {
    return Health;
}

int Agent::GetKills() const {
    return Kills;
}
