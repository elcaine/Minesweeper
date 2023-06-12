#include "PIC.h"

std::unordered_map<std::string, sf::Texture> PIC::pics;

sf::Texture& PIC::getPic(const char* shortName) {
	if (pics.find(shortName) == pics.end()) {
		std::string fPath = "images/";
		fPath += shortName;
		fPath += ".png";
		pics[shortName].loadFromFile(fPath);
	}
	return pics[shortName];
}

void PIC::wipe() {
	pics.clear();
}