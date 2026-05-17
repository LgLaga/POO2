#include "Backbone.h"
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <fstream>
#include "Attack.h"
#include "Passive.h"
#include "Server.h"
#include "Software.h"
#include <vector>
#include <algorithm>

using namespace std;

void Engine::start()
{
    cout << "Engine started!" << endl;
}

void Engine::renderStats()
{
    gotoxy(53, 22);
    cout << "                         ";
    gotoxy(53, 23);
    cout << "                         ";
    gotoxy(53, 24);
    cout << "                         ";
    gotoxy(53, 25);
    cout << "                         ";
    gotoxy(53, 26);
    cout << "                         ";
    gotoxy(53, 22);
    cout << "Money: $" << this->Money;
    gotoxy(53, 23);
    cout << "Experience: " << this->Experience;
    gotoxy(53, 24);
    cout << "RAM: " << this->RAM << " GB";
    gotoxy(53, 25);
    cout << "Processing Power: " << this->ProcessingPower << " units";
    gotoxy(53, 26);
    cout << "Income: $" << this->Income;
}
void Engine::renderTerminal()
{
    gotoxy(4, 22);
    cout << "Terminal Output:";
    gotoxy(4, 23);
    cout << "> ";
}
void Engine::renderSoftwareCatalog()
{   
    int line = 3;
    for (const auto &pair : this->Catalog)
    {
        if (line < 18) 
        {
            gotoxy(107, line++);
            cout << "- " << pair.first;
        }
    }
}
void Engine::renderSoftwareList()
{
    int line = 3; // Start from the bottom of the Terminal box
    for (const auto &software : this->installedSoftware)
    {
        if (true)
        {
            gotoxy(82, line++);
            cout << "* " << software->getName();
        }
    }
}

void Engine::buySoftware(const string &softwareName)
{
    auto it = Catalog.find(softwareName);
    if (it != Catalog.end())
    {
        auto software = it->second;
        if (Money >= software->getCost())
        {
            Money -= software->getCost();
            installedSoftware.push_back(software);
            cout << "Bought " << softwareName << " for $" << software->getCost() << endl;
            renderStats(); 
            renderSoftwareList(); 
        }
        else
        {
            gotoxy(4, 22);
            cout << "Not enough money to buy " << softwareName << endl;
        }
    }
    else
    {
        gotoxy(4, 22);
        cout << "Software " << softwareName << " not found in catalog." << endl;
    }
}

#include <algorithm> 

void Engine::useSoftware(const string &softwareName)
{
    for (auto software : installedSoftware)
    {
        if (software->getName() == softwareName)
        {
            auto it = std::find(activeSoftware.begin(), activeSoftware.end(), software);   
            if (it != activeSoftware.end())
            {
                gotoxy(4, 22);
                cout << "Software " << softwareName << " is already running!          " << endl;
                return;
            }
            if(software->getRAMUsage() > this->RAM || software->getCPUUsage() > this->ProcessingPower)
            {
                gotoxy(4, 22);
                cout << "Not enough resources to run " << softwareName << ".          " << endl;
                return; 
            }

            
            software->setTimeRemaining(software->getDuration()); 
            software->setIsActive(true); 
            
            activeSoftware.push_back(software);
            this->Income += software->getPassiveMoney(); 
            
            
            renderTaskManager();
            renderStats();
            return;
        }
    }
    
    gotoxy(4, 22);
    cout << "Software " << softwareName << " not installed." << endl;
}

void Engine::unuseSoftware(const string &softwareName)
{
    for(auto software : activeSoftware)
    {
        if (software->getName() == softwareName)
        {
            software->setIsActive(false); 
            activeSoftware.erase(remove(activeSoftware.begin(), activeSoftware.end(), software), activeSoftware.end());
            cout << "Stopped using " << softwareName << endl;
            return;
        }
    }
    cout << "Software " << softwareName << " not currently active." << endl;
}

void Engine::render()
{
    setTerminalSize(130, 40);
    clearScreen();
    
    body(130, 40, 1, 1);
    
    body(10, 8, 3, 2);
    
    const char *skullAvatar[] = {

        "⣴⣾⣿⣿⣿⣿⣷⣦",

        "⣿⣿⣿⣿⣿⣿⣿⣿",

        "⡟⠛⠽⣿⣿⠯⠛⢻",

        "⣧⣀⣀⡾⢷⣀⣀⣼",

        " ⡏⢽⢴⡦⡯⢹",

        " ⠙⢮⣙⣋⡵⠋"

    };

    int avatarY = 3; 

    for (const char *line : skullAvatar)
    {

        gotoxy(4, avatarY++); 

        cout << line;
    }
    const char *map[] = {

        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣀⣄⣠⣀⡀⣀⣠⣤⣤⣤⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",

        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣄⢠⣠⣼⣿⣿⣿⣟⣿⣿⣿⣿⣿⣿⣿⣿⡿⠋⠀⠀⠀⢠⣤⣦⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠰⢦⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",

        "⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⣟⣾⣿⣽⣿⣿⣅⠈⠉⠻⣿⣿⣿⣿⣿⡿⠇⠀⠀⠀⠀⠀⠉⠀⠀⠀⠀⠀⢀⡶⠒⢉⡀⢠⣤⣶⣶⣿⣷⣆⣀⡀⠀⢲⣖⠒⠀⠀⠀⠀⠀⠀⠀",

        "⢀⣤⣾⣶⣦⣤⣤⣶⣿⣿⣿⣿⣿⣿⣽⡿⠻⣷⣀⠀⢻⣿⣿⣿⡿⠟⠀⠀⠀⠀⠀⠀⣤⣶⣶⣤⣀⣀⣬⣷⣦⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣦⣤⣦⣼⣀⠀",

        "⠈⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠓⣿⣿⠟⠁⠘⣿⡟⠁⠀⠘⠛⠁⠀⠀⢠⣾⣿⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠏⠙⠁",

        "⠀⠸⠟⠋⠀⠈⠙⣿⣿⣿⣿⣿⣿⣷⣦⡄⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⣼⣆⢘⣿⣯⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡉⠉⢱⡿⠀⠀⠀⠀⠀",

        "⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣟⡿⠦⠀⠀⠀⠀⠀⠀⠀⠙⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⡗⠀⠈⠀⠀⠀⠀⠀⠀",

        "⠀⠀⠀⠀⠀⠀⠀⠀⢻⣿⣿⣿⣿⣿⣿⣿⣿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿⣉⣿⡿⢿⢷⣾⣾⣿⣞⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠋⣠⠟⠀⠀⠀⠀⠀⠀⠀⠀",

        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠹⣿⣿⣿⠿⠿⣿⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣾⣿⣿⣷⣦⣶⣦⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣷⠈⠛⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀",

        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠻⣿⣤⡖⠛⠶⠤⡀⠀⠀⠀⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠙⣿⣿⠿⢻⣿⣿⡿⠋⢩⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",

        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠙⠧⣤⣦⣤⣄⡀⠀⠀⠀⠀⠀⠘⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠀⠀⠀⠘⣧⠀⠈⣹⡻⠇⢀⣿⡆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀",

        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢠⣿⣿⣿⣿⣿⣤⣀⡀⠀⠀⠀⠀⠀⠀⠈⢽⣿⣿⣿⣿⣿⠋⠀⠀⠀⠀⠀⠀⠀⠀⠹⣷⣴⣿⣷⢲⣦⣤⡀⢀⡀⠀⠀⠀⠀⠀⠀",

        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢿⣿⣿⣿⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⣿⣷⢀⡄⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠂⠛⣆⣤⡜⣟⠋⠙⠂⠀⠀⠀⠀⠀",

        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⣿⣿⣿⠟⠀⠀⠀⠀⠀⠀⠀⠀⠘⣿⣿⣿⣿⠉⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣤⣾⣿⣿⣿⣿⣆⠀⠰⠄⠀⠉⠀⠀",

        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⡿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢹⣿⡿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣿⠿⠿⣿⣿⣿⠇⠀⠀⢀⠀⠀⠀",

        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣿⡿⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⢻⡇⠀⠀⢀⣼⠗⠀⠀",

        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⠃⣀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠁⠀⠀⠀",

        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠒⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀"
    };
    int startY = 2;
    for (const char *line : map)
    {
        gotoxy(15, startY++);
        cout << line;
    }
    body(24, 17, 81, 2);
    gotoxy(82, 2);
    cout << "Software";
    body(24, 17, 105, 2);
    gotoxy(106, 2);
    cout << "Catalog";
    body(48, 19, 3, 21);
    gotoxy(4, 21);
    cout << "Terminal";
    body(48, 19, 81, 21);
    gotoxy(82, 21);
    cout << "TaskManager";
    body(28, 19, 52, 21);
    gotoxy(53, 21);
    cout << "Stats";
    renderStats();
    renderTerminal();
    renderSoftwareCatalog();
}

void Engine::renderTaskManager()
{
    for (int i = 22; i < 39; ++i)
    {
        gotoxy(82, i);
        cout << "                         "; 
    }
    gotoxy(82, 22);
    cout << "Active Software:";
    int line = 23;
    for (const auto &software : this->activeSoftware)
    {
        if (line < 40)
        {
            gotoxy(82, line++);
            cout << "* " << software->getName();
        }
    }
}

void Engine::gotoxy(int x, int y)
{
    cout << "\033[" << y << ";" << x << "H";
}

void Engine::clearScreen()
{
    // ANSI clear the console screen
    cout << "\033[2J\033[H";
}

void Engine::setTerminalSize(int width, int height)
{
    // \033[8; resizing
    cout << "\033[8;" << height << ";" << width << "t";
}

void Engine::body(int w, int h, int x, int y)
{

    std::string horizontal = "";
    for (int i = 0; i < w - 2; ++i)
    {
        horizontal += "═";
    }
    string top = "╔" + horizontal + "╗\n";
    string middle = "║" + string(w - 2, ' ') + "║\n";
    string bottom = "╚" + horizontal + "╝";
    gotoxy(x, y);
    cout << top;
    for (int i = 0; i < h - 2; ++i)
    {
        gotoxy(x, ++y);
        cout << middle;
    }
    gotoxy(x, ++y);
    cout << bottom;
}

void Engine::update(int seconds)
{
    auto nextWakeUp = chrono::steady_clock::now();

    while (this->isRunning)
    {
        nextWakeUp += chrono::seconds(seconds);
        this_thread::sleep_until(nextWakeUp);

        this->currentTime++;
        bool stateChanged = false;

        for (auto it = activeSoftware.begin(); it != activeSoftware.end(); )
        {
            if (*it == nullptr) {
                it = activeSoftware.erase(it);
                continue;
            }

            auto software = *it;

            if (software->getIsActive() && software->getDuration() > 0)
            {
                int remaining = software->getTimeRemaining() - seconds;
                software->setTimeRemaining(remaining);
                
                if (remaining <= 0)
                {
                    software->setIsActive(false);
                    software->setTimeRemaining(0);
                    this->Income -= software->getPassiveMoney();
                    
                    it = activeSoftware.erase(it);
                    stateChanged = true; 
                    continue;
                }
            }
            ++it;
        }
        if (this->Income > 0 && currentTime % 10 == 0) { //every 10 seconds, for example, you could check if currentTime % 10 == 0
            this->Money += this->Income;
            stateChanged = true; // Mark true so the Stats box reflects the new cash balance
        }
        if (stateChanged)
        {
            renderTaskManager();
            renderStats();
            gotoxy(6, 23); 
            cout << flush; 
        }
    }
}
void Engine::loadAssets()
{
    ifstream assetFile("assets.txt");
    try
    {
        if (!assetFile)
        {
            cerr << "Error: Could not open assets.txt" << endl;
            return;
        }
    }
    catch (const std::exception &e)
    {
        cerr << "Error: " << e.what() << endl;
        return;
    }
    string typeofAsset;
    while (assetFile >> typeofAsset)
    {
        if (typeofAsset == "Attack")
        {
            auto attack = make_shared<Attack>();
            assetFile >> *attack;
            Catalog[attack->getName()] = attack;
        }
        else if (typeofAsset == "Passive")
        {
            auto passive = make_shared<Passive>();
            assetFile >> *passive;
            Catalog[passive->getName()] = passive;
        }
        else if (typeofAsset == "Server")
        {
            auto server = make_shared<Server>();
            assetFile >> *server;
            ServersCatalog[server->getName()] = server;
        }
        else
        {
            cerr << "Unknown asset type: " << typeofAsset << endl;
        }
    }
}
void Engine::printCatalog()
{
    cout << "Software Catalog:" << endl;
    for (const auto &pair : Catalog)
    {
        cout << "- " << pair.first << ": " << endl;
        pair.second->print();
    };
}