
#include "texture.h"
std::string cwd(std::string res) {
	char currwd[FILENAME_MAX];
	std::string resu;
	try {
		if (getcwd(currwd, sizeof(currwd)) != NULL) {
			resu = currwd;
			resu += DEFSL + res;
		}
		else {
			throw 1;
		}
	}
	catch (int)
	{
#ifdef _WIN32
		MessageBoxA(NULL, "Wrong path", "Error!", MB_ICONEXCLAMATION | MB_OK);
		exit(1);
#elif __linux__	
		std::cerr << "Wrong path";
		exit(1);
#endif
	}
	return resu;
}
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
	MessageBoxA(NULL,path.c_str(),"Error!", MB_ICONEXCLAMATION | MB_OK);
	exit(1);
#elif __linux__	
	std::cerr<<"resource not found";
	exit(1);
#endif
}

	}
sf::Texture *texture::map() {
	
	return &textu;
}
