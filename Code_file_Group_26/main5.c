#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h"

int main() {
    printf("\n\n--------------------  Working on music files in .mp3 format  --------------------\n\n");

    printf("Testcase - 5:\n");
 
    findAndCompressPalindromes("Music_Note_2.txt", "Compressed_file_5.txt");
    Decompress("Compressed_file_5.txt");
    compare_files("Music_Note_2.txt", "Decompressed_file_5.txt");
    percent_compression("Compressed_file_5.txt", "Decompressed_file_5.txt");

    return 0;
}

