#include "BottomStuff.h"

BottomStuff::BottomStuff() {
	sf::Sprite SETdebug(PIC::getPic("debug"));
	debug = SETdebug;
	sf::Sprite SETface_lose(PIC::getPic("face_lose"));
	face_lose = SETface_lose;
	sf::Sprite SETface_happy(PIC::getPic("face_happy"));
	face_happy = SETface_happy;
	sf::Sprite SETface_win(PIC::getPic("face_win"));
	face_win = SETface_win;
	sf::Sprite SETtest_1(PIC::getPic("test_1"));
	test_1 = SETtest_1;
	sf::Sprite SETtest_2(PIC::getPic("test_2"));
	test_2 = SETtest_2;
	sf::Sprite SETtest_3(PIC::getPic("test_3"));
	test_3 = SETtest_3;

	debug.setPosition(500, 512);
	test_1.setPosition(503.0f + debug.getTextureRect().width, 512.0f);
	test_2.setPosition(test_1.getPosition().x + debug.getTextureRect().width + 2, 512);
	test_3.setPosition(test_2.getPosition().x + debug.getTextureRect().width + 2, 512);
	face_happy.setPosition(400.0f - (face_win.getTextureRect().width / 2), 512.0f);
	face_lose.setPosition(400.0f - (face_win.getTextureRect().width / 2), 512.0f);
	face_win.setPosition(400.0f - (face_win.getTextureRect().width / 2), 512.0f);
	faceNow = face_happy;
}

void BottomStuff::faceMeow(int x) {
    if (x == 0)
        faceNow = face_happy;
    else if (x == 1)
        faceNow = face_win;
    else
        faceNow = face_lose;
}

void BottomStuff::showBottom(sf::RenderWindow& w) {
	w.draw(faceNow);
	w.draw(debug);
	w.draw(test_1);
	w.draw(test_2);
	w.draw(test_3);
}

bool BottomStuff::updateRat(sf::Event event, sf::Vector2f& ratAt,
        bool& leftRat, bool& rightRat, bool& debugy, Board* bb) {
    bool newGame = false;
    if (event.mouseButton.button == sf::Mouse::Left) {
        leftRat = true;
        if (debug.getGlobalBounds().contains(ratAt) && debugy == false)
            debugy = true;
        else if (debug.getGlobalBounds().contains(ratAt) && debugy == true)
            debugy = false;
        else if (faceNow.getGlobalBounds().contains(ratAt)) {
            (*bb).newBoard();
            faceNow = face_happy;
            newGame = true;
        }
        else if (test_1.getGlobalBounds().contains(ratAt)) {
            (*bb).setBoard("boards/testboard1.brd");
            faceNow = face_happy;
            newGame = true;
        }
        else if (test_2.getGlobalBounds().contains(ratAt)) {
            (*bb).setBoard("boards/testboard2.brd");
            faceNow = face_happy;
            newGame = true;
        }
        else if (test_3.getGlobalBounds().contains(ratAt)) {
            (*bb).setBoard("boards/testboard3.brd");
            faceNow = face_happy;
            newGame = true;
        }
    }
    else if (event.mouseButton.button == sf::Mouse::Right) {
        rightRat = true;
    }
    return newGame;
}