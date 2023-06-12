#pragma once
#include "Board.h"

class BottomStuff
{
    sf::Sprite debug;
    sf::Sprite faceNow;
    sf::Sprite face_lose;
    sf::Sprite face_happy;
    sf::Sprite face_win;
    sf::Sprite test_1;
    sf::Sprite test_2;
    sf::Sprite test_3;
public:
    BottomStuff();
    void faceMeow(int);
    void showBottom(sf::RenderWindow&);
    bool updateRat(sf::Event, sf::Vector2f&, bool&, bool&, bool&, Board*);
};

