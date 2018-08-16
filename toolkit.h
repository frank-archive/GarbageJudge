#pragma once
#include<string>
#include<cstdlib>
#include<unordered_map>
#include<cstring>
#include<regex>

#include<unistd.h>
#include<sys/stat.h>
#include<sys/time.h>
#include<sys/resource.h>
#include<sys/types.h>
#include<sys/wait.h>

#include"EnumDef.h"

bool isWorkDir();
void enterDir(std::string dir);

std::string trim(std::string c);
std::unordered_map<std::string, std::string> parseYamlFile(std::string file);


void setTimeLimit(int seconds);
void setMemoryLimit(long long kilobytes);
void setCreateFileSizeLimit(long long kilobytes);
struct Usage {
	int time_passed, mem_used;
};
static int getMemoryPeak(int proc_id, bool is_page);//kb
ProcStatus watchSubProcess(int proc_id, bool is_use_vm, Usage *ret, int time_limit = 0, int memory_limit = 0);