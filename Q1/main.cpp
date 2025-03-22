#include <iostream>
using namespace std;
const int MAP_SIZE = 5;
struct coordinates
{
    int x;
    int y;
};
struct Unit
{
    string unitType;
    int health;
    int attack;
    int defense;
    int movementRange;
    struct coordinates position;
    Unit(string u, int h, int a, int d, int m, int x, int y)
    {
        unitType = u;
        health = h;
        attack = a;
        defense = d;
        movementRange = m;
        position.x = x;
        position.y = y;
    }
    void moveUnit(int newX, int newY)
    {
        position.x = newX;
        position.y = newY;
    }
    bool isAlive()
    {
        return (health > 0);
    }
    void attackUnit(Unit *enemyUnit)
    {
        int damage = attack - enemyUnit->defense;
        if (damage > 0)
        {
            enemyUnit->health -= damage;
        }
    }
    void displayInfo()
    {
        cout << "Unit Type: " << unitType << endl;
        cout << "Health: " << health << endl;
        cout << "Attack: " << attack << endl;
        cout << "Defense: " << defense << endl;
        cout << "Movement Range: " << movementRange << endl;
        cout << "Position: (" << position.x << ", " << position.y << ")" << endl;
    }
};

struct Map
{
    struct Unit *units[MAP_SIZE][MAP_SIZE];
    void initializeMap()
    {
        for (int i = 0; i < MAP_SIZE; i++)
        {
            for (int j = 0; j < MAP_SIZE; j++)
            {
                units[i][j] = NULL;
            }
        }
    }
    void addUnitToMap(Unit *unit, int x, int y)
    {
        units[x][y] = unit;
    }
    void removeUnitFromMap(int x, int y)
    {
        units[x][y] = NULL;
    }
    void displayMap()
    {
        for (int i = 0; i < MAP_SIZE; i++)
        {
            for (int j = 0; j < MAP_SIZE; j++)
            {
                if (units[i][j] == NULL)
                {
                    cout << "_ ";
                }
                else
                {
                    cout << units[i][j]->unitType[0] << " ";
                }
            }
            cout << endl;
        }
    }
    ~Map()
    {
        for (int i = 0; i < MAP_SIZE; i++)
        {
            for (int j = 0; j < MAP_SIZE; j++)
            {
                if (units[i][j] != nullptr)
                {
                    delete units[i][j];
                    units[i][j] = nullptr;
                }
            }
        }
    }
};
struct Player
{
    string playerName;
    struct Unit *units[10];
    int unitCount = 0;
    Player(string name, int count)
    {
        playerName = name;
        unitCount = count;
    }

    void addUnit(Unit *newUnit)
    {
        if (unitCount < 10)
        {
            units[unitCount++] = newUnit;
        }
    }

    void removeUnit(Unit *unit)
    {
        for (int i = 0; i < unitCount; i++)
        {
            if (units[i] == unit)
            {
                delete units[i];
                units[i] = nullptr;
                for (int j = i; j < unitCount - 1; j++)
                    units[j] = units[j + 1];
                unitCount--;
                return;
            }
        }
    }

    void displayUnits()
    {
        cout << playerName << "'s Units:" << endl;
        for (int i = 0; i < unitCount; i++)
        {
            units[i]->displayInfo();
        }
        cout << endl;
    }
    ~Player()
    {
        for (int i = 0; i < unitCount; i++)
        {
            delete units[i];
        }
    }
};

struct Game
{
    struct Player *players[2];
    struct Map *gameMap;
    int turn;

    Game(string p1, string p2)
    {
        players[0] = new Player(p1, 0);
        players[1] = new Player(p2, 0);
        gameMap = new Map();
        gameMap->initializeMap();
        turn = 0;
    }

    void nextTurn()
    {
        turn = 1 - turn;
    }

    void playerAction(int x, int y, int newX, int newY)
    {
        struct Unit *unit = gameMap->units[x][y];
        if (unit == NULL)
        {
            cout << "No unit at this position" << endl;
            return;
        }
        if (unit != nullptr)
        {
            gameMap->removeUnitFromMap(x, y);
            gameMap->addUnitToMap(unit, newX, newY);
        }
    }

    bool checkVictory()
    {
        if (players[0]->unitCount == 0)
        {
            cout << players[1]->playerName << " wins!" << endl;
            return true;
        }
        if (players[1]->unitCount == 0)
        {
            cout << players[0]->playerName << " wins!" << endl;
            return true;
        }
        return false;
    }

    void resolveCombat(Unit *attacker, Unit *defender, Player *defenderPlayer)
    {

        int damage = attacker->attack - defender->defense;
        if (damage > 0)
        {
            defender->health -= damage;
            cout << attacker->unitType << " attacked " << defender->unitType
                 << " causing " << damage << " damage.\n";
        }
        else
        {
            cout << "No damage inflicted! Defense is too high.\n";
            return;
        }

        if (defender->health <= 0)
        {
            cout << defender->unitType << " has been defeated!\n";
            defenderPlayer->removeUnit(defender);
            gameMap->removeUnitFromMap(defender->position.x, defender->position.y);
        }
    }
    ~Game()
    {
        delete players[0];
        delete players[1];
        delete gameMap;
    }
};

int main()
{

    Game game("Player1", "Player2");

    Unit *u1 = new Unit("Soldier", 100, 25, 10, 1, 0, 1);
    Unit *u2 = new Unit("Soldier", 100, 25, 10, 1, 0, 1);
    Unit *u3 = new Unit("Soldier", 100, 25, 10, 1, 0, 1);
    game.players[0]->addUnit(u1);
    game.players[0]->addUnit(u2);
    game.players[0]->addUnit(u3);

    Unit *u4 = new Unit("Soldier", 100, 25, 10, 1, 4, 1);
    Unit *u5 = new Unit("Soldier", 100, 25, 10, 1, 4, 1);
    Unit *u6 = new Unit("Soldier", 100, 25, 10, 1, 4, 1);
    game.players[1]->addUnit(u4);
    game.players[1]->addUnit(u5);
    game.players[1]->addUnit(u6);

    game.gameMap->addUnitToMap(u1, 0, 1);
    game.gameMap->addUnitToMap(u2, 0, 2);
    game.gameMap->addUnitToMap(u3, 0, 3);
    game.gameMap->addUnitToMap(u4, 4, 1);
    game.gameMap->addUnitToMap(u5, 4, 2);
    game.gameMap->addUnitToMap(u6, 4, 3);

    game.gameMap->displayMap();

    return 0;
}