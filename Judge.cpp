#include"Judge.h"
#include"toolkit.h"

#include"Language.h"
#include"Problem.h"
#include"Compiler.h"

extern LanguageManager lang_pool;
using namespace std;

ProcStatus Judge::judge(Task task) {
	if (lang_pool.isSupported(task.lang) == false)
		return LANG_NO_SUPPORT;
	if (access(to_string(task.problem_id).c_str(), 0) == ENOENT)
		return PROB_NO_FOUND;
	Problem *config = readProblemConfig();
	enterDir(to_string(task.submission_id));
	////////////////COMPILE//////////////////////
	Compiler comp(task);
	if (comp.getStatus().success == false) {
		status = CE;
		compiler_info = comp.getStatus().message;
		time_usage = 0, memory_usage = 0, score = 0;
		return CE;
	}
	/////////////////RUN/////////////////////////
	
}
