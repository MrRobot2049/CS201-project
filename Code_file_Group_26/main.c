#include<stdio.h>
#include<stdlib.h>
#include"header.h"
#include<ctype.h>
int main(){
	int count = 1;
	printf("Running Test Cases....\n\n");

	printf("--------------------  Working on DNA files in .txt format  --------------------\n");

	printf("Testcase - 1\n");
	findAndCompressPalindromes("testcase3.txt","Compressed_file_3.txt");
        Decompress("Compressed_file_3.txt");
        compare_files("testcase3.txt","Decompressed_file_3.txt");
        percent_compression("Compressed_file_3.txt","Decompressed_file_3.txt");
	
	/*printf("Testcase - 2\n");
	findAndCompressPalindromes("testcase2.txt","Compressed_file_2.txt");
        Decompress("Compressed_file_2.txt");
        compare_files("testcase2.txt","Decompressed_file_2.txt");
        percent_compression("Compressed_file_2.txt","Decompressed_file_2.txt");
	
	printf("Testcase - 3\n");
	findAndCompressPalindromes("testcase3.txt","Compressed_file_3.txt");
        Decompress("Compressed_file_3.txt");
        compare_files("testcase3.txt","Decompressed_file_3.txt");
        
	percent_compression("Compressed_file_3.txt","Decompressed_file_3.txt");*/
	/*printf("\n\n--------------------  Working on music files in .mp3 format  --------------------\n\n");
	
	printf("Testcase - 1\n");
	//music_notes_converter("testcase1.mp3");
	findAndCompressPalindromes("Music_Note_1.txt","Compressed_file_1.txt");
	Decompress("Compressed_file_1.txt");
	compare_files("Music_Note_1.txt","Decompressed_file_1.txt");
	percent_compression("Compressed_file_1.txt","Decompressed_file_1.txt");

	printf("\nTestcase - 2\n");
	music_notes_converter("testcase2.mp3");
        findAndCompressPalindromes("Music_Note_2.txt","Compressed_file_2.txt");
        Decompress("Compressed_file_2.txt");
        compare_files("Music_Note_2.txt","Decompressed_file_2.txt");
        percent_compression("Compressed_file_2.txt","Decompressed_file_2.txt");
	
	printf("\nTestcase - 3\n");
	music_notes_converter("testcase3.mp3");
        findAndCompressPalindromes("Music_Note_3.txt","Compressed_file_3.txt");
        Decompress("Compressed_file_3.txt");
        compare_files("Music_Note_3.txt","Decompressed_file_3.txt");
        percent_compression("Compressed_file_3.txt","Decompressed_file_3.txt");


	
	printf("\n\n--------------------  Working on music files in .txt format  --------------------\n");
	printf("\nTestcase - 4\n");
        music_notes_converter("testcase4.txt");
        findAndCompressPalindromes("Music_Note_4.txt","Compressed_file_4.txt");
        Decompress("Compressed_file_4.txt");
        compare_files("Music_Note_4.txt","Decompressed_file_4.txt");
        percent_compression("Compressed_file_4.txt","Decompressed_file_4.txt");
	
	printf("\nTestcase - 5\n");
        music_notes_converter("testcase5.txt");
        findAndCompressPalindromes("Music_Note_5.txt","Compressed_file_5.txt");
        Decompress("Compressed_file_5.txt");
        compare_files("Music_Note_5.txt","Decompressed_file_5.txt");
        percent_compression("Compressed_file_5.txt","Decompressed_file_5.txt");
	
	printf("\nTestcase - 6\n");
        music_notes_converter("testcase6.txt");
        findAndCompressPalindromes("Music_Note_6.txt","Compressed_file_6.txt");
        Decompress("Compressed_file_6.txt");
        compare_files("Music_Note_6.txt","Decompressed_file_6.txt");
        percent_compression("Compressed_file_6.txt","Decompressed_file_6.txt");
	
	printf("\nTestcase - 7\n");
        music_notes_converter("testcase7.txt");
        findAndCompressPalindromes("Music_Note_7.txt","Compressed_file_7.txt");
        Decompress("Compressed_file_7.txt");
        compare_files("Music_Note_7.txt","Decompressed_file_7.txt");
        percent_compression("Compressed_file_7.txt","Decompressed_file_7.txt");
	
	printf("\nTestcase - 8\n");
        music_notes_converter("testcase8.txt");
        findAndCompressPalindromes("Music_Note_8.txt","Compressed_file_8.txt");
        Decompress("Compressed_file_8.txt");
        compare_files("Music_Note_8.txt","Decompressed_file_8.txt");
        percent_compression("Compressed_file_8.txt","Decompressed_file_8.txt");

	printf("\n\n--------------------  Working on DNA files in .txt format  --------------------\n");
	
	        printf("\nTestcase - 9\n");
        music_notes_converter("testcase9.txt");
        findAndCompressPalindromes("Music_Note_9.txt","Compressed_file_9.txt");
        Decompress("Compressed_file_9.txt");
        compare_files("Music_Note_9.txt","Decompressed_file_9.txt");
        percent_compression("Compressed_file_9.txt","Decompressed_file_9.txt");

        printf("\nTestcase - 10\n");
        music_notes_converter("testcase10.txt");
        findAndCompressPalindromes("Music_Note_10.txt","Compressed_file_10.txt");
        Decompress("Compressed_file_10.txt");
        compare_files("Music_Note_10.txt","Decompressed_file_10.txt");
        percent_compression("Compressed_file_10.txt","Decompressed_file_10.txt");

        printf("\nTestcase - 11\n");
        music_notes_converter("testcase11.txt");
        findAndCompressPalindromes("Music_Note_11.txt","Compressed_file_11.txt");
        Decompress("Compressed_file_11.txt");
        compare_files("Music_Note_11.txt","Decompressed_file_11.txt");
        percent_compression("Compressed_file_11.txt","Decompressed_file_11.txt");

        printf("\nTestcase - 12\n");
        music_notes_converter("testcase12.txt");
        findAndCompressPalindromes("Music_Note_12.txt","Compressed_file_12.txt");
        Decompress("Compressed_file_12.txt");
        compare_files("Music_Note_12.txt","Decompressed_file_12.txt");
        percent_compression("Compressed_file_12.txt","Decompressed_file_12.txt");

        printf("\nTestcase - 13\n");
        music_notes_converter("testcase13.txt");
        findAndCompressPalindromes("Music_Note_13.txt","Compressed_file_13.txt");
        Decompress("Compressed_file_13.txt");
        compare_files("Music_Note_13.txt","Decompressed_file_13.txt");
        percent_compression("Compressed_file_13.txt","Decompressed_file_13.txt");



	char user_input;
        char file_name[100]; // Buffer to store file name
        while (1) {  // Loop until 'c' is pressed
            printf("Press 'i' to take user input file, 'c' to continue..\n");
            printf("Your choice: ");
            scanf(" %c", &user_input);  // Note the space before %c to consume any newline
	    getchar();
            if (user_input == 'c') {
            break;  // Exit the loop
            } 
            else if (user_input == 'i') {
                printf("Enter file name: ");
                scanf("%s", file_name);
                //printf("File name entered: %s\n", file_name);
		printf("Compressing file..\n");
		//compress given file
		printf("Decompressing file..\n");
		//decompress

            } 
            else {
                printf("Invalid option. Please enter 'i' or 'c'.\n");
            }

            
    }*/
	//findAndCompressPalindromes("testcase1.txt","Compressed_file_1.txt");
     //   Decompress("Compressed_file_1.txt");
   //     compare_files("testcase1.txt","Decompressed_file_1.txt");
    //    percent_compression("Compressed_file_1.txt","Decompressed_file_1.txt");

	//music_notes_converter("testcase1.mp3");
	//findAndCompressPalindromes("Music_Note_2.txt","Compressed_1.txt");
	//Decompress("Compressed_1.txt");
	//compare_files("Music_Note_2.txt","Decompressed_file_3.txt");
	//percent_compression("Compressed_1.txt","Decompressed_file_1.txt");
	//music_notes_converter("testcase3.txt");
        //music_notes_converter("testcase4.txt");
	//Decompress("sample.txt");
	//percent_compression("filec.txt", "filed.txt");
        return 0;
}
