#pragma once

class Shader;

class IUniformProvider
{
public:
    virtual ~IUniformProvider() = default;
    virtual void ApplyUniforms(const shared_ptr<Shader>& shader) = 0;
};