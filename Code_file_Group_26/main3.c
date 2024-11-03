#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <ctype.h>

int main() {
    printf("Running Test Cases....\n\n");

    printf("--------------------  Working on DNA files in .txt format  --------------------\n");

    printf("Testcase - 3:\n");
    findAndCompressPalindromes("testcase3.txt", "Compressed_file_3.txt");
    Decompress("Compressed_file_3.txt");
    compare_files("testcase3.txt", "Decompressed_file_3.txt");
    percent_compression("Compressed_file_3.txt", "Decompressed_file_3.txt");

    return 0;
}

