#ifndef PASSIVE_H
#define PASSIVE_H
#include "Software.h"
#include <string>
#include <iostream>

using namespace std;

class Passive : public Software
{
protected:
    int BonusProcessingPower;
    int BonusRAM;   
    int PassiveMoney;
public:
    Passive() : Software("", 0, 0, 0, ""), BonusProcessingPower(0), BonusRAM(0), PassiveMoney(0) {}
    Passive(string name, int ram, int cpu, int cost, string description, int bonusPower, int bonusRAM, int passiveMoney) 
    : Software(name, ram, cpu, cost, description), BonusProcessingPower(bonusPower), BonusRAM(bonusRAM), PassiveMoney(passiveMoney) {}
    Passive(const Passive& other) : Software(other), BonusProcessingPower(other.BonusProcessingPower), BonusRAM(other.BonusRAM), PassiveMoney(other.PassiveMoney) {}
    void print() override {
        Software::print();
        cout << "Bonus Processing Power: " << BonusProcessingPower << endl;
        cout << "Bonus RAM: " << BonusRAM << " MB" << endl;
        cout << "Passive Money: $" << PassiveMoney << endl;
    }
    friend istream& operator>>(istream &is, Passive &passive);
    int getBonusProcessingPower() const override;
    int getBonusRAM() const override;
    int getPassiveMoney() const override;
};
#endif