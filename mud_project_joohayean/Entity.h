#pragma once
#include <string>
#include <vector>
using namespace std;

class Entity {
protected:
    string name;
    int    hp;
    int    maxHp;
    int    attack;

public:
    Entity(const string& n, int h, int atk);
    virtual ~Entity();

    virtual int  getAttack()   const;
    virtual void showInfo()    const = 0;   // 순수 가상함수

    void takeDamage(int dmg);
    void heal(int amount);

    bool   isAlive()      const;
    string getName()      const;
    int    getHp()        const;
    int    getMaxHp()     const;
    int    getAttackVal() const;
};
