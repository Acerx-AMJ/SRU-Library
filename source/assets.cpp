#include "SRU/assets.hpp"
#include <filesystem>

static std::unordered_map<std::string, Texture> textures;
static std::unordered_map<std::string, Font> fonts;
static std::unordered_map<std::string, Shader> shaders;
static std::unordered_map<std::string, Model> models;
static std::unordered_map<std::string, SoundPool> sounds;

// Load asset functions
Texture &loadTexture(const std::string &name, const std::string &path) {
   if (auto it = textures.find(name); it != textures.end()) {
      return it->second;
   }

   Texture texture = LoadTexture(path.c_str());
   if (texture.id == 0) {
      printf("srulib::loadTexture: Failed to load texture from file '%s'.\n", path.c_str());
      exit(EXIT_FAILURE);
   }
   textures.insert({name, texture});
   return textures[name];
}

Font &loadFont(const std::string &name, const std::string &path) {
   if (auto it = fonts.find(name); it != fonts.end()) {
      return it->second;
   }

   Font font = LoadFontEx(path.c_str(), 120, nullptr, 0);
   if (font.texture.id == 0) {
      printf("srulib::loadFont: Failed to load font from file '%s'.\n", path.c_str());
      exit(EXIT_FAILURE);      
   }

   SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
   fonts.insert({name, font});
   return fonts[name];
}

Shader &loadShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath) {
   if (auto it = shaders.find(name); it != shaders.end()) {
      return it->second;
   }

   Shader shader = LoadShader(vertexPath.c_str(), fragmentPath.c_str());
   if (shader.id == 0) {
      printf("srulib::loadShader: Failed to load shader from files: vertex: '%s', fragment: '%s'.\n", vertexPath.c_str(), fragmentPath.c_str());
      exit(EXIT_FAILURE);
   }
   shaders.insert({name, shader});
   return shaders[name];
}

Model &loadModel(const std::string &name, const std::string &path) {
   if (auto it = models.find(name); it != models.end()) {
      return it->second;
   }

   Model model = LoadModel(path.c_str());
   if (model.meshCount == 0) {
      printf("srulib::loadModel: Failed to load model from file '%s'.\n", path.c_str());
      exit(EXIT_FAILURE);
   }
   models.insert({name, model});
   return models[name];
}

SoundPool &loadSoundIntoPool(const std::string &name, const std::string &path) {
   Sound newSound = LoadSound(path.c_str());
   if (newSound.frameCount == 0) {
      printf("srulib::loadSoundIntoPool: Failed to load sound from file '%s'.\n", path.c_str());
      exit(EXIT_FAILURE);
   }

   SoundPool &pool = sounds[name];
   pool.push_back(newSound);
   return pool;
}

void loadTextures(const std::string &path) {
   if (std::filesystem::exists(path) && !std::filesystem::is_directory(path)) {
      printf("srulib::loadTextures: Path '%s' is not a directory.\n", path.c_str());
      exit(EXIT_FAILURE);
   }
   
   std::filesystem::create_directories(path);
   for (const auto &file: std::filesystem::recursive_directory_iterator(path)) {
      if (file.is_regular_file()) {
         loadTexture(file.path().stem().string(), file.path().string());
      }
   }
}

void loadFonts(const std::string &path) {
   if (std::filesystem::exists(path) && !std::filesystem::is_directory(path)) {
      printf("srulib::loadFonts: Path '%s' is not a directory.\n", path.c_str());
      exit(EXIT_FAILURE);
   }
   
   std::filesystem::create_directories(path);
   for (const auto &file: std::filesystem::recursive_directory_iterator(path)) {
      if (file.is_regular_file()) {
         loadFont(file.path().stem().string(), file.path().string());
      }
   }
}

void loadShaders(const std::string &path) {
   if (std::filesystem::exists(path) && !std::filesystem::is_directory(path)) {
      printf("srulib::loadShaders: Path '%s' is not a directory.\n", path.c_str());
      exit(EXIT_FAILURE);
   }

   std::filesystem::create_directories(path);
   for (const auto &file: std::filesystem::recursive_directory_iterator(path)) {
      if (!file.is_regular_file()) {
         continue;
      }
      
      std::string filename = file.path().stem().string();

      if (shaders.find(filename) != shaders.end()) {
         continue;
      }

      if (file.path().extension().string() == ".fs") {
         std::filesystem::path vertexPath = file.path().parent_path() / (filename + ".vs");
         loadShader(filename, (std::filesystem::exists(vertexPath) ? vertexPath.string() : std::string()), file.path().string());
      } else if (file.path().extension().string() == ".vs") {
         std::filesystem::path fragmentPath = file.path().parent_path() / (filename + ".fs");
         loadShader(filename, file.path().string(), (std::filesystem::exists(fragmentPath) ? fragmentPath.string() : std::string()));
      }
   }
}

void loadModels(const std::string &path) {
   if (std::filesystem::exists(path) && !std::filesystem::is_directory(path)) {
      printf("srulib::loadModels: Path '%s' is not a directory.\n", path.c_str());
      exit(EXIT_FAILURE);
   }
   
   std::filesystem::create_directories(path);
   for (const auto &file: std::filesystem::recursive_directory_iterator(path)) {
      if (file.is_regular_file()) {
         loadModel(file.path().stem().string(), file.path().string());
      }
   }
}

void loadSounds(const std::string &path) {
   if (std::filesystem::exists(path) && !std::filesystem::is_directory(path)) {
      printf("srulib::loadSounds: Path '%s' is not a directory.\n", path.c_str());
      exit(EXIT_FAILURE);
   }

   std::filesystem::create_directories(path);
   for (const auto &file: std::filesystem::recursive_directory_iterator(path)) {
      if (!file.is_regular_file()) {
         continue;
      }

      std::string stem = file.path().stem().string();
      if (isdigit(stem.back())) {
         stem = stem.substr(0, stem.find_last_not_of("1234567890") + 1);
      }
      loadSoundIntoPool(stem, file.path().string());
   }
}

void loadAssets(const std::string &path) {
   enum class FileType: char { texture, font, shader, model, sound };
   static std::unordered_map<std::string, FileType> fileTypeExtensions {{
      // Supported textures by Raylib
      {".png", FileType::texture}, {".bmp", FileType::texture}, {".tga", FileType::texture}, {".jpg", FileType::texture},
      {".jpeg", FileType::texture}, {".gif", FileType::texture}, {".qoi", FileType::texture}, {".psd", FileType::texture},
      {".dds", FileType::texture}, {".hdr", FileType::texture}, {".ktx", FileType::texture}, {".astc", FileType::texture},
      {".pkm", FileType::texture}, {".pvr", FileType::texture},

      // Supported fonts by Raylib
      {".fnt", FileType::font}, {".ttf", FileType::font}, {".otf", FileType::font},

      // Shaders
      {".fs", FileType::shader}, {".vs", FileType::shader},

      // Supported models by Raylib
      {".obj", FileType::model}, {".iqm", FileType::model}, {".gltf", FileType::model}, {".vox", FileType::model}, {".m3d", FileType::model},

      // Supported audio by Raylib
      {".wav", FileType::sound}, {".ogg", FileType::sound}, {".mp3", FileType::sound}, {".flac", FileType::sound}, {".xm", FileType::sound},
      {".mod", FileType::sound}, {".qoa", FileType::sound}
   }};

   if (std::filesystem::exists(path) && !std::filesystem::is_directory(path)) {
      printf("srulib::loadAssets: Path '%s' is not a directory.\n", path.c_str());
      exit(EXIT_FAILURE);
   }

   std::filesystem::create_directories(path);
   for (const auto &file: std::filesystem::recursive_directory_iterator(path)) {
      if (!file.is_regular_file()) {
         continue;
      }

      if (auto it = fileTypeExtensions.find(file.path().extension().string()); it != fileTypeExtensions.end()) {
         FileType type = it->second;

         switch (type) {
         case FileType::texture:
            loadTexture(file.path().stem().string(), file.path().string());
            break;
         case FileType::font:
            loadFont(file.path().stem().string(), file.path().string());
            break;
         case FileType::shader: {
            std::string filename = file.path().stem().string();

            if (shaders.find(filename) != shaders.end()) {
               continue;
            }

            if (file.path().extension().string() == ".fs") {
               std::filesystem::path vertexPath = file.path().parent_path() / (filename + ".vs");
               loadShader(filename, (std::filesystem::exists(vertexPath) ? vertexPath.string() : std::string()), file.path().string());
            } else if (file.path().extension().string() == ".vs") {
               std::filesystem::path fragmentPath = file.path().parent_path() / (filename + ".fs");
               loadShader(filename, file.path().string(), (std::filesystem::exists(fragmentPath) ? fragmentPath.string() : std::string()));
            }
            break;
         }
         case FileType::model:
            loadModel(file.path().stem().string(), file.path().string());
            break;
         case FileType::sound: {
            std::string stem = file.path().stem().string();
            if (isdigit(stem.back())) {
               stem = stem.substr(0, stem.find_last_not_of("1234567890") + 1);
            }
            loadSoundIntoPool(stem, file.path().string());
            break;
         }}
      }
   }
}

// Unload asset functions
void unloadTexture(const std::string &name) {
   if (auto it = textures.find(name); it != textures.end()) {
      UnloadTexture(it->second);
      textures.erase(it);
   }
}

void unloadFont(const std::string &name) {
   if (auto it = fonts.find(name); it != fonts.end()) {
      UnloadFont(it->second);
      fonts.erase(it);
   }
}

void unloadShader(const std::string &name) {
   if (auto it = shaders.find(name); it != shaders.end()) {
      UnloadShader(it->second);
      shaders.erase(it);
   }
}

void unloadModel(const std::string &name) {
   if (auto it = models.find(name); it != models.end()) {
      UnloadModel(it->second);
      models.erase(it);
   }
}

void unloadSound(const std::string &name) {
   if (auto it = sounds.find(name); it != sounds.end()) {
      for (Sound &sound: it->second) {
         UnloadSound(sound);
      }
      sounds.erase(it);
   }
}

void unloadTextures() {
   for (auto &[_, texture]: textures) {
      UnloadTexture(texture);
   }
   textures.clear();
}

void unloadFonts() {
   for (auto &[_, font]: fonts) {
      UnloadFont(font);
   }
   fonts.clear();
}

void unloadShaders() {
   for (auto &[_, shader]: shaders) {
      UnloadShader(shader);
   }
   shaders.clear();
}

void unloadModels() {
   for (auto &[_, model]: models) {
      UnloadModel(model);
   }
   models.clear();
}

void unloadSounds() {
   for (auto &[_, soundPool]: sounds) {
      for (Sound &sound: soundPool) {
         UnloadSound(sound);
      }
   }
   sounds.clear();
}

void unloadAssets() {
   unloadTextures();
   unloadFonts();
   unloadShaders();
   unloadModels();
   unloadSounds();
}

// Asset getter functions
bool textureExists(const std::string &name) {
   return textures.find(name) != textures.end();
}

bool fontExists(const std::string &name) {
   return fonts.find(name) != fonts.end();
}

bool shaderExists(const std::string &name) {
   return shaders.find(name) != shaders.end();
}

bool modelExists(const std::string &name) {
   return models.find(name) != models.end();
}

bool soundExists(const std::string &name) {
   return sounds.find(name) != sounds.end();
}

Texture &getTexture(const std::string &name) {
   if (auto it = textures.find(name); it != textures.end()) {
      return it->second;
   }
   printf("srulib::getTexture: Texture '%s' does not exist.\n", name.c_str());
   exit(EXIT_FAILURE);
}

Font &getFont(const std::string &name) {
   if (auto it = fonts.find(name); it != fonts.end()) {
      return it->second;
   }
   printf("srulib::getFont: Font '%s' does not exist.\n", name.c_str());
   exit(EXIT_FAILURE);
}

Shader &getShader(const std::string &name) {
   if (auto it = shaders.find(name); it != shaders.end()) {
      return it->second;
   }
   printf("srulib::getShader: Shader '%s' does not exist.\n", name.c_str());
   exit(EXIT_FAILURE);
}

Model &getModel(const std::string &name) {
   if (auto it = models.find(name); it != models.end()) {
      return it->second;
   }
   printf("srulib::getModel: Model '%s' does not exist.\n", name.c_str());
   exit(EXIT_FAILURE);
}

SoundPool &getSoundPool(const std::string &name) {
   if (auto it = sounds.find(name); it != sounds.end()) {
      return it->second;
   }
   printf("srulib::getSoundPool: Sound '%s' does not exist.\n", name.c_str());
   exit(EXIT_FAILURE);
}

std::unordered_map<std::string, Texture> &getTextureMap() {
   return textures;
}

std::unordered_map<std::string, Font> &getFontMap() {
   return fonts;
}

std::unordered_map<std::string, Shader> &getShaderMap() {
   return shaders;
}

std::unordered_map<std::string, Model> &getModelMap() {
   return models;
}

std::unordered_map<std::string, SoundPool> &getSoundPoolMap() {
   return sounds;
}
