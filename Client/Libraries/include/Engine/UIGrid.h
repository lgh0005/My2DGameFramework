#pragma once
#include "IUIElement.h"

enum class AlignType
{
	None,
	Horizontal,
	Vertical
};

class UIGrid : public IUIElement
{
	using Super = IUIElement;

public:
	UIGrid(const string& name, const glm::vec2& size, int32 row, int32 column, int32 padding = 0);
	virtual ~UIGrid() override = default;

public:
	void Arrange(vector<shared_ptr<IUIElement>>& uis, const glm::vec2& parentSize);

private:
	int32 _row;
	int32 _column;
	int32 _padding;
};

