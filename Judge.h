#pragma once
#include"Task.h"
#include"toolkit.h"

struct Judge {
	unsigned long time_usage;
	unsigned long memory_usage;
	int score;
	ProcStatus status;
	std::string compiler_info;
	ProcStatus judge(Task task);
};
class NormalCase {

};