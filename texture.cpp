#include "texture.h"
texture::texture(const std::string &path)
{
try
{
	if (!textu.loadFromFile(path))  //load texture if path not found throw error
		throw 1;

}
catch (int )
{

	//MessageBoxA(NULL, "resource not found","Error!", MB_ICONEXCLAMATION | MB_OK);
	std::cerr<<"file not found";
	
}

	}
sf::Texture *texture::map() {
	
	return &textu;
}
