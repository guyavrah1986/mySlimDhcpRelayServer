#pragma once


#include <log4cxx/basicconfigurator.h>
#include <log4cxx/consoleappender.h>
#include <log4cxx/logger.h>
#include <log4cxx/patternlayout.h>

// Define a global logger for all "clients" (main, unit tests...)
auto logger = log4cxx::Logger::getLogger("GlobalLogger");

/*
auto layout = new log4cxx::PatternLayout("%d{ISO8601} [%t] - %m%n");
log4cxx::ConsoleAppenderPtr consoleAppender = new log4cxx::ConsoleAppender(layout);
// Add the ConsoleAppender to the root logger
logger->addAppender(consoleAppender);
*/
