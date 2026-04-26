#pragma once
#include <vector>
#include <iostream>
using namespace std;

// 타일 종류
enum class TileType {
    EMPTY,    // .  빈 공간
    WALL,     // #  벽
    MONSTER,  // M  고블린
    ORC,      // M  오크 (색 다름)
    BOSS1,    // B  1층 보스
    BOSS2,    // B  마왕
    SHOP,     // S  상점
    CHEST,    // C  보물상자
    STAIRS    // E  계단 (다음 층)
};

// 타일 하나
struct Tile {
    TileType type;
    bool     visited;
    Tile();
};

// ── Map 클래스 ────────────────────────────────────────
class Map {
private:
    static const int SIZE = 10;
    vector<vector<Tile>> tiles;     // 2차원 vector!
    int floor;

public:
    Map(int floorNum);

    void     initFloor();
    void     render(int px, int py) const;
    TileType checkAndClear(int x, int y);

    void     setTile(int x, int y, TileType t);
    TileType getTile(int x, int y) const;
    int      getSize()  const;
    int      getFloor() const;
};
