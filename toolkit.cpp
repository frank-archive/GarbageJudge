#include"toolkit.h"
#include<unistd.h>

bool isWorkDir() {///////////////////¿ÉÄÜÐÞ¸Ä
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
