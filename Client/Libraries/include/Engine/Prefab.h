#pragma once

class Scene;
class GameObject;
class RenderPass;

class Prefab
{
public:
    virtual ~Prefab() = default;

    virtual shared_ptr<GameObject> Instantiate
    (
        const string& name,
        const glm::vec3& position,
        const glm::vec3& rotation = glm::vec3(0.0f),
        const glm::vec3& scale = glm::vec3(1.0f)
    ) abstract;

    void SetRenderPass(const shared_ptr<RenderPass>& renderPass);
    void SetCurrentScene(const shared_ptr<Scene>& scene);

protected:
    shared_ptr<RenderPass> _renderPass;
    weak_ptr<Scene> _currentScene;
};
