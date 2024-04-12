#pragma once

#include <log4cxx/logger.h>
#include <log4cxx/basicconfigurator.h>

// Define a global logger for all unit tests functions
auto logger = log4cxx::Logger::getLogger("GlobalLogger");
