#include <iostream>
#include <windows.h>
#include "classes.h"
#include <conio.h>
#include <random>

using namespace std;

void intro();
void youWon();
void youLost();

int main() {
    bool running = true, play = false, firstTime = true;
    SetConsoleOutputCP(CP_UTF8);

    while (running){
        if (firstTime){
            intro();
        }
        firstTime = false;
        
        Map map, enemyMap;
        Ship carrier(1), battleship(2), cruiser(3), submarine(4), destroyer(5);
        Ship cpuCarrier(1), cpuBattleship(2), cpuCruiser(3), cpuSubmarine(4), cpuDestroyer(5);

        Player cpu(enemyMap, cpuCarrier, cpuBattleship, cpuCruiser, cpuSubmarine, cpuDestroyer, true);
        Player player(map, carrier, battleship, cruiser, submarine, destroyer, false);

        if (player.ready == true && cpu.ready == true){
            play = true;
        }

        while (play){
            player.printGame();
            player.shoot(&cpu);

            if (!cpu.seeIfAlive()){
                player.printGame();
                youWon();
                firstTime = true;
                play = false;
                break;
            }
            
            cpu.CPUshoot(&player);

            if (!player.seeIfAlive()){
                player.printGame();
                youLost();
                firstTime = true;
                play = false;
                break;
            }
        }
    }

    return 0;
}

void intro() {
    system("cls");
    string vet[] = {"                                                                                   ", 
                    "            ┏━━┓       ┏┓  ┏┓ ┏┓     ┏━━━┓┏┓               ┏┓                      ",
                    "            ┃┏┓┃      ┏┛┗┓┏┛┗┓┃┃     ┃┏━┓┃┃┃               ┃┃                      ",
                    "            ┃┗┛┗┓┏━━┓ ┗┓┏┛┗┓┏┛┃┃ ┏━━┓┃┗━━┓┃┗━┓┏┓┏━━┓┏━━┓   ┃┗━┓┏┓ ┏┓┏━┓            ", 
                    "            ┃┏━┓┃┗━┓┃  ┃┃  ┃┃ ┃┃ ┃┏┓┃┗━━┓┃┃┏┓┃┣┫┃┏┓┃┃━━┫   ┃┏┓┃┃┃ ┃┃┗━┛            ", 
                    "            ┃┗━┛┃┃┗┛┗┓ ┃┗┓ ┃┗┓┃┗┓┃┃━┫┃┗━┛┃┃┃┃┃┃┃┃┗┛┃┣━━┃   ┃┗┛┃┃┗━┛┃┏━┓            ",
                    "            ┗━━━┛┗━━━┛ ┗━┛ ┗━┛┗━┛┗━━┛┗━━━┛┗┛┗┛┗┛┃┏━┛┗━━┛   ┗━━┛┗━┓┏┛┗━┛            ", 
                    "                                                ┃┃             ┏━┛┃                ", 
                    "                                                ┗┛             ┗━━┛                ", 
                    "  ┏┓  ┏┓                          ┏━━┓                   ┏━━┓           ┏┓         ", 
                    "  ┃┗┓┏┛┃                          ┃┏┓┃                   ┃┏┓┃          ┏┛┗┓        ", 
                    "  ┗┓┃┃┏┛┏┓┏━┓ ┏┓┏━━┓┏┓┏┓┏┓┏━━┓    ┃┗┛┗┓┏┓┏━━┓ ┏━━━┓┏┓    ┃┗┛┗┓┏━━┓ ┏━━┓┗┓┏┛┏━━┓┏━━┓", 
                    "   ┃┗┛┃ ┣┫┃┏┓┓┣┫┃┏━┛┣┫┃┃┃┃┃━━┫    ┃┏━┓┃┣┫┗━┓┃ ┣━━┃┃┣┫    ┃┏━┓┃┗━┓┃ ┃━━┫ ┃┃ ┃┏┓┃┃━━┫", 
                    "   ┗┓┏┛ ┃┃┃┃┃┃┃┃┃┗━┓┃┃┃┗┛┃┣━━┃    ┃┗━┛┃┃┃┃┗┛┗┓┃┃━━┫┃┃    ┃┗━┛┃┃┗┛┗┓┣━━┃ ┃┗┓┃┗┛┃┣━━┃", 
                    "    ┗┛  ┗┛┗┛┗┛┗┛┗━━┛┗┛┗━━┛┗━━┛    ┗━━━┛┗┛┗━━━┛┗━━━┛┗┛    ┗━━━┛┗━━━┛┗━━┛ ┗━┛┗━━┛┗━━┛", 
                    "                                                                                   "};
    
    for (int i = 0; i < 16; i++){
        cout << vet[i] << endl;
        Sleep(40);
    }
    cout << "Press any key to Play...\nPress ESC to Exit..." << endl;
    char key = getch();
    if (key == 27){
        exit(0);
    }
}

void youLost(){
    system("cls");
    string vet[] = {"                                      ",
                    "  ┏┓  ┏┓            ┏┓          ┏┓  ┏┓",
                    "  ┃┗┓┏┛┃            ┃┃         ┏┛┗┓ ┃┃",
                    "  ┗┓┗┛┏┛┏━━┓┏┓┏┓    ┃┃ ┏━━┓┏━━┓┗┓┏┛ ┃┃",
                    "   ┗┓┏┛ ┃┏┓┃┃┃┃┃    ┃┃ ┃┏┓┃┃━━┫ ┃┃  ┗┛",
                    "    ┃┃  ┃┗┛┃┃┗┛┃    ┃┗┓┃┗┛┃┣━━┃ ┃┗┓ ┏┓",
                    "    ┗┛  ┗━━┛┗━━┛    ┗━┛┗━━┛┗━━┛ ┗━┛ ┗┛",
                    "                                      "};
    
    for (int i = 0; i < 8; i++){
        cout << vet[i] << endl;
        Sleep(40);
    }
    cout << "Press any key to continue...\nPress ESC to Exit..." << endl;
    char key = getch();
    if (key == 27){
        exit(0);
    }
}

void youWon(){
    system("cls");
    string vet[] = {"                                    ", 
                    "  ┏┓  ┏┓                           ┏┓",
                    "  ┃┗┓┏┛┃                           ┃┃",
                    "  ┗┓┗┛┏┛┏━━┓┏┓┏┓    ┏┓┏┓┏┓┏━━┓┏━┓  ┃┃",
                    "   ┗┓┏┛ ┃┏┓┃┃┃┃┃    ┃┗┛┗┛┃┃┏┓┃┃┏┓┓ ┗┛",
                    "    ┃┃  ┃┗┛┃┃┗┛┃    ┗┓┏┓┏┛┃┗┛┃┃┃┃┃ ┏┓",
                    "    ┗┛  ┗━━┛┗━━┛     ┗┛┗┛ ┗━━┛┗┛┗┛ ┗┛",
                    "                                     "};
    
    for (int i = 0; i < 8; i++){
        cout << vet[i] << endl;
        Sleep(40);
    }
    cout << "Press any key to continue...\nPress ESC to Exit..." << endl;
    char key = getch();
    if (key == 27){
        exit(0);
    }
}