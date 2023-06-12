#include "Board.h"
using namespace std;

Board::Board() {
    //.............................MAKE MINES
    while (numMines < startMines) {
        randoX = Randinator::iNum(0, 24);
        randoY = Randinator::iNum(0, 15);
        if (!gameTiles[randoX][randoY].ruMine()) {
            ++numMines;
            gameTiles[randoX][randoY].beMine();
        }
    }
    nearMineCounter();
    //showMines();//......................................... (last two function are cout tools to debug)
    //showNearMineCount();
}

void Board::newBoard() {
    short x, y;
    for (y = 0; y < 16; ++y) {//............................. CLEAR CRUD
        for (x = 0; x < 25; ++x) {
            gameTiles[x][y].resetTile();
        }
    }
    clickedTiles = 0;
    numMines = 0;
    while (numMines < startMines) {//........................ MAKE MINES
        randoX = Randinator::iNum(0, 24);
        randoY = Randinator::iNum(0, 15);
        if (!gameTiles[randoX][randoY].ruMine()) {
            ++numMines;
            gameTiles[randoX][randoY].beMine();
        }
    }
    nearMineCounter();
    //showMines();//......................................... (last two function are cout tools to debug)
    //showNearMineCount();
}

void Board::setBoard(string s) {
    short x, y;
    //.............................CLEAR CRUD
    for (y = 0; y < 16; ++y) {
        for (x = 0; x < 25; ++x) {
            gameTiles[x][y].resetTile();
        }
    }
    clickedTiles = 0;
    numMines = 0;
    //.............................MAKE MINES
    ifstream minesIn;
    minesIn.open(s);
    if (!minesIn.is_open()) {
        cout << "big big problem now" << endl;
    }
    char tmp;
    for (y = 0; y < 16; ++y) {
        for (x = 0; x < 25; ++x) {
            minesIn >> tmp;
            if (tmp == '1') {
                ++numMines;
                gameTiles[x][y].beMine();
            }
        }
    }
    nearMineCounter();
    //showMines();//......................................... (last two function are cout tools to debug)
    //showNearMineCount();
}

void Board::nearMineCounter() {
    short x, y;
    for (y = 0; y < 16; ++y) {
        for (x = 0; x < 25; ++x) {
            if (!gameTiles[x][y].ruMine()) {
                short _x[] = { x - 1, x, x + 1 };
                short _y[] = { y - 1, y, y + 1 };
                for (short yy : _y) {
                    for (short xx : _x) {
                        if (x == xx && y == yy) {
                            //self, do not count
                        }
                        else if (xx < 0 || yy < 0 || xx > 24 || yy > 15) {
                            //off da board, do nada
                        }
                        else if (gameTiles[xx][yy].ruMine()) {
                            gameTiles[x][y].incrementMinesNear();
                        }
                    }
                }
            }
        }
    }
}

void Board::incrementClickedTiles() {
    ++clickedTiles;
}

int Board::getNumMines() {
    return numMines;
}

int Board::getNumClickedTiles() {
    return clickedTiles;
}
//..//////////////////////
void Board::showMines() {
    cout << endl;
    for (short y = 0; y < 16; ++y) {
        for (short x = 0; x < 25; ++x) {
            cout << gameTiles[x][y].ruMine();
        }
        cout << endl;
    }
}

void Board::showNearMineCount() {
    cout << endl;
    for (short y = 0; y < 16; ++y) {
        for (short x = 0; x < 25; ++x) {
            cout << gameTiles[x][y].minesNear();
        }
        cout << endl;
    }
}