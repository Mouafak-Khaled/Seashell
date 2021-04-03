#include <stdio.h>
#include <string.h>
#include<unistd.h>

void pwd() {
    char buf[100];
    getcwd(buf, 100);
    printf("%s\n", buf);
}

void printList(FILE *pFile) {
    char c = fgetc(pFile);
    while (c != EOF) {
        printf("%c", c);
        c = fgetc(pFile);
    }
}

void del(char *name, FILE *r) {
    FILE *temp = fopen("tmp.txt", "a");
    char *in;
    size_t len = 0;
    while (getline(&in, &len, r) != -1) {
        char *pch = strtok(in, " ");
        if (strcmp(pch, name) != 0) {
            fprintf(temp, "%s ", pch);
            fprintf(temp, "%s", strtok(NULL, " "));
        }
    }
    remove("list.txt");
    rename("tmp.txt", "list.txt");
    fflush(temp);
}

void setDir(char *name, FILE *r) {
    char dir[100];
    getcwd(dir, 100);
    del(name, r);
    FILE *a = fopen("list.txt", "a");
    fprintf(a, "%s %s\n", name, dir);
    fflush(a);
}

void jump(char *name, FILE *r) {
    char *in;
    size_t len = 0;
    while (getline(&in, &len, r) != -1) {
        char *pch = strtok(in, " ");
        if (strcmp(pch, name) == 0) {
            printf("old directory: "), pwd();
            char* a = strtok(NULL, " ");
            a[strlen(a) - 1] = 0;
            chdir(a);
            printf("moved to: "), pwd();
            break;
        }
    }
}

int main2(int argc, char *argv[]) {
    FILE *a = fopen("list.txt", "a");
    FILE *r = fopen("list.txt", "r");

    if (argc < 2) { printf("Arguments expected.\n"); }
    else if (argc == 2) {
        if (strcmp("pwd", argv[1]) == 0) pwd();
        else printf("Not a valid argument\n");
    } else {
        if (strcmp("shortdir", argv[1]) == 0)
            if (strcmp("set", argv[2]) == 0) setDir(argv[3], r);
            else if (strcmp("jump", argv[2]) == 0) jump(argv[3], r);
            else if (strcmp("del", argv[2]) == 0) del(argv[3], r);
            else if (strcmp("clear", argv[2]) == 0) fclose(fopen("list.txt", "w"));
            else if (strcmp("list", argv[2]) == 0) printList(r);
            else printf("Not a valid argument\n");
        else printf("Not a valid argument\n");
    }

    fflush(a), fflush(r), fclose(r), fclose(a);

    return 0;
}







