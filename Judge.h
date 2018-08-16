#pragma once
#include"Task.h"
#include"EnumDef.h"

struct Judge {
	unsigned long time_usage;
	unsigned long memory_usage;
	int score;
	JudgeStatus status;
	std::string compiler_info;
	JudgeStatus judge(Task task);
};