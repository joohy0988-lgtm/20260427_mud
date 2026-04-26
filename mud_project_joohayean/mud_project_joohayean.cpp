#include <string>

class Entity {
protected:
    std::string name;
    int hp, maxHp, attack;

public:
    Entity(const std::string& n, int h, int atk)
        : name(n), hp(h), maxHp(h), attack(atk) {}

    virtual ~Entity() {}
    virtual void showInfo() const = 0;  

    void takeDamage(int dmg) { hp -= dmg; if (hp < 0) hp = 0; }
    bool isAlive() const { return hp > 0; }
};
