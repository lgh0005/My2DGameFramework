#include "pch.h"
#include "TimeManager.h"

void TimeManager::Init()
{

}

void TimeManager::Update()
{
    _currentTime = SDL_GetPerformanceCounter();
    deltaTime = (_currentTime - _lastTime) / (float)SDL_GetPerformanceFrequency();
    FPS = 1.f / deltaTime;
    _lastTime = _currentTime;
}
