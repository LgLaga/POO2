#include "Software.h"
#include <string>
#include <iostream>

using namespace std;

int Software::getCost() const {
    return Cost;
}
int Software::getRAMUsage() const {
    return RAMUsage;
}
int Software::getCPUUsage() const {
    return CPUUsage;
}
string Software::getName() const {
    return Name;
}
void Software::setName(string name) {
    Name = name;
}
void Software::setRAMUsage(int ram) {
    RAMUsage = ram;
}
void Software::setCPUUsage(int cpu) {  
    CPUUsage = cpu;
}
void Software::setCost(int cost) {
    Cost = cost;
}   
string Software::getDescription() const {
    return Description;
}
void Software::setDescription(string description) {
    Description = description;
}
void Software::print() {
    cout << "Name: " << Name << endl;
    cout << "RAM Usage: " << RAMUsage << " GB" << endl;
    cout << "CPU Usage: " << CPUUsage << " units" << endl;
    cout << "Cost: $" << Cost << endl;
    cout << "Description: " << Description << endl;
}