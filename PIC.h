#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>

class PIC
{	
	static std::unordered_map<std::string, sf::Texture> pics;
public:
	static sf::Texture& getPic(const char*);
	static void wipe();
};

