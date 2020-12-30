#pragma once
#include <string>

class Logger
{
public:
	enum LogType { LOG_ERROR, LOG_NEW_EVENT, LOG_INFO };

	enum LogVerbosity { L1 = 1, L2, L3, L4 };

	// Prints messages into output stream.
	void Print(const std::string text, LogVerbosity logVerb = L1, LogType logType = LOG_INFO);

	void SetLogVerbosity(LogVerbosity lv);

	LogVerbosity GetLogVerbosity();

	static Logger* GetInstance();

protected:
	Logger();

	virtual ~Logger();

	static Logger* instance_;

	LogVerbosity log_verbosity_;			// Log verbosity. 
};

