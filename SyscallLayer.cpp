#include "SyscallLayer.h"

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

std::map<std::string, std::string> fparse(std::string file) {
	std::map<std::string, std::string>ret;
	FILE *f = fopen(file.c_str(), "r");
	char buffer[2048]; file = "";
	while (fgets(buffer, 2048, f)) {
		int temp = std::string(buffer).find(":");
		if (temp == -1) {
			printf("parse configuration error\n");
			exit(PROBLEM_SETTING_INVALID);
		}
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

int getProc(int pid, std::string target) {
	char path[1024]; int ret;
	sprintf(path, "/proc/%d/status", pid);
	FILE *p_status = fopen(path, "r");
	if (p_status == 0)return 0;
	while (fgets(path, 1024, p_status))
		if (std::string(path).find(target) != -1) {
			sscanf(path + target.size() + 1, "%d", &ret);
			break;
		}

	fclose(p_status); return ret;
}

int vsystem(const char * fmt, ...) {
	char comm[4096];
	va_list list;
	va_start(list, fmt);
	vsprintf(comm, fmt, list);
	va_end(list);
	return system(comm);
}
