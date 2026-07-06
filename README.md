# SRU-Library
## About
SRU-Lib is a simple C++ utility library designed for use with Raylib to reduce rewriting different utility functions and managers for different Raylib projects. Inspired by my own utilities.
## ToC
- [Usage](#usage)
- [Documentation](#documentation)
- - [assets.hpp](#assetshpp)
- - [audio.hpp](#audiohpp)
- - [file.hpp](#filehpp)
- - [random.hpp](#randomhpp)
- - [render.hpp](#renderhpp)
- - [sru.hpp](#sruhpp)
- - [text.hpp](#texthpp)
- - [util.hpp](#utilhpp)
- - [Macros](#macros)

## Usage
SRU-Lib is meant to be used together with CMake's FetchContent module and can be imported as follows:
```cmake
include(FetchContent)
FetchContent_Declare(srulib
   GIT_REPOSITORY https://github.com/Acerx-AMJ/SRU-Library.git
   GIT_TAG main
   GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(srulib)
```
However, you have to import Raylib yourself. That can also be done with FetchContent:
```cmake
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
```
And finally you have to link it to your project:
```cmake
target_link_libraries(${PROJECT_NAME} PRIVATE raylib srulib)
```
Here's a full example:
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

add_executable(${PROJECT_NAME} main.cpp) # add your source files
target_link_libraries(${PROJECT_NAME} PRIVATE raylib srulib)
```

## Documentation
Here you will find the documentation of all headers, functions and structures found in the library. Select by header:
- [assets.hpp](#assetshpp)
- [audio.hpp](#audiohpp)
- [file.hpp](#filehpp)
- [random.hpp](#randomhpp)
- [render.hpp](#renderhpp)
- [sru.hpp](#sruhpp)
- [text.hpp](#texthpp)
- [util.hpp](#utilhpp)

Or browse miscellaneous documentation:
- [Macros](#macros)

## assets.hpp
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

## audio.hpp
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

## file.hpp
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

## random.hpp
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

## render.hpp
Responsible for providing screen, size and position math utilities as well as drawing utilities.

---
```cpp
float getWindowWidth();
float getWindowHeight();
Vector2 getWindowSize();
```   
Returns the size of the window.

---
```cpp
Vector2 getWindowCenter();
```
Returns the position of the center of the window.

---
```cpp
Vector2 getWindowCenterOffset(Vector2 offset);
```
Returns the position of the center of the window with the added offset.

---
```cpp
Vector2 mapRatioToScreen(Vector2 ratio);
Vector2 mapRatioToScreen(float ratioX, float ratioY);
```
Maps ratio where X and Y are [0; 1] to screen position where X is [0; width] and Y is [0; height].

---
```cpp
Vector2 mapScreenToRatio(Vector2 screen);
Vector2 mapScreenToRatio(float screeX, float screenY);
```
Maps screen position where X is [0; width] and Y is [0; height] to a ratio where X and Y are [0; 1].

---
```cpp
Vector2 mapCubicRatioToScreen(Vector2 ratio);
Vector2 mapCubicRatioToScreen(float ratioX, float ratioY);
Vector2 mapScreenToCubicRatio(Vector2 screen);
Vector2 mapScreenToCubicRatio(float screenX, float screenY);
```
Cubic ratio versions of the previous functions. Are meant for object sizes that should preserve aspect ratio. Sources the smallest size field of the screen - width or height.

---
```cpp
Vector2 mapRatioToRectangle(Rectangle rect, Vector2 ratio);
Vector2 mapRatioToRectangle(Rectangle rect, float ratioX, float ratioY);
```
Maps ratio where X and Y are [0; 1] to a position in the rectangle where X is [rect.x; rect.width] and Y is [rect.y; rect.height].

---
```cpp
Vector2 mapRectangleToRatio(Rectangle rect, Vector2 position);
Vector2 mapRectangleToRatio(Rectangle rect, float positionX, float positionY);
```
Maps position in the rectangle where X is [rect.x; rect.width] and Y is [rect.y; rect.height] to a ratio where X and Y are [0; 1].

---
```cpp
Vector2 mapCubicRatioToRectangle(Rectangle rect, Vector2 ratio);
Vector2 mapCubicRatioToRectangle(Rectangle rect, float ratioX, float ratioY);
Vector2 mapRectangleToCubicRatio(Rectangle rect, Vector2 position);
Vector2 mapRectangleToCubicRatio(Rectangle rect, float positionX, float positionY);
```
Cubic ratio versions of the previous functions. Are meant for object sizes that should preserve aspect ratio. Sources the smallest size fieldof the rectangle - width or height.

---
```cpp
Vector2 getTextSize(Font font, const char *text, float fontSize, float spacing);
```
Returns the size of the text based on parameters.

---
```cpp
Vector2 getTextOrigin(Font font, const char *text, float fontSize, float spacing);
```
Returns the center position of the text based on parameters.

---
```cpp
constexpr inline Vector2 getOrigin(Vector2 size);
```
Returns the origin/center of the size.

---
```cpp
constexpr inline Rectangle getSource(Texture texture);
```
Returns the full texture source - *{0, 0, width, height}*.

---
```cpp
void drawText(Font font, Vector2 position, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
void drawTextCentered(Font font, Vector2 position, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
void drawTextOrigin(Font font, Vector2 position, Vector2 origin, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
```
Draw text with the specified origin. *drawText* assumes top-left position, *drawTextCentered* assumes center position and *drawTextOrigin* takes custom origin. Fits spacing using *fitSpacing*.

---
```cpp
void drawTextResponsive(Font font, Vector2 ratio, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
void drawTextCenteredResponsive(Font font, Vector2 ratio, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
void drawTextOriginResponsive(Font font, Vector2 ratio, Vector2 origin, const char *text, float fontSize, Color color = WHITE, float rotation = 0.0f);
```
Responsive variations of the previous functions. Instead of passing screen position, pass screen ratio [0; 1]. Also scales font size and spacing automatically based on screen size.

---
```cpp
void drawRect(Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawRectCentered(Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawRectOrigin(Vector2 position, Vector2 origin, Vector2 size, Color color = WHITE, float rotation = 0.0f);
```
Draw rectangle with the specified origin. *drawRect* assumes top-left position, *drawRectCentered* assumes center position and *drawRectOrigin* takes custom origin.

---
```cpp
void drawRectResponsive(Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawRectCenteredResponsive(Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawRectOriginResponsive(Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawRectResponsiveCubic(Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawRectCenteredResponsiveCubic(Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawRectOriginResponsiveCubic(Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
```
Responsive variations of the previous functions. Instead of passing screen position, pass screen ratio [0; 1]. Cubic versions will preserve aspect ratio of the size.

---
```cpp
void drawTexture(Texture texture, Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawTextureCentered(Texture texture, Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawTextureOrigin(Texture texture, Vector2 position, Vector2 origin, Vector2 size, Color color = WHITE, float rotation = 0.0f);
```
Draw texture with the specified origin. *drawRect* assumes top-left position, *drawRectCentered* assumes center position and *drawRectOrigin* takes custom origin. Draws the entire texture.

---
```cpp
void drawTextureResponsive(Texture texture, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureCenteredResponsive(Texture texture, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureOriginResponsive(Texture texture, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureResponsiveCubic(Texture texture, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureCenteredResponsiveCubic(Texture texture, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureOriginResponsiveCubic(Texture texture, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
```
Responsive variations of the previous functions. Instead of passing screen position, pass screen ratio [0; 1]. Cubic versions will preserve aspect ratio of the size.

---
```cpp
void drawTextureSource(Texture texture, Rectangle source, Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawTextureSourceCentered(Texture texture, Rectangle source, Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawTextureSourceOrigin(Texture texture, Rectangle source, Vector2 position, Vector2 origin, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawTextureSourceResponsive(Texture texture, Rectangle source, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureSourceCenteredResponsive(Texture texture, Rectangle source, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureSourceOriginResponsive(Texture texture, Rectangle source, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureSourceResponsiveCubic(Texture texture, Rectangle source, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureSourceCenteredResponsiveCubic(Texture texture, Rectangle source, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureSourceOriginResponsiveCubic(Texture texture, Rectangle source, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
```
Custom source variations of the previous functions. Instead of drawing the whole texture draw a specific region. Includes responsive functions.

---
```cpp
using AnimationID = size_t;
```
Animation ID of a specific animation config instance.

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
void drawTextureAnimated(Animation animation, Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedCentered(Animation animation, Vector2 position, Vector2 size, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedOrigin(Animation animation, Vector2 position, Vector2 origin, Vector2 size, Color color = WHITE, float rotation = 0.0f);
```
Draw animated texture with the specified origin. *drawTextureAnimated* assumes top-left position, *drawTextureAnimatedCentered* assumes center position and *drawTextureAnimatedOrigin* takes custom origin.

---
```cpp
void drawTextureAnimatedResponsive(Animation animation, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedCenteredResponsive(Animation animation, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedOriginResponsive(Animation animation, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedResponsiveCubic(Animation animation, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedCenteredResponsiveCubic(Animation animation, Vector2 ratio, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
void drawTextureAnimatedOriginResponsiveCubic(Animation animation, Vector2 ratio, Vector2 origin, Vector2 sizeRatio, Color color = WHITE, float rotation = 0.0f);
```
Responsive variations of the previous functions. Instead of passing screen position, pass screen ratio [0; 1]. Cubic versions will preserve aspect ratio of the size.

## sru.hpp
Includes all headers provided by the library.

## text.hpp
Responsible for modifying text.

---
```cpp
std::string wrap(const std::string &string, Font font, float maxWidth, float fontSize, float spacing);
```
Wrap the text to fit in the width.

---
```cpp
std::string truncate(const std::string &string, Font font, float maxWidth, float fontSize, float spacing);
```
Truncate the text to fit in the width.

---
```cpp
std::string fitInside(const std::string &string, Font font, Vector2 maxSize, float fontSize, float spacing);
```
Wrap and then truncate the text to fit in the bounds.

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
void wrapInPlace(std::string &string, Font font, float maxWidth, float fontSize, float spacing);
void truncateInPlace(std::string &string, Font font, float maxWidth, float fontSize, float spacing);
void fitInsideInPlace(std::string &string, Font font, Vector2 maxSize, float fontSize, float spacing);
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
```
Same as the previous functions but operate directly on the output.

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
Returns a font size that will fit as closely to the width as possible.

---
```cpp
inline float getFontSizeScaled(float fontSize);
```
Returns the font size scaled responsively based on the window size. Safe from UI overflows.

## util.hpp
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
constexpr inline Vector2 R4pos(Rectangle rect);
constexpr inline Vector2 R4size(Rectangle rect);
constexpr inline Vector2 R4center(Rectangle rect);
constexpr inline Vector2 R4origin(Rectangle rect);
```
Returns the position/size/center/origin of the rectangle respectively.

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

## Macros
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
