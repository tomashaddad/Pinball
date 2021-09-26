#pragma once

#include <string>

enum class TextureType {
	DIFFUSE,
	SPECULAR,
	NORMAL,
	HEIGHT
};

struct Texture {
	unsigned int id;
	TextureType type;
	std::string path;
};