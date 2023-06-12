#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "Randinator.h"
#include "Tile.h"
#include "PIC.h"

class Board
{
    int randoX = 0;
    int randoY = 0;
    int numMines = 0;
    int startMines = 50;
    int clickedTiles = 0;
public:
    Tile gameTiles[25][16] = {};
    Board();
    void newBoard();
    void setBoard(std::string);
    void nearMineCounter();
    void incrementClickedTiles();
    int getNumMines();
    int getNumClickedTiles();
    //.. last two function are cout tools to debug)
    void showMines();
    void showNearMineCount();
};

