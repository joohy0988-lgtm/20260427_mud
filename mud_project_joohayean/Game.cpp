#include "Game.h"
#include "Player.h"
#include "Monster.h"
#include "Map.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// ── Constructor / Destructor ──────────────────────────
Game::Game()
    : player(nullptr), map1(nullptr), map2(nullptr),
      gameOver(false), victory(false) {}

Game::~Game() {
    delete player;
    delete map1;
    delete map2;
}

// ── run ──────────────────────────────────────────────
void Game::run() {
    while (true) {
        init();
        playLoop();

        if (victory) {
            system("cls");
            cout << "\n";
            cout << "****************************\n";
            cout << "*  Princess rescued!!!     *\n";
            cout << "*  The kingdom is saved!   *\n";
            cout << "****************************\n\n";
        }
        else {
            system("cls");
            cout << "\n=== GAME OVER ===\n\n";
        }

        cout << "Play again? (1:Yes  0:No)\n> ";
        int retry;
        cin >> retry;
        if (retry != 1) break;
        cin.ignore();
    }
}

// ── init ─────────────────────────────────────────────
void Game::init() {
    delete player; delete map1; delete map2;
    gameOver = false;
    victory  = false;

    system("cls");
    cout << "=== LABYRINTH ===\n\n";
    cout << "Enter hero name: ";
    string name;
    cin >> name;

    player = new Player(name);
    map1   = new Map(1);
    map2   = new Map(2);

    system("cls");
    cout << "=== Choose starting item ===\n";
    cout << "1. Weapon  (Dagger - ATK +3)\n";
    cout << "2. Food    (Bread x5 - HP restore)\n";
    cout << "3. Key     (Open treasure chests)\n> ";
    int choice;
    cin >> choice;

    if      (choice == 1) player->addItem("Dagger");
    else if (choice == 2) {
        for (int i = 0; i < 5; i++)
            player->addItem("Bread");
    }
    else                  player->addItem("Key");

    cin.ignore();
}

// ── playLoop ─────────────────────────────────────────
void Game::playLoop() {
    Map* curMap = map1;
    player->setPos(0, 0);

    while (!gameOver && !victory) {
        curMap->render(player->getPosX(), player->getPosY());
        player->showInfo();

        char input;
        cin.get(input);
        if (input == '\n') continue;

        if (input == 'q' || input == 'Q') {
            cout << "Quit? (y/n): ";
            char c; cin.get(c);
            if (c == 'y' || c == 'Y') { gameOver = true; break; }
            continue;
        }

        if (input == 'i' || input == 'I') {
            player->showInventory();
            cout << "Use item no. (0=cancel): ";
            int idx; cin >> idx;
            if (idx > 0) player->useItem(idx - 1);
            cin.ignore();
            continue;
        }

        if (!player->move(input)) continue;

        int      px   = player->getPosX();
        int      py   = player->getPosY();
        TileType tile = curMap->checkAndClear(px, py);

        if (tile == TileType::MONSTER) {
            Monster* mob = new Goblin();
            handleBattle(mob);
            delete mob;
        }
        else if (tile == TileType::ORC) {
            Monster* mob = new Orc();
            handleBattle(mob);
            delete mob;
        }
        else if (tile == TileType::BOSS1) {
            handleBoss1Rush();
        }
        else if (tile == TileType::BOSS2) {
            DarkLord* dl = new DarkLord();
            handleBattle(dl);
            if (!player->isAlive()) gameOver = true;
            else                    victory  = true;
            delete dl;
        }
        else if (tile == TileType::SHOP)   handleShop();
        else if (tile == TileType::CHEST)  handleChest();
        else if (tile == TileType::STAIRS) handleStairs(curMap);

        if (!player->isAlive()) gameOver = true;
    }
}

// ── handleBattle ─────────────────────────────────────
void Game::handleBattle(Monster* mob) {
    cout << "\n=== BATTLE START! ===\n";
    mob->showInfo();
    cout << "Press Enter...\n";
    cin.get();

    while (player->isAlive() && mob->isAlive()) {
        system("cls");
        player->showInfo();
        mob->showInfo();
        cout << "\n[1] Attack   [2] Item\n> ";

        int action; cin >> action;

        if (action == 1) {
            mob->takeDamageWithDef(player->getAttackVal());
            DarkLord* dl = dynamic_cast<DarkLord*>(mob);
            if (dl) dl->checkEnrage();
        }
        else if (action == 2) {
            player->showInventory();
            if (player->getInventorySize() > 0) {
                cout << "No.: "; int idx; cin >> idx;
                player->useItem(idx - 1);
            }
            cin.ignore(); continue;
        }

        if (!mob->isAlive()) {
            cout << mob->getName() << " defeated!\n";
            string loot = mob->dropLoot();
            if (loot != "none") {
                if (loot.find("Gold") != string::npos) {
                    int g = (loot=="Gold1") ? 1 : (loot=="Gold2") ? 2 : 3;
                    player->addGold(g);
                    cout << "Got " << g << " gold!\n";
                } else {
                    player->addItem(loot);
                }
            }
            cout << "Press Enter...\n";
            cin.ignore(); cin.get();
            return;
        }

        int dmg = mob->getAttack();
        player->takeDamage(dmg);
        cout << mob->getName() << " attacks! -" << dmg << " HP!\n";

        if (mob->isPoisonous()) player->applyPoison(3);
        player->tickPoison();

        if (!player->isAlive()) { cout << "You died...\n"; return; }
        cout << "Press Enter...\n";
        cin.ignore(); cin.get();
    }
}

// ── handleBoss1Rush ───────────────────────────────────
void Game::handleBoss1Rush() {
    cout << "=== MOB RUSH! Goblin x2 + Orc x1 ===\n";
    cin.get();

    vector<Monster*> wave;
    wave.push_back(new Goblin());
    wave.push_back(new Goblin());
    wave.push_back(new Orc());

    for (Monster* m : wave) {
        if (player->isAlive()) handleBattle(m);
        delete m;
    }

    if (player->isAlive()) {
        cout << "*** Hero Sword obtained! ATK +5 ***\n";
        player->addItem("HeroSword");
        cin.get();
    }
}

// ── handleShop ────────────────────────────────────────
void Game::handleShop() {
    vector<string> items  = {"Bread(HP+3)", "Apple(HP+4)", "Dagger(ATK+3)", "Key", "HPPotion(HP+10)"};
    vector<int>    prices = {2,              3,             5,               3,     5};

    while (true) {
        system("cls");
        cout << "=== SHOP ===  Gold: " << player->getGold() << "G\n";
        for (int i = 0; i < (int)items.size(); i++)
            cout << i+1 << ". " << items[i] << " - " << prices[i] << "G\n";
        cout << "0. Exit\n> ";

        int choice; cin >> choice;
        if (choice == 0) break;
        if (choice < 1 || choice > (int)items.size()) continue;

        if (player->spendGold(prices[choice-1]))
            player->addItem(items[choice-1]);
    }
    cin.ignore();
}

// ── handleChest ───────────────────────────────────────
void Game::handleChest() {
    cout << "=== TREASURE CHEST ===\n";
    if (player->hasKey()) {
        player->useKey();
        int gold = 3 + rand() % 5;
        player->addGold(gold);
        cout << "Opened! Got " << gold << " gold!\n";
    } else {
        cout << "Need a Key! Buy one at the shop.\n";
    }
    cout << "Press Enter...\n";
    cin.get();
}

// ── handleStairs ──────────────────────────────────────
void Game::handleStairs(Map*& curMap) {
    if (player->getFloor() == 1) {
        cout << "Moving to Floor 2!\n";
        player->nextFloor();
        player->setPos(0, 0);
        curMap = map2;
        cout << "Press Enter...\n";
        cin.get();
    }
}
