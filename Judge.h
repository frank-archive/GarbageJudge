#pragma once
#include"Task.h"
#include"EnumDef.h"

class Judge {
	unsigned long time_usage;
	unsigned long memory_usage;
	JudgeStatus status;
	int score;
public:
	JudgeStatus judge(Task task);
};