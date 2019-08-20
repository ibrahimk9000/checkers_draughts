#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#ifdef _WIN32
#include <windows.h>
#elif __linux__
#include <iostream>
#endif
class texture
{
private:
	sf::Texture textu;
public:
	texture(const std::string &path);
	sf::Texture *map();

};