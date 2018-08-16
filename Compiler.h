#pragma once
#include<string>
#include"Task.h"
class Compiler {
	struct CompileStatus {
		bool success;
		std::string message;
	}status;
public:
	Compiler(Task unc);
	CompileStatus getStatus();
};