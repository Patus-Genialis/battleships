#include <iostream>
#include <windows.h>
#include "classes.h"
#include <conio.h>
#include <random>
#include <string.h>

using namespace std;
std::random_device rd;
void getXandY(int *x, int *y);

//------------------------------------------------------------------------------------------------------------------------------
Ship::Ship(int type){
    this->dir = -1;
    if (type == 1){
        this->size = 5;
        this->type = "Carrier";
    } else if (type == 2){
        this->size = 4;
        this->type = "Battleship";
    } else if (type == 3){
        this->size = 3;
        this->type = "Cruiser";
    } else if (type == 4){
        this->size = 3;
        this->type = "Submarine";
    } else if (type == 5){
        this->size = 2;
        this->type = "Destroyer";
    }
    this->health = this->size;
    this->xVet = new int[this->size];
    this->yVet = new int[this->size];
    this->xVet[0] = 0;
    this->yVet[0] = 0;
}

bool Ship::seeIfAlive(){
    if (this->health <= 0){
        this->isAlive = false;
        return false;
    }
    return true;
}

//------------------------------------------------------------------------------------------------------------------------------
Map::Map(){
    clearMap();
};

void Map::clearMap(){
    for(int i = 0; i < 15; i++){
        for(int j = 0; j < 15; j++){
            this->map[i][j] = ' ';
        }
    }
}

void Map::printMap(){
    int line = 1;
    system("cls");
    std::cout << "Your map:\n0 | 1 2 3 4 5 6 7 8 9 a b c d e f|\n"; 
    for (int i =  0; i < 15; i++){
        std::cout << hex << line << " |";
        for (int j = 0; j < 15; j++){
            if (this->map[i][j] == '#') {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                std::cout << " " << this->map[i][j];
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            } else {
                std::cout << " " << this->map[i][j];
            }
        }
        std::cout << "|\n";
        line++;
    }
}

bool Map::addShip(Ship *ship){
    Map aux_map;
    bool placed = false;
    char key;

    while (!placed){
        aux_map.updateMap(this->map);

        if (ship->dir == -1){ // horizontal
            for (int i = 0; i < ship->size; i++){
                aux_map.map[ship->xVet[0]][ship->yVet[0] + i] = '#';
            }
        } else if (ship->dir == 1){ // vertical
            for (int i = 0; i < ship->size; i++){
                aux_map.map[ship->xVet[0] + i][ship->yVet[0]] = '#';
            }
        }
        aux_map.printMap();
        std::cout << "Use WASD to move the ship and R to Rotate\nPress ENTER to place it, Press F to reset\nPress ESC to Exit" << endl;

        key = getch();
        cin.clear();
        fflush(stdin);

        if (key == 27){ // esc
            exit(0);
        } else if (key == 'r'){
            if (ship->dir == -1){
                if (ship->xVet[0] + ship->size-1 < 15){
                    ship->dir *= -1; // rotate
                }
            } else {
                if (ship->yVet[0] + ship->size-1 < 15){
                    ship->dir *= -1; // rotate
                }
            }
        } else if (key == 'f'){
            return false;
        }else if (key == 13){ // enter
            bool flag = true;
            if (ship->dir == -1){ // horizontal
                if (ship->yVet[0] + ship->size > 15){
                    flag = false;
                }
                for (int i = 0; i < ship->size; i++){
                    if (this->map[ship->xVet[0]][ship->yVet[0] + i] == '#'){
                        flag = false;
                    }
                }
            } else if (ship->dir == 1){ // vertical
                if (ship->xVet[0] + ship->size > 15){
                    flag = false;
                }
                for (int i = 0; i < ship->size; i++){
                    if (this->map[ship->xVet[0] + i][ship->yVet[0]] == '#'){
                        flag = false;
                    }
                }
            }
            if (flag == true){
                placed = true;
            }
        } else if (key == 'w'){
            if (ship->xVet[0] > 0){
                ship->xVet[0]--;
            }
        } else if (key == 'a'){
            if (ship->yVet[0] > 0){
                ship->yVet[0]--;
            }
        } else if (key == 's'){
            if (ship->dir == 1){
                if (ship->xVet[0] + ship->size < 15){
                    ship->xVet[0]++;
                }
            } else {
                if (ship->xVet[0] < 14){
                    ship->xVet[0]++;
                }
            }
        } else if (key == 'd'){
            if (ship->dir == -1){
                if (ship->yVet[0] + ship->size < 15){
                    ship->yVet[0]++;
                }
            } else {
                if (ship->yVet[0] < 14){
                    ship->yVet[0]++;
                }
            }
        }
    }

    if (ship->dir == -1){ // horizontal
        for (int i = 0; i < ship->size; i++){
            ship->xVet[i] = ship->xVet[0];
            ship->yVet[i] = ship->yVet[0] + i;
        }
    } else if (ship->dir == 1){ // vertical
        for (int i = 0; i < ship->size; i++){
            ship->xVet[i] = ship->xVet[0] + i;
            ship->yVet[i] = ship->yVet[0];
        }
    }
    this->updateMap(aux_map.map);
    return true;
}

void Map::updateMap(char map[15][15]){
    for (int i = 0; i < 15; i++){
        for (int j = 0; j < 15; j++){
            this->map[i][j] = map[i][j];
        }
    }
}

void Map::addShipCPU(Ship *ship){
    std::uniform_int_distribution<> distr(0, 14);
    std::uniform_int_distribution<> distr2(0, 1);
    std::uniform_int_distribution<> distr3(0, 14 - ship->size);

    bool placed = false, flag = true;

    if (distr2(rd) == 0){
        ship->dir = -1;
    } else {
        ship->dir = 1;
    }

    while (!placed) {
        flag = true;

        if (ship->dir == -1){
            ship->xVet[0] = distr(rd);
            ship->yVet[0] = distr3(rd);
        } else {
            ship->xVet[0] = distr3(rd);
            ship->yVet[0] = distr(rd);
        }

        if (ship->dir == -1){ // horizontal
            for (int i = 0; i < ship->size; i++){
                if (this->map[ship->xVet[0]][ship->yVet[0] + i] == '#'){
                    flag = false;
                    break;
                }
            }
        } else if (ship->dir == 1){ // vertical
            for (int i = 0; i < ship->size; i++){
                if (this->map[ship->xVet[0] + i][ship->yVet[0]] == '#'){
                    flag = false;
                    break;
                }
            }
        }
        if (flag == true){
            placed = true;
        }
    }

    if (ship->dir == -1){ // horizontal
        for (int i = 0; i < ship->size; i++){
            ship->xVet[i] = ship->xVet[0];
            ship->yVet[i] = ship->yVet[0] + i;
        }
    } else if (ship->dir == 1){ // vertical
        for (int i = 0; i < ship->size; i++){
            ship->xVet[i] = ship->xVet[0] + i;
            ship->yVet[i] = ship->yVet[0];
        }
    }

    if (ship->dir == -1){ // horizontal
        for (int i = 0; i < ship->size; i++){
            this->map[ship->xVet[0]][ship->yVet[0] + i] = '#';
        }
    } else if (ship->dir == 1){ // vertical
        for (int i = 0; i < ship->size; i++){
            this->map[ship->xVet[0] + i][ship->yVet[0]] = '#';
        }
    }
}
//------------------------------------------------------------------------------------------------------------------------------
Player::Player(Map map, Ship carrier, Ship battleship, Ship cruiser, Ship submarine, Ship destroyer, bool cpu) {
    this->map = map;
    this->cpu = cpu;
    this->enemyMap = Map();
    this->ships[0] = carrier;
    this->ships[1] = battleship;
    this->ships[2] = cruiser;
    this->ships[3] = submarine;
    this->ships[4] = destroyer;
    if (this->cpu == true){
        for (int i = 0; i < 5; i++){
            this->map.addShipCPU(&this->ships[i]);
        }
        this->ready = true;
    } else {
        for (int i = 0; i < 5; i++){
            if (!this->map.addShip(&this->ships[i])){
                this->ready = false;
                break;
            }
            this->ready = true;
        }
    }
    this->hitCount = 0;
    this->hitSide = 1;
}

void Player::printGame(){
    int line = 1;
    system("cls");
    std::cout << "Your map:                                   Enemy map:\n0 | 1 2 3 4 5 6 7 8 9 a b c d e f|          0 | 1 2 3 4 5 6 7 8 9 a b c d e f|\n";

    for (int i =  0; i < 15; i++){
        std::cout << hex << line << " |";
        for (int j = 0; j < 15; j++){
            if (this->map.map[i][j] == '#') {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
                std::cout << " " << this->map.map[i][j];
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            } else if (this->map.map[i][j] == 'X'){
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                std::cout << " " << this->map.map[i][j];
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            } else {
                std::cout << " " << this->map.map[i][j];
            }
        }
        std::cout << "|          " << hex << line << " |";
        for (int j = 0; j < 15; j++){
            if (this->enemyMap.map[i][j] == 'X') {
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                std::cout << " " << this->enemyMap.map[i][j];
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
            } else {
                std::cout << " " << this->enemyMap.map[i][j];
            }
        }
        std::cout << "|\n";
        line++;
    }
}

void Player::shoot(Player *enemy){
    int x, y;
    int Pships, Eships;
    bool isValid = false;
    
    Pships = this->aliveShips();
    Eships = enemy->aliveShips();
    cout << "Alive ships: " << Pships << "                              Alive ships: " << Eships << endl;
    std::cout << "Enter coordinates to shoot: ";

    getXandY(&x, &y);

    bool ready = false;
    while (!ready){
        x = x - 1;
        y = y - 1;
        if (x < 0 || x > 14 || y < 0 || y > 14){
            std::cout << "Out of bounds, try again:\n";
            std::cout << "Enter coordinates to shoot: ";
            getXandY(&x, &y);
            ready = false;
        } else if (enemy->map.map[x][y] == 'X' || enemy->map.map[x][y] == 'O'){
            std::cout << "You already shot there, try again:\n";
            std::cout << "Enter coordinates to shoot: ";
            getXandY(&x, &y);
            ready = false;
        } else {
            ready = true;
        }
    }   

    if (enemy->map.map[x][y] == '#'){
        enemy->map.map[x][y] = 'X';
        this->enemyMap.map[x][y] = 'X';
        std::cout << "Hit!\n";
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < enemy->ships[i].size; j++){
                if (enemy->ships[i].xVet[j] == x && enemy->ships[i].yVet[j] == y){
                    enemy->ships[i].health--;
                    if (!enemy->ships[i].seeIfAlive()){
                        std::cout << "You sunk the enemy's " << enemy->ships[i].type << "!\n";
                    }
                    break;
                }
            }
        }
    } else if (enemy->map.map[x][y] == ' '){
        enemy->map.map[x][y] = 'O';
        this->enemyMap.map[x][y] = 'O';
        std::cout << "Miss!\n";
    } 
    Sleep(1000);
}

bool Player::seeIfAlive(){
    for (int i = 0; i < 5; i++){
        if (this->ships[i].isAlive == true){
            return true;
        }
    }
    return false;
}

int Player::aliveShips(){
    int cont = 0;
    for (int i = 0; i < 5; i++){
        if (this->ships[i].isAlive == true){
            cont++;
        }
    }
    return cont;
}

void Player::CPUshoot(Player *enemy){
    int x, y;

    this->CPUthink(&x, &y, enemy);

    if (enemy->map.map[x][y] == '#'){
        if (this->hitCount == 0){
            this->hitsX[0] = x;
            this->hitsY[0] = y;
            this->firstTime = true;
            this->hitSide = 1;
        } else if (this->hitCount == 1){
            this->firstTime = true;
            this->hitSide = 1;
            this->hitsX[1] = x;
            this->hitsY[1] = y;
            if (this->hitsX[0] == this->hitsX[1]){
                this->hitDir = -1;
            } else {
                this->hitDir = 1;
            }
        }

        this->hitCount++;
        this->hitsX[2] = x;
        this->hitsY[2] = y;
        enemy->map.map[x][y] = 'X';
        this->enemyMap.map[x][y] = 'X';
        std::cout << "The enemy hit you!\n";
        for (int i = 0; i < 5; i++){
            for (int j = 0; j < enemy->ships[i].size; j++){
                if (enemy->ships[i].xVet[j] == x && enemy->ships[i].yVet[j] == y){
                    enemy->ships[i].health--;
                    if (!enemy->ships[i].seeIfAlive()){
                        this->hitCount = 0;
                        this->hitSide = 1;
                        this->firstTime = true;
                        std::cout << "The enemy sunk your " << enemy->ships[i].type << "!\n";
                    }
                    break;
                }
            }
        }
    } else if (enemy->map.map[x][y] == ' '){
        if (this->hitCount >= 2){
            if (this->hitSide == -1){
                this->hitCount = 1;
            }
            this->hitSide = -1;
            this->firstTime = true;
        }
        enemy->map.map[x][y] = 'O';
        this->enemyMap.map[x][y] = 'O';
        std::cout << "The enemy missed!\n";
    } 
    Sleep(1000);
}

void Player::CPUthink(int *xpos, int *ypos, Player *enemy) {
    int x, y;

    if (this->hitCount == 0){
        this->CPUchooseFhit (&x, &y, enemy);
    } else if (this->hitCount == 1){
        this->CPUchooseShit (&x, &y, enemy);
    } else if (this->hitCount >= 2){
        this->CPUchooseThit (&x, &y, enemy);
    }
    *xpos = x;
    *ypos = y;
}

void Player::CPUchooseFhit(int *xpos, int *ypos, Player *enemy){
    int x, y;
    std::uniform_int_distribution<> distr(0, 14);
    bool ready = false;

    while (!ready){
        x = distr(rd);
        y = distr(rd);
        if (enemy->map.map[x][y] == 'X' || enemy->map.map[x][y] == 'O'){
            ready = false;
        } else {
            ready = true;
        }
    }
    *xpos = x;
    *ypos = y;
}

void Player::CPUchooseShit(int *xpos, int *ypos, Player *enemy){
    int x, y;
    int trys = 0;
    bool isValid = false;
    
    while (!isValid){
        if (trys == 0){
            x = this->hitsX[0];
            y = this->hitsY[0] + 1;
        } else if (trys == 1){
            x = this->hitsX[0] + 1;
            y = this->hitsY[0];
        } else if (trys == 2){
            x = this->hitsX[0];
            y = this->hitsY[0] - 1;
        } else if (trys == 3){
            x = this->hitsX[0] - 1;
            y = this->hitsY[0];
        }

        if (x < 0 || x > 14 || y < 0 || y > 14){
            trys++;
            isValid = false;
        } else if (enemy->map.map[x][y] == 'X' || enemy->map.map[x][y] == 'O'){
            trys++;
            isValid = false;
        } else {
            isValid = true;
        }
        if (trys >= 4){
            this->CPUchooseFhit(xpos, ypos, enemy);
            this->hitCount = 0;
            return;
        }
    }
    *xpos = x;
    *ypos = y;
}

void Player::CPUchooseThit(int *xpos, int *ypos, Player *enemy){
    int x, y;
    bool isValid = false;

    here:
    if (this->firstTime){
        if (this->hitSide == 1){
            if (this->hitDir == -1){
                if (this->hitsY[0] > this->hitsY[1]){
                    x = this->hitsX[0];
                    y = this->hitsY[0];
                } else {
                    x = this->hitsX[1];
                    y = this->hitsY[1];
                }
            } else {
                if (this->hitsX[0] > this->hitsX[1]){
                    x = this->hitsX[0];
                    y = this->hitsY[0];
                } else {
                    x = this->hitsX[1];
                    y = this->hitsY[1];
                }
            }
        } else {
            if (this->hitDir == -1){
                if (this->hitsY[0] < this->hitsY[1]){
                    x = this->hitsX[0];
                    y = this->hitsY[0];
                } else {
                    x = this->hitsX[1];
                    y = this->hitsY[1];
                }
            } else {
                if (this->hitsX[0] < this->hitsX[1]){
                    x = this->hitsX[0];
                    y = this->hitsY[0];
                } else {
                    x = this->hitsX[1];
                    y = this->hitsY[1];
                }
            }
        }
    } else {
        x = this->hitsX[2];
        y = this->hitsY[2];
    }

    while (!isValid){
        if (this->hitDir == -1){
            if (this->hitSide == 1){
                y++;
            } else {
                y--;
            }
        } else {
            if (this->hitSide == 1){
                x++;
            } else {
                x--;
            }
        }

        if (x < 0 || x > 14 || y < 0 || y > 14){
            isValid = false;
            if (this->hitSide == 1){
                this->hitSide *= -1;
                goto here;
            } else {
                this->CPUchooseShit (&x, &y, enemy);
                this->hitCount = 1;
                isValid = true;
            }
        } else if (enemy->map.map[x][y] == 'X' || enemy->map.map[x][y] == 'O'){
            isValid = false;
            if (this->hitSide == 1){
                this->hitSide *= -1;
                goto here;
            } else {
                this->CPUchooseShit (&x, &y, enemy);
                this->hitCount = 1;
                isValid = true;
            }
        } else {
            isValid = true;
        }
    }
    this->firstTime = false;
    *xpos = x;
    *ypos = y;
}

void getXandY(int *x, int *y){
    char posx, posy;
    bool isValid = false;

    while (!isValid){
        cin >> posx >> posy;
        cin.clear();
        fflush(stdin);

        if (isxdigit(posx) == false || isxdigit(posy) == false){
            isValid = false;
            std::cout << "Invalid input, try again:\n";
        } else {
            isValid = true;
        }
    }
    std::string s(1, posx), s2(1, posy);
    *x = stoi(s, 0, 16);
    *y = stoi(s2, 0, 16);
}
//------------------------------------------------------------------------------------------------------------------------------