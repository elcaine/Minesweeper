#include "Tile.h"

Tile::Tile() {
}

bool Tile::ruClik() {
	return isClik;
}
void Tile::beClik() {
	isClik = true;
}

bool Tile::ruMine() {
	return isMine;
}
void Tile::beMine() {
	isMine = true;
}

bool Tile::ruFlag() {
	return isFlag;
}
void Tile::beFlag() {
	isFlag = true;
}
void Tile::unFlag() {
	isFlag = false;
}

int Tile::minesNear() {
	return numMinesNear;
}
void Tile::incrementMinesNear() {
	++numMinesNear;
}

void Tile::resetTile() {
	isClik = false;
	isMine = false;
	isFlag = false;
	numMinesNear = 0;
}

