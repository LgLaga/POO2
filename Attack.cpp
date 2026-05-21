#include "Attack.h"

using namespace std;

istream& operator>>(std::istream& in, Attack& attack) {
    in >> attack.Name >> attack.RAMUsage >> attack.CPUUsage >> attack.Cost;
    char dummy;
    in >> dummy;
    getline(in, attack.Description, '|');
    in >> attack.AttackPower 
       >> attack.StealthLevel 
       >> attack.Duration 
       >> attack.timeRemaining
       >> attack.isActive 
       >> attack.isAutomated;

    return in;
}

int Attack::getAttackPower() const {
    return AttackPower;
}
int Attack::getStealthLevel() const {
    return StealthLevel;
}
int Attack::getDuration() const {
    return Duration;
}
bool Attack::getIsActive() const {
    return isActive;
}
bool Attack::getIsAutomated() const {
    return isAutomated;
}  
int Attack::getTimeRemaining() const {
    return timeRemaining;
}
void Attack::setAttackPower(int power) {
    AttackPower = power;
}
void Attack::setStealthLevel(int stealth) {
    StealthLevel = stealth;
}
void Attack::setDuration(int duration) {
    Duration = duration;
}
void Attack::setTimeRemaining(int time) {
    timeRemaining = time;
}
void Attack::setIsActive(bool active) {
    isActive = active;
}
void Attack::setIsAutomated(bool automated) {
    isAutomated = automated;
}
void Attack::setTargetServerIP(const string& ip) {
    TargetServerIP = ip;
}
string Attack::getTargetServerIP() {
    return TargetServerIP;
}   