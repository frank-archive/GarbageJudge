#pragma once
#include"toolkit.h"

class LanguageManager {
	struct Language {
		std::string suffix;
		std::string compile_command;
		std::string compile_error_mark;//regex
		unsigned long compile_timeout;

		std::string run_command;
		int time_bonus_multiplier;
		bool is_use_vm;//if true, consider using page size to determine memory usage
	};
	std::unordered_map<std::string, Language>pool;

public:
	void support(//adds a new language
		std::string name,
		std::string suffix,
		std::string command,
		std::string error_mark,
		unsigned long timeout,
		std::string run_command,
		int multiplier = 1,
		bool is_use_vm = false
	);
	Language &operator[](std::string name);
	bool isSupported(std::string name);
};
LanguageManager parseLanguage(std::string json_ex);