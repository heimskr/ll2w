#pragma once

#include <string>

extern int global_argc;
extern char **global_argv;
extern std::atomic<const std::string *> global_function_name;

bool hasArg(const char *);
