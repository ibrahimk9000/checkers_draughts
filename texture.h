#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>

#ifdef _WIN32
#define getcwd _getcwd
#define DEFSL "\\res\\"
#include <direct.h>
#include <windows.h>

#elif __linux__
#include <unistd.h>
#include <iostream>
#define DEFSL "/res/"
#endif
std::string cwd(std::string res);
class texture
{
private:
	sf::Texture textu;
public:
	texture(const std::string &path);
	sf::Texture *map();

};