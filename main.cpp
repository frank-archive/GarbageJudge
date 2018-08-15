#include<string>
#include<map>
#include"SyscallLayer.h"
#include"EnumDef.h"
#include"Compiler.h"
#include"Judger.h"
using namespace std;
string code_path;

void help() {
	printf("judger [code_path] [mem_limit(kb)] [time_limit(ms)] <workdir>\n");
	printf("or you can put a zip file called \"problem.zip\" and a \"code.*\" file to proceed\n");
}

//////////////////////////////////////////////////////////////////////////////
bool argsCheck(int argc, char **argv) {
	if (argc < 5) {
		help();
		return 1;
	}
	if (access(argv[1], 0) == ENOENT) {
		printf("error code path\n");
		return 1;
	}
	if (access(argv[4], 0) == ENOENT) {
		printf("error problem package path\n");
		return 1;
	}
	if (argc > 5 && chdir(argv[5]) == -1) {
		printf("invalid workdir");
		return 1;
	}
	code_path = argv[1];
	string package_path = argv[2];
	execl("/bin/cp", "cp", code_path.c_str(), ".", nullptr);
	execl("/bin/cp", "cp", package_path.c_str(), ".", nullptr);
	while (package_path.find("/"))
		package_path = package_path.substr(package_path.find("/"));
	execl("unzip", "unzip", package_path.c_str());
	return 0;
}
bool selfCheck() {
	if (access("problem.zip", 0) == ENOENT)return 1;
	if (
		access("code.cpp", 0) == ENOENT && 
		access("code.java", 0) == ENOENT
	)return 1;/////////////////////remember to edit here when patching
	execl("unzip", "unzip", "problem");
	return 0;
}
int main(int argc,char **argv) {
	if (argc > 1) {
		if (argsCheck(argc, argv)) {
			help();
			return -1;
		}
	}
	else if (selfCheck()) {
		help();
		return -1;
	}
	
	int temp = 0;
	while (temp = code_path.find('/') != -1)
		code_path = code_path.substr(temp);
	langtype lang = tellType(code_path);
	if (compile(lang, code_path) == CE) {
		printf(compile_error.c_str());
		return CE;
	}
	code_path = code_path.substr(0, code_path.find('.'));
	retcode result = judge(lang, code_path);
	
	return result;
}