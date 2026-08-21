# SRU-Library
## About
SRU-Lib is a simple C++ utility library designed for use with Raylib to reduce rewriting different utility functions and managers for different Raylib projects. Inspired by my own utilities.
## ToC
- [Usage](#usage)
- [Documentation](#documentation)
- - [assets.hpp](#assetshpp)
- - [audio.hpp](#audiohpp)
- - [constants.hpp](#constantshpp)
- - [error.hpp](#errorhpp)
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
- [error.hpp](#errorhpp)
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
Responsible for asset loading, unloading and retrieval. Handles textures, fonts, shaders and models. Note that different asset types use different containers so a texture can exist with a font that's using an identical name whereas two textures with the same name cannot. Is not thread safe.

### loadAsset
```cpp
Texture &loadTexture(const std::string &name, const std::string &path);
Font &loadFont(const std::string &name, const std::string &path);
Shader &loadShader(const std::string &name, const std::string &vertexPath, const std::string &fragmentPath);
Model &loadModel(const std::string &name, const std::string &path);
SoundPool &loadSoundIntoPool(const std::string &name, const std::string &path);
```
Load an asset from the given path and save it. Returns the asset if it already exists. **loadShader** skips loading vertext/fragment shader if passed path is empty. **loadSoundIntoPool** load a sound into a sound pool and returns the whole pool instead of just returning a sound. 

**loadTexture** and **loadFont** provide fallbacks on fail, whereas **loadShader**, **loadModel** and **loadSoundIntoPool** provide invalid objects on fail. It's possible to check if an asset failed to load using [assetExists](#assetexists) family of functions.

### loadAssets
```cpp
void loadTextures(const std::string &path);
void loadFonts(const std::string &path);
void loadShaders(const std::string &path);
void loadModels(const std::string &path);
void loadSounds(const std::string &path);
```
Load all files as assets recursively from the given path. Creates the folder if it doesn't already exist and won't load any assets if the path provided is not a directory. **loadSounds** automatically groups sounds with the same name but with different numbering together in a pool (e.g. sound, sound1, sound2, ...) and **loadShader** automatically groups vertex (.vs) and fragment (.fs) shaders with the same name together. See [loadAsset](#loadasset) family of functions for more info on loading.

```cpp
void loadAssets(const std::string &path);
```
Load all files recursively as assets based on the file extension. Only loads file types supported by [Raylib](https://github.com/raysan5/raylib/blob/master/FAQ.md#what-file-formats-are-supported-by-raylib) and .vs and .fs files. Creates the folder if it does not exist and won't load any assets if the path provided is not a directory. Automatically groups sounds with the same name but with different numbering together in a pool (e.g. sound, sound1, sound2, ...) and vertex (.vs) and fragment (.fs) shaders with the same name together. See [loadAsset](#loadasset) family of functions for more info on loading.

### unloadAsset
```cpp
void unloadTexture(const std::string &name);
void unloadFont(const std::string &name);
void unloadShader(const std::string &name);
void unloadModel(const std::string &name);
void unloadSound(const std::string &name);
```
Unloads an asset if it exists. Does nothing otherwise.

### unloadAssets
```cpp
void unloadTextures();
void unloadFonts();
void unloadShaders();
void unloadModels();
void unloadSounds();
```
Unloads all assets from the specified container.

```cpp
void unloadAssets();
```
Unloads all assets - textures, fonts, shaders, models and sounds.

### assetExists
```cpp
bool textureExists(const std::string &name);
bool fontExists(const std::string &name);
bool shaderExists(const std::string &name);
bool modelExists(const std::string &name);
bool soundExists(const std::string &name);
```
Returns whether or not asset by the given name exists. Assets that fail to load, including fallback assets, do not exist in the map and therefore this can be used for error checking.

### getAsset
```cpp
Texture &getTexture(const std::string &name);
Font &getFont(const std::string &name);
Shader &getShader(const std::string &name);
Model &getModel(const std::string &name);
SoundPool &getSoundPool(const std::string &name);
```
Returns asset by name if it exists. **getTexture** and **getFont** provide fallbacks on fail, whereas **getShader**, **getModel** and **getSoundPool** provide invalid objects. It's possible to check if an asset is valid using [assetExists](#assetexists) family of functions.

### getAssetMap
```cpp
std::unordered_map<std::string, Texture> &getTextureMap();
std::unordered_map<std::string, Font> &getFontMap();
std::unordered_map<std::string, Shader> &getShaderMap();
std::unordered_map<std::string, Model> &getModelMap();
std::unordered_map<std::string, SoundPool> &getSoundPoolMap();
```
Returns a reference to the given asset map.

# audio.hpp
Responsible for playing audio.

### Audio Macros
```cpp
#define SRULIB_MIN_PITCH 0.925f
```
Defines the default minimum pitch used in *playSound*. Default is 0.925.

```cpp
#define SRULIB_MAX_PITCH 1.075f
```
Defines the default maximum pitch used in *playSound*. Default is 1.075.

### playSound
```cpp
void playSound(const std::string &name, float volume = 1.0f);
void playSound(const std::string &name, float pitch, float volume);
```
Retrieves the sound pool from the asset manager if exists and plays a random sound. If no pitch is supplied then random pitch is used instead based on [Audio Macros](#audio-macros). Throws a warning on non-existent/invalid sound pool.

```cpp
void playRawSound(Sound sound, float volume = 1.0f);
void playRawSound(Sound sound, float pitch, float volume);
```
Plays a sound. If no pitch is supplied then random pitch is used instead based on [Audio Macros](#audio-macros).

# constants.hpp
Responsible for providing common constants.

### Origin Constants
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

### Render Constants
```cpp
constexpr inline Rectangle FULL_SOURCE = {0, 0, 0, 0};
constexpr inline Rectangle WINDOW_AREA = {0, 0, 0, 0};
```
Defaults for render functions - use full texture source and use window boundaries as area respectively.

```cpp
constexpr inline Vector2 GRID_CELL_INVALID = {-1.0f, -1.0f};
```
Invalid grid cell. Returns from [getGridCell](#getgridcell).

### Ratio Constants
```cpp
constexpr inline int RATIO = 0;
constexpr inline int CUBIC_RATIO = 1;
constexpr inline int FILL_RATIO = 2;
```
Ratio types used in [render.hpp](#renderhpp) header. **RATIO** uses regular size. **CUBIC_RATIO** uses minimum size component - width or height - as both size components, meaning it preserves aspect ratio and prevents any overflow. **FILL_RATIO** uses maximum size component - width or height - as both size components, meaning it is guaranteed to overflow and fill.

### File Constants
```cpp
constexpr inline int FILE_TRIMMED = 0;
constexpr inline int FILE_TRIMMED_COMMENTS = 1;
constexpr inline int FILE_RAW = 2;
```
File read types used in [file.hpp](#filehpp) header. **FILE_TRIMMED** reads lines, trims them and ignores empty ones. **FILE_TRIMMED_COMMENTS** reads lines, trims them and ignores empty ones and comments, **FILE_RAW** returns raw lines.

# error.hpp
Responsible for customizing error handling used in the library.

### Log Level
```cpp
enum class SRULibLogLevel { all, error, none };
```
Log level of the library: all - log warnings and errors, error - log only fatal errors, none - do not log anything.

```cpp
void setSRULibLogLevel(SRULibLogLevel level);
```
Set the log level of the library.

### Callback
```cpp
typedef void(*SRULibCallback)(const char *msg);
```
Callback used for displaying errors and warnings.

```cpp
void setSRULibErrorCallback(SRULibCallback callback);
void setSRULibWarningCallback(SRULibCallback callback);
```
Set error/warning callback for the library. By default warning callback simply prints the warning, whereas error callback prints the error and calls **exit(EXIT_FAILURE)**.

### Error/Warning
```cpp
void SRULibError(const char *msg);
void SRULibWarning(const char *msg);
```
Call the error/warning callback with the given message.

# file.hpp
Responsible for providing common file I/O utilities.

### getLinesFromFile
```cpp
std::vector<std::string> getLinesFromFile(const std::string &path, int type = FILE_TRIMMED, const std::string &comment = "");
```
Get all lines from a file. See [File Constants](#file-constants) for read types.

### getRandomLineFromFile
```cpp
std::string getRandomLineFromFile(const std::string &path, int type = FILE_TRIMMED, const std::string &comment = "");
```
Get a random line from a file. See [File Constants](#file-constants) for read types.

### getKeyValuePairFromFile
```cpp
std::unordered_map<std::string, std::string> getKeyValuePairFromFile(const std::string &path, const std::string &delimiter = "=", int type = FILE_TRIMMED, const std::string &comment = "");
```
Get a key value pair from a file. See [File Constants](#file-constants) for read types. Lines are expected to be in format **KEY=VALUE**. Unless read type is set to **FILE_RAW**, empty keys will be ignored. Values, however, can be empty and if no delimiter is found in a line then the line will be used as a key with an empty value.

### getFileContents
```cpp
std::string getFileContents(const std::string &path);
```
Reads entire file into a string.

### getFileInPlace
```cpp
void getLinesFromFileInPlace(std::vector<std::string> &output, const std::string &path, int type = FILE_TRIMMED, const std::string &comment = "");
void getRandomLineFromFileInPlace(std::string &output, const std::string &path, int type = FILE_TRIMMED, const std::string &comment = "");
void getKeyValuePairFromFileInPlace(std::unordered_map<std::string, std::string> &output, const std::string &path, const std::string &delimiter = "=", int type = FILE_TRIMMED, const std::string &comment = "");
void getFileContentsInPlace(std::string &output, const std::string &path);
```
Same as the previous functions but store output directly in a variable.

### writeFile
```cpp
bool writeKeyValuePairToFile(const std::string &path, const std::unordered_map<std::string, std::string> &map, const std::string &delimiter = "=");
bool writeFile(const std::string &path, const std::string &contents);
bool writeFile(const std::string &path, const std::vector<std::string> &lines);
```
Writes contents to a file. **writeKeyValuePairToFile** writes the map in the format **KEY=VALUE**. Returns the success of the operation.

### appendFile
```cpp
bool appendFile(const std::string &path, const std::string &contents);
bool appendFile(const std::string &path, const std::vector<std::string> &lines);
```
Appends contents to a file. Returns the success of the operation.

### createDirectory
```cpp
bool createDirectory(const std::string &path);
```
Creates directories recursively. Returns the success of the operation.

### deleteFile
```cpp
bool deleteFile(const std::string &path);
```
Deletes file/directory recursively. Returns the success of the operation. Will return false when attempting to delete a file that does not exist.

### copyFile/moveFile
```cpp
bool copyFile(const std::string &path, const std::string &destination);
bool moveFile(const std::string &path, const std::string &destination);
```
Copy/move a file/directory recursively. Returns the success of the operation

### pathExists
```cpp
bool pathExists(const std::string &path);
bool fileExists(const std::string &path);
bool directoryExists(const std::string &path);
```
Returns whether path/file/directory exists.

### Line/Header Structs
```cpp
struct Line {
   std::string field;
   std::string value;
};
```
A line containing a field and value.

```cpp
struct Header {
   std::string name;
   std::vector<Line> lines;
};
```
A header containing its name and lines associated with it.

### getHeadersFromConfig
```cpp
std::vector<Header> getHeadersFromConfig(const std::string &path, const std::string &comment = "#", const std::string &headerStart = "[", const std::string &headerEnd = "]", char delimiter = '=');
```
Returns headers with their following config based on following syntax, here's a syntax example assuming **comment='#'**, **headerStart='['**, **headerEnd=']'**, **delimiter='='**:
```python
# Comments and empty lines are ignored
[audio]
sfx_volume=1
music_volume=1

[display]
fullscreen=true
resolution=1920,1080
```
This file would return two headers - audio and display - with their corresponding config key, value pairs. The values from the key, value pairs can be extracted using [getValue](#getvalue) functions.

### getValue
```cpp
int getIntValue(const std::string &value, bool *ok = nullptr);
float getFloatValue(const std::string &value, bool *ok = nullptr);
bool getBoolValue(const std::string &value, bool *ok = nullptr);
std::string getStringValue(const std::string &value, bool *ok = nullptr);
Vector2 getV2Value(const std::string &value, char delimiter = ',', bool *ok = nullptr);
Vector3 getV3Value(const std::string &value, char delimiter = ',', bool *ok = nullptr);
Vector4 getV4Value(const std::string &value, char delimiter = ',', bool *ok = nullptr);
Color getColorValue(const std::string &value, char delimiter = ',', bool *ok = nullptr);
std::vector<int> getIntArrayValue(const std::string &value, char delimiter = ',', bool *ok = nullptr);
std::vector<float> getFloatArrayValue(const std::string &value, char delimiter = ',', bool *ok = nullptr);
std::vector<char> getBoolArrayValue(const std::string &value, char delimiter = ',', bool *ok = nullptr);
std::vector<std::string> getArrayValue(const std::string &value, char delimiter = ',', bool *ok = nullptr);
std::vector<Line> getDictionaryValue(const std::string &value, char delimiter = ',', char keyValueDelimiter = '=', bool *ok = nullptr);
```
Converts string to specified value. Returns 0/BLACK/empty on fail. Optionally sets **ok** based on success of the conversion. **getIntArrayValue**, **getFloatArrayValue**, **getBoolArrayValue** and **getArrayValue** return values separated by commas. **getDictionaryValue** returns key, value pairs separated by commas.

# particles.hpp
Responsible for providing a particle manager.

### Particle/Cluster Structs
```cpp
struct Particle {
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
- **texture** - texture of the particle.
- **position** - position of the particle. Does not need to be set in the config if particles are to be spawned in specific locations.
- **velocity** - the velocity of the particle - how much it moves per second.
- **acceleration** - the acceleration of the particle - how much faster velocity gets per second.
- **size** - the size of the particle.
- **scale** - how much should the particle scale per second.
- **rotation** - rotation of the particle.
- **rotationVelocity** - the velocity of the rotation - how much it rotates per second.
- **friction** - how quickly the velocity slows down.
- **lifetime** - lifetime of the particle in seconds.
- **age** - the age of the particle in seconds. Should not be edited manually.
- **splitX** - the split position X of the particle. Should not be edited manually.
- **splitY** - the split position Y of the particle. Should not be edited manually.
- **splitWidth** - in how many pieces should the texture be split on X axis. If both are non-zero then particle count is ignored and instead is calculated by **splitWidth** * **splitHeight**.
- **splitHeight** - in how many pieces should the texture be split on Y axis. If both are non-zero then particle count is ignored and instead is calculated by **splitWidth** * **splitHeight**.

```cpp
struct ParticleConfig {
   Texture2D *texture = nullptr;
   Particle minimum, maximum;
   size_t count = 0;
   bool cubic = false;
};
```
Particle config instance responsible for saving common particle data. **cubic** controls whether particles should have equal width and height.

```cpp
struct ParticleCluster {
   ParticleConfig config;
   std::vector<Particle> cluster;
};
```
Particle cluster containing particle config and all alive particles.

### pushParticleCluster
```cpp
void pushParticleCluster(const std::string &name, ParticleConfig config);
```
Create a new particle cluster instance and assign it to the given name.

### removeParticleCluster
```cpp
void removeParticleCluster(const std::string &name);
```
Removes particle cluster by name. Does nothing if it does not exist.

### particleClusterExists
```cpp
bool particleClusterExists(const std::string &name);
```
Returns whether or not particle cluster exists.

### getParticleCluster
```cpp
ParticleCluster &getParticleCluster(const std::string &name);
```
Returns particle cluster by name. Returns invalid object if it does not exist.

### getParticleClusterCount
```cpp
size_t getParticleClusterCount();
```
Returns particle cluster count.

### getParticleClusterContainer
```cpp
std::unordered_map<std::string, ParticleCluster> &getParticleClusterContainer();
```
Returns the particle cluster container.

### isParticleClusterEmpty
```cpp
bool isParticleClusterEmpty(const std::string &name);
```
Returns whether or not there are no alive particles in the particle cluster.

### getParticleCount
```cpp
size_t getParticleCount(const std::string &name);
size_t getTotalParticleCount();
```
Get particle count of a single cluster or the total particle count of all clusters.

### updateParticles
```cpp
void updateParticles(float DT);
void updateParticleCluster(const std::string &name, float DT);
void updateParticleCluster(ParticleCluster &cluster, float DT);
```
Update particles - either all active clusters or a single specific one - based on delta time.

### drawParticles
```cpp
void drawParticles();
void drawParticleCluster(const std::string &name);
void drawParticleCluster(const ParticleCluster &cluster);
void drawResponsiveParticles(Rectangle area = WINDOW_AREA, int type = RATIO);
void drawResponsiveParticleCluster(const std::string &name, Rectangle area = WINDOW_AREA, int type = RATIO);
void drawResponsiveParticleCluster(const ParticleCluster &cluster, Rectangle area = WINDOW_AREA, int type = RATIO);
```
Render particles - either all active clusters or a single specific one. Responsive versions require positional config values (**position**, **velocity**, **acceleration**, **size**) to be in ratio coordinates instead of screen coordinates. Check [Ratio Constants](#ratio-constants) for more info on ratio types. Cubic ratio is most likely preferable due to it preserving aspect ratio.

### clearParticles
```cpp
void clearParticles();
void clearParticleCluster(const std::string &name);
void clearParticleCluster(ParticleCluster &cluster);
```
Clear particles - either all active clusters or a single specific one.

### spawnParticles
```cpp
void spawnParticles(const std::string &name, size_t count = 0, Texture *texture = nullptr, Vector2 position = {}, bool useConfigPosition = true);
void spawnParticles(ParticleCluster &cluster, size_t count = 0, Texture *texture = nullptr, Vector2 position = {}, bool useConfigPosition = true);
```
Spawn particles. If different count, texture or position is supplied then that is used instead of the value from particle config.

# random.hpp
Responsible for providing easy to use random functions for integers, real numbers and vectors.

### Random Macro
```cpp
#define SRULIB_USE_RAND
```
If defined, C **rand()** function will be used instead of **std::mt19937**. When defined, the random must be seeded manually.

### getRNG
```cpp
#ifndef SRULIB_USE_RAND
inline std::mt19937 &getRNG();
#endif
```
Returns the random device used for generating random numbers.

### seedRandom
```cpp
inline void seedRandom(int seed);
inline void seedRandomFromTime();
```
Seeds the random device with the given seed or time.

### randomIndex
```cpp
inline size_t randomIndex(size_t size);
```
Returns a random index in range [0; size). If size is 0 then 0 is returned.

### randomInt
```cpp
inline int randomInt(int min, int max);
```
Returns a random integer in range [min; max].

### randomFloat
```cpp
inline float randomFloat(float min, float max);
```
Returns a random real number in range [min; max].

### chance
```cpp
inline bool chance(int percent);
inline bool chancePrecise(float percent);
```
Returns true roughly with the probability of the given percent. **chance** expects percent in range [0; 100], whereas **chancePrecise** expects percent in range [0; 1].

### randomVx
```cpp
inline Vector2 randomV2(Vector2 min, Vector2 max);
inline Vector3 randomV3(Vector3 min, Vector3 max);
inline Vector4 randomV4(Vector4 min, Vector4 max);

inline Vector2 randomV2(float min, float max);
inline Vector3 randomV3(float min, float max);
inline Vector4 randomV4(float min, float max);
```
Returns a vector with all values being a random real number in range [min; max]. Values are not guaranteed to be equal.

### randomVxValue
```cpp
inline Vector2 randomV2Value(float min, float max);
inline Vector3 randomV3Value(float min, float max);
inline Vector4 randomV4Value(float min, float max);
```
Returns a vector with all values being a random real number in range [min; max]. All values will be identical.

### randomElement
```cpp
template<class T>
inline auto &randomElement(T &range);
```
Returns a random element from a container. The container must implement **size()** and **operator[size_t]** functions, like **std::vector** does. Calling this on an empty container will index 0 and cause undefined behavior.

# render.hpp
Responsible for providing screen, size and position math utilities as well as drawing utilities.

### getWindowSize
```cpp
float getWindowWidth();
float getWindowHeight();
Vector2 getWindowSize();
Vector2 getCubicWindowSize();
```   
Returns the size of the window. **getCubicWindowSize** returns the size of the window as a square with its sides being the smallest size component - width or height.

### getWindowCenter
```cpp
Vector2 getWindowCenter();
```
Returns the center of the window.

### getWindowArea
```cpp
Rectangle getWindowArea();
```
Returns the area (boundaries) of the window {0, 0, width, height}.

### mapRatioToArea
```cpp
Rectangle mapRatioToArea(Rectangle ratio, Vector2 origin = CENTER, Rectangle area = WINDOW_AREA, int type = RATIO);
Rectangle mapRatioToArea(Vector2 startRatio, Vector2 endRatio, Vector2 origin = CENTER, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapRatioToArea(Vector2 ratio, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapRatioToArea(float ratioX, float ratioY, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapSizeRatioToArea(Vector2 sizeRatio, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapSizeRatioToArea(float sizeRatioX, float sizeRatioY, Rectangle area = WINDOW_AREA, int type = RATIO);
```
Maps a ratio to an area. Default area is the window boundaries. **mapSizeRatioToArea** must be used for converting size ratios whereas **mapRatioToArea** must be used for position. Check [Ratio Constants](#constantshpp) for more info on ratio types.

### mapAreaToRatio
```cpp
Rectangle mapAreaToRatio(Rectangle rect, Vector2 origin = CENTER, Rectangle area = WINDOW_AREA, int type = RATIO);
Rectangle mapAreaToRatio(Vector2 start, Vector2 end, Vector2 origin = CENTER, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapAreaToRatio(Vector2 position, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapAreaToRatio(float x, float y, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapAreaToSizeRatio(Vector2 size, Rectangle area = WINDOW_AREA, int type = RATIO);
Vector2 mapAreaToSizeRatio(float width, float height, Rectangle area = WINDOW_AREA, int type = RATIO);
```
Maps area coordinates to a ratio. Default area is the window boundaries. **mapAreaToSizeRatio** must be used for converting size whereas **mapAreaToRatio** must be used for position. Check [Ratio Constants](#constantshpp) for more info on ratio types.

### mapRatioToX
```cpp
float mapRatioToX(float ratioX, Rectangle area = WINDOW_AREA, int type = RATIO);
float mapRatioToY(float ratioY, Rectangle area = WINDOW_AREA, int type = RATIO);
float mapRatioToWidth(float ratioX, Rectangle area = WINDOW_AREA, int type = RATIO);
float mapRatioToHeight(float ratioY, Rectangle area = WINDOW_AREA, int type = RATIO);
```
Maps a X/Y/width/height ratio to an area. Default area is the window boundaries. Check [Ratio Constants](#constantshpp) for more info on ratio types.

### mapXToRatio
```cpp
float mapXToRatio(float x, Rectangle area = WINDOW_AREA, int type = RATIO);
float mapYToRatio(float y, Rectangle area = WINDOW_AREA, int type = RATIO);
float mapWidthToRatio(float width, Rectangle area = WINDOW_AREA, int type = RATIO);
float mapHeightToRatio(float height, Rectangle area = WINDOW_AREA, int type = RATIO);
```
Maps area's X/Y/width/height to a ratio. Default area is the window boundaries. Check [Ratio Constants](#constantshpp) for more info on ratio types.

### convertRatio
```cpp
Vector2 convertRatio(Vector2 ratio, int type = RATIO, int target = RATIO, Rectangle area = WINDOW_AREA);
float convertRatioX(float ratio, int type = RATIO, int target = RATIO, Rectangle area = WINDOW_AREA);
float convertRatioY(float ratio, int type = RATIO, int target = RATIO, Rectangle area = WINDOW_AREA);
```
Converts a ratio of type **type** to ratio of type **target** in the given area. Check [Ratio Constants](#constantshpp) for more info on ratio types. Whether or not using **convertRatioX** or **convertRatioY** for a single axis is important.

### gridPosition
```cpp
Vector2 gridPosition(Rectangle grid, int columns, int rows, int column, int row, Vector2 origin = CENTER);
Vector2 gridRatio(Rectangle grid, int columns, int rows, int column, int row, Vector2 origin = CENTER);
```
Get position/ratio of a grid cell. **row** and **column** are 0-indexed. **origin** is the origin of the cell, where (0; 0) is top-left and (1; 1) is bottom-right and by default it is the center of the cell.

### gridRectangle
```cpp
Rectangle gridRectangle(Vector2 size, Rectangle grid, int columns, int rows, int column, int row, Vector2 origin = CENTER);
Rectangle gridRatioRectangle(Vector2 sizeRatio, Rectangle grid, int columns, int rows, int column, int row, Vector2 origin = CENTER);
```
Get position/ratio of a grid cell and combine it into a rectangle. **row** and **column** are 0-indexed. **origin** is the origin of the cell, where (0; 0) is top-left and (1; 1) is bottom-right and by default it is the center of the cell.

### getGridCellSize
```cpp
Vector2 getGridCellSize(Rectangle grid, int columns, int rows);
Vector2 getGridCellRatio(Rectangle grid, int columns, int rows, int type = RATIO);
```
Get grid cell size in grid/ratio coordinates. **getGridCellRatio** will always return the global ratio, not local ratio for the grid area. Check [Ratio Constants](#constantshpp) for more info on ratio types.

### getGridCell
```cpp
Vector2 getGridCell(Rectangle grid, int columns, int rows, Vector2 position);
```
Returns the grid cell that the position is currently in. Returns **GRID_CELL_INVALID** (from [constants.hpp](#constantshpp)) if position is outside of the grid.

### snapToGrid
```cpp
Vector2 snapToGrid(Rectangle grid, int columns, int rows, Vector2 position, Vector2 origin = CENTER);
```
Snaps the position to the grid. Returns position if position is outside of the grid. **origin** is the origin of the cell, where (0; 0) is top-left and (1; 1) is bottom-right and by default it is the center of the cell.

### drawText
```cpp
void drawText(Font font, Vector2 position, const char *text, float fontSize, Vector2 origin = CENTER, Color color = WHITE, float rotation = 0.0f);
```
Draw text. **origin** must be in range [0; 1]. Fits spacing using **fitSpacing**.

### drawTextResponsive
```cpp
void drawTextResponsive(Font font, Vector2 ratio, const char *text, float fontSize, Vector2 origin = CENTER, Color color = WHITE, Rectangle area = WINDOW_AREA, float rotation = 0.0f);
```
Responsive variation of the previous function. Instead of passing screen position, pass ratio [0; 1]. Also scales font size and spacing automatically based on screen size. If no area is supplied then window boundaries are used instead.

### drawText std::string Overloads
```cpp
void drawText(const std::string &font, Vector2 position, const char *text, float fontSize, Vector2 origin = CENTER, Color color = WHITE, float rotation = 0.0f);
void drawTextResponsive(const std::string &font, Vector2 ratio, const char *text, float fontSize, Vector2 origin = CENTER, Color color = WHITE, Rectangle area = WINDOW_AREA, float rotation = 0.0f);
```
Instead of passing a font, pass an identifier of a font found in the asset manager ([assets.hpp](#assetshpp)).

### drawRect
```cpp
void drawRect(Vector2 position, Vector2 size, Vector2 origin = CENTER, Color color = WHITE, float rotation = 0.0f);
void drawRect(Rectangle rect, Vector2 origin = CENTER, Color color = WHITE, float rotation = 0.0f);
```
Draw rectangle. **origin** must be in range [0; 1].

### drawRectResponsive
```cpp
void drawRectResponsive(Vector2 ratio, Vector2 sizeRatio, Vector2 origin = CENTER, Color color = WHITE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
void drawRectResponsive(Rectangle ratios, Vector2 origin = CENTER, Color color = WHITE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
```
Responsive variations of the previous functions. Instead of passing screen position, pass ratio [0; 1]. If no area is supplied then window boundaries are used instead. Check [Ratio Constants](#constantshpp) for more info on ratio types.

### drawTexture
```cpp
void drawTexture(Texture texture, Vector2 position, Vector2 size, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, float rotation = 0.0f);
void drawTexture(Texture texture, Rectangle rect, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, float rotation = 0.0f);
```
Draw texture. **origin** must be in range [0; 1]. If no source is supplied then the whole texture is rendered.

### drawTextureResponsive
```cpp
void drawTextureResponsive(Texture texture, Vector2 ratio, Vector2 sizeRatio, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
void drawTextureResponsive(Texture texture, Rectangle ratios, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
```
Responsive variations of the previous functions. Instead of passing screen position, pass ratio [0; 1]. If no area is supplied then window boundaries are used instead. Check [Ratio Constants](#constantshpp) for more info on ratio types.

### drawTexture std::string Overloads
```cpp
void drawTexture(const std::string &texture, Vector2 position, Vector2 size, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, float rotation = 0.0f);
void drawTexture(const std::string &texture, Rectangle rect, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, float rotation = 0.0f);
void drawTextureResponsive(const std::string &texture, Vector2 ratio, Vector2 sizeRatio, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
void drawTextureResponsive(const std::string &texture, Rectangle ratios, Vector2 origin = CENTER, Color color = WHITE, Rectangle source = FULL_SOURCE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
```
Instead of passing a texture, pass an identifier to a texture in the asset manager ([assets.hpp](#assetshpp)).

### AnimationID
```cpp
typedef size_t AnimationID;
```
Animation ID of a specific animation config instance. 0 - nil.

### AnimationConfig
```cpp
struct AnimationConfig {
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

### Animation
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

### pushAnimation
```cpp
AnimationID pushAnimation(AnimationConfig config);
```
Create a new config instance and return its ID.

### getAnimation
```cpp
AnimationConfig &getAnimation(AnimationID ID);
```
Get animation config instance by its ID. Throws warning if ID is invalid.

### getAnimationContainer
```cpp
std::vector<AnimationConfig> &getAnimationContainer();
```
Get animation config container.

### getAnimationSource
```cpp
Rectangle getAnimationSource(Animation animation);
Rectangle getAnimationSource(Animation animation, AnimationConfig config);
```
Get calculated animation frame source based on animation's state. Throws warning if animation's config ID is invalid.

### isAnimationPlaying
```cpp
bool isAnimationPlaying(Animation &animation, AnimationID ID);
```
Returns true if animation is playing and isn't finished. Looping animations will never finish.

### setAnimationState
```cpp
void setAnimationState(Animation &animation, AnimationID ID);
```
Sets animation's state to the given config if the same config isn't already being used and resets animation to default.

### forceAnimationState
```cpp
void forceAnimationState(Animation &animation, AnimationID ID);
```
Sets animation's state to the given config and resets animation to default.

### animate
```cpp
void animate(Animation &animation, float DT);
```
Update animation if it isn't paused and isn't finished playing.

### drawTextureAnimated
```cpp
void drawTextureAnimated(Animation animation, Vector2 position, Vector2 size, Vector2 origin = CENTER, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimated(Animation animation, Rectangle rect, Vector2 origin = CENTER, Color color = WHITE, float rotation = 0.0f);
```
Draw animated texture. **origin** must be in range [0; 1].

### drawTextureAnimatedResponsive
```cpp
void drawTextureAnimatedResponsive(Animation animation, Vector2 ratio, Vector2 sizeRatio, Vector2 origin = CENTER, Color color = WHITE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
void drawTextureAnimatedResponsive(Animation animation, Rectangle ratios, Vector2 origin = CENTER, Color color = WHITE, Rectangle area = WINDOW_AREA, int type = RATIO, float rotation = 0.0f);
```
Responsive variations of the previous functions. Instead of passing screen position, pass ratio [0; 1]. If no area is supplied then window boundaries are used instead. Check [Ratio Constants](#constantshpp) for more info on ratio types.

# sru.hpp
Includes all headers provided by the library.

# text.hpp
Responsible for modifying text.

### wrap
```cpp
std::string wrap(const std::string &string, Font font, float maxWidth, float fontSize);
```
Wrap the text to fit in the width. Fits spacing using [fitSpacing](#fitspacing).

### truncate
```cpp
std::string truncate(const std::string &string, Font font, float maxWidth, float fontSize);
```
Truncate the text to fit in the width. Fits spacing using [fitSpacing](#fitspacing).

### fitInside
```cpp
std::string fitInside(const std::string &string, Font font, Vector2 maxSize, float fontSize);
```
Wrap and then truncate the text to fit in the bounds. Fits spacing using [fitSpacing](#fitspacing).

### divideText
```cpp
std::vector<std::string> divideText(const std::string &string, Font font, float maxWidth, float fontSize);
```
Divides the text into lines to fit in the width. Works similarly to **wrap**. Fits spacing using [fitSpacing](#fitspacing).

### toRomanNumeral
```cpp
std::string toRomanNumeral(size_t number);
```
Convert the number to a roman numeral. Highest numeral is M - 1000.

### toCase
```cpp
std::string toUpper(const std::string &string);
std::string toLower(const std::string &string);
std::string toTitle(const std::string &string);
std::string capitalize(const std::string &string);
```
Convert the string to uppercase/lowercase/title/capitalized. **toTitle** capitalizes all words and removes underscores. **capitalize** only capitalizes the first character if it's a letter.

### trim
```cpp
std::string trim(const std::string &string);
std::string trimLeft(const std::string &string);
std::string trimRight(const std::string &string);
```
Trim leading/trailing spaces from the string.

### split
```cpp
std::vector<std::string> split(const std::string &string, char delimiter);
std::vector<std::string> split(const std::string &string, const std::string &delimiter);
std::vector<std::string> splitOnWhiteSpace(const std::string &string);
```
Split string into pieces based on the delimeter. **splitOnWhiteSpace** handles all white space including tabs, new lines and some others. Will start or end with an empty string if the string respectively starts or ends with the delimeter except for in **splitOnWhiteSpace**.

### join
```cpp
std::string join(const std::vector<std::string> &parts, const std::string &delimiter);
std::string join(const std::vector<std::string> &parts);
```
Joins all of the strings into one. Separates with delimiter if it is specified.

### clean
```cpp
std::vector<std::string> clean(const std::vector<std::string> &strings);
```
Removes all empty strings from the vector and trims all strings.

### textInPlace
```cpp
void wrapInPlace(std::string &string, Font font, float maxWidth, float fontSize);
void truncateInPlace(std::string &string, Font font, float maxWidth, float fontSize);
void fitInsideInPlace(std::string &string, Font font, Vector2 maxSize, float fontSize);
void divideTextInPlace(std::vector<std::string> &output, const std::string &string, Font font, float maxWidth, float fontSize);
void toRomanNumeralInPlace(std::string &string, size_t number);
void toUpperInPlace(std::string &string);
void toLowerInPlace(std::string &string);
void toTitleInPlace(std::string &string);
void capitalizeInPlace(std::string &string);
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

### contains
```cpp
bool contains(const std::string &string, const std::string &substring);
bool startsWith(const std::string &string, const std::string &substring);
bool endsWith(const std::string &string, const std::string &substring);
```
Returns true if the string contains the given substring in a specific location.

# tween.hpp
Responsible for tweening utility functions and providing formulas for doing so.

### Tween Formulas
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
Different tween formulas. *t* must be in range [0; 1]. Some functions are not guaranteed to return a result in range [0; 1], like for example the *bounce* function, and might overshoot/undershoot slightly.

### Formula
```cpp
typedef float(*Formula)(float);
```
Function that takes in *t* in range [0; 1] and returns a value roughly in range [0; 1].

### TweenValue
```cpp
enum class TweenValue: char {
   none, integer, floating, v2, v3, v4, r4, color
};
```
Tween value. Applied automatically by [createTween](#createtween) functions.

### TweenType
```cpp
enum class TweenType: char {
   automatic, manual, loop, pingpong
};
```
Tween type. Default is **automatic** - remove the tween when it finishes. **manual** - do not remove the tween automatically and make the user remove it manually using [TweenID::kill](#tweenidkill) function. **loop** - loop the tween until the user stops it. **pingpong** - loop the tween and reverse it on finish (making it bounce back and forth) until the user stops it.

### TweenID
```cpp
struct TweenID {
   size_t ID = 0;
   int generation = 0;

   constexpr TweenID();
   constexpr TweenID(size_t ID);
   constexpr TweenID(size_t ID, int generation);

   TweenID chain(int *value, int target, float time, Formula formula = linear);
   TweenID chain(float *value, float target, float time, Formula formula = linear);
   TweenID chain(Vector2 *value, Vector2 target, float time, Formula formula = linear);
   TweenID chain(Vector3 *value, Vector3 target, float time, Formula formula = linear);
   TweenID chain(Vector4 *value, Vector4 target, float time, Formula formula = linear);
   TweenID chain(Rectangle *value, Rectangle target, float time, Formula formula = linear);
   TweenID chain(Color *value, Color target, float time, Formula formula = linear);

   TweenID parallel(int *value, int target, float time, Formula formula = linear);
   TweenID parallel(float *value, float target, float time, Formula formula = linear);
   TweenID parallel(Vector2 *value, Vector2 target, float time, Formula formula = linear);
   TweenID parallel(Vector3 *value, Vector3 target, float time, Formula formula = linear);
   TweenID parallel(Vector4 *value, Vector4 target, float time, Formula formula = linear);
   TweenID parallel(Rectangle *value, Rectangle target, float time, Formula formula = linear);
   TweenID parallel(Color *value, Color target, float time, Formula formula = linear);

   void stop();
   void resume();
   void toggleStopped();
   void restart();
   void reverse();
   void kill();

   bool isStopped();
   bool isKilled();
   bool isPlaying();
   bool isFinished();
   bool isReversed();
   bool isValid();
   bool isRoot();

   struct Tween &tween();
   struct Tween &root();
};
```
**TweenID** holds an internal ID to a tween and is used for chaining and adding parallel tweens to the root tween, see [createTween](#createtween). It also has utility functions for managing the root tween and retrieving its state.

### TweenID::chain
```cpp
TweenID TweenID::chain(int *value, int target, float time, Formula formula = linear);
TweenID TweenID::chain(float *value, float target, float time, Formula formula = linear);
TweenID TweenID::chain(Vector2 *value, Vector2 target, float time, Formula formula = linear);
TweenID TweenID::chain(Vector3 *value, Vector3 target, float time, Formula formula = linear);
TweenID TweenID::chain(Vector4 *value, Vector4 target, float time, Formula formula = linear);
TweenID TweenID::chain(Rectangle *value, Rectangle target, float time, Formula formula = linear);
TweenID TweenID::chain(Color *value, Color target, float time, Formula formula = linear);
```
Create a new tween and run it after this tween has finished playing.

### TweenID::parallel
```cpp
TweenID TweenID::parallel(int *value, int target, float time, Formula formula = linear);
TweenID TweenID::parallel(float *value, float target, float time, Formula formula = linear);
TweenID TweenID::parallel(Vector2 *value, Vector2 target, float time, Formula formula = linear);
TweenID TweenID::parallel(Vector3 *value, Vector3 target, float time, Formula formula = linear);
TweenID TweenID::parallel(Vector4 *value, Vector4 target, float time, Formula formula = linear);
TweenID TweenID::parallel(Rectangle *value, Rectangle target, float time, Formula formula = linear);
TweenID TweenID::parallel(Color *value, Color target, float time, Formula formula = linear);
```
Create a new tween and run it in parallel with the current one.

### TweenID::stop/Tween::resume
```cpp
void TweenID::stop();
void TweenID::resume();
void TweenID::toggleStopped();
```
Stop/resume the root tween. Tween will not account for any value changes when resumed.

### TweenID::restart
```cpp
void TweenID::restart();
```
Restart the root tween. Tween will not reset the values to the initial and that is user's responsibility if they wish to.

### TweenID::reverse
```cpp
void TweenID::reverse();
```
Reverse the root tween. This means swapping end and start for all sub-tweens and inversing the progress.

### TweenID::kill
```cpp
void TweenID::kill();
```
Kill the root tween and all of its sub-tweens. Will invalidate the **TweenID** for the root and all sub-tweens and throw a warning if any function is called from them.

### TweenID Getters
```cpp
bool TweenID::isStopped();
bool TweenID::isKilled();
bool TweenID::isPlaying();
bool TweenID::isFinished();
bool TweenID::isReversed();
bool TweenID::isValid();
bool TweenID::isRoot();
```
Check if tween is stopped/killed/playing/finished/reversed/valid/root tween respectively.

### TweenID Tween Getters
```cpp
Tween &TweenID::tween();
Tween &TweenID::root();
```
Get tween/root tween based on ID. Throws a warning and returns invalid tween if **TweenID** is invalid or the underlying tween has been killed. While references won't be invalidated, the tween itself can be invalidated and might point to a different tween. That's why it's recommended to not hold onto these references and instead use functions provided by **TweenID**.

### Tween
```cpp
struct Tween {
   Formula formula = linear;
   TweenID id = 0;
   TweenID root = 0;
   TweenID chained = 0;
   TweenID paralleled = 0;
   TweenValue value = TweenValue::none;
   TweenType type = TweenType::automatic;

   bool reversed = false;
   bool stopped = false;
   bool killed = false;
   bool started = false;
   bool finished = false;

   float timer = 0.0f;
   float time = 0.0f;
   float progress = 0.0f;
   int generation = 0;

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
Tween that holds information necessary for interpolating from a value to a target. Must not be created manually and it is recommended to not be edited manually. Create it with [createTween](#createtween) and chain and parallel using [TweenID::chain](#tweenidchain) and [TweenID::parallel](#tweenidparallel).

### createTween
```cpp
TweenID createTween(int *value, int target, float time, Formula formula = linear, TweenType type = TweenType::automatic);
TweenID createTween(float *value, float target, float time, Formula formula = linear, TweenType type = TweenType::automatic);
TweenID createTween(Vector2 *value, Vector2 target, float time, Formula formula = linear, TweenType type = TweenType::automatic);
TweenID createTween(Vector3 *value, Vector3 target, float time, Formula formula = linear, TweenType type = TweenType::automatic);
TweenID createTween(Vector4 *value, Vector4 target, float time, Formula formula = linear, TweenType type = TweenType::automatic);
TweenID createTween(Rectangle *value, Rectangle target, float time, Formula formula = linear, TweenType type = TweenType::automatic);
TweenID createTween(Color *value, Color target, float time, Formula formula = linear, TweenType type = TweenType::automatic);
```
Create a new root tween. Must be updated using [updateTweens](#updatetweens). See [Tween Formulas](#tween-formulas) for a list of all built-in formulas. See [TweenType](#tweentype) for further type information.

### updateTweens
```cpp
void updateTweens(float DT);
```
Update all playing tweens.

### killAllTweens
```cpp
void killAllTweens();
void killFinishedTweens();
```
Kill all/all finished tweens.

### getTweenCount
```cpp
size_t getTweenCount();
size_t getTweenFreeSpotCount();
```
Get tween count/killed tween count that could be used to hold a new tween.

# util.hpp
Responsible for vector and color utility functions.

### Vx Constructors
```cpp
template<typename T, typename Y>
constexpr inline Vector2 V2(T x, Y y);

template<typename T, typename Y, typename U>
constexpr inline Vector3 V3(T x, Y y, U z);

template<typename T, typename Y, typename U, typename I>
constexpr inline Vector4 V4(T x, Y y, U z, I w);
```
Returns a vector with all values set.

```cpp
template<typename T>
constexpr inline Vector2 V2(T value);

template<typename T>
constexpr inline Vector3 V3(T value);

template<typename T>
constexpr inline Vector4 V4(T value);
```
Returns a vector where all values are set to the given value.

```cpp
constexpr inline Vector2 V2();
constexpr inline Vector3 V3();
constexpr inline Vector4 V4();
```
Returns a zero-initialized vector.

```cpp
constexpr inline Vector3 V3(Color color);
constexpr inline Vector4 V4(Color color);
```
Converts the color to a vector. Changes all values from [0; 255] to [0; 1].

### R4 Constructors
```cpp
template<typename T, typename Y, typename U, typename I>
constexpr inline Rectangle R4(T x, Y y, U w, I h);
```
Returns a rectangle with all values set.

```cpp
constexpr inline Rectangle R4();
```
Returns a zero-initialized rectangle.

```cpp
constexpr inline Rectangle R4(Vector2 position, Vector2 size);
```
Constructs a rectangle from position and size.

### R4 Position
```cpp
constexpr inline Rectangle R4bounds(Rectangle rect, Vector2 origin = CENTER);
constexpr inline Vector2 R4topleft(Rectangle rect, Vector2 origin = CENTER);
constexpr inline Vector2 R4pos(Rectangle rect);
constexpr inline Vector2 R4size(Rectangle rect);
constexpr inline Vector2 R4origin(Rectangle rect, Vector2 origin = CENTER);
constexpr inline Vector2 R4anchor(Rectangle rect, Vector2 origin, Vector2 targetOrigin);
```
Returns the real boundaries/top-left position/position/size/origin/anchor of the rectangle respectively. *R4anchor* - returns global position with *targetOrigin* applied based on its origin. *R4topleft* - returns the top-left corner of the rectangle based on its origin.

### V2 Position
```cpp
constexpr inline Rectangle getBounds(Vector2 position, Vector2 size, Vector2 origin = CENTER);
constexpr inline Vector2 getTopleft(Vector2 position, Vector2 size, Vector2 origin = CENTER);
constexpr inline Vector2 getOrigin(Vector2 size, Vector2 origin = CENTER);
constexpr inline Vector2 getAnchor(Vector2 position, Vector2 size, Vector2 origin, Vector2 targetOrigin);
```
Returns the real boundaries/top-left position/origin/anchor respectively. *getAnchor* - returns global position with *targetOrigin* applied based on its origin. *getTopleft* - returns the top-left corner based on origin.

### fitSpacing
```cpp
constexpr float fitSpacing(float fontSize);
```
Fits spacing based on font size.

### fitFontSize
```cpp
inline float fitFontSize(Font font, const char *text, float maxWidth);
```
Fits font size based on width. Fits spacing automatically using *fitSpacing*.

### Text Size/Position
```cpp
inline Vector2 getTextSize(Font font, const char *text, float fontSize);
inline Rectangle getTextBounds(Font font, const char *text, float fontSize, Vector2 position, Vector2 origin = CENTER);
inline Vector2 getTextTopleft(Font font, const char *text, float fontSize, Vector2 position, Vector2 origin = CENTER);
inline Vector2 getTextOrigin(Font font, const char *text, float fontSize, Vector2 origin = CENTER);
inline Vector2 getTextAnchor(Font font, const char *text, float fontSize, Vector2 position, Vector2 origin, Vector2 targetOrigin);
```
Returns the size/real boundaries/top-left position/origin/anchor of the text respectively. *getAnchor* - returns global position with *targetOrigin* applied based on its origin. *getTopleft* - returns the top-left corner based on origin.

### getSource
```cpp
constexpr inline Rectangle getSource(Texture texture);
```
Returns full texture source.

### Rectangle Comparison
```cpp
constexpr inline bool operator == (Rectangle lhs, Rectangle rhs);
constexpr inline bool operator != (Rectangle lhs, Rectangle rhs);
```
Rectangle comparison functions.

### RGB
```cpp
template<typename T, typename Y, typename U>
constexpr inline Color RGB(T r, Y g, U b);
```
Returns an RGB color.

```cpp
constexpr inline Color RGB(Vector3 color);
```
Converts vector to RGB color. Changes all values from [0; 1] to [0; 255].

```cpp
constexpr inline Color RGBF(float r, float g, float b);
```
Converts float values [0; 1] to RGB [0; 255].

```cpp
template<typename T, typename Y, typename U, typename I>
constexpr inline Color RGBA(T r, Y g, U b, I a);
constexpr inline Color RGBA(Color rgb, unsigned char a);
```
Returns an RGBA color.

```cpp
constexpr inline Color RGBA(Vector4 color);
```
Converts vector to RGBA color. Changes all values from [0; 1] to [0; 255].

```cpp
constexpr inline Color RGBAF(float r, float g, float b, float a);
```
Converts float values [0; 1] to RGB [0; 255].

### HEX
```cpp
constexpr inline Color HEX(const char *hex);
```
Returns a HEX color. The string must be in one of the formats: *#rgb*, *#rgba*, *#rrggbb* or *#rrggbbaa*, where symbols are 0-9, a-f or A-F.

### HSL
```cpp
constexpr inline Color HSL(float h, float s, float l);
constexpr inline Color HSLA(float h, float s, float l, float a);
```
Returns a HSL color. **H** must be in range [0; 360], **S** in range [0; 1], **L** in range [0; 1] and **A** in range [0; 1].

### HSV
```cpp
constexpr inline Color HSV(float h, float s, float v);
constexpr inline Color HSVA(float h, float s, float v, float a);
```
Returns a HSV color. **H** must be in range [0; 360], **S** in range [0; 1], **V** in range [0; 1] and **A** in range [0; 1].

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
