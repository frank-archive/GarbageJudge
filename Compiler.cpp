#include"Compiler.h"
#include<regex>
using namespace std;
bool isCompileError(langtype lang, string message) {
	if (regex_search(message, regex(match_compile_error[lang])))
		return true;
	return false;
}

retcode compile(langtype lang, std::string filename) {
	int pid = fork();

	if (pid == 0) {
		freopen("compile_message", "w", stderr);
		freopen("compile_message", "w", stdout);

		long long time_limit = (lang == JAVA ? 30 : 10);
		setTimeLimit(time_limit);
		setCreateFileSizeLimit(40 * 1024);

		if (lang == NOT_SUPPORTED || compile_commands[lang].size() == 0) {
			printf("language not supported");
			exit(0);
		}
		string output_name = filename.substr(filename.find('.') + 1);
		vsystem(compile_commands[lang].c_str(), filename.c_str(), output_name.c_str());
		exit(0);
	}
	else {
		int status = 0;
		waitpid(pid, &status, 0);

		FILE *compile_message = fopen("compile_message", "r");
		char buffer[2048]; std::string cm;
		while (fgets(buffer, 2048, compile_message))cm += buffer;
		fclose(compile_message);
		if (isCompileError(lang, cm)) {
			compile_error = cm;
			return CE;
		}
		if (WIFSIGNALED(status) && WTERMSIG(status) == SIGKILL) {
			compile_error = "compilation time exceeded\n";
			return CE;
		}
		return ACCEPTED;
	}
}