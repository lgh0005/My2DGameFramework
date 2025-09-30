#pragma once
#include "ISingleton.h"

class RenderPass;
class SpriteMesh;
class Material;

class Instancer
{
	using InstanceID = pair<shared_ptr<SpriteMesh>, shared_ptr<Material>>;

public:
	Instancer() = default;
	~Instancer() = default;
	
public:
	void Init();
	void Render(const shared_ptr<Camera>& camera);

public:
	void AddInstance(const string& meshName, const string& materialName, const glm::mat4& model);

private:
	map<InstanceID, vector<glm::mat4>> _instances;
};

