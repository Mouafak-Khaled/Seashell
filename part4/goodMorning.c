#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc <= 2) printf("no valid input!\n");
    else {
        FILE *j = fopen("job", "w");
        char *hours = strtok(argv[1], ".");
        char *min = strtok(NULL, ".");
        fprintf(j, "%s %s * * * DISPLAY=:0.0 rhythmbox-client --play %s\n", min, hours, argv[2]);
        fclose(j);
        execlp("crontab", "crontab", "job", (char *) NULL);
    }

    return 0;
}
