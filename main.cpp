#include <iostream>
#include "Backbone.h"
#include <string>
#include <chrono>
#include <thread>
#include "Attack.h"
#include "Passive.h"
#include "Server.h"


using namespace std;

int main() {
    int a, b, terminalline = 23;
    Engine engine;
    engine.start();
    thread updateThread(&Engine::update, &engine, 1); 
    updateThread.detach(); 
    engine.loadAssets(); 
    //engine.printCatalog(); // Print the loaded catalog to verify it works
    engine.render();
    //engine.buySoftware("Worm");
    //engine.buySoftware("Worm2");
    //engine.buySoftware("BitMiner");
    //engine.renderSoftwareList();
    //engine.renderSoftwareList();
    while(true) {
        
        string command;
        engine.gotoxy(5, terminalline);
        getline(cin, command);
        if (command == "exit") {
            break; 
        } else if (command.rfind("buy ", 0) == 0) {
            string softwareName = command.substr(4); 
            engine.buySoftware(softwareName);
        } else if (command.rfind("use ", 0) == 0) { 
            string softwareName = command.substr(4); 
            engine.useSoftware(softwareName);
            engine.renderStats(); 
            engine.renderTaskManager(); 
        } else if (command.rfind("unuse ", 0) == 0) { 
            string softwareName = command.substr(6); 
            engine.unuseSoftware(softwareName);
            engine.renderStats(); 
            engine.renderTaskManager(); 
        } else {
            engine.gotoxy(4, terminalline++);
            cout << "Unknown command: " << command << endl;
        }
        engine.gotoxy(4, ++terminalline);
        cout << "> "; 
        if (terminalline > 40) { 
            terminalline = 23;
            engine.renderTerminal(); 
        }

    }
    cin >> a;
    cin >> b;
    return 0;
}