#pragma once
#include <string>

#include "Entity.h"
#include <vector>
using namespace std;

// ── Monster (Entity 상속) ─────────────────────────────
class Monster : public Entity {
protected:
    int            defense;
    bool           canPoison;
    vector<string> dropPool;   // vector 드랍 목록

public:
    Monster(const string& n, int h, int atk, int def);
    virtual ~Monster() {}

    void   takeDamageWithDef(int atkDmg);
    string dropLoot() const;

    int  getDefense()  const;
    bool isPoisonous() const;

    void showInfo() const override;
};

// ── Goblin (Monster 상속) ─────────────────────────────
class Goblin : public Monster {
public:
    Goblin();
    void showInfo() const override;
};

// ── Orc (Monster 상속) ───────────────────────────────
class Orc : public Monster {
public:
    Orc();
    void showInfo() const override;
};

// ── Boss1 : 1층 보스 (Monster 상속) ──────────────────
class Boss1 : public Monster {
public:
    Boss1();
    void showInfo() const override;
};

// ── DarkLord : 마왕 (Monster 상속) ───────────────────
class DarkLord : public Monster {
private:
    bool enraged;

public:
    DarkLord();

    void checkEnrage();
    int  getAttack()  const override;
    bool isEnraged()  const;

    void showInfo() const override;
};
