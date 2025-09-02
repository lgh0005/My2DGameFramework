#include "pch.h"
#include "Logger.h"

void Logger::Init()
{
	// TODO : Logger 시작 로그를 작성한다.
}

void Logger::Update()
{
}

void Logger::WriteLog(const string& msg)
{
	ofstream logFile("../Debug/Error_report.log", ios::app);
	if (logFile.is_open())
	{
		logFile << msg << endl;
	}
}
