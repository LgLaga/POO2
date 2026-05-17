#ifndef SERVER_H
#define SERVER_H
#include <string>
#include <iostream>

using namespace std;

class Server {
private:
    string Name;
    string IPAddress;
    int SecurityLevel;
    int DataValue;
public:
    Server() = default;
    string getName() const;
    string getIPAddress() const;
    int getSecurityLevel() const;
    int getDataValue() const;
    Server(string name, string ip, int security, int data);
    Server(const Server& other) = default;
    friend istream& operator>>(std::istream& in, Server& server);
    void setName(string name);
    void setIPAddress(string ip);
    void setSecurityLevel(int security);
    void setDataValue(int data);
};

#endif // SERVER_H