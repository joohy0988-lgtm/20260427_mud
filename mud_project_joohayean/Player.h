#pragma once
#include "Entity.h"
#include <vector>
#include <string>
using namespace std;

class Player : public Entity {
private:
    int gold;
    int mp;
    int maxMp;
    int keys;
    int floor;
    int posX, posY;
    bool poisoned;
    int  poisonTurns;
    vector<string> inventory;

public:
    Player(const string& n);

    void showInfo()      const override;
    void showInventory() const;

    void addItem(const string& item);
    bool useItem(int idx);
    bool hasItem(const string& item) const;
    int  getInventorySize() const;

    bool move(char dir);
    int  getPosX()  const;
    int  getPosY()  const;
    void setPos(int x, int y);

    void addGold(int g);
    bool spendGold(int g);
    int  getGold() const;

    void healMp(int amount);
    int  getMp() const;

    void applyPoison(int turns);
    void tickPoison();
    bool isPoisoned() const;

    void addKey();
    bool hasKey()  const;
    void useKey();

    int  getFloor() const;
    void nextFloor();
};