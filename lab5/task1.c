#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <linux/limits.h>
#include <unistd.h>
#include "LineParser.h"
#include <sys/types.h>
#include <sys/wait.h>

cmdLine* cmdList = NULL;

int main(int argc, char** argv) {
    char current_path[PATH_MAX];
    char user_input[2048];
    struct cmdLine* line;
    int PID;
    int debug = 0;
    if (argc > 1 && strcmp(argv[1], "-d") == 0)
        debug = 1;
    while (1){
        getcwd(current_path,PATH_MAX);
        printf("%s$", current_path);
        fgets(user_input, 2048, stdin);
        line = parseCmdLines(user_input);
        if (cmdList == NULL) {
            cmdList = line;
        }
        if (strcmp(line->arguments[0], "quit") == 0) {
            freeCmdLines(line);
            exit(1);
        } else if (strcmp(line->arguments[0],"cd") == 0) {
            char *newPath = line->arguments[1];
            int chdirSucc = chdir(newPath);
        } else {
            PID = execute(line);
            if (debug == 1)
                printf("PID: %d, Executing command: %s\n", PID, line->arguments[0]);
        }
        freeCmdLines(cmdList);
    }
    return 0;
}

int execute(cmdLine *pCmdLine) {
    int childPro = fork();
    if (childPro == 0){
        int return_val = execvp(pCmdLine->arguments[0],pCmdLine->arguments);
        if (return_val == -1) {
            perror("execv failed");
            freeCmdLines(pCmdLine);
            exit(1);
        }  
    } else if (childPro == -1) {
        perror("fork failed");
        exit(1);
    } else if (pCmdLine->blocking == 1) {
        if(waitpid(childPro, NULL, 0) == -1) {
            perror("waitpid error");
            exit(1);
        }
    }
    return childPro;
}
