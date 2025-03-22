#include<iostream>
using namespace std;
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
};
int main(){
    cout<<"Hello World!"<<endl;
    return 0;
}