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
#include <fstream>

using namespace std;

ofstream debugOut("debug.txt");

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

void Engine::clearTerminal()
{
    for (int i = 22; i < 39; ++i)
    {
        gotoxy(4, i);
        cout << "                                      ";
    }
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
            saveCursor();
            gotoxy(4, 22);
            cout << "Bought " << softwareName << " for $" << software->getCost() << endl;
            renderStats(); 
            renderSoftwareList(); 
            restoreCursor();
        }
        else
        {
            saveCursor();
            gotoxy(4, 22);
            cout << "Not enough money to buy " << softwareName << endl;
            restoreCursor();
        }
    }
    else
    {
        saveCursor();
        gotoxy(4, 22);
        cout << "Software " << softwareName << " not found in catalog." << endl;
        restoreCursor();
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
                saveCursor();
                gotoxy(4, 22);
                cout << "Software " << softwareName << " is already running!          " << endl;
                restoreCursor();
                return;
            }
            if(software->getRAMUsage() > this->availableRAM() || software->getCPUUsage() > this->availableProcessingPower())
            {
                saveCursor();
                gotoxy(4, 22);
                cout << "Not enough resources to run " << softwareName << ".          " << endl;
                restoreCursor();
                return; 
            }
            software->setTimeRemaining(software->getDuration()); 
            software->setIsActive(true); 
            
            activeSoftware.push_back(software);
            this->Income += software->getPassiveMoney(); 
            debugOut << "Income updated: $" << this->Income << endl;
            debugOut << activeSoftware.size() << " active software(s)." << endl;
            saveCursor();
            renderTaskManager();
            renderStats();
            restoreCursor();
            return;
        }
    }
    
    saveCursor();
    gotoxy(4, 22);
    cout << "Software " << softwareName << " not installed." << endl;
    restoreCursor();
}

void Engine::unuseSoftware(const string &softwareName)
{
    saveCursor();
    for(auto software : activeSoftware)
    {
        if (software->getName() == softwareName)
        {
            software->setIsActive(false); 
            activeSoftware.erase(remove(activeSoftware.begin(), activeSoftware.end(), software), activeSoftware.end());
            cout << "Stopped using " << softwareName << endl;
            restoreCursor();
            return;
        }
    }
    cout << "Software " << softwareName << " not currently active." << endl;
    restoreCursor();
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
    string emptyLine = "                                             "; // 45 de spații utile

    // 1. Status RAM & CPU (Rămân neschimbate)
    gotoxy(82, 22); cout << emptyLine;
    gotoxy(82, 22); cout << "RAM: " << this->availableRAM() << " / " << this->RAM << " GB";

    gotoxy(82, 23); cout << emptyLine;
    gotoxy(82, 23); cout << "Processes: " << (this->ProcessingPower - this->availableProcessingPower()) << " / " << this->ProcessingPower;

    // 2. Afișarea listei cu Bare de Încărcare
    int line = 24;
    for (const auto &software : this->activeSoftware)
    {
        if (line < 39)
        {
            gotoxy(82, line);
            cout << emptyLine; // Curățăm complet linia veche
            
            gotoxy(82, line);
            cout << "* " << software->getName();

            // Dacă software-ul are durată (este un atac/program cu timer)
            if (software->getDuration() > 0)
            {
                // Generăm o bară de încărcare lungă de 10 caractere
                string bar = generateProgressBar(software->getTimeRemaining(), software->getDuration(), 10);
                
                // O poziționăm decalat pe aceeași linie (lăsăm spațiu după nume)
                gotoxy(100, line);
                cout << bar << " " << software->getTimeRemaining() << "s";
            }
            else
            {
                // Pentru programe pasive permanente (fără timer), scriem doar statusul stabil
                gotoxy(100, line);
                cout << "[PERMANENT]";
            }
            line++;
        }
    }

    // 3. Curățarea liniilor rămase libere jos
    while (line < 39)
    {
        gotoxy(82, line++);
        cout << emptyLine;
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
                    saveCursor();
                    software->setIsActive(false);
                    software->setTimeRemaining(0);
                    this->Income -= software->getPassiveMoney();
                    restoreCursor();
                    it = activeSoftware.erase(it);
                    stateChanged = true; 
                    continue;
                }
            }
            ++it;
        }
        if (this->Income > 0 && this->currentTime % 10 == 0) { //every 10 seconds, for example, you could check if currentTime % 10 == 0
            this->Money += this->Income * 10;
            stateChanged = true; // Mark true so the Stats box reflects the new cash balance
        }
        if (stateChanged)
        {
            saveCursor();
            renderTaskManager();
            renderStats();
            restoreCursor();
        }
        bool areTimersActive = false;
        for (const auto& sw : activeSoftware) {
            if (sw->getDuration() > 0) {
                areTimersActive = true;
                break;
            }
        }

        if (stateChanged || areTimersActive || this->Income > 0)
        {
            saveCursor(); // 🟢 Protejăm inputul prompt al utilizatorului cu scutul ANSI
            
            renderTaskManager(); // Va redesena barele actualizate: [#####.....] 4s -> [####......] 3s
            if (stateChanged || this->currentTime % 10 == 0) {
                renderStats(); // Update la bani doar când e necesar ca să evităm flicker-ul inutil
            }
            
            restoreCursor(); // 🟢 Întoarcem cursorul exact unde scria jucătorul în Terminal
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
void Engine::printServersCatalog()
{
    cout << "Servers Catalog:" << endl;
    for (const auto &pair : ServersCatalog)
    {
        cout << "- " << pair.first << ": " << endl;
        pair.second->print();
    };
}
int Engine::availableRAM() const
{
    int usedRAM = 0;
    for (const auto &software : activeSoftware)
    {
        usedRAM += software->getRAMUsage();
    }
    return RAM - usedRAM;
}
int Engine::availableProcessingPower() const
{
    int usedProcessingPower = 0;
    for (const auto &software : activeSoftware)
    {
        usedProcessingPower++;
    }
    return ProcessingPower - usedProcessingPower;
}
void Engine::saveCursor() {
    cout << "\0337" << flush; // Save cursor position
}
void Engine::restoreCursor() {
    cout << "\0338" << flush; // Restore cursor position
}
string Engine::generateProgressBar(int remaining, int duration, int width)
{
    if (duration <= 0) return string(width, '#');

    // Calculăm progresul efectiv (cât s-a scurs din timp)
    int elapsed = duration - remaining;
    float progress = static_cast<float>(elapsed) / duration;
    
    // Siguranță pentru margini
    if (progress < 0.0f) progress = 0.0f;
    if (progress > 1.0f) progress = 1.0f;

    int filledLength = static_cast<int>(progress * width);
    int emptyLength = width - filledLength;

    return "[" + string(filledLength, '#') + string(emptyLength, '.') + "]";
}

void Engine::showServerInfo(const string& serverName) {
    // Căutăm serverul în catalogul de servere
    auto it = ServersCatalog.find(serverName);
    if (it == ServersCatalog.end()) {
        saveCursor();
        gotoxy(4, getTerminalLine());
        cout << "Server '" << serverName << "' not found!                      ";
        setTerminalLine(getTerminalLine() + 1);
        restoreCursor();
        return;
    }

    auto server = it->second;
    saveCursor(); // 🟢 Înghețăm poziția promptului în care scrie jucătorul

    int currentY = getTerminalLine();
    string emptyLine = "                                           "; // 43 de spații pentru a șterge textul vechi din casetă

    // Scriem proprietățile serverului linie cu linie, controlând axa Y manual
    gotoxy(4, currentY); cout << emptyLine;
    gotoxy(4, currentY++); cout << "Server Connections Info:";

    gotoxy(4, currentY); cout << emptyLine;
    gotoxy(4, currentY++); cout << "Hostname      : " << server->getName();

    gotoxy(4, currentY); cout << emptyLine;
    gotoxy(4, currentY++); cout << "IP Address    : " << server->getIPAddress();

    gotoxy(4, currentY); cout << emptyLine;
    gotoxy(4, currentY++); cout << "Security Level: " << server->getSecurityLevel() << " / 10";

    gotoxy(4, currentY); cout << emptyLine;
    gotoxy(4, currentY++); cout << "Data Value    : $" << server->getDataValue();

    // Actualizăm variabila terminalului pentru ca următorul prompt "> " să apară exact sub info
    setTerminalLine(currentY);

    restoreCursor(); // 🟢 Cursorul sare înapoi la promptul utilizatorului, complet fluid
}

void Engine::showSoftwareInfo(const string& softwareName) {
    auto it = Catalog.find(softwareName);
    if (it == Catalog.end()) {
        saveCursor();
        gotoxy(4, getTerminalLine());
        cout << "Software not found!                      ";
        setTerminalLine(getTerminalLine() + 1);
        restoreCursor();
        return;
    }

    auto software = it->second;
    saveCursor();

    // Resetăm zona de scriere în interiorul Terminalului dacă textul este prea jos
    int currentY = getTerminalLine();
    string emptyLine = "                                           "; // Golește rândul din interiorul box-ului

    gotoxy(4, currentY); cout << emptyLine;
    gotoxy(4, currentY++); cout << "Software Info:";

    gotoxy(4, currentY); cout << emptyLine;
    gotoxy(4, currentY++); cout << "Name: " << software->getName();

    gotoxy(4, currentY); cout << emptyLine;
    gotoxy(4, currentY++); cout << "RAM Usage: " << software->getRAMUsage() << " GB";

    gotoxy(4, currentY); cout << emptyLine;
    gotoxy(4, currentY++); cout << "CPU Usage: " << software->getCPUUsage() << " units";

    gotoxy(4, currentY); cout << emptyLine;
    gotoxy(4, currentY++); cout << "Cost: $" << software->getCost();

    gotoxy(4, currentY); cout << emptyLine;
    gotoxy(4, currentY++); cout << "Description: " << software->getDescription().substr(0, 30);

    // Dacă este de tip Attack, putem face un cast dinamic sau citi proprietățile specifice direct prin metodele virtuale:
    if (software->getDuration() > 0) {
        gotoxy(4, currentY); cout << emptyLine;
        gotoxy(4, currentY++); cout << "Attack Power: " << software->getAttackPower();

        gotoxy(4, currentY); cout << emptyLine;
        gotoxy(4, currentY++); cout << "Stealth Level: " << software->getStealthLevel();

        gotoxy(4, currentY); cout << emptyLine;
        gotoxy(4, currentY++); cout << "Duration: " << software->getDuration() << "s";
    }
    if (software->getPassiveMoney() > 0) {
        gotoxy(4, currentY); cout << emptyLine;
        gotoxy(4, currentY++); cout << "Passive Income: $" << software->getPassiveMoney() << " per second";
    }
    if (software->getBonusRAM() > 0) {
        gotoxy(4, currentY); cout << emptyLine;
        gotoxy(4, currentY++); cout << "Bonus RAM: " << software->getBonusRAM() << " GB";
    }
    if(software->getBonusProcessingPower() > 0) {
        gotoxy(4, currentY); cout << emptyLine;
        gotoxy(4, currentY++); cout << "Bonus Processing Power: " << software->getBonusProcessingPower() << " units";
    }

    // Actualizăm linia terminalului global pentru următoarea comandă a utilizatorului
    setTerminalLine(currentY);

    restoreCursor();
}