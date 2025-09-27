#pragma once

class Utils
{

public:
	template<typename T>
	static bool IsValidPtr(const weak_ptr<T>& weakPtr, shared_ptr<T>& outPtr)
	{
		outPtr = weakPtr.lock();
		return outPtr != nullptr;
	}
};

