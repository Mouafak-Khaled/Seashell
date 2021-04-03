#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    if (argc < 3) printf("no valid arguments!\n");
    else {
        if (strcmp(argv[1], "-a") == 0 || strcmp(argv[1], "-b") != 0) { //as text files
            int i = strcmp(argv[1], "-a") == 0 ? 0 : -1;
            FILE *file1 = fopen(argv[i + 2], "r");
            FILE *file2 = fopen(argv[i + 3], "r");
            int diffCount = 0;

            char *file1line, *file2line;
            size_t len1 = 0, len2 = 0;

            while (getline(&file1line, &len1, file1) != -1) {
                if (getline(&file2line, &len2, file2) == -1) {
                    diffCount++, printf("%s", file1line);
                    break;
                }
                if (strcmp(file1line, file2line) == 0) continue;
                diffCount++, printf("%s", file2line);
            }

            while (getline(&file1line, &len1, file1) != -1) diffCount++, printf("%s", file1line);
            while (getline(&file2line, &len2, file2) != -1) diffCount++, printf("%s", file2line);

            if (diffCount == 0) printf("The two text files are identical\n");
            else printf("\n%d different lines found\n", diffCount);

            fclose(file1), fclose(file2);
        } else if (strcmp(argv[1], "-b") == 0) { //as text files
            if (strcmp(argv[2], argv[3]) == 0) {
                printf("The two files are identical\n");
                exit(0);
            }

            FILE *file1 = fopen(argv[2], "rb"), *file2 = fopen(argv[3], "rb");
            long bitDiff = 0;
            int c1, c2;

            while (1) {
                c1 = getc(file1), c2 = getc(file2);
                if (c2 == EOF || c1 == EOF) break;
                for (int i = 7; i >= 0; i--) if (c1 >> i & c2 >> i) bitDiff++;
            }
            if (c1 == EOF) while (c2 != EOF) bitDiff += 7, c2 = getc(file2);
            else if (c2 == EOF) while (c1 != EOF) bitDiff += 7, c1 = getc(file2);
            printf("The two files are different in %ld bytes\n", bitDiff);

        }

    }
    return 0;
}
