#pragma once

// Framework
#include "Engine/EnginePch.h"
#ifdef _DEBUG
#pragma comment(lib, "Engine/Debug/Engine.lib")
#else
#pragma comment(lib, "Engine/Release/Engine.lib")
#endif

// Game
#include "Game.h"