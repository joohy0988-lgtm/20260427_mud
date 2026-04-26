#include "Entity.h"
#include <iostream>
using namespace std;

// 생성자
Entity::Entity(const string& n, int h, int atk)
    : name(n), hp(h), maxHp(h), attack(atk) {}

// 소멸자
Entity::~Entity() {}

// 공격력 반환
int Entity::getAttack() const {
    return attack;
}

// 데미지 받기
void Entity::takeDamage(int dmg) {
    hp -= dmg;
    if (hp < 0) hp = 0;
}

// HP 회복
void Entity::heal(int amount) {
    hp += amount;
    if (hp > maxHp) hp = maxHp;
}

// 생존 여부
bool Entity::isAlive() const {
    return hp > 0;
}

string Entity::getName()      const { return name; }
int    Entity::getHp()        const { return hp; }
int    Entity::getMaxHp()     const { return maxHp; }
int    Entity::getAttackVal() const { return attack; }

