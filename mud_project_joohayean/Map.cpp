#include "Map.h"
using namespace std;

Tile::Tile() : type(TileType::EMPTY), visited(false) {}

Map::Map(int floorNum) : floor(floorNum) {
    tiles.resize(SIZE, vector<Tile>(SIZE));
    initFloor();
}

void Map::initFloor() {
    if (floor == 1) {
        setTile(3, 2, TileType::MONSTER);
        setTile(7, 4, TileType::MONSTER);
        setTile(5, 5, TileType::BOSS1);
        setTile(8, 1, TileType::SHOP);
        setTile(2, 7, TileType::CHEST);
        setTile(9, 9, TileType::STAIRS);
    }
    else if (floor == 2) {
        setTile(2, 1, TileType::MONSTER);
        setTile(6, 2, TileType::MONSTER);
        setTile(1, 5, TileType::ORC);
        setTile(4, 6, TileType::ORC);
        setTile(7, 7, TileType::ORC);
        setTile(5, 4, TileType::BOSS2);
        setTile(9, 0, TileType::SHOP);
        setTile(3, 8, TileType::CHEST);
    }
}

void Map::render(int px, int py) const {
    system("cls");
    cout << "=== Floor " << floor << " ===\n";
    for (int y = 0; y < SIZE; y++) {
        for (int x = 0; x < SIZE; x++) {
            if (x == px && y == py) { cout << "@ "; continue; }
            switch (tiles[y][x].type) {
                case TileType::EMPTY:   cout << ". "; break;
                case TileType::WALL:    cout << "# "; break;
                case TileType::MONSTER: cout << "M "; break;
                case TileType::ORC:     cout << "M "; break;
                case TileType::BOSS1:   cout << "B "; break;
                case TileType::BOSS2:   cout << "B "; break;
                case TileType::SHOP:    cout << "S "; break;
                case TileType::CHEST:   cout << "C "; break;
                case TileType::STAIRS:  cout << "E "; break;
                default:               cout << ". "; break;
            }
        }
        cout << "\n";
    }
    cout << "@ Player  M Monster  B Boss  S Shop  C Chest  E Stairs\n";
    cout << "[WASD] Move  [I] Inventory  [Q] Quit\n";
}

TileType Map::checkAndClear(int x, int y) {
    TileType t = tiles[y][x].type;
    if (t != TileType::SHOP && t != TileType::STAIRS)
        tiles[y][x].type = TileType::EMPTY;
    tiles[y][x].visited = true;
    return t;
}

void     Map::setTile(int x,int y,TileType t) { tiles[y][x].type = t; }
TileType Map::getTile(int x,int y) const       { return tiles[y][x].type; }
int      Map::getSize()  const                 { return SIZE; }
int      Map::getFloor() const                 { return floor; }
