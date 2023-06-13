#pragma once
#include <map>
#include "Texture.h"

class TextureCache
{
private:
	std::map<std::string, Texture*> cache = {};

public:
	Texture* operator[] (std::string path);
};

