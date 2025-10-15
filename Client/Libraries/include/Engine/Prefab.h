#pragma once
#include "IResource.h"

class Scene;
class GameObject;
class RenderPass;

class Prefab : public IResource
{
    using Super = IResource;

public:
    Prefab(const string& name);
    virtual ~Prefab() = default;

    virtual shared_ptr<GameObject> Instantiate
    (
        const string& name,
        const glm::vec3& position,
        const glm::vec3& rotation = glm::vec3(0.0f),
        const glm::vec3& scale = glm::vec3(1.0f)
    ) abstract;

    void SetCurrentScene(const shared_ptr<Scene>& scene);

protected:
    weak_ptr<Scene> _currentScene;
};
