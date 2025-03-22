#include <iostream>
using namespace std;
enum ItemType
{
    WEAPON,
    ARMOR,
    POTION,
    MISC
};
enum EnemyType
{
    GOBLIN,
    TROLL,
    DRAGON,
    SKELTON
};
enum TerrainType
{
    FOREST,
    CAVE,
    MOUNTAIN,
    VILLAGE
};

struct Item{
    string name;
    enum ItemType type;
    int value;
    double weight;
    void describeItem(){
        cout << "Name: " << name << endl;
        cout << "Type: " << type << endl;
        cout << "Value: " << value << endl;
        cout << "Weight: " << weight << endl;
    }
};
struct Enemy{
    string name;
    enum EnemyType type;
    int health;
    int attackPower;
    int defensePower;
    void attackEnemy( int damage ){
        health -= damage;
        cout << name << " took " << damage << endl << "health: " << health << endl;
    }
};
struct Character{
    string name;
    int level;
    int experience;
    int health;
    int attackPower;
    int defensePower;
    struct Item *inventory[10];
    int inventorySize;
    void gainExperience(int exp){
        experience += exp;
        if (experience >= 100){
            level++;
            experience-=100;
            cout << "Leveled up to " << level << endl << "Experience: " << experience << endl << endl;
        }
    }
    void useItem(Item*item){
        if(item->type == POTION){
            health += item->value;
            cout << "Used " << item->name << endl << "Health: " << health << endl << endl;
        }
    }
    void displayCharacterInfo(){
        cout << "Name: " << name << endl;
        cout << "Level: " << level << endl;
        cout << "Experience: " << experience << endl;
        cout << "Health: " << health << endl;
        cout << "Attack Power: " << attackPower << endl;
        cout << "Defense Power: " << defensePower << endl;
        cout << "Inventory: " << endl;
        for(int i = 0; i < inventorySize; i++){
            cout << "Item " << i+1 << ": " << inventory[i]->name << endl;
        }
        cout<< endl;
    }
};

struct Terrain{
    string name;
    enum TerrainType type;
    struct Enemy *enemies[10];
    int numEnemies;
    struct Item *items[10];
    int numItems;
    void addEnemy(Enemy*enemy){
        enemies[numEnemies] = enemy;
        numEnemies++;
    }
    void addItem(Item*item){
        items[numItems] = item;
        numItems++;
    }
    void displayTerrainInfo(){
        cout << "Name: " << name << endl;
        cout << "Type: " << type << endl;
        cout << "Enemies: " << endl;
        for(int i = 0; i < numEnemies; i++){
            cout << enemies[i]->name << endl;
        }
        cout << "Items: " << endl;
        for(int i = 0; i < numItems; i++){
            cout << items[i]->name << endl;
        }
        cout << endl;
    }
};
struct Area{
    string name;
    struct Terrain *terrain;
    struct Area* connectedAreas[10];
    int numConnectedAreas;
    void addConnectedArea(Area*area){
        connectedAreas[numConnectedAreas] = area;
        numConnectedAreas++;
    }
    void displayAreaInfo(){
        cout << "Name: " << name << endl;
        cout << "Terrain: " << terrain->name << endl;
        cout << "Connected Areas: " << endl;
        for(int i = 0; i < numConnectedAreas; i++){
            cout << "Connected Area " << i+1 << ": " << connectedAreas[i]->name << endl;
        }
        cout << endl;
    }
};
struct GameWorld{
    struct Area *areas[10];
    int numAreas;
    void addArea(Area*area){
        areas[numAreas] = area;
        numAreas++;
    }
    void displayWorldInfo(){
        cout << "Areas: " << endl;
        for(int i = 0; i < numAreas; i++){
            cout << "Area " << i+1 << ": " << endl;
            areas[i]->displayAreaInfo();
            cout<< "Terrain "<<i+1<<": " << endl;
            areas[i]->terrain->displayTerrainInfo();
        }
        cout << endl;
    }
};
int main()
{
    
    Item sword = {"Sword", WEAPON, 100, 3.5};
    Item potion = {"Health Potion", POTION, 50, 0.5};
    Enemy goblin = {"Goblin", GOBLIN, 50, 10, 2};
    Terrain forest = {"Enchanted Forest", FOREST, {}, 0, {}, 0};
    Area village = {"Old Village", &forest, {}, 0};
    Area cave = {"Dark Cave", &forest, {}, 0};
    GameWorld world = {{}, 0};

    forest.addEnemy(&goblin);
    village.terrain->addItem(&sword);
    world.addArea(&village);
    village.addConnectedArea(&cave);
    cave.addConnectedArea(&village);

    
    struct Character hero = {"Knight", 1, 0, 100, 15, 5, {}, 0};
    hero.inventory[hero.inventorySize] = &potion;
    hero.inventorySize++;
    hero.inventory[hero.inventorySize] = &sword;
    hero.inventorySize++;
    hero.displayCharacterInfo();
    hero.gainExperience(120);
    hero.useItem(&potion);
    
    world.displayWorldInfo();
    
    return 0;
}