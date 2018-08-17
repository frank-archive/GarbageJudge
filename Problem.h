#pragma once
#include"toolkit.h"
#include<string>

struct Problem {
	bool isSet;
	ExecType type;
	int time_limit;
	int memory_limit;
	int test_cases;
	int score_per_cases;
};
Problem *readProblemConfig(std::string dir = (std::string)"./config");