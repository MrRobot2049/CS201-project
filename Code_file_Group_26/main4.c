#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "header.h"

int main() {
    printf("\n\n--------------------  Working on music files in .mp3 format  --------------------\n\n");

    printf("Testcase - 4:\n");
   //  music_notes_converter("testcase2.mp3");
    findAndCompressPalindromes("Music_Note_1.txt", "Compressed_file_4.txt");
    Decompress("Compressed_file_4.txt");
    compare_files("Music_Note_1.txt", "Decompressed_file_4.txt");
    percent_compression("Compressed_file_4.txt", "Decompressed_file_4.txt");

    return 0;
}

