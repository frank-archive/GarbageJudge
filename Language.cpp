#include "Language.h"
#include"JsonParse.h"

void LanguageManager::support(std::string name, std::string suffix, std::string command, std::string error_mark, unsigned long timeout, std::string run_command, int multiplier, bool is_use_vm) {
	pool[name] = { suffix,command,error_mark,timeout,run_command,multiplier,is_use_vm };
}

LanguageManager::Language & LanguageManager::operator[](std::string name) {
	return pool[name];
}

bool LanguageManager::isSupported(std::string name) {
	if(pool.find(name)==pool.end())return false;
	return true;
}

LanguageManager parseLanguage(std::string json_ex) {
	json_ex += "     ";
	LanguageManager ret;
	while (json_ex.find('}')) {
		JSON a_language = JsonParse(json_ex);
		ret.support(
			a_language["name"].asString(),
			a_language["suffix"].asString(),
			a_language["compile_command"].asString(),
			a_language["compile_error_mark"].asString(),
			a_language["compile_timeout"].asInteger(),
			a_language["run_command"].asString(),
			a_language["time_bonus_multiplier"].asInteger(),
			a_language["is_use_vm"].asBool()
		);
		json_ex = json_ex.substr(json_ex.find('}') + 1);
	}
}
