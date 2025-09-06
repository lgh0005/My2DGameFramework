#pragma once
#include "IUIStatic.h"

class Text : public IUIStatic
{
	using Super = IUIStatic;

public:
	Text(const string& name, shared_ptr<ITexture> texture, shared_ptr<Shader> shader);
	virtual ~Text() override;

public:
	virtual void Init(shared_ptr<GameObject> owner) override;
	virtual void Render(const shared_ptr<Camera>& camera) override;
};

