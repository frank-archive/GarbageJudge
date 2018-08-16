#pragma once
#include"toolkit.h"
#include"EnumDef.h"
struct Task {
	int problem_id;
	int submission_id;
	std::string lang;
	std::string code_based;//base64
};

Task parse(std::string json);