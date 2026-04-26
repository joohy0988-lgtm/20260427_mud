#pragma once
#include "Player.h"
#include "Monster.h"
#include "Map.h"

// ── Game 클래스 (메인 루프 관리) ──────────────────────
class Game {
private:
    Player* player;
    Map*    map1;
    Map*    map2;
    bool    gameOver;
    bool    victory;

public:
    Game();
    ~Game();

    void run();       // 전체 루프 (재시작 포함)

private:
    void init();      // 게임 초기화 (시작 아이템 선택)
    void playLoop();  // 실제 플레이 루프

    // 이벤트 함수
    void handleBattle(Monster* mob);
    void handleBoss1Rush();
    void handleShop();
    void handleChest();
    void handleStairs(Map*& curMap);
};
