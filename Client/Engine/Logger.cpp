#include "pch.h"
#include "Logger.h"

void Logger::Init() {}
void Logger::Update() {}
void Logger::LateUpdate() {}

void Logger::WriteLog(const string& msg)
{
	ofstream logFile("../Debug/Error_report.log", ios::app);
	if (logFile.is_open())
	{
		logFile << msg << endl;
	}
}
