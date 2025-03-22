#include<iostream>
using namespace std;
const int MAP_SIZE = 10;
struct coordinates{
    int x;
    int y;
};
struct Unit{
    string unitType;
    int health;
    int attack;
    int defense;
    int movementRange;
    struct coordinates position;
    Unit(string u, int h, int a, int d, int m, int x, int y){
        unitType = u;
        health = h;
        attack = a;
        defense = d;
        movementRange = m;
        position.x = x;
        position.y = y;
    }
    void moveUnit(int newX, int newY){
        position.x = newX;
        position.y = newY;
    }
    bool isAlive(){
        return (health > 0);
    }
    void attackUnit(Unit* enemyUnit){
        int damage = attack - enemyUnit->defense;
        if(damage > 0){
            enemyUnit->health -= damage;
        }
    }
    void displayInfo(){
        cout<<"Unit Type: "<<unitType<<endl;
        cout<<"Health: "<<health<<endl;
        cout<<"Attack: "<<attack<<endl;
        cout<<"Defense: "<<defense<<endl;
        cout<<"Movement Range: "<<movementRange<<endl;
        cout<<"Position: ("<<position.x<<", "<<position.y<<")"<<endl;
    }
};

struct Map{
    struct Unit *units[MAP_SIZE][MAP_SIZE];
    void initializeMap(){
        for(int i=0; i<MAP_SIZE; i++){
            for(int j=0; j<MAP_SIZE; j++){
                units[i][j] = NULL;
            }
        }
    }
    void addUnitToMap(Unit* unit, int x, int y){
        units[x][y] = unit;
    }
    void removeUnitFromMap(int x, int y){
        units[x][y] = NULL;
    }
    void displayMap(){
        for(int i=0; i<MAP_SIZE; i++){
            for(int j=0; j<MAP_SIZE; j++){
                if(units[i][j] != NULL){
                    cout<<"U ";
                }
                else{
                    cout<<"- ";
                }
            }
            cout<<endl;
        }
    }
};
struct Player{
    string playerName;
    struct Unit* units[10];
    int unitCount = 0;
    Player(string name, int count){
        playerName = name;
        unitCount = count;
    }

    void addUnit(Unit* newUnit) {
        if (unitCount < 10) {
            units[unitCount++] = newUnit;
        }
    }

    void removeUnit(Unit* unit) {
        for (int i = 0; i < unitCount; i++) {
            if (units[i] == unit) {
                delete units[i]; 
                for (int j = i; j < unitCount - 1; j++)
                    units[j] = units[j + 1]; 
                unitCount--;
                return;
            }
        }
    }

    void displayUnits() {
        cout<<playerName<<"'s Units:"<<endl;
        for (int i = 0; i < unitCount; i++) {
            units[i]->displayInfo();
        }
    }
    ~Player(){
        for(int i=0; i<unitCount; i++){
            delete units[i];
        }
    }
};




int main(){
    cout<<"Hello World!"<<endl;
    return 0;
}