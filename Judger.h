#pragma once
#include<map>
#include<string>
#include"EnumDef.h"



std::map<std::string, std::string>config;
std::map<std::string, int>res;//time_peak,mem_peak,status,score
int score_per_test;
int time_limit, memory_limit;

int getMemory(langtype &lang, int pid, rusage &ruse);
retcode verdict(int judger, int player);
retcode monitorPlayerTimeMemory(langtype lang, int player);
retcode specialJudge(langtype &lang, std::string &file);
retcode interactiveJudge(langtype &lang, string &file);
retcode normalJudge(langtype &lang, string &file);
retcode judge(langtype lang, string file);