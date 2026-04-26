#include "Monster.h"
#include <iostream>
#include <cstdlib>
using namespace std;

// =====================================================
//  Monster
// =====================================================
Monster::Monster(const string& n, int h, int atk, int def)
    : Entity(n, h, atk), defense(def), canPoison(false) {}

void Monster::takeDamageWithDef(int atkDmg) {
    int real = atkDmg - defense;
    if (real < 1) real = 1;
    takeDamage(real);
    cout << name << " -" << real << " dmg! (HP:" << hp << ")\n";
}

string Monster::dropLoot() const {
    if (dropPool.empty()) return "none";
    int idx = rand() % (int)dropPool.size();
    return dropPool[idx];
}

int  Monster::getDefense()  const { return defense; }
bool Monster::isPoisonous() const { return canPoison; }

void Monster::showInfo() const {
    cout << "[" << name << "] HP:" << hp << "/" << maxHp
         << " DEF:" << defense << "\n";
}

// =====================================================
//  Goblin
// =====================================================
Goblin::Goblin() : Monster("Goblin", 10, 4, 2) {
    dropPool.push_back("Gold1");
    dropPool.push_back("Gold2");
    dropPool.push_back("Gold3");
    dropPool.push_back("RottenMeat");
    dropPool.push_back("Dagger");
}

void Goblin::showInfo() const {
    cout << "\n"
         << "  .  .\n"
         << " (o)(o)\n"
         << " ( __ )  < Kyaaak!\n"
         << "  \\  /\n\n";
    cout << "[Goblin] HP:" << hp << "/" << maxHp
         << " DEF:" << defense << "\n";
}

// =====================================================
//  Orc
// =====================================================
Orc::Orc() : Monster("Orc", 15, 6, 3) {
    dropPool.push_back("Gold2");
    dropPool.push_back("Gold3");
    dropPool.push_back("RottenMeat");
    dropPool.push_back("Dagger");
}

void Orc::showInfo() const {
    cout << "\n"
         << "  ___\n"
         << " |o o|\n"
         << " | ^ |  > Grrrr!\n"
         << "  ---\n\n";
    cout << "[Orc] HP:" << hp << "/" << maxHp
         << " DEF:" << defense << "\n";
}

// =====================================================
//  Boss1
// =====================================================
Boss1::Boss1() : Monster("DungeonGuard", 30, 8, 3) {
    dropPool.push_back("Gold3");
    dropPool.push_back("Gold3");
}

void Boss1::showInfo() const {
    cout << "\n"
         << " /\\   /\\\n"
         << "( o   o )\n"
         << " \\  ^  /  >> None shall pass!\n"
         << "  |||||\n\n";
    cout << "[DungeonGuard] HP:" << hp << "/" << maxHp
         << " DEF:" << defense << "\n";
}

// =====================================================
//  DarkLord
// =====================================================
DarkLord::DarkLord() : Monster("DarkLord", 50, 10, 4), enraged(false) {
    canPoison = true;
    dropPool.push_back("Princess");
}

void DarkLord::checkEnrage() {
    if (!enraged && hp <= maxHp / 2) {
        enraged  = true;
        attack  += 4;
        cout << "DarkLord is ENRAGED! ATK increased!\n";
    }
}

int  DarkLord::getAttack()  const { return enraged ? attack + 2 : attack; }
bool DarkLord::isEnraged()  const { return enraged; }

void DarkLord::showInfo() const {
    cout << "\n"
         << "  /\\     /\\\n"
         << " /  \\   /  \\\n"
         << "( ))) O ((( )\n"
         << " \\  \\___/  /   >>> No one can defeat me!\n"
         << "  \\_______/\n\n";
    cout << "[DarkLord] HP:" << hp << "/" << maxHp;
    if (enraged) cout << " [ENRAGED]";
    cout << " DEF:" << defense << "\n";
}
