#ifndef ATTACK_H
#define ATTACK_H

#include "Software.h"
#include <iostream>
#include <string>


using namespace std;

class Attack : public Software
{
protected:
    int AttackPower;
    int StealthLevel;
    int Duration;
    int timeRemaining;
    bool isActive;
    bool isAutomated;
    string TargetServerIP;
public:
    Attack() : Software("", 0, 0, 0, ""), AttackPower(0), StealthLevel(0), Duration(0), timeRemaining(0), isActive(false), isAutomated(false), TargetServerIP("") {}
    Attack(string name, int ram, int cpu, int cost, string description, int power, int stealth, int duration, int time, bool active, bool automated) 
        : Software(name, ram, cpu, cost, description), AttackPower(power), StealthLevel(stealth), Duration(duration), timeRemaining(time), isActive(active), isAutomated(automated), TargetServerIP("") {}
    friend istream& operator>>(std::istream& in, Attack& attack);
    void print() override { 
        Software::print();
        cout << "Attack Power: " << AttackPower << endl;
        cout << "Stealth Level: " << StealthLevel << endl;
        cout << "Duration: " << Duration << " seconds" << endl;
        cout << "Time Remaining: " << timeRemaining << " seconds" << endl;
        cout << "Active: " << (isActive ? "Yes" : "No") << endl;
        cout << "Automated: " << (isAutomated ? "Yes" : "No") << endl;
    }
    Attack(const Attack& other) : Software(other), AttackPower(other.AttackPower), StealthLevel(other.StealthLevel), Duration(other.Duration), timeRemaining(other.timeRemaining), isActive(other.isActive), isAutomated(other.isAutomated), TargetServerIP(other.TargetServerIP) {}
    int getAttackPower() const override;
    void setTargetServerIP(const string& ip) override;
    int getStealthLevel() const override;
    int getDuration() const override;
    int getTimeRemaining() const override;
    bool getIsActive() const override;
    bool getIsAutomated() const override;
    void setAttackPower(int power) override;
    string getTargetServerIP() override;
    void setStealthLevel(int stealth) override;
    void setDuration(int duration) override;
    void setTimeRemaining(int time) override;
    void setIsActive(bool active) override;
    void setIsAutomated(bool automated) override;
};

#endif // ATTACK_H