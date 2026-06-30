#pragma once
#include <raylib.h>
#include <string>
#include <unordered_map>
#include <vector>

using SoundPool = std::vector<Sound>;

// Load asset functions
Texture &loadTexture(const std::string &name, const std::string &path);
Font &loadFont(const std::string &name, const std::string &path);
Shader &loadShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath);
Model &loadModel(const std::string &name, const std::string &path);
SoundPool &loadSoundIntoPool(const std::string &name, const std::string &path);

void loadTextures(const std::string &path);
void loadFonts(const std::string &path);
void loadShaders(const std::string &path);
void loadModels(const std::string &path);
void loadSounds(const std::string &path);
void loadAssets(const std::string &path);

// Unload asset functions
void unloadTexture(const std::string &name);
void unloadFont(const std::string &name);
void unloadShader(const std::string &name);
void unloadModel(const std::string &name);
void unloadSound(const std::string &name);

void unloadTextures();
void unloadFonts();
void unloadShaders();
void unloadModels();
void unloadSounds();
void unloadAssets();

// Asset getter functions
bool textureExists(const std::string &name);
bool fontExists(const std::string &name);
bool shaderExists(const std::string &name);
bool modelExists(const std::string &name);
bool soundExists(const std::string &name);

Texture &getTexture(const std::string &name);
Font &getFont(const std::string &name);
Shader &getShader(const std::string &name);
Model &getModel(const std::string &name);
SoundPool &getSoundPool(const std::string &name);

std::unordered_map<std::string, Texture> &getTextureMap();
std::unordered_map<std::string, Font> &getFontMap();
std::unordered_map<std::string, Shader> &getShaderMap();
std::unordered_map<std::string, Model> &getModelMap();
std::unordered_map<std::string, SoundPool> &getSoundPoolMap();
