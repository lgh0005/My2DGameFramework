#pragma once
#include "IUIElement.h"

enum class AlignType
{
	None,
	Horizontal,
	Vertical
};

class IUIContainer : public IUIElement
{
	using Super = IUIElement;

public:
	IUIContainer(const string& name, const glm::vec2& size);
	virtual ~IUIContainer() override;

public:

protected:
	AlignType _align;
	int32 _padding;
	int32 _row;
	int32 _column;
	vector<IUIElement> _uis;
};

