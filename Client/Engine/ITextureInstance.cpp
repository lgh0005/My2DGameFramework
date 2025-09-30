#include "pch.h"
#include "ITextureInstance.h"
#include "Camera.h"
#include "Shader.h"

ITextureInstance::ITextureInstance(const string& name, const string& filePath) : Super(name, filePath)
{

}

void ITextureInstance::Awake()
{
    LoadTexture();
    CreateRect();
}

void ITextureInstance::Render(const shared_ptr<Shader>& shader, const glm::mat4& model, const shared_ptr<Camera>& camera)
{
    if (_instances.empty()) return;

    glUseProgram(shader->GetShaderProgram());
    glBindVertexArray(_vao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ibo);

    // 카메라 관련 Uniform
    shader->SetUniformValue(Uniforms::UNIFORM_VIEW, camera->GetView());
    shader->SetUniformValue(Uniforms::UNIFORM_PROJECTION, camera->GetProjection());
    shader->SetUniformValue(Uniforms::UNIFORM_TEXTURE, 0);
    shader->ApplyUniforms();

    UseTexture();

    // 인스턴스 데이터 업로드
    glBindBuffer(GL_ARRAY_BUFFER, _instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(InstanceData) * _instances.size(), _instances.data(), GL_DYNAMIC_DRAW);

    // 인스턴스용 정점 속성 (mat4는 4 vec4 속성으로 나누어야 함)
    for (GLuint i = 0; i < 4; i++)
    {
        glEnableVertexAttribArray(2 + i);
        glVertexAttribPointer(2 + i, 4, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (void*)(sizeof(GLfloat) * i * 4));
        glVertexAttribDivisor(2 + i, 1); // 한 인스턴스당 한 번만 업데이트
    }

    // 인스턴스 렌더링
    glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, (GLsizei)_instances.size());

    // 정리
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void ITextureInstance::AddInstance(const glm::mat4& model)
{
	_instances.push_back({ model });
}

void ITextureInstance::LoadTexture()
{
	Super::LoadTexture();
	glGenBuffers(1, &_instanceVBO);
}
