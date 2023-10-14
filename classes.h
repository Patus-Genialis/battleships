class Ship{
    public:
        bool isAlive = true;
        int size, dir, health;
        int *xVet, *yVet;
        std::string type;
        Ship(int type = 1);
        bool seeIfAlive();
};

class Map{
    public:
        char map[15][15];
        Map();
        void printMap();
        bool addShip(Ship *ship);
        void updateMap(char map[15][15]);
        void clearMap();
        //CPU functions
        void addShipCPU(Ship *ship);
};

class Player{
    public:
        bool ready = false, cpu;
        Map map, enemyMap;
        Ship ships[5];
        Player(Map map, Ship carrier, Ship battleship, Ship cruiser, Ship submarine, Ship destroyer, bool cpu);
        void shoot(Player *enemy);
        void printGame();
        bool seeIfAlive();
        int aliveShips();
        // CPU functions
        bool firstTime = true;
        int hitsX[3], hitsY[3], hitDir, hitCount = 0, hitSide = 1;
        void CPUthink(int *xpos, int *ypos, Player *enemy);
        void CPUshoot(Player *enemy);
        void CPUchooseFhit(int *xpos, int *ypos, Player *enemy);
        void CPUchooseShit(int *xpos, int *ypos, Player *enemy);
        void CPUchooseThit(int *xpos, int *ypos, Player *enemy);
};