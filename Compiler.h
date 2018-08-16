#pragma once
#include"Task.h"
#include"toolkit.h"
class Compiler {
	struct CompileStatus {
		bool success;
		std::string message;
	}status;
public:
	Compiler(Task unc);
	CompileStatus getStatus();
};