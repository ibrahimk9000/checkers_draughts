
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
#ifdef _WIN32
	MessageBoxA(NULL, "resource not found","Error!", MB_ICONEXCLAMATION | MB_OK);
	exit(1);
#elif __linux__	
	std::cerr<<"file not found";
	exit(1);
#endif
}

	}
sf::Texture *texture::map() {
	
	return &textu;
}
