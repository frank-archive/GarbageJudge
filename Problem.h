#pragma once
#include"Language.h"
#include"EnumDef.h"

struct Problem {
	bool isSet;
	ExecType type;
	int time_limit;
	int memory_limit;
	int test_cases;
	int score_per_cases;
};
Problem *readProblemConfig(std::string dir = (string)"./config");