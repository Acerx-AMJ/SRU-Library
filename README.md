# SRU-Library
## About
SRU-Lib is a simple C++ utility library designed for use with Raylib to reduce rewriting different utility functions and managers for different Raylib projects. Inspired by my own utilities.
## ToC
- [Usage](#usage)
- [Documentation](#documentation)
- - [assets.hpp](#assetshpp)
- - [audio.hpp](#audiohpp)
- - [random.hpp](#randomhpp)
- - [render.hpp](#renderhpp)
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
- [random.hpp](#randomhpp)
- [render.hpp](#renderhpp)
- [text.hpp](#texthpp)
- [util.hpp](#utilhpp)

Or browse miscellaneous documentation:
- [Macros](#macros)

## assets.hpp
Responsible for asset loading, unloading and retrieval. Handles textures, fonts, shaders and models. Note that different asset types use different containers so a texture can exist with a font that's using an identical name whereas two textures with the same name cannot.

---
```cpp
using SoundPool = std::vector<Sound>;
```
Pool of sounds. If loaded automatically, sounds with the same names but different numbering will be loaded into the same pool (e.g. sound, sound1, sound2 and so on will be put in the same pool).

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
inline float getFontSizeScaled(float fontSize);
inline float getSpacingScaled(float spacing = 1.0f);
```
Returns the font size scaled responsively based on the window size. Safe from UI overflows.

---
```cpp
inline float getWindowWidth();
inline float getWindowHeight();
inline Vector2 getWindowSize();
```   
Returns the size of the window.

---
```cpp
inline Vector2 getWindowCenter();
```
Returns the position of the center of the window.

---
```cpp
inline Vector2 getWindowCenterOffset(Vector2 offset);
```
Returns the position of the center of the window with the added offset.

---
```cpp
inline Vector2 translateRatioToScreen(Vector2 ratio);
inline Vector2 translateRatioToScreen(float ratioX, float ratioY);
```
Translates ratio where X and Y are [0; 1] to screen position where X is [0; width] and Y is [0; height].

---
```cpp
inline Vector2 translateScreenToRatio(Vector2 screen);
inline Vector2 translateScreenToRatio(float screeX, float screenY);
```
Translates screen position where X is [0; width] and Y is [0; height] to a ratio where X and Y are [0; 1].

---
```cpp
inline Vector2 getTextSize(Font font, const char *text, float fontSize, float spacing);
```
Returns the size of the text based on parameters.

---
```cpp
inline Vector2 getTextOrigin(Font font, const char *text, float fontSize, float spacing);
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
void wrapInPlace(std::string &string, Font font, float maxWidth, float fontSize, float spacing);
void truncateInPlace(std::string &string, Font font, float maxWidth, float fontSize, float spacing);
void fitInsideInPlace(std::string &string, Font font, Vector2 maxSize, float fontSize, float spacing);
void toRomanNumeralInPlace(std::string &string, size_t number);
void toUpperInPlace(std::string &string);
void toLowerInPlace(std::string &string);
void trimInPlace(std::string &string);
void trimLeftInPlace(std::string &string);
void trimRightInPlace(std::string &string);
```
Same as the previous functions but operates directly on the string.

---
```cpp
float fitFontSize(const char *string, Font font, float maxWidth, float spacing);
float fitFontSize(const std::string &string, Font font, float maxWidth, float spacing);
```
Returns a font size that will fit as closely to the width as possible.

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
