#include<stdlib.h>
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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define INITIAL_MAXN 1000

struct Node {
    int start, end;
    int length;
    int insertEdg[26];
    int suffixEdg;
};

struct Node *tree;
struct Node root1, root2;
int ptr;
char *s; // Pointer to dynamically allocate string
int currNode;
int maxNodes = INITIAL_MAXN;
int palindromeArray[INITIAL_MAXN][3]; // Use INITIAL_MAXN instead of PALINDROME_MAX
int palindromeCount = 0;

// Counting sort to sort palindromic substrings by length in descending order
void countingSortPalindromes(int palindromeArray[][3], int numPalindromes) {
    int maxLength = 0;

    // Find the maximum length in the palindromeArray
    for (int i = 0; i < numPalindromes; i++) {
        if (palindromeArray[i][2] > maxLength) {
            maxLength = palindromeArray[i][2];
        }
    }

    // Create count array
    int *count = (int *)calloc(maxLength + 1, sizeof(int));

    // Store the count of each length
    for (int i = 0; i < numPalindromes; i++) {
        count[palindromeArray[i][2]]++;
    }

    // Modify the count array for sorting in descending order
    for (int i = maxLength - 1; i >= 0; i--) {
        count[i] += count[i + 1];
    }

    // Output array to hold sorted elements
    int sortedPalindromes[INITIAL_MAXN][3];
    for (int i = 0; i < numPalindromes; i++) {
        int length = palindromeArray[i][2];
        sortedPalindromes[count[length] - 1][0] = palindromeArray[i][0];
        sortedPalindromes[count[length] - 1][1] = palindromeArray[i][1];
        sortedPalindromes[count[length] - 1][2] = palindromeArray[i][2];
        count[length]--;
    }

    // Copy sorted array back to palindromeArray
    for (int i = 0; i < numPalindromes; i++) {
        palindromeArray[i][0] = sortedPalindromes[i][0];
        palindromeArray[i][1] = sortedPalindromes[i][1];
        palindromeArray[i][2] = sortedPalindromes[i][2];
    }

    free(count);
}

// Function to insert a character at index idx
void insert(int idx) {
    int tmp = currNode;
    while (1) {
        int curLength = tree[tmp].length;
        if (idx - curLength >= 1 && s[idx] == s[idx - curLength - 1]) break;
        tmp = tree[tmp].suffixEdg;
    }

    if (tree[tmp].insertEdg[s[idx] - 'A'] != 0) {
        currNode = tree[tmp].insertEdg[s[idx] - 'A'];
        return;
    }

    if (ptr >= maxNodes - 1) {
        maxNodes *= 2;
        tree = realloc(tree, maxNodes * sizeof(struct Node));
        if (!tree) {
            perror("Failed to reallocate memory");
            exit(EXIT_FAILURE);
        }
    }

    ptr++;
    tree[tmp].insertEdg[s[idx] - 'A'] = ptr;
    tree[ptr].length = tree[tmp].length + 2;
    tree[ptr].end = idx;
    tree[ptr].start = idx - tree[ptr].length + 1;

    tmp = tree[tmp].suffixEdg;
    currNode = ptr;

    if (tree[currNode].length == 1) {
        tree[currNode].suffixEdg = 2;
        return;
    }

    while (1) {
        int curLength = tree[tmp].length;
        if (idx - curLength >= 1 && s[idx] == s[idx - curLength - 1]) break;
        tmp = tree[tmp].suffixEdg;
    }

    tree[currNode].suffixEdg = tree[tmp].insertEdg[s[idx] - 'A'];

    // Change this line to check for palindromes greater than 2
    if (tree[currNode].length > 2 && palindromeCount < INITIAL_MAXN) { 
        palindromeArray[palindromeCount][0] = tree[currNode].start;
        palindromeArray[palindromeCount][1] = tree[currNode].end;
        palindromeArray[palindromeCount][2] = tree[currNode].length;
        palindromeCount++;
    }
}

// Function to compress palindromes as per rules
void compressPalindrome(char str[], int length, int palindromeArray[][3], int numPalindromes) {
    int interval[INITIAL_MAXN] = {0}; // Use INITIAL_MAXN instead of MAX_LENGTH

    for (int i = 0; i < numPalindromes; i++) {
        int start = palindromeArray[i][0];
        int end = palindromeArray[i][1];
        int palindromeLength = palindromeArray[i][2];

        // Change the condition to compress palindromes greater than 2
        if (palindromeLength > 2 && interval[start] == 0 && interval[end] == 0) {
            if (palindromeLength % 2 == 0) {
                int mid1 = start + (palindromeLength / 2);
                int mid2 = mid1 + 1;
                str[mid1] = '.';
                str[mid2] = '.';

                for (int j = start; j < mid1; j++) str[j] = tolower(str[j]);
                for (int j = mid2 + 1; j <= end; j++) str[j] = '\0';
            } else {
                int mid = start + (palindromeLength + 1) / 2;
                for (int j = mid + 1; j <= end; j++) str[j] = '\0';
                str[mid] = '.';

                for (int j = start; j < mid; j++) str[j] = tolower(str[j]);
            }

            for (int j = start; j <= end; j++) interval[j] = 1;
        }
    }
}

// Function to write the compressed output to a file without spaces
void writeCompressedOutput(char str[], int length, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Error opening file for writing");
        return;
    }

    for (int i = 0; i < length; i++) {
        if (str[i] != '\0') {
            fputc(str[i], file);
        }
    }

    fclose(file);
}

// Function to find, sort, and compress palindromic substrings from a file
void findAndCompressPalindromes(const char *inputFile, const char *outputFile) {
    FILE *file = fopen(inputFile, "r");
    if (!file) {
        perror("Error opening file");
        return;
    }

    // Move to the end of the file to get the size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the string based on file size
    s = malloc(fileSize + 1); // +1 for null terminator
    if (!s) {
        perror("Failed to allocate memory for string");
        fclose(file);
        return;
    }

    if (!fgets(s, fileSize + 1, file)) {
        perror("Error reading from file");
        free(s);
        fclose(file);
        return;
    }
    fclose(file);

    s[strcspn(s, "\n")] = '\0'; // Remove newline character if present

    root1.length = -1;
    root1.suffixEdg = 1;
    root2.length = 0;
    root2.suffixEdg = 1;
    tree = malloc(maxNodes * sizeof(struct Node));
    if (!tree) {
        perror("Failed to allocate memory");
        free(s);
        exit(EXIT_FAILURE);
    }

    tree[1] = root1;
    tree[2] = root2;
    ptr = 2;
    currNode = 1;

    int l = strlen(s);
    for (int i = 0; i < l; i++) {
        insert(i);
    }

    countingSortPalindromes(palindromeArray, palindromeCount);

    compressPalindrome(s, l, palindromeArray, palindromeCount);
    writeCompressedOutput(s, l, outputFile);

    free(s);
    free(tree);
}

// Uncomment to test
/*int main() {
    findAndCompressPalindromes("input.txt", "compressed.txt");
    return 0;
}*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include"header.h"

#define INITIAL_SIZE 1000 // Initial size for dynamic allocation
#define FILENAME_SIZE 50  // Size for the filename buffer

// Function to generate a unique filename
void generate_unique_filename_2(char *filename, size_t size) {
    int count = 1;
    FILE *file;

    snprintf(filename, size, "Decompressed_file_%d.txt", count);
    file = fopen(filename, "r");

    while (file != NULL) {
        fclose(file);
        count++;
        snprintf(filename, size, "Decompressed_file_%d.txt", count);
        file = fopen(filename, "r");
    }
}

// Function to append the generated result to the result array
void append_result(char **result, const char *new_string, size_t *current_size) {
    if (strlen(*result) + strlen(new_string) + 1 > *current_size) {
        *current_size *= 2; // Double the size
        *result = realloc(*result, *current_size);
        if (*result == NULL) {
            perror("Failed to reallocate memory");
            exit(1);
        }
    }
    strcat(*result, new_string);
}

// Function to create palindromes based on the segment type
void create_palindrome(char *input, int is_full_palindrome, char *str) {
    int len = strlen(input);
    strcpy(str, input); // Copy the initial part

    if (is_full_palindrome) {
        for (int i = len - 1; i >= 0; i--) {
            str[len++] = str[i];
        }
    } else {
        for (int i = len - 2; i >= 0; i--) {
            str[len++] = str[i];
        }
    }
    str[len] = '\0'; // Null terminate the final string
}

// Function to process individual segments with uppercase handling
void process_input(char *input, char **result, size_t *current_size) {
    char str[100]; // Temporary string to hold the processed input
    char temp[50]; // Temporary buffer for the current segment
    int temp_index = 0;
    
    for (int i = 0; input[i] != '\0'; i++) {
        // If we find a dot, process the segment collected so far
        if (input[i] == '.') {
            // Check for double dot
            int is_full_palindrome = (input[i + 1] == '.');
            if (is_full_palindrome) i++; // Skip the second dot for double dot case

            temp[temp_index] = '\0'; // Null-terminate the segment in temp
            if (temp_index > 0) { // Process temp only if it's non-empty
                if (strpbrk(temp, "ABCDEFGHIJKLMNOPQRSTUVWXYZ") != NULL) {
                    append_result(result, temp, current_size); // Append as-is if it has uppercase
                } else {
                    create_palindrome(temp, is_full_palindrome, str); // Generate palindrome if lowercase
                    append_result(result, str, current_size);
                }
            }
            temp_index = 0; // Reset temp for the next segment
        } else if (isupper(input[i])) {
            // Append uppercase characters directly to result
            char uppercase_str[2] = {input[i], '\0'};
            append_result(result, uppercase_str, current_size);
        } else {
            // Collect lowercase characters in temp
            temp[temp_index++] = input[i];
        }
    }

    // Final check to process any remaining lowercase characters at the end
    temp[temp_index] = '\0'; // Null-terminate the remaining characters in temp
    if (temp_index > 0) {
        if (strpbrk(temp, "ABCDEFGHIJKLMNOPQRSTUVWXYZ") != NULL) {
            append_result(result, temp, current_size); // Append as-is if it has uppercase
        } else {
            create_palindrome(temp, 0, str); // Generate odd-length palindrome if lowercase
            append_result(result, str, current_size);
        }
    }
}
void toUpperCase(char *str){
    int i = 0;
    while(str[i] != '\0'){
        str[i] = toupper(str[i]);
        i++;
    }
}

// Function to process the file input and return the final result as a dynamically allocated string
char *process_file_input(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return NULL;
    }

    size_t current_size = INITIAL_SIZE; // Start with initial buffer size
    char *result = (char *)malloc(current_size * sizeof(char));
    if (result == NULL) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }
    result[0] = '\0'; // Initialize as an empty string

    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        line[strcspn(line, "\n")] = '\0'; // Remove newline if present
        process_input(line, &result, &current_size); // Process and append to result
    }

    fclose(file);
    toUpperCase(result);
    return result; // Return the dynamically allocated result
}

// New function compress that takes only the input filename
void Decompress(const char *input_filename) {
    // Process the file and get the concatenated result
    char *result = process_file_input(input_filename);
    if (result == NULL) {
        fprintf(stderr, "Failed to process input file.\n");
        return; // Exit if file processing failed
    }

    // Generate a unique filename for the output
    char output_filename[FILENAME_SIZE];
    generate_unique_filename_2(output_filename, FILENAME_SIZE);

    // Write the result to the output file
    FILE *output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        perror("Error creating output file");
        free(result);
        return;
    }
    fprintf(output_file, "%s\n", result);
    fclose(output_file);

    printf("Final result written to %s\n", output_filename);

    // Free the allocated memory
    free(result);
}
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

#include<stdio.h>
#include<stdlib.h>
#include"header.h"
#include<ctype.h>
int main(){
	int count = 1;
	printf("Running Test Cases....\n\n");

	printf("--------------------  Working on DNA files in .txt format  --------------------\n");

	printf("Testcase - 1\n");
	findAndCompressPalindromes("testcase1.txt","Compressed_file_1.txt");
        Decompress("Compressed_file_1.txt");
        compare_files("testcase1.txt","Decompressed_file_1.txt");
        percent_compression("Compressed_file_1.txt","Decompressed_file_1.txt");
	
	printf("Testcase - 2\n");
	findAndCompressPalindromes("testcase2.txt","Compressed_file_2.txt");
        Decompress("Compressed_file_2.txt");
        compare_files("testcase2.txt","Decompressed_file_2.txt");
        percent_compression("Compressed_file_2.txt","Decompressed_file_2.txt");
	
	printf("Testcase - 3\n");
	findAndCompressPalindromes("testcase3.txt","Compressed_file_3.txt");
        Decompress("Compressed_file_3.txt");
        compare_files("testcase3.txt","Decompressed_file_3.txt");
        
	percent_compression("Compressed_file_3.txt","Decompressed_file_3.txt");
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
	findAndCompressPalindromes("testcase1.txt","Compressed_file_1.txt");
        Decompress("Compressed_file_1.txt");
        compare_files("testcase1.txt","Decompressed_file_1.txt");
        percent_compression("Compressed_file_1.txt","Decompressed_file_1.txt");

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
