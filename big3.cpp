#include "Board.h"
#include "BottomStuff.h"

sf::Sprite digitIs(int);
void killTiles(Board&, short, short);
void showMineCount(sf::RenderWindow&, int);
void numOnTile(sf::RenderWindow&, Tile&, unsigned int, unsigned int);

int main()
{
    bool debugy = false;
    bool rightRat, leftRat;
    unsigned int _x = 800;//25 tiles
    unsigned int _y = 600;//16 tiles..... 400 total
    int win = 0;
    int flagsRem = 0;
    unsigned int xx, yy;

    BottomStuff daDowns;
    Board* disBoard = new Board();
    flagsRem = (*disBoard).getNumMines();

    sf::Vector2f ratAt;
    sf::Sprite flag(PIC::getPic("flag"));
    sf::Sprite mine(PIC::getPic("mine"));
    sf::Sprite tile_hidden(PIC::getPic("tile_hidden"));
    sf::Sprite tile_revealed(PIC::getPic("tile_revealed"));
    sf::RenderWindow window(sf::VideoMode(_x, _y), "k3wL sToRy, br0!");

    while (window.isOpen()){
        rightRat = false;
        leftRat = false;

        sf::Event event;//====================================================== MIGHTY MIGHTY EVENT CHECKER
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
            //================================================================== WHERE CLICKETH THE RAT
            else if (event.type == sf::Event::MouseButtonReleased) {
                ratAt = (sf::Vector2f)sf::Mouse::getPosition(window);
                if (daDowns.updateRat(event, ratAt, leftRat, rightRat, debugy, disBoard)) {
                    win = 0;
                    flagsRem = (*disBoard).getNumMines();
                }
            }
            //..mouse click FIN
        }//..event polling FIN

        //====================================================================== WHERE RUNNING IS RAN'D
        window.clear();
        for (yy = 0; yy * 32 < 512; ++yy) {
            for (xx = 0; xx * 32 < _x; ++xx) {
                if (win == 0) {//=============================================== UPDATING isMINE, isCLICK, isFLAG
                    if (ratAt.x > xx * 32 && ratAt.x < xx * 32 + 32 && ratAt.y > yy * 32 && ratAt.y < yy * 32 + 32) {
                        if (leftRat && !(*disBoard).gameTiles[xx][yy].ruFlag()) {
                            if (!(*disBoard).gameTiles[xx][yy].ruClik()) {
                                (*disBoard).incrementClickedTiles();
                                (*disBoard).gameTiles[xx][yy].beClik();
                                //---------------------------------------------- END GAME (defeat)
                                if ((*disBoard).gameTiles[xx][yy].ruMine()) {
                                    win = -1;
                                    daDowns.faceMeow(win);
                                }
                                //---------------------------------------------- KILL ZERO-MINES-NEAR AREA
                                else if ((*disBoard).gameTiles[xx][yy].minesNear() == 0) {
                                    killTiles((*disBoard), xx, yy);
                                }                              
                            }
                            //-------------------------------------------------- END GAME (win)
                            if (win == 0 && (*disBoard).getNumClickedTiles() == 400 - (*disBoard).getNumMines()) {
                                flagsRem = 0;
                                win = 1;
                                daDowns.faceMeow(win);
                            }
                        }
                        //------------------------------------------------------ TOGGLE FLAG
                        else if (rightRat && !(*disBoard).gameTiles[xx][yy].ruClik()) {
                            if (!(*disBoard).gameTiles[xx][yy].ruFlag()) {
                                (*disBoard).gameTiles[xx][yy].beFlag();
                                --flagsRem;
                            }
                            else {
                                (*disBoard).gameTiles[xx][yy].unFlag();
                                ++flagsRem;
                            }
                        }
                    }//.. checking mine, click, flag FIN
                }
                //============================================================== DRAW da DRAWINGS
                if ((*disBoard).gameTiles[xx][yy].ruFlag()) {
                    tile_hidden.setPosition(xx * 32.0f, yy * 32.0f);
                    flag.setPosition(xx * 32.0f, yy * 32.0f);
                    window.draw(tile_hidden);
                    window.draw(flag);
                }
                else if (!(*disBoard).gameTiles[xx][yy].ruClik()) {
                    tile_hidden.setPosition(xx * 32.0f, yy * 32.0f);
                    window.draw(tile_hidden);
                }
                else
                {
                    numOnTile(window, (*disBoard).gameTiles[xx][yy], xx, yy);
                }
                //============================================================== WIN, DEFEAT, or DEBUGGY
                if(win == 1){
                    if ((*disBoard).gameTiles[xx][yy].ruMine())
                        (*disBoard).gameTiles[xx][yy].beFlag();
                }
                else if (win == -1 && (*disBoard).gameTiles[xx][yy].ruMine()) {
                    tile_revealed.setPosition(xx * 32.0f, yy * 32.0f);
                    window.draw(tile_revealed); 
                    if ((*disBoard).gameTiles[xx][yy].ruFlag()) {
                        flag.setPosition(xx * 32.0f, yy * 32.0f);
                        window.draw(flag);
                    }
                    mine.setPosition(xx * 32.0f, yy * 32.0f);      
                    window.draw(mine);
                }
                else if (debugy && (*disBoard).gameTiles[xx][yy].ruMine()) {
                    mine.setPosition(xx * 32.0f, yy * 32.0f);
                    window.draw(mine);
                }
            }
        }
    showMineCount(window, flagsRem);
    daDowns.showBottom(window);
    window.display();
}//.. running the run stuff FIN
PIC::wipe();
return 0;
}//.. main FIN

//=============================================================== FLAG KOMPUTATINATOR
sf::Sprite digitIs(int i) {
    if (i < 0)
        i *= -1;

    if (i % 10 == 0) {
        sf::Sprite d0(PIC::getPic("digits"));
        d0.setTextureRect(sf::IntRect(0, 0, 21, 32));
        return d0;
    }
    else if (i % 10 == 1) {
        sf::Sprite d1(PIC::getPic("digits"));
        d1.setTextureRect(sf::IntRect(21, 0, 21, 32));
        return d1;
    }
    else if (i % 10 == 2) {
        sf::Sprite d2(PIC::getPic("digits"));
        d2.setTextureRect(sf::IntRect(42, 0, 21, 32));
        return d2;
    }
    else if (i % 10 == 3) {
        sf::Sprite d3(PIC::getPic("digits"));
        d3.setTextureRect(sf::IntRect(63, 0, 21, 32));
        return d3;
    }
    else if (i % 10 == 4) {
        sf::Sprite d4(PIC::getPic("digits"));
        d4.setTextureRect(sf::IntRect(84, 0, 21, 32));
        return d4;
    }
    else if (i % 10 == 5) {
        sf::Sprite d5(PIC::getPic("digits"));
        d5.setTextureRect(sf::IntRect(105, 0, 21, 32));
        return d5;
    }
    else if (i % 10 == 6) {
        sf::Sprite d6(PIC::getPic("digits"));
        d6.setTextureRect(sf::IntRect(126, 0, 21, 32));
        return d6;
    }
    else if (i % 10 == 7) {
        sf::Sprite d7(PIC::getPic("digits"));
        d7.setTextureRect(sf::IntRect(147, 0, 21, 32));
        return d7;
    }
    else if (i % 10 == 8) {
        sf::Sprite d8(PIC::getPic("digits"));
        d8.setTextureRect(sf::IntRect(168, 0, 21, 32));
        return d8;
    }
    else {
        sf::Sprite d9(PIC::getPic("digits"));
        d9.setTextureRect(sf::IntRect(189, 0, 21, 32));
        return d9;
    }
}

void killTiles(Board& bb, short xTOm, short yTOn) {
    short _m[] = { xTOm - 1, xTOm, xTOm + 1 };
    short _n[] = { yTOn - 1, yTOn, yTOn + 1 };
    for (short nn : _n) {
        for (short mm : _m) {
            if (xTOm == mm && yTOn == nn) {
                //self killed elsewhere, do nada
            }
            else if (mm < 0 || nn < 0 || mm > 24 || nn > 15) {
                //off da board, do more nada
            }
            else if (!(bb.gameTiles[mm][nn].ruClik() || bb.gameTiles[mm][nn].ruFlag())) {
                //KILL ME
                bb.gameTiles[mm][nn].beClik();
                bb.incrementClickedTiles();
                if (bb.gameTiles[mm][nn].minesNear() == 0)
                    killTiles(bb, mm, nn);
            }
        }
    }
}

void showMineCount(sf::RenderWindow& disWin, int flagsNow) {
    int getD;
    sf::Sprite d100;
    sf::Sprite d010;
    sf::Sprite d001;

    getD = flagsNow;
    d001 = digitIs(getD);
    getD /= 10;
    d010 = digitIs(getD);
    getD /= 10;
    d100 = digitIs(getD);
    if (flagsNow < 0) {
        sf::Sprite dneg(PIC::getPic("digits"));
        dneg.setTextureRect(sf::IntRect(210, 0, 21, 32));
        dneg.setPosition(0, 512);
        d100.setPosition(21, 512);
        d010.setPosition(42, 512);
        d001.setPosition(63, 512);
        disWin.draw(dneg);
    }
    else {
        d100.setPosition(0, 512);
        d010.setPosition(21, 512);
        d001.setPosition(42, 512);
    }
    disWin.draw(d100);
    disWin.draw(d010);
    disWin.draw(d001);
}

void numOnTile(sf::RenderWindow& disWin, Tile& t, unsigned int xx, unsigned int yy) {
    sf::Sprite tile_revealed(PIC::getPic("tile_revealed"));
    sf::Sprite disNum;
    if (t.minesNear() == 8) {
        sf::Sprite number_8(PIC::getPic("number_8"));
        disNum = number_8;
    }
    else if (t.minesNear() == 7) {
        sf::Sprite number_7(PIC::getPic("number_7"));
        disNum = number_7;
    }
    else if (t.minesNear() == 6) {
        sf::Sprite number_6(PIC::getPic("number_6"));
        disNum = number_6;
    }
    else if (t.minesNear() == 5) {
        sf::Sprite number_5(PIC::getPic("number_5"));
        disNum = number_5;
    }
    else if (t.minesNear() == 4) {
        sf::Sprite number_4(PIC::getPic("number_4"));
        disNum = number_4;
    }
    else if (t.minesNear() == 3) {
        sf::Sprite number_3(PIC::getPic("number_3"));
        disNum = number_3;
    }
    else if (t.minesNear() == 2) {
        sf::Sprite number_2(PIC::getPic("number_2"));
        disNum = number_2;
    }
    else if (t.minesNear() == 1) {
        sf::Sprite number_1(PIC::getPic("number_1"));
        disNum = number_1;
    }
    else {
        disNum = tile_revealed;
    }
    tile_revealed.setPosition(xx * 32.0f, yy * 32.0f);
    disNum.setPosition(xx * 32.0f, yy * 32.0f);
    disWin.draw(tile_revealed);
    disWin.draw(disNum);
}