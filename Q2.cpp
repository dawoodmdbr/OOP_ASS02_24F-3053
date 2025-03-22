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
            cout << "Leveled up to " << level << endl;
        }
    }
    void useItem(Item*item){
        if(item->type == POTION){
            health += item->value;
            cout << "Health: " << health << endl;
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
            cout << "Enemy " << i+1 << ": " << enemies[i]->name << endl;
        }
        cout << "Items: " << endl;
        for(int i = 0; i < numItems; i++){
            cout << "Item " << i+1 << ": " << items[i]->name << endl;
        }
    }
};

int main()
{
    cout << "Hello World";
    return 0;
}