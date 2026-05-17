#ifndef BACKBONE_H
#define BACKBONE_H
#include <string>
#include <vector>
#include <map>
#include "Software.h"
#include "Server.h"
#include "Attack.h"
#include "Passive.h"
#include <atomic>
#include <memory>

using namespace std;

class Engine
{
private:
    int Money;
    int Experience;
    int RAM;
    int ProcessingPower;
    int Income;
    atomic<bool> isRunning;
    atomic<int> currentTime;
    string Name; 
    map<string, shared_ptr<Software>> Catalog;
    map<string, shared_ptr<Server>> ServersCatalog;
    vector<shared_ptr<Software>> softwareList;
    vector<shared_ptr<Software>> installedSoftware;
    vector<shared_ptr<Software>> activeSoftware;
public:
    Engine() : Money(1000), Experience(0), RAM(10), ProcessingPower(1), Income(0), isRunning(true), currentTime(0) {}
    void start();
    void render();
    void gotoxy(int x, int y);
    void clearScreen();
    void setTerminalSize(int width, int height);
    void body(int h, int w, int x, int y);
    void update(int sec);
    void loadAssets();
    void printCatalog();
    void renderStats();
    void renderTerminal();
    void renderTaskManager();
    void renderSoftwareCatalog();
    void renderSoftwareList();
    void buySoftware(const string& softwareName);
    void useSoftware(const string& softwareName);
    void unuseSoftware(const string& softwareName);
};

#endif // BACKBONE_H
