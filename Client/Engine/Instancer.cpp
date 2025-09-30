#include "pch.h"
#include "Instancer.h"
#include "Material.h"
#include "Shader.h"
#include "SpriteMesh.h"
#include "ITexture.h"
#include "RenderPass.h"
#include "Camera.h"

void Instancer::AddInstance(const string& meshName, const string& materialName, const glm::mat4& model)
{
    shared_ptr<SpriteMesh> mesh = RESOURCE.GetResource<SpriteMesh>(meshName);
    shared_ptr<Material> material = RESOURCE.GetResource<Material>(materialName);

	InstanceID id = make_pair(mesh, material);
	_instances[id].push_back(model);
}

void Instancer::Init()
{
    for (auto& [id, _] : _instances)
    {
        shared_ptr<SpriteMesh> mesh = id.first;
        shared_ptr<Material> material = id.second;

        material->Bind();
        mesh->Bind();
    }
}

void Instancer::Render(const shared_ptr<Camera>& camera)
{
    for (auto& [id, matrices] : _instances)
    {
        shared_ptr<SpriteMesh> mesh = id.first;
        shared_ptr<Material> material = id.second;
        shared_ptr<Shader> shader = material->GetShader();
        shared_ptr<ITexture> texture = material->GetTexture();

        shader->Use();

        // MVP 계산 및 Uniform 설정
        glm::mat4 view = camera->GetView();
        glm::mat4 projection = camera->GetProjection();
        shader->SetUniformValue(Uniforms::UNIFORM_VIEW, view);
        shader->SetUniformValue(Uniforms::UNIFORM_PROJECTION, projection);

        texture->UseTexture();
        shader->SetUniformValue(Uniforms::UNIFORM_TEXTURE, (int)texture->GetTexture());

        shader->ApplyUniforms();

        if (matrices.size() == 1)
        {
            shader->SetUniformValue(Uniforms::UNIFORM_MODEL, matrices[0]);
            shader->ApplyUniforms();
            mesh->Draw();
        }
        else if (matrices.size() > 1) mesh->DrawInstanced(matrices);
        else continue;

        shader->Unuse();
    }

    _instances.clear();
}