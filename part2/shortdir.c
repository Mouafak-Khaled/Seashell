#include <stdio.h>
#include <string.h>
#include<unistd.h>
#include <stdlib.h>


void printList(FILE *pFile) {
    char c = fgetc(pFile);
    while (c != EOF) {
        printf("%c", c);
        c = fgetc(pFile);
    }
}

void pwd() {
    char buf[100];
    getcwd(buf, 100);
    printf("%s\n", buf);
}

void del(char *name, FILE *r, char path[258], char tmp[258]) {
    FILE *temp = fopen(tmp, "a");
    char *in;
    size_t len = 0;
    while (getline(&in, &len, r) != -1) {
        char *pch = strtok(in, " ");
        if (strcmp(pch, name) != 0) {
            fprintf(temp, "%s ", pch);
            fprintf(temp, "%s", strtok(NULL, " "));
        }
    }
    remove(path);
    rename(tmp, path);
    fflush(temp);
}

void setDir(char *name, FILE *r, char path[258], char tmp[258]) {
    char dir[100];
    getcwd(dir, 100);
    del(name, r, path, tmp);
    FILE *a = fopen(path, "a");
    fprintf(a, "%s %s\n", name, dir);
    fflush(a);
}

void jump(char *name, FILE *r) {
    char *in;
    char *a;
    char *pch;
    size_t len = 0;
    int alias = 0;
    while (getline(&in, &len, r) != -1) {
        pch = strtok(in, " ");
        if (strcmp(pch, name) == 0) {
            printf("old directory: "), pwd();
            a = strtok(NULL, " ");
            a[strlen(a) - 1] = 0;
            chdir(a);
            printf("moved to: "), pwd();
            alias = 1;
            break;
        }
    }
    if (alias == 0) {
        chdir(name);
        printf("moved to: "), pwd();
    }

}

int main(int argc, char *argv[]) {
    char path[258];
    strcpy(path, getenv("HOME"));
    strcat(path, "/Documents/paths.txt");

    char tmp[258];
    strcpy(tmp, getenv("HOME"));
    strcat(tmp, "/Documents/tmp.txt");

    FILE *a = fopen(path, "a");
    FILE *r = fopen(path, "r");


    if (argc < 2) { printf("Arguments expected.\n"); }
    else {
        if (strcmp("set", argv[1]) == 0) {
            if (argv[2] == NULL) printf("Arguments expected.\n");
            else setDir(argv[2], r, path, tmp);
        } else if (strcmp("jump", argv[1]) == 0) {
            if (argv[2] == NULL) printf("Arguments expected.\n");
            else jump(argv[2], r);
        } else if (strcmp("del", argv[1]) == 0) {
            if (argv[2] == NULL) printf("Arguments expected.\n");
            else del(argv[2], r, path, tmp);
        } else if (strcmp("clear", argv[1]) == 0) fclose(fopen(path, "w"));
        else if (strcmp("list", argv[1]) == 0) printList(r);
        else printf("Not a valid argument\n");
    }
    fflush(a), fflush(r), fclose(r), fclose(a);

    return 0;
}







