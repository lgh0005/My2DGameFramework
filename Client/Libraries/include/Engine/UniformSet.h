#pragma once
#include "IResource.h"

class Shader;

#pragma region TEMPLATE_PROPERTIES
using UniformValue = variant<int, float, bool, glm::vec2, glm::vec3, glm::vec4, glm::mat3, glm::mat4>;
#pragma endregion

class UniformSet : public IResource
{
	using Super = IResource;

public:
	UniformSet(const string& name);
	~UniformSet() = default;

public:
	template<typename T>
	void Set(const string& name, const T& value)
	{
		_uniforms[name] = value;
	}

	void Remove(const string& name);
	bool Has(const string& name) const;
	void Apply(const shared_ptr<Shader>& shader) const;

private:
	unordered_map<string, UniformValue> _uniforms;
};

