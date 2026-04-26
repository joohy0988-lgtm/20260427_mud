#include "Player.h"
#include <iostream>
using namespace std;

Player::Player(const string& n)
    : Entity(n, 30, 5),
      gold(0), mp(10), maxMp(10),
      keys(0), floor(1),
      posX(0), posY(0),
      poisoned(false), poisonTurns(0) {}

void Player::showInfo() const {
    cout << "================================\n";
    cout << "  [Hero] " << name << "  (Floor " << floor << ")\n";
    cout << "  HP : " << hp << "/" << maxHp;
    if (poisoned) cout << " [POISONED]";
    cout << "\n";
    cout << "  MP : " << mp  << "/" << maxMp << "\n";
    cout << "  ATK: " << attack
         << "  GOLD: " << gold
         << "  KEY: " << keys << "\n";
    cout << "================================\n";
}

void Player::addItem(const string& item) {
    inventory.push_back(item);
    cout << "[GET] " << item << "!\n";
}

bool Player::useItem(int idx) {
    if (idx < 0 || idx >= (int)inventory.size()) return false;
    string& it = inventory[idx];

    // HP restore items
    if (it == "Bread")           { heal(3);  cout << "Bread: HP+3\n"; }
    else if (it == "Apple")      { heal(4);  cout << "Apple: HP+4\n"; }
    else if (it == "HPPotion(HP+10)") { heal(10); cout << "Potion: HP+10\n"; }
    else if (it == "RottenMeat") { heal(2);  cout << "RottenMeat: HP+2\n"; }

    // Weapon equip
    else if (it == "Dagger" || it == "Dagger(ATK+3)") {
        attack += 3; cout << "Dagger equipped! ATK+" << 3 << "\n";
    }
    else if (it == "HeroSword") {
        attack += 5; cout << "HeroSword equipped! ATK+5\n";
    }

    // Key
    else if (it == "Key") {
        keys++;
        cout << "Key added!\n";
        inventory.erase(inventory.begin() + idx);
        return true;
    }

    inventory.erase(inventory.begin() + idx);
    return true;
}

bool Player::hasItem(const string& item) const {
    for (const auto& it : inventory)
        if (it == item) return true;
    return false;
}

void Player::showInventory() const {
    cout << "--- Inventory (" << inventory.size() << ") ---\n";
    if (inventory.empty()) { cout << "(empty)\n"; return; }
    for (int i = 0; i < (int)inventory.size(); i++)
        cout << i+1 << ". " << inventory[i] << "\n";
}

int Player::getInventorySize() const { return (int)inventory.size(); }

bool Player::move(char dir) {
    int nx = posX, ny = posY;
    if      (dir=='w'||dir=='W') ny--;
    else if (dir=='s'||dir=='S') ny++;
    else if (dir=='a'||dir=='A') nx--;
    else if (dir=='d'||dir=='D') nx++;
    else return false;

    if (nx<0||nx>=10||ny<0||ny>=10) { cout << "Wall!\n"; return false; }
    posX = nx; posY = ny;
    return true;
}

int  Player::getPosX()         const { return posX; }
int  Player::getPosY()         const { return posY; }
void Player::setPos(int x,int y)     { posX=x; posY=y; }

void Player::addGold(int g)          { gold += g; }
bool Player::spendGold(int g) {
    if (gold < g) { cout << "Not enough gold!\n"; return false; }
    gold -= g; return true;
}
int  Player::getGold()         const { return gold; }

void Player::healMp(int amount) { mp+=amount; if(mp>maxMp) mp=maxMp; }
int  Player::getMp()           const { return mp; }

void Player::applyPoison(int turns) {
    poisoned=true; poisonTurns=turns;
    cout << "Poisoned! (" << turns << " turns)\n";
}
void Player::tickPoison() {
    if (!poisoned) return;
    takeDamage(2); poisonTurns--;
    cout << "Poison dmg -2!\n";
    if (poisonTurns<=0) { poisoned=false; cout << "Poison cleared.\n"; }
}
bool Player::isPoisoned() const { return poisoned; }

void Player::addKey()        { keys++; }
bool Player::hasKey()  const { return keys > 0; }
void Player::useKey()        { if (keys>0) keys--; }

int  Player::getFloor() const { return floor; }
void Player::nextFloor()      { floor++; }
