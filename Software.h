#ifndef SOFTWARE_H
#define SOFTWARE_H

#include <string>

using namespace std;

class Software
{
protected:
    string Name;
    int RAMUsage;
    int CPUUsage;
    int Cost;
    string Description; 
public:
    Software(string name, int ram, int cpu, int cost, string description) : Name(name), RAMUsage(ram), CPUUsage(cpu), Cost(cost), Description(description) {}
    Software() : Name(""), RAMUsage(0), CPUUsage(0), Cost(0), Description("") {}
    Software(const Software& other) : Name(other.Name), RAMUsage(other.RAMUsage), CPUUsage(other.CPUUsage), Cost(other.Cost), Description(other.Description) {}
    virtual ~Software() = default;
    virtual void print();
    virtual int getAttackPower() const { return 0; } 
    virtual int getStealthLevel() const { return 0; } 
    virtual int getDuration() const { return 0; }
    virtual int getTimeRemaining() const { return 0; }
    virtual bool getIsActive() const { return false; }
    virtual bool getIsAutomated() const { return false; }
    virtual void setAttackPower(int power) {}
    virtual void setStealthLevel(int stealth) {}
    virtual void setDuration(int duration) {}
    virtual void setTimeRemaining(int time) {}
    virtual void setIsActive(bool active) {}
    virtual void setIsAutomated(bool automated) {}
    virtual int getBonusProcessingPower() const { return 0; } 
    virtual int getBonusRAM() const { return 0; } 
    virtual int getPassiveMoney() const { return 0; } 
    virtual void setBonusProcessingPower(int power) {}
    virtual void setBonusRAM(int ram) {}
    virtual void setPassiveMoney(int money) {}
    virtual void setTargetServerIP(const string& ip) { return; }
    virtual string getTargetServerIP() { return ""; }
    int getCost() const;
    int getRAMUsage() const;
    int getCPUUsage() const;
    string getName() const;
    string getDescription() const;
    void setName(string name);
    void setDescription(string description);
    void setRAMUsage(int ram);
    void setCPUUsage(int cpu);
    void setCost(int cost);
};

#endif // SOFTWARE_H