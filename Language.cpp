#include "Language.h"

void LanguageManager::support(std::string suffix, std::string name, std::string command, std::string error_mark, unsigned long timeout, int multiplier, bool is_use_vm) {
	pool[name] = { suffix,command,error_mark,timeout,multiplier,is_use_vm };
}

LanguageManager::Language & LanguageManager::operator[](std::string name) {
	return pool[name];
}

bool LanguageManager::isSupported(std::string name) {
	if(pool.find(name)==pool.end())return false;
	return true;
}
