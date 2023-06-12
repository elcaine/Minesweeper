#pragma once
#include <SFML/Graphics.hpp>

class Tile : public sf::Sprite
{
	bool isClik = false;
	bool isMine = false;
	bool isFlag = false;
	int numMinesNear = 0;
public:
	Tile();

	bool ruClik();
	void beClik();

	bool ruMine();
	void beMine();

	bool ruFlag();
	void beFlag();
	void unFlag();

	int minesNear();
	void incrementMinesNear();
	void resetTile();
};

