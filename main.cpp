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
        engine.gotoxy(5, engine.getTerminalLine());
        engine.gotoxy(4, engine.getTerminalLine());
        cout << "> "; 
        getline(cin, command);
        engine.setTerminalLine(engine.getTerminalLine() + 1);
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
        } else if (command == "catalog") {
            engine.printCatalog();
        } else if (command == "servers") {
            engine.serverscan();
        } else if (command.rfind("info server ", 0) == 0) {
            string serverName = command.substr(12);
            engine.showServerInfo(serverName);
        } else if (command.rfind("info software ", 0) == 0) {
            string softwareName = command.substr(14);
            engine.showSoftwareInfo(softwareName);
        
        } else if (command.rfind("hack ", 0) == 0) {
            stringstream ss(command);
            string cmd, attackName, serverIP;
            ss >> cmd >> attackName >> serverIP;
            if (attackName.empty() || serverIP.empty()) {
                engine.saveCursor();
                engine.gotoxy(4, engine.getTerminalLine());
                cout << "Format gresit! Foloseste: hack {nume_atac} {server_ip}           ";
                engine.setTerminalLine(engine.getTerminalLine() + 1);
                engine.restoreCursor();
    } else {
        // Apelăm funcția din engine care procesează atacul
        engine.executeHack(attackName, serverIP);
    }
}
        else if (command == "clear") {
            engine.clearTerminal();
            engine.setTerminalLine(23);
            engine.renderStats();
        } else {
            engine.gotoxy(4, engine.getTerminalLine());
            engine.setTerminalLine(engine.getTerminalLine() + 1);
            cout << "Unknown command: " << command << endl;
        }
        if (engine.getTerminalLine() > 38) { 
            engine.setTerminalLine(23);
            engine.clearTerminal();
        }

    }
    cin >> a;
    cin >> b;
    return 0;
}