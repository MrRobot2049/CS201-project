#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h"

int main() {
    printf("\n\n--------------------  Working on music files in .mp3 format  --------------------\n\n");

    printf("Testcase - 6:\n");
    // music_notes_converter("testcase3.mp3");
    findAndCompressPalindromes("Music_Note_3.txt", "Compressed_file_6.txt");
    Decompress("Compressed_file_6.txt");
    compare_files("Music_Note_3.txt", "Decompressed_file_6.txt");
    percent_compression("Compressed_file_6.txt", "Decompressed_file_6.txt");

    return 0;
}

