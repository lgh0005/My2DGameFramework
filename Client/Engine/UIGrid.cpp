#include "pch.h"
#include "UIGrid.h"
#include "GameObject.h"
#include "Transform.h"

UIGrid::UIGrid(const string& name, const glm::vec2& size, int32 row, int32 column, int32 padding)
	: Super(name, size), _row(row), _column(column), _padding(padding)
{
}

// TODO : 여기도 Dirty 패턴 써서 최적화
void UIGrid::Arrange(vector<shared_ptr<IUIElement>>& uis, const glm::vec2& parentSize)
{
    glm::vec2 cellSize
    (
        (parentSize.x - (_column - 1) * _padding) / _column,
        (parentSize.y - (_row - 1) * _padding) / _row
    );

    for (int32 i = 0; i < uis.size(); i++)
    {
        int32 r = i / _column;
        int32 c = i % _column;

        glm::vec2 pos
        (
            c * (cellSize.x + _padding),
            r * (cellSize.y + _padding)
        );

        auto& ui = uis[i];
        auto owner = ui->GetOwner();
        if (owner)
        {
            auto transform = owner->GetTransform();
            if (transform)
            {
                transform->SetPosition(glm::vec3(pos.x, pos.y, 0.0f));
                transform->SetScale(glm::vec3(cellSize.x, cellSize.y, 1.0f));
            }
        }
    }
}
