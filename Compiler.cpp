#include "Compiler.h"
#include"toolkit.h"

#include"Language.h"

extern LanguageManager lang_pool;

static const std::string base64_chars =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";
static bool is_base64(unsigned char c) {
	return (isalnum(c) || (c == '+') || (c == '/'));
}
std::string decode(std::string encoded_string) {
	int in_len = encoded_string.size();
	int i = 0, in_ = 0;unsigned char char_array_4[4], char_array_3[3];std::string ret;
	while (in_len-- && (encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
	char_array_4[i++] = encoded_string[in_++];
	if (i == 4) {for (i = 0; i < 4; i++)char_array_4[i] = base64_chars.find(char_array_4[i]);
	char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
	char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
	char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
	for (i = 0; i < 3; i++)ret += char_array_3[i];i = 0;}}
	if (i) {for (int j = i; j <4; j++)char_array_4[j] = 0;
	for (int j = 0; j <4; j++)char_array_4[j] = base64_chars.find(char_array_4[j]);
	char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
	char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
	char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
	for (int j = 0; (j < i - 1); j++) ret += char_array_3[j];}return ret;
}

Compiler::Compiler(Task unc) {
	std::string code_decoded = decode(unc.code_based);
	std::string source_filename = ("Main." + lang_pool[unc.lang].suffix).c_str();
	FILE *pPlayer = fopen(source_filename.c_str(), "w");
	fprintf(pPlayer, "%s", code_decoded.c_str());

	int proc = fork();
	if (proc == 0) {
		freopen("compile_message.txt", "w", stdout);
		freopen("compile_message.txt", "w", stderr);
		setTimeLimit(lang_pool[unc.lang].compile_timeout);
		char cmd[1024]; memset(cmd, 0, sizeof cmd);
		sprintf(cmd, lang_pool[unc.lang].compile_command.c_str(),
			source_filename, "Main");
		int ret = system(cmd);
		exit(0);
	}
	Usage fin;
	ProcStatus ret = watchSubProcess(proc, 0, &fin, lang_pool[unc.lang].compile_timeout);
	FILE *compile_message = fopen("compile_message.txt", "r"); char buffer[1024];
	while (fgets(buffer, 1024, compile_message))status.message += buffer;
	if (ret != AC||
		std::regex_search(status.message,std::regex(lang_pool[unc.lang].compile_error_mark))) {
		status.success = false;
	}
	else status.success = true;
}

Compiler::CompileStatus Compiler::getStatus() {
	return status;
}
