#include"Language.h"
#include"Judge.h"
#include"toolkit.h"
#include<queue>
#include<cstring>
using namespace std;
queue<int>pipelist;
queue<string>result;
LanguageManager lang_pool;
char task_buffer[8192];
int main() {
	if (isWorkDir() == 0)return 0;////////////
	///////////////read configuration/////////
	FILE *pLang = fopen("support_lang", "r");
	string lang_config; int len = 0;
	while (fgets(task_buffer, 4096, pLang))
		lang_config += task_buffer;
	
	parseLanguage(lang_config);

	///////////////apocalypse/////////////////
	if (access("judger_in.fifo", 0) == ENOENT)
		mkfifo("judger_in.fifo", 777);

	FILE *ear; int pipe_line[2];
	while (1) {
		ear = fopen("judger_in.fifo", "r");
		while (fgets(task_buffer, 8192, ear)) {//hang up
			pipe(pipe_line);
			int proc = fork();
			if (proc == 0) {
				Task new_task = parseTask(task_buffer); Judge high;
				high.judge(new_task); memset(task_buffer, 0, sizeof task_buffer);
				sprintf(task_buffer, "%d %d %d %s", high.status, high.score, high.memory_usage, high.time_usage, high.compiler_info);
				write(pipe_line[1], task_buffer, 2048);
				return 0;
			}
			pipelist.push(pipe_line[0]);
			while (read(pipelist.front(), task_buffer, 2048)) {
				result.push(task_buffer);
				pipelist.pop();
			}
		}
	}
}