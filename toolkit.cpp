#include"toolkit.h"
#include<unistd.h>

bool isWorkDir() {///////////////////可能修改
	if (access("workdir", 0) != ENOENT)return true;
	return false;
}
void enterDir(std::string dir) {
	if (access(dir.c_str(), 00) == ENOENT)
		execl("/bin/mkdir", "mkdir", dir.c_str());
	chdir(dir.c_str());
}

std::string trim(std::string c) {
	int start = 0, end;
	while (isspace(c[start]))
		start++;
	end = start;
	while (!isspace(c[end]))
		end++;
	return c.substr(start, end - start);
}
std::unordered_map<std::string, std::string> parseYamlFile(std::string file) {
	std::unordered_map<std::string, std::string>ret;
	FILE *f = fopen(file.c_str(), "r");
	char buffer[2048]; file = "";
	while (fgets(buffer, 2048, f)) {
		int temp = std::string(buffer).find(":");
		if (temp == -1)continue;
		ret[trim(std::string(buffer).substr(0, temp - 1).c_str())] =
			trim(std::string(buffer).substr(temp).c_str());
	}
	fclose(f);
}

void setTimeLimit(int seconds) {
	rlimit LIM; LIM.rlim_cur = LIM.rlim_max = seconds;
	setrlimit(RLIMIT_CPU, &LIM);
}

void setMemoryLimit(long long kilobytes) {
	rlimit LIM; LIM.rlim_cur = LIM.rlim_max = kilobytes * 1024;
	setrlimit(RLIMIT_DATA, &LIM);
}
void setCreateFileSizeLimit(long long kilobytes) {
	rlimit LIM; LIM.rlim_cur = LIM.rlim_max = kilobytes * 1024;
	setrlimit(RLIMIT_FSIZE, &LIM);
}

int getMemoryPeak(int proc_id, bool is_page) {
	if (!is_page) {
		char path[1024]; int ret;
		sprintf(path, "/proc/%d/status", proc_id);
		FILE *p_status = fopen(path, "r");
		if (p_status == 0)return 0;
		while (fgets(path, 1024, p_status))
			if (std::string(path).find("VmPeak:") != -1) {
				sscanf(path + 8, "%d", &ret);
				break;
			}

		fclose(p_status); return ret;
	}
}

ProcStatus watchSubProcess(int proc_id, bool is_use_vm, Usage * ret, int time_limit, int memory_limit) {
	if (time_limit == 0 || time_limit > 300)time_limit = 300;//最大实际资源限制
	if (memory_limit == 0 || memory_limit > 1024 * 30)memory_limit = 1024 * 30;
	int status; rusage ruse; ProcStatus fin_status = AC;
	alarm(time_limit);
	while (1) {
		ret->mem_used = getMemoryPeak(proc_id, is_use_vm);
		if (ret->mem_used > memory_limit)
			kill(proc_id, SIGSEGV);

		wait4(proc_id, &status, __WALL, &ruse);

		if (WIFEXITED(status))break;
		if (WIFSIGNALED(status)) {
			switch (WEXITSTATUS(status)) {
			case SIGSEGV:
				fin_status = MLE;
				break;
			case SIGALRM:
				alarm(0);
			case SIGXCPU:
			case SIGKILL:
				fin_status = TLE;
				break;
			default:
				fin_status = RE;
				break;
			}
			break;
		}
	}
	ret->time_passed = ruse.ru_utime.tv_usec;
	return fin_status;
}
