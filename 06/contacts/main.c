#include <stdio.h>
#include <string.h>
#include "contacts.h"

// Stolen from module 04 mystr library hehe
static size_t my_split(char* s, char sep, char* parts[], size_t max_parts) {
    /* it's like strtok() but better */

    char* start = s;
    char* p = start;
    size_t n = 0;
    while (*p) {
        if (*p == sep) {
            if (n < max_parts) {
                *p = '\0';
                parts[n] = start;
                n += 1;
                start = p + 1;                
            } else { break; }
        }
        p++;
    }
    if (n < max_parts) {
        parts[n] = start;
        n++;
    }
    return n;
}

static void execute_add(Contacts* c, char* args) {
    char* arr[3];
    if (my_split(args, ',', arr, 3) != 3) {
        printf("Missing or malformed argument(s), try again.\n");
    }
    int num;
    if (sscanf(arr[2], "%d", &num) != 1) {
        printf("Missing or malformed argument(s), try again.\n");
    } else {
        Contact con;
        if (strlen(arr[0]) > 24 || strlen(arr[1]) > 74) {
            printf("Missing or malformed argument(s), try again.\n");
        }
        strcpy(con.name, arr[0]);
        strcpy(con.email, arr[1]);
        con.age = num;
        con_push(c, &con);  
    }
}

static void execute_del(Contacts* c, char* args) {
    int idx;
    if (sscanf(args, "%d", &idx) == 1) {
        con_delete(c, idx);    
    } else {
        printf("Missing or malformed arguments, try again.\n");
    }
    
}

static void execute_find(Contacts* c, char* args) {
    Contact* con = con_find(c, args);
    if (con != NULL) {
        printf("%s,%s,%d", con->name, con->email, con->age);
    } else {
        printf("Missing or malformed arguments (too long?), try again.\n");
    }
}

static void execute_list(Contacts* c) {
    for (size_t i = 0; i < con_len(c); i++) {
        Contact* con = con_get(c, i);
        printf("%zu: %s,%s,%d\n", i, con->name, con->email, con->age);
    }
}

static void execute_quit() {
    
}

int main(void) {
    char line[128];
    printf("> ");

    // READING FROM FILE/CONTACTS INIT GOES HERE!
    
    while (fgets(line, sizeof line, stdin) != NULL) {
        line[strcspn(line, "\n")] = '\0';
        char* split_result = strchr(line, ' ');
        if (split_result != NULL) { 
            // command is add or del or find
            split_result[0] = '\0';
            char* args = &split_result[1];
            if (strcmp(line, "add") == 0) {
                execute_add(c, args);
            } else if (strcmp(line, "del") == 0) {
                execute_del(c, args);
            } else if (strcmp(line, "find") == 0) {
                execute_find(c, args);
            }
        }
        // command is list or quit
        if (strcmp(line, "list") == 0) {
            execute_list(c);
        } else if (strcmp(line, "quit") == 0) {
            execute_quit();
        } else {
            printf("Unrecognized command. Try again.\n");
        }
        printf("> ");
    }
    execute_quit();
}
