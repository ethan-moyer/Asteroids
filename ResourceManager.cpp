#include "ResourceManager.h"

std::unordered_map<std::string, Texture2D> ResourceManager::textureCache;
std::unordered_map<std::string, Sound> ResourceManager::soundCache;

Texture2D ResourceManager::GetTexture(const std::string& path)
{
	if (textureCache.find(path) != textureCache.end())
	{
		return textureCache.at(path);
	}
	else
	{
		Texture2D tex = LoadTexture(path.c_str());
		textureCache.insert({ path, tex });
		return tex;
	}
}

Sound ResourceManager::GetSound(const std::string& path)
{
	if (soundCache.find(path) != soundCache.end())
	{
		return soundCache.at(path);
	}
	else
	{
		Sound sound = LoadSound(path.c_str());
		soundCache.insert({ path, sound });
		return sound;
	}
}

void ResourceManager::Unload()
{
	for (std::pair<std::string, Texture2D> pair : textureCache)
	{
		UnloadTexture(pair.second);
	}
	textureCache.clear();

	for (std::pair<std::string, Sound> pair : soundCache)
	{
		UnloadSound(pair.second);
	}
	soundCache.clear();
}