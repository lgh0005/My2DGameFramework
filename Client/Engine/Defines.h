#pragma once

// Custom SDL assert
#define SDL_ASSERT(expr, msg, getErrorFunc)                                      \
  do                                                                             \
{                                                                                \
    if (expr)                                                                    \
    {                                                                            \
        cout << msg << ": " << getErrorFunc() << endl;                           \
        SDL_Quit();                                                              \
        exit(-1);                                                                \
    }                                                                            \
} while (0)

// Custom GLEW assert
#define GLEW_ASSERT(expr, msg)                                                    \
do                                                                                \
{                                                                                 \
    if (expr)                                                                     \
    {                                                                             \
        cout << msg << ": " << (const char*)glewGetErrorString(expr) << endl;     \
        SDL_Quit();                                                               \
        exit(-1);                                                                 \
    }                                                                             \
} while(0)

// Custom FMOD assert
#define FMOD_ASSERT(result)                                                      \
do                                                                               \
{                                                                                \
    if (result != FMOD_OK)                                                       \
    {                                                                            \
        cout << "Load audio Failed : " << FMOD_ErrorString(result) << endl;      \
        SDL_Quit();                                                              \
        exit(-1);                                                                \
    }                                                                            \
} while (0)

// Make singleton class
#define DECLARE_SINGLE(classname)                                                \
private:                                                                         \
    classname() = default;                                                       \
    friend class ISingleton<classname>;
