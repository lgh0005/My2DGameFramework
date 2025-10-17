#pragma once
#include "ISingleton.h"

class Logger : public ISingleton<Logger>
{
	DECLARE_SINGLE(Logger);

public:
	virtual void Init() override;
	virtual void Update() override;
	virtual void LateUpdate() override;

public:
	static void WriteLog(const string& msg);

	template<typename Func>
	static void DebugAssert(bool cond, const string& msg, Func err = nullptr)
	{
		if (!cond) return;

		ostringstream oss;
		oss << msg;

		if constexpr (!is_same_v<Func, nullptr_t>)
		{
			auto val = err();
			oss << ": " << val;
		}

		string logMessage = oss.str();

#ifdef _DEBUG
		cerr << logMessage << endl;
		WriteLog(logMessage);
		SDL_Quit();
		exit(-1);
#else
		cerr << "[Release Warning] " << logMessage << endl;
		WriteLog("[Release Warning] " + logMessage);
#endif
	}
};

