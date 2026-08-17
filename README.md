# SRU-Library
## About
SRU-Lib is a simple C++ utility library designed for use with Raylib to reduce rewriting different utility functions and managers for different Raylib projects. Inspired by my own utilities.
## ToC
- [Usage](#usage)
- [Documentation](#documentation)
- - [assets.hpp](#assetshpp)
- - [audio.hpp](#audiohpp)
- - [constants.hpp](#constantshpp)
- - [file.hpp](#filehpp)
- - [particles.hpp](#particleshpp)
- - [random.hpp](#randomhpp)
- - [render.hpp](#renderhpp)
- - [sru.hpp](#sruhpp)
- - [text.hpp](#texthpp)
- - [tween.hpp](#tweenhpp)
- - [util.hpp](#utilhpp)
- - [Macros](#macros)

## Usage
SRU-Lib is meant to be used together with CMake's FetchContent module. It uses Raylib as a dependency that the user must also include themselves. Here's a full working CMake example:
```cmake
cmake_minimum_required(VERSION 3.10)
project(srulib-test) # name of your project

set(CMAKE_CXX_STANDARD 17) # at least C++17 for SRU-Lib
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(raylib
   GIT_REPOSITORY https://github.com/raysan5/raylib.git
   GIT_TAG 5.5 # or another version
   GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(raylib)

FetchContent_Declare(srulib
   GIT_REPOSITORY https://github.com/Acerx-AMJ/SRU-Library.git
   GIT_TAG main
   GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(srulib)

# include_directories(${PROJECT_SOURCE_DIR}/include) # optional if writing a larger project
add_executable(${PROJECT_NAME} main.cpp) # add your source files
target_link_libraries(${PROJECT_NAME} PRIVATE raylib srulib)
```
Project structure for this CMake file would look something like this:
```
Project
|__ build/
|__ main.cpp
|__ CMakeLists.txt
```
And to build the project:
```bash
cmake -B build # build CMake cache (rerun after adding new source files)
cmake --build build # build project
```
And finally run:
```bash
./build/srulib-test # or whatever you named your project
```

## Documentation
Here you will find the documentation of all headers, functions and structures found in the library. Select by header:
- [assets.hpp](#assetshpp)
- [audio.hpp](#audiohpp)
- [constants.hpp](#constantshpp)
- [file.hpp](#filehpp)
- [particles.hpp](#particleshpp)
- [random.hpp](#randomhpp)
- [render.hpp](#renderhpp)
- [sru.hpp](#sruhpp)
- [text.hpp](#texthpp)
- [tween.hpp](#tweenhpp)
- [util.hpp](#utilhpp)

Or browse miscellaneous documentation:
- [Macros](#macros)

# assets.hpp
Responsible for asset loading, unloading and retrieval. Handles textures, fonts, shaders and models. Note that different asset types use different containers so a texture can exist with a font that's using an identical name whereas two textures with the same name cannot.

---
```cpp
Texture &loadTexture(const std::string &name, const std::string &path);
Font &loadFont(const std::string &name, const std::string &path);
Shader &loadShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath);
Model &loadModel(const std::string &name, const std::string &path);
SoundPool &loadSoundIntoPool(const std::string &name, const std::string &path);
```
Loads an asset from the given path and saves it in an internal asset map. Returns the asset if it already exists. Terminates if the asset failed to load. *loadShader* skips loading vertex or fragment shader if an empty string is supplied. *loadSoundIntoPool* instead loads the sound in the pool with the given name and returns the pool.

---
```cpp
void loadTextures(const std::string &path);
void loadFonts(const std::string &path);
void loadShaders(const std::string &path);
void loadModels(const std::string &path);
void loadSounds(const std::string &path);
```
Loads all files as assets recursively from the given path. Creates the folder if it does not exist. Terminates if the path provided is a file or if any of the assets failed to load. *loadShader* automatically groups vertex (.vs) and fragment (.fs) shaders together. *loadSounds* automatically groups sounds with the same name but different numbering (e.g. sound, sound1, sound2, ...).

---
```cpp
void loadAssets(const std::string &path);
```
Loads all files recursively as assets based on the file extension. Only loads file types supported by Raylib (see [here](https://github.com/raysan5/raylib/blob/master/FAQ.md#what-file-formats-are-supported-by-raylib)) and .vs and .fs files. Creates the folder if it does not exist. Terminates if the path provided is a file or if any of the assets failed to load. Automatically groups sounds with the same name but different numbering (e.g. sound, sound1, sound2, ...).

---
```cpp
void unloadTexture(const std::string &name);
void unloadFont(const std::string &name);
void unloadShader(const std::string &name);
void unloadModel(const std::string &name);
void unloadSound(const std::string &name);
```
Unloads an asset if it exists.

---
```cpp
void unloadTextures();
void unloadFonts();
void unloadShaders();
void unloadModels();
void unloadSounds();
```
Unloads all assets from the specified container.

---
```cpp
void unloadAssets();
```
Unloads all assets - textures, fonts, shaders, models and sounds.

---
```cpp
bool textureExists(const std::string &name);
bool fontExists(const std::string &name);
bool shaderExists(const std::string &name);
bool modelExists(const std::string &name);
bool soundExists(const std::string &name);
```
Returns whether or not asset by the given name exists.

---
```cpp
Texture &getTexture(const std::string &name);
Font &getFont(const std::string &name);
Shader &getShader(const std::string &name);
Model &getModel(const std::string &name);
SoundPool &getSoundPool(const std::string &name);
```
Returns asset by name if it exists. Terminates if it does not.

---
```cpp
std::unordered_map<std::string, Texture> &getTextureMap();
std::unordered_map<std::string, Font> &getFontMap();
std::unordered_map<std::string, Shader> &getShaderMap();
std::unordered_map<std::string, Model> &getModelMap();
std::unordered_map<std::string, SoundPool> &getSoundPoolMap();
```
Returns a reference to the specified map.

# audio.hpp
Responsible for playing audio.

---
```cpp
#define SRULIB_MIN_PITCH 0.925f
```
Defines the default minimum pitch used in *playSound*. Default is 0.925.

---
```cpp
#define SRULIB_MAX_PITCH 1.075f
```
Defines the default maximum pitch used in *playSound*. Default is 1.075.

---
```cpp
void playSound(const std::string &name, float volume = 1.0f);
```
Retrives the sound pool from the asset manager, selects a random sound from the pool and plays it. Assigns the sound a random pitch based on macros.

---
```cpp
void playSoundPure(const std::string &name, float pitch = 1.0f, float volume = 1.0f);
```
Retrieves the sound pool from the asset manager, selects a random sound from the pool and plays it.

---
```cpp
void playRawSound(Sound sound, float volume = 1.0f);
```
Plays the sound. Assigns the sound a random pitch based on macros.

---
```cpp
void playRawSoundPure(Sound sound, float pitch = 1.0f, float volume = 1.0f);
```
Plays the sound.

# constants.hpp
Responsible for providing common constants.

---
```cpp
constexpr inline Vector2 TOP_LEFT = {0.0f, 0.0f};
constexpr inline Vector2 TOP_CENTER = {0.5f, 0.0f};
constexpr inline Vector2 TOP_RIGHT = {1.0f, 0.0f};
constexpr inline Vector2 CENTER_LEFT = {0.0f, 0.5f};
constexpr inline Vector2 CENTER = {0.5f, 0.5f};
constexpr inline Vector2 CENTER_RIGHT = {1.0f, 0.5f};
constexpr inline Vector2 BOTTOM_LEFT = {0.0f, 1.0f};
constexpr inline Vector2 BOTTOM_CENTER = {0.5f, 1.0f};
constexpr inline Vector2 BOTTOM_RIGHT = {1.0f, 1.0f};
```
Origin presets for render, grid and origin functions.

---
```cpp
constexpr inline Rectangle FULL_SOURCE = {0, 0, 0, 0};
constexpr inline Rectangle WINDOW_AREA = {0, 0, 0, 0};
```
Defaults for render functions - use full texture source and use window boundaries as area respectively.

---
```cpp
constexpr inline int RATIO = 0;
constexpr inline int CUBIC_RATIO = 1;
constexpr inline int FILL_RATIO = 2;
```
Ratio types used in [render.hpp](#renderhpp) header. *RATIO* uses regular size. *CUBIC_RATIO* uses minimum size component - width or height - as both size components, meaning it preserves aspect ratio and prevents any overflow. *FILL_RATIO* uses maximum size component - width or height - as both size components, meaning it is guaranteed to overflow and fill.

---
```cpp
constexpr inline Vector2 GRID_CELL_INVALID = {-1.0f, -1.0f};
```
Invalid grid cell. Returns from *getGridCell* from [render.hpp](#renderhpp) header.

# file.hpp
Responsible for providing common file I/O utilities.

---
```cpp
std::vector<std::string> getLinesFromFile(const std::string &path);
std::vector<std::string> getRawLinesFromFile(const std::string &path);
std::vector<std::string> getLinesFromFileIgnoringComments(const std::string &path, const std::string &comment);
```
Get all lines from a file. *getRawLinesFromFile* returns raw lines, *getLinesFromFile* trims lines and ignores empty lines and *getLinesFromFileIgnoringComments* trims lines and ignores empty lines and comments. Comments are ignored from the start of the comment to the end of the line. Throws a warning if the file couldn't be opened. In that case the output will be empty.

---
```cpp
std::string getRandomLineFromFile(const std::string &path);
std::string getRandomRawLineFromFile(const std::string &path);
std::string getRandomLineFromFileIgnoringComments(const std::string &path, const std::string &comment);
```
Get a random line from a file. *getRandomRawLineFromFile* returns raw lines, *getRandomLineFromFile* trims lines and ignores empty lines and *getRandomLineFromFileIgnoringComments* trims lines and ignores empty lines and comments. Comments are ignored from the start of the comment to the end of the line. Throws a warning if the file couldn't be opened. In that case the output will be empty.

---
```cpp
std::unordered_map<std::string, std::string> getKeyValuePairFromFile(const std::string &path, const std::string &delimiter);
std::unordered_map<std::string, std::string> getRawKeyValuePairFromFile(const std::string &path, const std::string &delimiter);
std::unordered_map<std::string, std::string> getKeyValuePairFromFileIgnoringComments(const std::string &path, const std::string &delimiter, const std::string &comment);
```
Get a key value pair from a file. *getRawKeyValuePairFromFile* returns raw lines, *getKeyValuePairFromFile* trims lines and ignores empty lines and *getKeyValuePairFromFileIgnoringComments* trims lines and ignores empty lines and comments. Comments are ignored from the start of the comment to the end of the line. Lines are expected to be in the format: key delimiter value (e.g. `color=red`). If a line does not contain the delimiter the line will be used as a key with an empty value. For both functions except *getRawKeyValuePairFromFile* empty keys are ignored. All functions allow empty values (e.g. `color=` or `color`). Throws a warning if the file couldn't be opened. In that case the output will be empty.

---
```cpp
std::string getFileContents(const std::string &path);
```
Reads entire contents of the file into a string. Throws a warning if the file couldn't be opened. In that case the output will be empty.

---
```cpp
void getLinesFromFileInPlace(std::vector<std::string> &output, const std::string &path);
void getRawLinesFromFileInPlace(std::vector<std::string> &output, const std::string &path);
void getLinesFromFileIgnoringCommentsInPlace(std::vector<std::string> &output, const std::string &path, const std::string &comment);
void getRandomLineFromFileInPlace(std::string &output, const std::string &path);
void getRandomRawLineFromFileInPlace(std::string &output, const std::string &path);
void getRandomLineFromFileIgnoringCommentsInPlace(std::string &output, const std::string &path, const std::string &comment);
void getKeyValuePairFromFileInPlace(std::unordered_map<std::string, std::string> &output, const std::string &path, const std::string &delimiter);
void getRawKeyValuePairFromFileInPlace(std::unordered_map<std::string, std::string> &output, const std::string &path, const std::string &delimiter);
void getKeyValuePairFromFileIgnoringCommentsInPlace(std::unordered_map<std::string, std::string> &output, const std::string &path, const std::string &delimiter, const std::string &comment);
void getFileContentsInPlace(std::string &output, const std::string &path);
```
Same as the previous functions but store output directly in a variable.

---
```cpp
bool writeKeyValuePairToFile(const std::string &path, const std::unordered_map<std::string, std::string> &map, const std::string &delimiter);
```
Writes the map to a file in the format: key delimiter value (e.g. `color=red`). Throws a warning if the file couldn't be opened. Returns the success of the operation.

---
```cpp
bool writeFile(const std::string &path, const std::string &contents);
bool writeFileLines(const std::string &path, const std::vector<std::string> &lines);
```
Writes the contents to the file. Throws a warning if the file couldn't be opened. Returns the success of the operation.

---
```cpp
bool appendFile(const std::string &path, const std::string &contents);
bool appendFileLines(const std::string &path, const std::vector<std::string> &lines);
```
Appends the contents to the existing contents of the file. Throws a warning if the file couldn't be opened. Returns the success of the operation.

---
```cpp
struct Line {
   Line() = default;
   Line(const std::string &field, const std::string &value);

   std::string field;
   std::string value;
};
```
A line containing a field and value.

---
```cpp
struct Header {
   Header() = default;
   Header(const std::string &name, const std::vector<Line> &lines)
      : name(name), lines(lines) {}

   std::string name;
   std::vector<Line> lines;
};
```
A header containing its name and lines associated with it.

---
```cpp
std::vector<Header> getHeadersFromConfig(const std::string &path, const std::string &comment, const std::string &headerStart, const std::string &headerEnd, char delimiter);
```
Returns headers with their following config based on following syntax, here's an example assuming *comment='#'*, *headerStart='['*, *headerEnd=']'*, *delimiter='='*:
```python
# Comments and empty lines are ignored
[audio]
sfx_volume=1
music_volume=1

[display]
fullscreen=true
resolution=1920,1080
```
This file would return the following:
```
std::vector<Header>{
   Header{
      name = "audio",
      lines = {
         Line{
            field = "sfx_volume",
            value = "1",
         },
         Line{
            field = "music_volume",
            value = "1",
         },
      },
   },
   Header{
      name = "resolution",
      lines = {
         Line{
            field = "fullscreen",
            value = "true",
         },
         Line{
            field = "resolution",
            value = "1920,1080",
         },
      },
   },
}
```
And then the following values can be extracted using these functions:

---
```cpp
int getIntValue(const std::string &value);
float getFloatValue(const std::string &value);
bool getBoolValue(const std::string &value);
std::string getStringValue(const std::string &value);
Vector2 getV2Value(const std::string &value);
Vector3 getV3Value(const std::string &value);
Vector4 getV4Value(const std::string &value);
Color getColorValue(const std::string &value);
std::vector<int> getIntArrayValue(const std::string &value);
std::vector<float> getFloatArrayValue(const std::string &value);
std::vector<bool> getBoolArrayValue(const std::string &value);
std::vector<std::string> getArrayValue(const std::string &value);
std::vector<Line> getDictionaryValue(const std::string &value, char delimiter);
```
Converts string to specified value. *getIntValue*, *getFloatValue*, *getBoolValue*, *getV2Value*, *getV3Value*, *getV4Value* throws warning on invalid type and returns 0 as fallback. *getColorValue* throws warning on invalid type and returns a black color as fallback. *getIntArrayValue*, *getFloatArrayValue*, *getBoolArrayValue*, *getArrayValue* returns values separated by commas and throw warnings on their sub-types being invalid. *getDictionaryValue* returns key, value pairs separated by commas and throws warning when delimiter is not found.


# particles.hpp
Responsible for providing a particle manager.

---
```cpp
using ParticleID = size_t;
```
Particle ID of a specific particle config instance/particle cluster. 0 - nil.

---
```cpp
struct Particle {
   Particle() = default;
   Particle(Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 size, float scale, float rotation, float rotationVelocity, float friction, float lifetime);
   Particle(Texture *texture, Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 size, float scale, float rotation, float rotationVelocity, float friction, float lifetime);
   Particle(Texture *texture, Vector2 position, Vector2 velocity, Vector2 acceleration, Vector2 size, float scale, float rotation, float rotationVelocity, float friction, float lifetime, int splitX, int splitY, int splitWidth, int splitHeight);

   Texture2D *texture = nullptr;
   Vector2 position, velocity, acceleration;
   Vector2 size;
   float scale = 1.0f;
   float rotation = 0.0f;
   float rotationVelocity = 0.0f;
   float friction = 0.0f;
   float lifetime = 0.0f;
   float age = 0.0f;
   int splitX = 0;
   int splitY = 0;
   int splitWidth = 0;
   int splitHeight = 0;
};
```
A single particle.
- *texture* - texture of the particle.
- *position* - position of the particle. Does not need to be set in the config if particles are to be spawned in specific locations.
- *velocity* - the velocity of the particle - how much it moves per second.
- *acceleration* - the acceleration of the particle - how much faster velocity gets per second.
- *size* - the size of the particle.
- *scale* - how much should the particle scale per second.
- *rotation* - rotation of the particle.
- *rotationVelocity* - the velocity of the rotation - how much it rotates per second.
- *friction* - how quickly the velocity slows down.
- *lifetime* - lifetime of the particle in seconds.
- *age* - the age of the particle in seconds. Should not be edited manually.
- *splitX* - the split position X of the particle when calling *spawnSplitParticles()*. Should not be edited manually.
- *splitY* - the split position Y of the particle when calling *spawnSplitParticles()*. Should not be edited manually.
- *splitWidth* - in how many pieces should the texture be split on X axis when calling *spawnSplitParticles()*.
- *splitHeight* - in how many pieces should the texture be split on Y axis when calling *spawnSplitParticles()*.

---
```cpp
struct ParticleConfig {
   Texture2D *texture = nullptr;
   Particle minimum, maximum;
   size_t count = 0;
   bool cubic = false;
};
```
Particle config instance responsible for saving common particle data.

---
```cpp
ParticleID pushParticleConfig(ParticleConfig config);
```
Create a new config instance and return its ID. Automatically creates a particle cluster with the same ID.

---
```cpp
ParticleConfig &getParticleConfig(ParticleID ID);
```
Get particle config instance by its ID. Terminates if ID is invalid.

---
```cpp
std::vector<ParticleConfig> &getParticleConfigContainer();
```
Get particle config container.

---
```cpp
std::vector<std::vector<Particle>> &getParticleClusters();
```
Get particle cluster container.

---
```cpp
std::vector<Particle> &getParticleCluster(ParticleID ID);
```
Get a specific particle cluster by ID.

---
```cpp
void updateParticles(float DT);
void updateParticleCluster(ParticleID ID, float DT);
```
Update a specific particle cluster or all active clusters at once.

---
```cpp
void drawParticles();
void drawParticleCluster(ParticleID ID);
void drawResponsiveParticles(Rectangle area = WINDOW_AREA, int type = RATIO);
void drawResponsiveParticleCluster(ParticleID ID, Rectangle area = WINDOW_AREA, int type = RATIO);
```
Draw a specific particle cluster or all active clusters at once. *drawResponsiveParticles* and *drawResponsiveParticleCluster* draws using ratios instead of screen coordinates, meaning all config values need to be changed to ratios if these were to be used. Check [ratio constants](#constantshpp) for more info on ratio types. Cubic ratio is most likely preferable due to it preserving aspect ratio.

---
```cpp
void clearParticles();
void clearParticleCluster(ParticleID ID);
```
Clear all particles of a specific particle cluster or all particles at once.

---
```cpp
void spawnParticles(ParticleID ID);
void spawnParticles(Vector2 position, ParticleID ID);
void spawnParticles(size_t count, ParticleID ID);
void spawnParticles(size_t count, Vector2 position, ParticleID ID);
void spawnParticles(Texture *texture, ParticleID ID);
void spawnParticles(Texture *texture, Vector2 position, ParticleID ID);
void spawnParticles(Texture *texture, size_t count, ParticleID ID);
void spawnParticles(Texture *texture, size_t count, Vector2 position, ParticleID ID);
```
Spawn particles with the given parameters. If a parameter is not supplied then the one from the config is assumed.

---
```cpp
void spawnSplitParticles(ParticleID ID);
void spawnSplitParticles(Vector2 position, ParticleID ID);
void spawnSplitParticles(int splitWidth, int splitHeight, ParticleID ID);
void spawnSplitParticles(int splitWidth, int splitHeight, Vector2 position, ParticleID ID);
void spawnSplitParticles(Texture *texture, ParticleID ID);
void spawnSplitParticles(Texture *texture, Vector2 position, ParticleID ID);
void spawnSplitParticles(Texture *texture, int splitWidth, int splitHeight, ParticleID ID);
void spawnSplitParticles(Texture *texture, int splitWidth, int splitHeight, Vector2 position, ParticleID ID);
```
Cut the texture into `splitWidth * splitHeight` pieces and spawn the particles with the given parameters. If a parameter is not supplied then the one from the config is assumed.

# random.hpp
Responsible for providing easy to use random functions for integers, real numbers and vectors.

---
```cpp
#define SRULIB_USE_RAND
```
If defined, C *rand()* function will be used instead of *std::mt19937*. When defined, the random must be seeded manually.

---
```cpp
#ifndef SRULIB_USE_RAND
inline std::mt19937 &getRNG();
#endif
```
Returns the random device used for generating random numbers.

---
```cpp
inline void seedRandom(int seed);
```
Seeds the random device with the given seed.

---
```cpp
inline void seedRandomFromTime();
```
Seeds the random device using the current time.

---
```cpp
inline size_t randomIndex(size_t size);
```
Returns a random index in range [0; size).

---
```cpp
inline int randomInt(int min, int max);
```
Returns a random integer in range [min; max].

---
```cpp
inline float randomFloat(float min, float max);
```
Returns a random real number in range [min; max].

---
```cpp
inline bool chance(int percent);
```
Returns true roughly with the probability of the given percent. Percent are expected to be in range [0; 100].

---
```cpp
inline bool chancePrecise(float percent);
```
Returns true roughly with the probability of the given percent. Percent are expected to be in range [0; 1].

---
```cpp
inline Vector2 randomV2(Vector2 min, Vector2 max);
inline Vector3 randomV3(Vector3 min, Vector3 max);
inline Vector4 randomV4(Vector4 min, Vector4 max);

inline Vector2 randomV2(float min, float max);
inline Vector3 randomV3(float min, float max);
inline Vector4 randomV4(float min, float max);
```
Returns a vector with all values being a random real number in range [min; max]. All values are not guaranteed to be equal.

---
```cpp
inline Vector2 randomV2Value(float min, float max);
inline Vector3 randomV3Value(float min, float max);
inline Vector4 randomV4Value(float min, float max);
```
Returns a vector with all values being a random real number in range [min; max]. All values will be identical.

---
```cpp
template<class T>
inline auto &randomElement(T &range);
```
Returns a random element from a container. The container must implement *size()* and *operator[size_t]* functions, like *std::vector* does.

# render.hpp
Responsible for providing screen, size and position math utilities as well as drawing utilities.

---
```cpp
float getWindowWidth();
float getWindowHeight();
Vector2 getWindowSize();
Vector2 getCubicWindowSize();
```   
Returns the size of the window. *getCubicWindowSize* returns the size of the window as a square with its sides being the smallest size component - width or height.

---
```cpp
Vector2 getWindowCenter();
```
Returns the center of the window.

---
```cpp
Rectangle getWindowArea();
```
Returns the area (boundaries) of the window {0, 0, width, height}.

---
```cpp
Rectangle mapRatioToArea(Rectangle ratio, Vector2 origin = CENTER, Rectangle area = WINDOW_AREA, int type = RATIO);
Rectangle mapRatioToArea(Vector2 startRatio, Vector2 endRatio, Vector2 origin = CENTER, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapRatioToArea(Vector2 ratio, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapRatioToArea(float ratioX, float ratioY, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapSizeRatioToArea(Vector2 sizeRatio, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapSizeRatioToArea(float sizeRatioX, float sizeRatioY, Rectangle area = WINDOW_AREA, int type = RATIO);
```
Maps a ratio to an area. Default area is the window boundaries. *mapSizeRatioToArea* must be used for converting size ratios whereas *mapRatioToArea* must be used for position. Check [ratio constants](#constantshpp) for more info on ratio types.

---
```cpp
Rectangle mapAreaToRatio(Rectangle rect, Vector2 origin = CENTER, Rectangle area = WINDOW_AREA, int type = RATIO);
Rectangle mapAreaToRatio(Vector2 start, Vector2 end, Vector2 origin = CENTER, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapAreaToRatio(Vector2 position, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapAreaToRatio(float x, float y, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapAreaToSizeRatio(Vector2 size, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapAreaToSizeRatio(float width, float height, Rectangle area = WINDOW_AREA, int type = RATIO);
```
Maps area coordinates to a ratio. Default area is the window boundaries. *mapAreaToSizeRatio* must be used for converting size whereas *mapAreaToRatio* must be used for position. Check [ratio constants](#constantshpp) for more info on ratio types.

---
```cpp
float mapRatioToX(float ratioX, Rectangle area = WINDOW_AREA, int type = RATIO);
float mapRatioToY(float ratioY, Rectangle area = WINDOW_AREA, int type = RATIO);
float mapRatioToWidth(float ratioX, Rectangle area = WINDOW_AREA, int type = RATIO);
float mapRatioToHeight(float ratioY, Rectangle area = WINDOW_AREA, int type = RATIO);
```
Maps a X/Y/width/height ratio to an area. Default area is the window boundaries. Check [ratio constants](#constantshpp) for more info on ratio types.

---
```cpp
float mapXToRatio(float x, Rectangle area = WINDOW_AREA, int type = RATIO);
float mapYToRatio(float y, Rectangle area = WINDOW_AREA, int type = RATIO);
float mapWidthToRatio(float width, Rectangle area = WINDOW_AREA, int type = RATIO);
float mapHeightToRatio(float height, Rectangle area = WINDOW_AREA, int type = RATIO);
```
Maps area's X/Y/width/height to a ratio. Default area is the window boundaries. Check [ratio constants](#constantshpp) for more info on ratio types.

---
```cpp
Vector2 gridPosition(Rectangle grid, int columns, int rows, int column, int row, Vector2 origin = CENTER);
Vector2 gridRatio(Rectangle grid, int columns, int rows, int column, int row, Vector2 origin = CENTER);
```
Get position/ratio of a grid cell. *row* and *column* are 0-indexed. *origin* is the origin of the cell, where (0; 0) is top-left and (1; 1) is bottom-right and by default it is the center of the cell.

---
```cpp
Rectangle gridRectangle(Vector2 size, Rectangle grid, int columns, int rows, int column, int row, Vector2 origin = CENTER);
Rectangle gridRatioRectangle(Vector2 sizeRatio, Rectangle grid, int columns, int rows, int column, int row, Vector2 origin = CENTER);
```
Get position/ratio of a grid cell and combine it into a rectangle. *row* and *column* are 0-indexed. *origin* is the origin of the cell, where (0; 0) is top-left and (1; 1) is bottom-right and by default it is the center of the cell.

---
```cpp
Vector2 getGridCellSize(Rectangle grid, int columns, int rows);
Vector2 getGridCellRatio(Rectangle grid, int columns, int rows, int type = RATIO);
```
Get grid cell size in grid/ratio coordinates. *getGridCellRatio* will always return the global ratio, not local ratio for the grid area. Check [ratio constants](#constantshpp) for more info on ratio types.

---
```cpp
Vector2 getGridCell(Rectangle grid, int columns, int rows, Vector2 position);
```
Returns the grid cell that the position is currently in. Returns *GRID_CELL_INVALID* (from [constants.hpp](#constantshpp)) if position is outside of the grid.

---
```cpp
Vector2 snapToGrid(Rectangle grid, int columns, int rows, Vector2 position, Vector2 origin = CENTER);
```
Snaps the position to the grid. Returns position if position is outside of the grid. *origin* is the origin of the cell, where (0; 0) is top-left and (1; 1) is bottom-right and by default it is the center of the cell.

---
```cpp
Vector2 getTextSize(Font font, const char *text, float fontSize, float spacing);
```
Returns the size of the text based on parameters.

---
```cpp
Vector2 getTextOrigin(Font font, const char *text, float fontSize, float spacing, Vector2 origin = CENTER);
```
Returns the center position of the text based on parameters. *origin* must be in range [0; 1].

---
```cpp
constexpr inline Vector2 getOrigin(Vector2 size, Vector2 origin = CENTER);
```
Returns the origin of the size. *origin* must be in range [0; 1].

---
```cpp
constexpr inline Rectangle getSource(Texture texture);
```
Returns the full texture source - *{0, 0, width, height}*.

---
```cpp
void drawText(Font font, Vector2 position, const char *text, float fontSize, Vector2 origin = CENTER, Color color = WHITE, float rotation = 0.0f);
```
Draw text. *origin* must be in range [0; 1]. Fits spacing using *fitSpacing*.

---
```cpp
void drawTextResponsive(Font font, Vector2 ratio, const char *text, float fontSize, Vector2 origin = CENTER, Color color = WHITE, Rectangle area = WINDOW_AREA, float rotation = 0.0f);
```
Responsive variation of the previous function. Instead of passing screen position, pass ratio [0; 1]. Also scales font size and spacing automatically based on screen size. If no area is supplied then window boundaries are used instead.

---
```cpp
void drawText(const std::string &font, Vector2 position, const char *text, float fontSize, Vector2 origin = CENTER, Color color = WHITE, float rotation = 0.0f);
void drawTextResponsive(const std::string &font, Vector2 ratio, const char *text, float fontSize, Vector2 origin = CENTER, Color color = WHITE, Rectangle area = WINDOW_AREA, float rotation = 0.0f);
```
Instead of passing a font, pass an identifier of a font found in the asset manager ([assets.hpp](#assetshpp)).

---
```cpp
void drawRect(Vector2 position, Vector2 size, Vector2 origin = CENTER, Color color = WHITE, float rotation = 0.0f);
void drawRect(Rectangle rect, Vector2 origin = CENTER, Color color = WHITE, float rotation = 0.0f);
```
Draw rectangle. *origin* must be in range [0; 1].

---
```cpp
void drawRectResponsive(Vector2 ratio, Vector2 sizeRatio, Vector2 origin = CENTER, Color color = WHITE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
void drawRectResponsive(Rectangle ratios, Vector2 origin = CENTER, Color color = WHITE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
```
Responsive variations of the previous functions. Instead of passing screen position, pass ratio [0; 1]. If no area is supplied then window boundaries are used instead. Check [ratio constants](#constantshpp) for more info on ratio types.

---
```cpp
void drawTexture(Texture texture, Vector2 position, Vector2 size, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, float rotation = 0.0f);
void drawTexture(Texture texture, Rectangle rect, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, float rotation = 0.0f);
```
Draw texture. *origin* must be in range [0; 1]. If no source is supplied then the whole texture is rendered.

---
```cpp
void drawTextureResponsive(Texture texture, Vector2 ratio, Vector2 sizeRatio, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
void drawTextureResponsive(Texture texture, Rectangle ratios, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
```
Responsive variations of the previous functions. Instead of passing screen position, pass ratio [0; 1]. If no area is supplied then window boundaries are used instead. Check [ratio constants](#constantshpp) for more info on ratio types.

---
```cpp
void drawTexture(const std::string &texture, Vector2 position, Vector2 size, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, float rotation = 0.0f);
void drawTexture(const std::string &texture, Rectangle rect, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, float rotation = 0.0f);
void drawTextureResponsive(const std::string &texture, Vector2 ratio, Vector2 sizeRatio, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
void drawTextureResponsive(const std::string &texture, Rectangle ratios, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
```
Instead of passing a texture, pass an identifier to a texture in the asset manager ([assets.hpp](#assetshpp)).

---
```cpp
using AnimationID = size_t;
```
Animation ID of a specific animation config instance. 0 - nil.

---
```cpp
struct AnimationConfig {
public:
   AnimationConfig() = default;
   AnimationConfig(Texture texture, size_t frameWidth, size_t frameHeight, size_t gap, size_t frameY, size_t frameCount, float frameTime, bool loop = true);
   AnimationConfig(Texture texture, size_t frameSize, size_t gap, size_t frameY, size_t frameCount, float frameTime, bool loop = true);
   AnimationConfig(Texture texture, size_t frameSize, size_t frameCount, float frameTime, bool loop = true);

   Texture texture;
   size_t frameWidth = 0;
   size_t frameHeight = 0;
   size_t gapX = 0;
   size_t gapY = 0;
   size_t frameY = 0;
   size_t frameCount = 0;
   float frameTime = 0.0f;
   bool loop = true;
};
```
Animation config instance responsible for saving common animation data between different animated objects.

---
```cpp
struct Animation {
   Animation() = default;
   Animation(size_t ID, bool paused, bool flipX, bool flipY, bool randomStart = false);
   Animation(size_t ID, bool randomStart = false);

   size_t ID = 0;
   size_t frame = 0;
   float timer = 0.0f;
   bool paused = false;
   bool flipX = false;
   bool flipY = false;
   bool finished = false;
};
```
Animated object instance.

---
```cpp
AnimationID pushAnimation(AnimationConfig config);
```
Create a new config instance and return its ID.

---
```cpp
AnimationConfig &getAnimation(AnimationID ID);
```
Get animation config instance by its ID. Terminates if ID is invalid.

---
```cpp
std::vector<AnimationConfig> &getAnimationContainer();
```
Get animation config container.

---
```cpp
Rectangle getAnimationSource(Animation animation);
Rectangle getAnimationSource(Animation animation, AnimationConfig config);
```
Get calculated animation frame source based on animation's state. Terminates if animation's config ID is invalid.

---
```cpp
bool isAnimationPlaying(Animation &animation, AnimationID ID);
```
Returns true if animation is playing and isn't finished. Looping animations will never finish.

---
```cpp
void setAnimationState(Animation &animation, AnimationID ID);
```
Sets animation's state to the given config if the same config isn't already being used and resets animation to default.

---
```cpp
void forceAnimationState(Animation &animation, AnimationID ID);
```
Sets animation's state to the given config and resets animation to default.

---
```cpp
void animate(Animation &animation, float DT);
```
Update animation if it isn't paused and isn't finished playing.

---
```cpp
void drawTextureAnimated(Animation animation, Vector2 position, Vector2 size, Vector2 origin = CENTER, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimated(Animation animation, Rectangle rect, Vector2 origin = CENTER, Color color = WHITE, float rotation = 0.0f);
```
Draw animated texture. *origin* must be in range [0; 1].

---
```cpp
void drawTextureAnimatedResponsive(Animation animation, Vector2 ratio, Vector2 sizeRatio, Vector2 origin = CENTER, Color color = WHITE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
void drawTextureAnimatedResponsive(Animation animation, Rectangle ratios, Vector2 origin = CENTER, Color color = WHITE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
```
Responsive variations of the previous functions. Instead of passing screen position, pass ratio [0; 1]. If no area is supplied then window boundaries are used instead. Check [ratio constants](#constantshpp) for more info on ratio types.

# sru.hpp
Includes all headers provided by the library.

# text.hpp
Responsible for modifying text.

---
```cpp
std::string wrap(const std::string &string, Font font, float maxWidth, float fontSize);
```
Wrap the text to fit in the width.

---
```cpp
std::string truncate(const std::string &string, Font font, float maxWidth, float fontSize);
```
Truncate the text to fit in the width.

---
```cpp
std::string fitInside(const std::string &string, Font font, Vector2 maxSize, float fontSize);
```
Wrap and then truncate the text to fit in the bounds.

---
```cpp
std::vector<std::string> divideText(const std::string &string, Font font, float maxWidth, float fontSize);
```
Divides the text into lines to fit in the width. Works similarly to *wrap*.

---
```cpp
std::string toRomanNumeral(size_t number);
```
Convert the number to a roman numeral. Highest numeral is M - 1000.

---
```cpp
std::string toUpper(const std::string &string);
```
Convert the string to uppercase.

---
```cpp
std::string toLower(const std::string &string);
```
Convert the string to lowercase.

---
```cpp
std::string trim(const std::string &string);
std::string trimLeft(const std::string &string);
std::string trimRight(const std::string &string);
```
Trim leading/trailing spaces from the string.

---
```cpp
std::vector<std::string> split(const std::string &string, char delimiter);
std::vector<std::string> split(const std::string &string, const std::string &delimiter);
std::vector<std::string> splitOnWhiteSpace(const std::string &string);
```
Split string into pieces based on the delimeter. *splitOnWhiteSpace* handles all white space including tabs, new lines and some others. Will start or end with an empty string if the string respectively starts or ends with the delimeter except for in *splitOnWhiteSpace*.

---
```cpp
std::string join(const std::vector<std::string> &parts, const std::string &delimiter);
std::string join(const std::vector<std::string> &parts);
```
Joins all of the strings into one. Separates with delimiter if it is specified.

---
```cpp
std::vector<std::string> clean(const std::vector<std::string> &strings);
```
Removes all empty strings from the vector and trims all strings.

---
```cpp
void wrapInPlace(std::string &string, Font font, float maxWidth, float fontSize);
void truncateInPlace(std::string &string, Font font, float maxWidth, float fontSize);
void fitInsideInPlace(std::string &string, Font font, Vector2 maxSize, float fontSize);
void divideTextInPlace(std::vector<std::string> &output, const std::string &string, Font font, float maxWidth, float fontSize);
void toRomanNumeralInPlace(std::string &string, size_t number);
void toUpperInPlace(std::string &string);
void toLowerInPlace(std::string &string);
void trimInPlace(std::string &string);
void trimLeftInPlace(std::string &string);
void trimRightInPlace(std::string &string);
void splitInPlace(std::vector<std::string> &output, const std::string &string, char delimiter);
void splitInPlace(std::vector<std::string> &output, const std::string &string, const std::string &delimiter);
void splitOnWhiteSpaceInPlace(std::vector<std::string> &output, const std::string &string);
void joinInPlace(std::string &output, const std::vector<std::string> &parts, const std::string &delimiter);
void joinInPlace(std::string &output, const std::vector<std::string> &parts);
void cleanInPlace(std::vector<std::string> &strings);
```
Same as the previous functions but operate directly on the output.

---
```cpp
bool contains(const std::string &string, const std::string &substring);
bool startsWith(const std::string &string, const std::string &substring);
bool endsWith(const std::string &string, const std::string &substring);
```
Returns true if the string contains the given substring in a specific location.

---
```cpp
float fitSpacing(float fontSize);
```
Returns spacing that fits the font size.

---
```cpp
float fitFontSize(const char *string, Font font, float maxWidth);
float fitFontSize(const std::string &string, Font font, float maxWidth);
```
Returns a font size that will fit as closely to the width as possible. Spacing is handled automatically using *fitSpacing()*.

---
```cpp
inline float getFontSizeScaled(float fontSize);
```
Returns the font size scaled responsively based on the window size. Safe from UI overflows.

# tween.hpp
Responsible for tweening utility functions and providing formulas for doing so.

---
```cpp
constexpr inline float linear(float t);
constexpr inline float quadratic(float t);
constexpr inline float quadraticOut(float t);
constexpr inline float quadraticInOut(float t);
constexpr inline float cubic(float t);
constexpr inline float cubicOut(float t);
constexpr inline float cubicInOut(float t);
constexpr inline float sinusoidal(float t);
constexpr inline float sinusoidalOut(float t);
constexpr inline float sinusoidalInOut(float t);
constexpr inline float exponential(float t);
constexpr inline float exponentialOut(float t);
constexpr inline float exponentialInOut(float t);
constexpr inline float circular(float t);
constexpr inline float circularOut(float t);
constexpr inline float circularInOut(float t);
constexpr inline float elastic(float t);
constexpr inline float elasticOut(float t);
constexpr inline float elasticInOut(float t);
constexpr inline float back(float t);
constexpr inline float backOut(float t);
constexpr inline float backInOut(float t);
constexpr inline float bounce(float t);
constexpr inline float bounceOut(float t);
constexpr inline float bounceInOut(float t);
```
Different tween formulas. *t* must be in range [0; 1]. Some function are not guaranteed to return a result in range [0; 1], like for example the *bounce* function and might overshoot/undershoot slightly.

---
```cpp
using TweenID = size_t;
```
ID of a tween. 0 - nil.

---
```cpp
using Formula = float(*)(float);
```
Function that takes in *t* in range [0; 1] and returns a value roughly in range [0; 1].

---
```cpp
enum class TweenType {
   none, integer, floating, v2, v3, v4, r4, color
};
```
Tween type. Applied automatically.

---
```cpp
struct Tween {
   TweenType type = TweenType::none;
   Formula formula = linear;
   TweenID id = 0;
   TweenID sequenced = 0;

   float timer = 0.0f;
   float time = 0.0f;
   float progress = 0.0f;
   bool paused = false;
   bool finished = false;

   union {
      struct { int *ivalue, istart, iend; };
      struct { float *fvalue, fstart, fend; };
      struct { Vector2 *v2value, v2start, v2end; };
      struct { Vector3 *v3value, v3start, v3end; };
      struct { Vector4 *v4value, v4start, v4end; };
      struct { Rectangle *r4value, r4start, r4end; };
      struct { Color *cvalue, cstart, cend; };
   };
};
```
Tween that holds information necessary for interpolating from a value to a target. Must not be created manually. *type*, *id* and *sequenced* must not be edited manually. *formula* can use any function that takes a float and returns a float, not necessarily the predefined formulas.

---
```cpp
TweenID createTween(int *value, int target, float time, Formula formula = linear);
TweenID createTween(float *value, float target, float time, Formula formula = linear);
TweenID createTween(Vector2 *value, Vector2 target, float time, Formula formula = linear);
TweenID createTween(Vector3 *value, Vector3 target, float time, Formula formula = linear);
TweenID createTween(Vector4 *value, Vector4 target, float time, Formula formula = linear);
TweenID createTween(Rectangle *value, Rectangle target, float time, Formula formula = linear);
TweenID createTween(Color *value, Color target, float time, Formula formula = linear);
```
Create a new tween. By default uses a linear formula. Tweens are ran and destroyed automatically and only require *updateTweens* to be called every frame.

---
```cpp
TweenID createSequencedTween(TweenID parentID, int *value, int target, float time, Formula formula = linear);
TweenID createSequencedTween(TweenID parentID, float *value, float target, float time, Formula formula = linear);
TweenID createSequencedTween(TweenID parentID, Vector2 *value, Vector2 target, float time, Formula formula = linear);
TweenID createSequencedTween(TweenID parentID, Vector3 *value, Vector3 target, float time, Formula formula = linear);
TweenID createSequencedTween(TweenID parentID, Vector4 *value, Vector4 target, float time, Formula formula = linear);
TweenID createSequencedTween(TweenID parentID, Rectangle *value, Rectangle target, float time, Formula formula = linear);
TweenID createSequencedTween(TweenID parentID, Color *value, Color target, float time, Formula formula = linear);
```
Creates a sequenced tween based on parent's ID. Sequenced tweens are paused by default and ran when the parent finishes playing. Killing a parent will subsequently kill all sequenced tweens. A single tween cannot have more than one sequenced tween. By default uses a linear formula. Tweens are ran and destroyed automatically and only require *updateTweens* to be called every frame.

---
```cpp
void pauseTween(TweenID ID);
void resumeTween(TweenID ID);
```
Pause/resume a tween.

---
```cpp
void killTween(TweenID ID);
```
Kill a tween and all sequent tweens.

---
```cpp
Tween &getTween(TweenID ID);
```
Get a tween from ID. Be warned and don't hold references for long as they can be invalidated due to being stored in a dynamic vector.

---
```cpp
float getTweenProgress(TweenID ID);
bool isTweenFinished(TweenID ID);
bool isTweenPaused(TweenID ID);
bool isTweenPlaying(TweenID ID);
bool isTweenValid(TweenID ID);
```
Tween getters.

---
```cpp
void updateTweens(float DT);
```
Update all playing tweens.

# util.hpp
Responsible for vector and color utility functions.

---
```cpp
template<typename T, typename Y>
constexpr inline Vector2 V2(T x, Y y);

template<typename T, typename Y, typename U>
constexpr inline Vector3 V3(T x, Y y, U z);

template<typename T, typename Y, typename U, typename I>
constexpr inline Vector4 V4(T x, Y y, U z, I w);
```
Returns a vector with all values set.

---
```cpp
template<typename T>
constexpr inline Vector2 V2(T value);

template<typename T>
constexpr inline Vector3 V3(T value);

template<typename T>
constexpr inline Vector4 V4(T value);
```
Returns a vector where all values are set to the given value.

---
```cpp
constexpr inline Vector2 V2();
constexpr inline Vector3 V3();
constexpr inline Vector4 V4();
```
Returns a zero-initialized vector.

---
```cpp
constexpr inline Vector3 V3(Color color);
constexpr inline Vector4 V4(Color color);
```
Converts the color to a vector. Changes all values from [0; 255] to [0; 1].

---
```cpp
template<typename T, typename Y, typename U, typename I>
constexpr inline Rectangle R4(T x, Y y, U w, I h);
```
Returns a rectangle with all values set.

---
```cpp
constexpr inline Rectangle R4();
```
Returns a zero-initialized rectangle.

---
```cpp
constexpr inline Rectangle R4(Vector2 position, Vector2 size);
```
Constructs a rectangle from position and size.

---
```cpp
constexpr inline Rectangle R4bounds(Rectangle rect, Vector2 origin = CENTER);
constexpr inline Vector2 R4pos(Rectangle rect);
constexpr inline Vector2 R4size(Rectangle rect);
constexpr inline Vector2 R4origin(Rectangle rect, Vector2 origin = CENTER);
constexpr inline Vector2 R4anchor(Rectangle rect, Vector2 origin = CENTER);
```
Returns the real boundaries/position/size/origin/anchor of the rectangle respectively. *R4origin* - local origin inside rectangle. *R4anchor* - global position with rectangle's origin applied.

---
```cpp
constexpr inline bool operator == (Rectangle lhs, Rectangle rhs);
constexpr inline bool operator != (Rectangle lhs, Rectangle rhs);
```
Rectangle comparison functions.

---
```cpp
constexpr inline Color fadeColor(Color color, float a);
```
Constexpr version of Raylib's *FadeColor(Color, float)*. Fades the color with the coresponding alpha, which must be in range [0; 1].

---
```cpp
template<typename T, typename Y, typename U>
constexpr inline Color RGB(T r, Y g, U b);
```
Returns an RGB color.

---
```cpp
constexpr inline Color RGB(Vector3 color);
```
Converts vector to RGB color. Changes all values from [0; 1] to [0; 255].

---
```cpp
constexpr inline Color RGBF(float r, float g, float b);
```
Converts float values [0; 1] to RGB [0; 255].

---
```cpp
template<typename T, typename Y, typename U, typename I>
constexpr inline Color RGBA(T r, Y g, U b, I a);
constexpr inline Color RGBA(Color rgb, unsigned char a);
```
Returns an RGBA color.

---
```cpp
constexpr inline Color RGBA(Vector4 color);
```
Converts vector to RGBA color. Changes all values from [0; 1] to [0; 255].

---
```cpp
constexpr inline Color RGBAF(float r, float g, float b, float a);
```
Converts float values [0; 1] to RGB [0; 255].

---
```cpp
constexpr inline Color HEX(const char *hex);
```
Returns a HEX color. The string must be in one of the formats: *#rgb*, *#rgba*, *#rrggbb* or *#rrggbbaa*, where symbols are 0-9, a-f or A-F.

---
```cpp
constexpr inline Color HSL(float h, float s, float l);
```
Returns a HSL color. H must be in range [0; 360], S in range [0; 1] and L in range [0; 1].

---
```cpp
constexpr inline Color HSLA(float h, float s, float l, float a);
```
Returns a HSLA color. H must be in range [0; 360], S in range [0; 1], L in range [0; 1] and A in range [0; 1].

---
```cpp
constexpr inline Color HSV(float h, float s, float v);
```
Returns a HSV color. H must be in range [0; 360], S in range [0; 1] and V in range [0; 1].

---
```cpp
constexpr inline Color HSVA(float h, float s, float v, float a);
```
Returns a HSVA color. H must be in range [0; 360], S in range [0; 1], V in range [0; 1] and A in range [0; 1].

# Macros
This section will document all macros present and their usage in one place. There are two ways to use these macros - either define them before including a header or define them in CMake. Defining them in CMake is safer since it protects you from ODR violations. You can include any macro in your project with this CMake function:
```cmake
target_compile_definitions(${PROJECT_NAME} PRIVATE
   "SRULIB_MIN_PITCH=0.9f"
   "SRULIB_MAX_PITCH=1.1f" # macro with a value
   "SRULIB_USE_RAND" # macro without a value
   # define as many as needed
)
```

---
```cpp
#define SRULIB_MIN_PITCH 0.925f
```
Defines the default minimum pitch used in *playSound*. Default is 0.925. Used in [audio.hpp](#audiohpp).

---
```cpp
#define SRULIB_MAX_PITCH 1.075f
```
Defines the default maximum pitch used in *playSound*. Default is 1.075. Used in [audio.hpp](#audiohpp).

---
```cpp
#define SRULIB_USE_RAND
```
If defined, C *rand()* function will be used instead of *std::mt19937*. When defined, the random must be seeded manually. Used in [random.hpp](#randomhpp).
