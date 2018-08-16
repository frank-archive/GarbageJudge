#include"Problem.h"

using namespace std;
Problem *readProblemConfig(std::string configfile_path) {
	if (access(configfile_path.c_str(), 0) == ENOENT) {
		printf("[error]:in readProblemConfig(string):problem path invalid\n");
		return nullptr;
	}
	Problem *ret = new Problem();
	unordered_map<string, string>parsed = parseYamlFile(configfile_path);
	if (parsed["type"] == "normal")ret->type = normal;
	else if (parsed["type"] == "special")ret->type = special;
	else if (parsed["type"] == "interactive")ret->type = interactive;

	if ((ret->memory_limit = atoi(parsed["memory_limit"].c_str())) == 0) {
		printf("[error]:in readProblemConfig(string):mem limit not specified\n");
		return nullptr;
	}
	if ((ret->time_limit = atoi(parsed["time_limit"].c_str())) == 0) {
		printf("[error]:in readProblemConfig(string):time_limit not specified\n");
		return nullptr;
	}
	if (ret->type != interactive &&
		(ret->score_per_cases = atoi(parsed["sore_per_case"].c_str())) == 0) {
		printf(
			"[warning]:in readProblemConfig(string):score_per_case not specified, using default:10\n"
		);
		ret->score_per_cases = 10;
	}
	if (ret->type != interactive &&
		(ret->test_cases = atoi(parsed["test_cases"].c_str())) == 0) {
		printf(
			"[warning]:in readProblemConfig(string):test_cases not specified, using default: 10\n"
		);
		ret->test_cases = 10;
	}
	ret->isSet = true;
}
