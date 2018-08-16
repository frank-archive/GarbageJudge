#include "Task.h"
#include"JsonParse.h"

Task parseTask(std::string json) {
	JSON task=JsonParse(json); Task ret;
	ret.lang = task["lang"].asString();
	ret.code_based = task["code"].asString();
	ret.problem_id = task["problem_id"].asInteger();
	ret.submission_id = task["submission_id"].asInteger();
	return ret;
}
