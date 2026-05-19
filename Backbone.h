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
    int terminalLine;
    atomic<bool> isRunning;
    atomic<int> currentTime;
    string Name; 
    map<string, shared_ptr<Software>> Catalog;
    map<string, shared_ptr<Server>> ServersCatalog;
    vector<shared_ptr<Software>> softwareList;
    vector<shared_ptr<Software>> installedSoftware;
    vector<shared_ptr<Software>> activeSoftware;
public:
    Engine() : Money(1000), Experience(0), RAM(10), ProcessingPower(5), Income(0), terminalLine(23), isRunning(true), currentTime(0) {}
    void start();
    void render();
    void gotoxy(int x, int y);
    void clearScreen();
    void setTerminalSize(int width, int height);
    void body(int h, int w, int x, int y);
    void update(int sec);
    void loadAssets();
    int availableRAM() const;
    int availableProcessingPower() const;
    void printCatalog();
    void printServersCatalog();
    void renderStats();
    void renderTerminal();
    void renderTaskManager();
    void renderSoftwareCatalog();
    void renderSoftwareList();
    int getTerminalLine() const { return terminalLine; }
    int getMoney() const { return Money; }
    int getIncome() const { return Income; }
    void setTerminalLine(int line) { terminalLine = line; }
    void buySoftware(const string& softwareName);
    void useSoftware(const string& softwareName);
    void unuseSoftware(const string& softwareName);
    void saveCursor();
    void restoreCursor();
    void clearTerminal();
    void showServerInfo(const string& serverName);
    void showSoftwareInfo(const string& softwareName);
    string generateProgressBar(int remaining, int total, int length);
};

#endif // BACKBONE_H
