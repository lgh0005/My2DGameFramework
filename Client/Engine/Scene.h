#pragma once

class IResource;
class GameObject;

class Scene
{
public:
	Scene(const string& name);
	virtual ~Scene();

public:
	void Init();
	void Update();

public:
	const string& GetName() { return _name; }

protected:
	virtual void CreateSceneContext() abstract;

protected:
	string _name;
	vector<shared_ptr<GameObject>> _gameObjects;
};

