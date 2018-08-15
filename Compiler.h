#pragma once
#include<string>

#include"LanguageConfig.h"
#include"SyscallLayer.h"
#include"EnumDef.h"

std::string compile_error;

bool isCompileError(langtype lang, std::string message);
retcode compile(langtype lang, std::string filename);