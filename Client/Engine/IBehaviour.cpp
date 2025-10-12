#include "pch.h"
#include "IBehaviour.h"

IBehaviour::IBehaviour(const string& name) : Super(name) {}

void IBehaviour::SetCurrentScene(const shared_ptr<Scene>& scene)
{
	_currentScene = scene;
}