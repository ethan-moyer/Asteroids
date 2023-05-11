#pragma once
#include <raylib.h>
#include <string>
#include <unordered_map>

class ResourceManager
{
public:
	static Texture2D GetTexture(const std::string& path);
	static Sound GetSound(const std::string& path);
	static void Unload();
private:
	static std::unordered_map<std::string, Texture2D> textureCache;
	static std::unordered_map<std::string, Sound> soundCache;
};

