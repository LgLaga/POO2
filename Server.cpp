#include "Server.h"

using namespace std;

Server::Server(string name, string ip, int security, int data) 
    : Name(name), IPAddress(ip), SecurityLevel(security), DataValue(data) {}

string Server::getName() const {
    return Name;
}
string Server::getIPAddress() const {
    return IPAddress;
}
int Server::getSecurityLevel() const {
    return SecurityLevel;
}
int Server::getDataValue() const {
    return DataValue;
}
void Server::setName(string name) {
    Name = name;
}
void Server::setIPAddress(string ip) {
    IPAddress = ip;
}
void Server::setSecurityLevel(int security) {
    SecurityLevel = security;
}
void Server::setDataValue(int data) {
    DataValue = data;
} 
std::istream& operator>>(std::istream& in, Server& server) {
    in >> server.Name >> server.IPAddress >> server.SecurityLevel >> server.DataValue;
    return in;
}

void Server::print() const {
    cout << "Name: " << Name << endl;
    cout << "IP Address: " << IPAddress << endl;
    cout << "Security Level: " << SecurityLevel << endl;
    cout << "Data Value: " << DataValue << endl;
}

void Server::describe() const {
    cout << "Server " << Name << " at " << IPAddress << " has a security level of " << SecurityLevel 
         << " and contains data valued at " << DataValue << "." << endl;
}

