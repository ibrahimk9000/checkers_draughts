#pragma once
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
class texture
{
private:
	sf::Texture textu;
public:
	texture(const std::string &path);
	sf::Texture *map();

};