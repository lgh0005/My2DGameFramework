#include "pch.h"
#include "UniformSet.h"
#include "Shader.h"

UniformSet::UniformSet(const string& name) : Super(name)
{

}

void UniformSet::Remove(const string& name)
{
	_uniforms.erase(name);
}

bool UniformSet::Has(const string& name) const
{
	return _uniforms.contains(name);
}

void UniformSet::Apply(const shared_ptr<Shader>& shader) const
{
    for (auto& [name, value] : _uniforms)
    {
        shader->SetUniformValue(name, value);
    }
    shader->ApplyUniforms();
}
