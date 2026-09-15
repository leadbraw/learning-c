#include <stdio.h>
#include <string.h>
#include "contacts.c"

static void execute_add(char* args) {
    
}

static void execute_del(char* args) {
    
}

static void execute_find(char* args) {
    
}

static void execute_list() {
    
}

static void execute_quit() {
    
}

int main(void) {
    printf("> ");

    char line[128];
    while (fgets(line, sizeof line, stdin) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        char* split_result = strchr(line, ' ');
        if (split_result != NULL) { 
            // command is add or del or find
            split_result[0] = '\0';
            char* args = &split_result[1];
            if (strcmp(line, "add") == 0) {
                execute_add(args);
            } else if (strcmp(line, "del") == 0) {
                execute_del(args);
            } else if (strcmp(line, "find") == 0) {
                execute_find(args);
            }
        }
        // command is list or quit
        if (strcmp(line, "list") == 0) {
            execute_list();
        } else if (strcmp(line, "quit") == 0) {
            execute_quit();
        }
    }
}
