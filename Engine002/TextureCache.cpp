#include "TextureCache.h"


Texture* TextureCache::operator[] (std::string path) {
	auto pointer = cache.find(path);
	if (pointer == cache.end()) {
		Texture* texture = new Texture(path.c_str());
		std::pair<std::string, Texture*> item = std::make_pair(path, texture);
		cache.insert(item);
		return texture;
	} else {
		return pointer->second;
	}
}