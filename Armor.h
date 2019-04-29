#ifndef ARMOR_H
#define ARMOR_H

#include <string>

class Armor
{
protected:
    std::string Type;
    int DmgReduction;
    int MovReduction;
public:
    Armor(std::string, int, int); // constructor
    virtual ~Armor() = 0; // destructor virtual pur
                          // pentru a asigura abstractizarea clasei Armor
                          // il voi lasa asa daca nu gasesc idei pentru alte functii virtuale
    std::string GetType(); // returneaza tipul armurii - necesar pentru Scout
    int GetMovReduction() const; // returneaza Movement Speed Reduction
    int GetDmgReduction() const;
};

#endif // ARMOR_H
