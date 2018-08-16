#include"Language.h"
#include"Judge.h"
#include"toolkit.h"
#include<queue>
using namespace std;
queue<Judge*>joblist;
LanguageManager lang_pool;
int main() {
	if (access("judger_in.fifo", 0) == ENOENT)
		mkfifo("judger_in.fifo", 777);

	FILE *ear; char task_buffer[8192];
	while (1) {
		ear = fopen("judger_in.fifo", "r");
		while (fgets(task_buffer, 8192, ear)) {//hang up
			Task new_task = parse(task_buffer);
			Judge *wish_you_AC = new Judge();
			
		}
	}
}