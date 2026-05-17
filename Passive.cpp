#include "Passive.h"

using namespace std;

std::istream& operator>>(std::istream& in, Passive& passive) {
    in >> passive.Name >> passive.RAMUsage >> passive.CPUUsage >> passive.Cost;
    char dummy;
    in >> dummy; 
    getline(in, passive.Description, '|'); 
    

    
    in >> passive.BonusProcessingPower 
       >> passive.BonusRAM 
       >> passive.PassiveMoney;

    return in;
}

int Passive::getBonusProcessingPower() const {
    return BonusProcessingPower;
}

int Passive::getBonusRAM() const {
    return BonusRAM;
}
int Passive::getPassiveMoney() const {
    return PassiveMoney;
}
