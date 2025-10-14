#pragma once

class Utils
{

// weak_ptr to shared_ptr
public:
	template<typename T>
	static bool IsValidPtr(const weak_ptr<T>& weakPtr, shared_ptr<T>& outPtr)
	{
		outPtr = weakPtr.lock();
		return outPtr != nullptr;
	}
};

