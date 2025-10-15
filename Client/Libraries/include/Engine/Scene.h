#pragma once

class IResource;
class GameObject;
class RenderPass;

class Scene : public enable_shared_from_this<Scene>
{
public:
	Scene(const string& name);
	virtual ~Scene() = default;

public:
	void Init();
	void Update();

public:
	const string& GetName() { return _name; }
	void ClearPreviousSceneContext();
	shared_ptr<GameObject> GetGameObject(const string& name);

public:
	void AddGameObject(const shared_ptr<GameObject>& gameObject);
	vector<shared_ptr<GameObject>>& GetGameObjectList() { return _gameObjects; }
	void AddRenderPass(const string& name, const shared_ptr<RenderPass>& renderPass);
	shared_ptr<RenderPass> GetRenderPass(const string& name);

protected:
	virtual void LoadResources() abstract;
	virtual void CreateRenderProperties() abstract;
	virtual void CreateSceneContext() abstract;

private:
	void ApplyPendingChanges();

protected:
	string _name;
	vector<shared_ptr<GameObject>> _gameObjects;
	vector<shared_ptr<GameObject>> _pendingAdd;
	unordered_map<string, shared_ptr<RenderPass>> _renderPasses;
};

