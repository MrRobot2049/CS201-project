#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <ctype.h>

int main() {
    printf("Running Test Cases....\n\n");

    printf("--------------------  Working on DNA files in .txt format  --------------------\n");

    printf("Testcase - 2:\n");
    findAndCompressPalindromes("testcase2.txt", "Compressed_file_2.txt");
    Decompress("Compressed_file_2.txt");
    compare_files("testcase2.txt", "Decompressed_file_2.txt");
    percent_compression("Compressed_file_2.txt", "Decompressed_file_2.txt");

    return 0;
}

