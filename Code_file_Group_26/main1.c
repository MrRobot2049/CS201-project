#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <ctype.h>

int main() {
    printf("Running Test Cases....\n\n");

    printf("--------------------  Working on DNA files in .txt format  --------------------\n");

    printf("Testcase - 1:\n");
    findAndCompressPalindromes("testcase1.txt", "Compressed_file_1.txt");
    Decompress("Compressed_file_1.txt");
    compare_files("testcase1.txt", "Decompressed_file_1.txt");
    percent_compression("Compressed_file_1.txt", "Decompressed_file_1.txt");

    return 0;
}

