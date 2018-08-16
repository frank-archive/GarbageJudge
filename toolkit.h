#pragma once
#include<string>
#include<cstdlib>
#include<unordered_map>

#include<unistd.h>
#include<sys/stat.h>

bool isWorkDir();
void enterDir(std::string dir);

std::string trim(std::string c);
std::unordered_map<std::string, std::string> parseYamlFile(std::string file);