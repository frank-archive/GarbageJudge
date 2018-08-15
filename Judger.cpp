#include "Judger.h"

#include<string>
#include"Compiler.h"
#include"SyscallLayer.h"
#include"LanguageConfig.h"

using namespace std;

int getMemory(langtype & lang, int pid, rusage & ruse) {
	if (lang == JAVA)return ruse.ru_minflt*getpagesize();
	else return getProc(pid, "VmPeak:") * 1024;
}

retcode verdict(int judger, int player) {
	if (WIFEXITED(player) || (WIFSIGNALED(player) && WTERMSIG(player) == SIGPIPE)) {
		if (WIFEXITED(judger)) {
			switch (WEXITSTATUS(judger)) {
			case 0: return ACCEPTED;
			case 1: return WA;
			default:return JUDGE_ERROR;
			}
		}
		else if (WIFSIGNALED(judger) && WTERMSIG(judger) == SIGPIPE)
			return WA;
		else return JUDGE_ERROR;
	}
	else return RE;
}

retcode monitorPlayerTimeMemory(langtype lang, int player) {
	int player_stat, current_memory, current_time;
	rusage ruse;
	int start_time = clock();
	while (1) {
		wait4(player, &player_stat, __WALL, &ruse);
		current_memory = getMemory(lang, player, ruse);
		current_time = clock() - start_time;
		current_time /= (CLOCKS_PER_SEC / 1000);

		if (current_memory > res["mem_peak"])
			res["mem_peak"] = current_memory;
		if (current_time > res["time_peak"])
			res["time_peak"] = current_time;
		if (current_memory > memory_limit) {
			ptrace(PTRACE_KILL, player, NULL, NULL);//shut up!!!player
			res["status"] = MLE;
			return MLE;
		}
		if (current_time > time_limit) {
			ptrace(PTRACE_KILL, player, NULL, NULL);
			res["status"] = TLE;
			return TLE;
		}
		if (WIFEXITED(player_stat))break;
	}
	return ACCEPTED;
}

retcode specialJudge(langtype & lang, std::string & file) {
	if (access("judger.cpp", 0) == ENOENT) {
		printf("[fatal]special judge doesn't exist\n");
		exit(PROBLEM_SETTING_INVALID);
	}
	if (compile(CPP, "judger.cpp") == CE) {
		printf("[fatal]judger can't be compiled\n");
		exit(PROBLEM_SETTING_INVALID);
	}
	//all clear
	int test_cases = atoi(config["cases"].c_str());
	if (test_cases == 0)test_cases = 10;
	for (int i = 0; i < test_cases; i++) {
		if (access((to_string(i) + ".in").c_str(), 0) == ENOENT) {
			printf("[warning]input file missing, skipping judge sequence...\n");
			break;
		}

		int judger_process = fork();
		if (judger_process == 0) {
			int judge_in = open("player2judger.fifo", O_RDONLY);
			dup2(judge_in, 0);
			close(judge_in);
			execl("judger", "judger", nullptr);
			exit(0);
		}
		int player_process = fork();
		if (player_process == 0) {
			int player_out = open("player2judger.fifo", O_WRONLY);
			int player_in = open((to_string(i) + ".in").c_str(), O_RDONLY);
			dup2(player_out, 1);
			dup2(player_in, 0);
			close(player_out);
			close(player_in);
			setTimeLimit(time_limit);
			setMemoryLimit(memory_limit);

			bootBin(lang, file);
			exit(0);
		}
		int player_stat, judger_stat;

		retcode ret_runtime = monitorPlayerTimeMemory(lang, player_process);
		if (ret_runtime == MLE || ret_runtime == TLE)return ret_runtime;

		waitpid(player_process, &player_stat, 0);
		waitpid(judger_process, &judger_stat, 0);
		switch (verdict(judger_stat, player_stat)) {
		case ACCEPTED:
			res["score"] += score_per_test;
			break;
		case WA: return WA;
		case RE: return RE;
		case JUDGE_ERROR:
			printf("judger crashed\n");
			exit(JUDGE_ERROR);
		}
	}
	return ACCEPTED;
}

retcode interactiveJudge(langtype & lang, string & file) {
	if (access("judger.cpp", 0) == ENOENT) {
		printf("[fatal]special judge doesn't exist\n");
		exit(PROBLEM_SETTING_INVALID);
	}
	if (compile(CPP, "judger.cpp") == CE) {
		printf("[fatal]judger can't be compiled\n");
		exit(PROBLEM_SETTING_INVALID);
	}
	int judger_process = fork();
	if (judger_process == 0) {
		int judge_in = open("player2judger.fifo", O_RDONLY);
		int judge_out = open("judger2player.fifo", O_WRONLY);
		dup2(judge_in, 0);
		dup2(judge_out, 1);
		close(judge_in);
		close(judge_out);
		execl("judger", "judger", nullptr);
		exit(0);
	}
	int player_process = fork();
	if (player_process == 0) {
		int player_out = open("player2judger.fifo", O_WRONLY);
		int player_in = open("judger2player.fifo", O_RDONLY);
		dup2(player_out, 1);
		dup2(player_in, 0);
		close(player_out);
		close(player_in);
		setTimeLimit(time_limit);
		setMemoryLimit(memory_limit);

		bootBin(lang, file);
		exit(0);
	}
	int player_stat, judger_stat;

	retcode ret_runtime = monitorPlayerTimeMemory(lang, player_process);
	if (ret_runtime == MLE || ret_runtime == TLE)return ret_runtime;

	waitpid(player_process, &player_stat, 0);
	waitpid(judger_process, &judger_stat, 0);
	switch (verdict(judger_stat, player_stat)) {
	case ACCEPTED:
		res["score"] += 100;
		return ACCEPTED;
	case WA: return WA;
	case RE: return RE;
	case JUDGE_ERROR:
		printf("judger crashed\n");
		exit(JUDGE_ERROR);
	}
}

retcode judge(langtype lang, string file) {
	config = fparse("config");
	score_per_test = atoi(config["score_per_test"].c_str());
	if (score_per_test == 0)score_per_test = 10;
	mkfifo("judger2player.fifo", 0644);
	mkfifo("player2judger.fifo", 0644);

	if (config["judge_type"] == "normal")
		return normalJudge(lang, file);
	if (config["judge_type"] == "special")
		return specialJudge(lang, file);
	if (config["judge_type"] == "interactive")
		return interactiveJudge(lang, file);
}
