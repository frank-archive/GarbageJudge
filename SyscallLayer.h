#pragma once
#include<sys/ptrace.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/user.h>
#include<sys/resource.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<syscall.h>
#include<cstdio>
#include<unistd.h>
#include<cstdlib>
#include<string>
#include<map>
#include<cstdarg>

#include"EnumDef.h"
//enters a directory. if it doesn't exist, create one.
void enterDir(std::string dir);

std::string trim(std::string c);

//parse configuration from a file: yaml formatted
std::map<std::string, std::string>fparse(std::string file);

void setTimeLimit(int seconds);
void setMemoryLimit(long long kilobytes);
void setCreateFileSizeLimit(long long kilobytes);
int getProc(int pid, std::string target);

int vsystem(const char *fmt, ...);