#include <stdio.h>
#include <ctype.h>
#include"header.h"
int counter(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error opening file: %s\n", filename);
        return -1;
    }

    int count = 0;
    char ch;
    while ((ch = fgetc(file)) != EOF) {
        if (isalpha(ch)) {
            count++;
        }
    }
    fclose(file);
    return count;
}

void percent_compression(const char *compressed_file, const char *decompressed_file) {
    int compressed_count = counter(compressed_file);
    int decompressed_count = counter(decompressed_file);

    if (compressed_count == -1 || decompressed_count == -1 || decompressed_count == 0) {
        printf("Error in file reading or decompressed file has zero alphabet characters.\n");
        return;
    }

    double percent = (100 - ((double)compressed_count / decompressed_count) * 100.0)*(100/50);
    printf("Compression Percentage: %.2f%%\n", percent);
}


