#pragma once
#include<unordered_map>
#include"EnumDef.h"

std::unordered_map<langtype, std::string>compile_commands;
void initCommands();
std::unordered_map<langtype, std::string>match_compile_error;
void initRegexCE();
langtype tellType(std::string fn);
void bootBin(langtype &lang, std::string &file);