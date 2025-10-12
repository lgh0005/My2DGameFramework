#include "pch.h"
#include "UIBlocker.h"

UIBlocker::UIBlocker(const string& name) : Super(name)
{

}

bool UIBlocker::IsInteractive()
{
	return _isInteractive;
}

void UIBlocker::SetInteractive(bool interactive)
{
	_isInteractive = interactive;
}
