#include <stdio.h>
#include"header.h"

float compare_files(const char *file1, const char *file2) {
    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");

    if (f1 == NULL || f2 == NULL) {
        perror("Error opening files");
        return -1.0;
    }

    int char1, char2;
    int total_chars = 0;
    int matching_chars = 0;

    // Read both files character by character
    while ((char1 = fgetc(f1)) != EOF && (char2 = fgetc(f2)) != EOF) {
        total_chars++;
        if (char1 == char2) {
            matching_chars++;
        }
    }

    // If one file has extra characters, count them in total_chars
    while ((char1 = fgetc(f1)) != EOF) total_chars++;
    while ((char2 = fgetc(f2)) != EOF) total_chars++;

    fclose(f1);
    fclose(f2);

    // Calculate the match percentage
    
    float match_percentage = (total_chars > 0) ? ((matching_chars) / (float)total_chars) * 100 : 0.0;
    printf("Matching Percentage: %.0f%%\n", match_percentage);
    return match_percentage;
}
