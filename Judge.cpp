#include"Judge.h"
#include"toolkit.h"

#include"Language.h"
#include"Problem.h"

extern LanguageManager lang_pool;
using namespace std;

JudgeStatus Judge::judge(Task task) {
	if (lang_pool.isSupported(task.lang) == false)
		return LANG_NO_SUPPORT;
	if (access(to_string(task.problem_id).c_str(), 0) == ENOENT)
		return PROB_NO_FOUND;

	Problem *config = readProblemConfig();
	enterDir(to_string(task.submission_id));

}
