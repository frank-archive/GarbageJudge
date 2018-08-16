#pragma once
#include"Language.h"
#include"EnumDef.h"

struct Problem {
	bool isSet;
	ExecType type;
	std::string lang;
	int time_limit;
	int memory_limit;
	int test_cases;
	int score_per_cases;
};
Problem *readProblemConfig(std::string dir = "./config");